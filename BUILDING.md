# Building matador-miner (fork)

**Status: verified working 2026-08-26.** Byte-exact gate passed, digest `5b1bff3c`.

This document exists because **the upstream repository cannot be built by anyone
other than its original author.** Three separate blockers stop a clean clone from
producing a binary. All three are documented and fixed below.

If you only want the short version, skip to [Quick build](#quick-build).

---

## Why upstream does not build

### 1. The build image was never published

`clean-stack/build-clean-rel.sh` runs the build inside `matador-build:pathb-deps-cm4`,
and `clean-stack/Dockerfile.pathb-deps-cm4` builds that image `FROM` two others:

```dockerfile
FROM matador-build:deps-2204-cuda1321-blas AS cm
FROM matador-build:pathb-deps
```

Neither exists on any public registry:

```
ERROR: pull access denied, repository does not exist or may require authorization
```

They were local images on the author's machine. The checked-in Dockerfile only ever
layered CMake onto a base nobody else has.

**Fix:** reconstruct the base from NVIDIA's public images. The pinned toolchain is
CUDA **13.3.33**, and that maps to a specific published tag:

| Docker tag | nvcc / glibc |
|---|---|
| `nvidia/cuda:13.3.0-devel-ubuntu22.04` | **V13.3.33 / glibc 2.35** ← the release image |
| `nvidia/cuda:13.3.0-devel-ubuntu24.04` | V13.3.33 / glibc 2.39 — same nvcc, too new for vast containers |
| `nvidia/cuda:13.3.1-devel-ubuntu22.04` | V13.3.73 — too new, breaks the build |

The patch level matters. `apt install cuda-toolkit-13-3` gives you 13.3.**73**, which
is *not* what the build expects. The Ubuntu series matters too: a 24.04 binary records
`GLIBC_2.38` / `GLIBC_2.39` and dies on jammy/vast containers with
`version 'GLIBC_2.38' not found`. Release binaries are built on **22.04**.

### 2. matador's link list omits the archive it needs

`clean-stack/core/CMakeLists.txt` links a fixed list of twelve BTX archives. It does
**not** include `libbtx_matmul_backend.a` — which is the only thing that defines every
`matmul_v4::cuda::*` and `matmul_v4::ascend::*` symbol the miner references.

```
libbtx_matmul_backend.a   9.8 MB — defines ComputeDigestAccel + 23 ascend symbols
matador link list          mentions it: 0 times
libmatador_core.a          defines ComputeDigestAccel: 0
```

Result: ~40 undefined references at link time. See [Patch 1](#patch-1-link-the-backend-archive).

### 3. cuBLASLt is needed but deliberately unlinked, and link order defeats the obvious fix

matador uses CUTLASS for its own GEMM and intentionally does not link cuBLASLt
(a static link balloons the binary from ~95 MB to ~598 MB, and the release path
refuses rather than falling back).

But `libbtx_matmul_backend.a` — which Patch 1 adds — calls cuBLASLt internally. That
produces 136 undefined `cublasLt*` references.

Adding `-lcublasLt` via `CMAKE_EXE_LINKER_FLAGS` **does not work**: CMake places those
flags *before* the archives, and GNU ld resolves left to right, so the symbols are
already unresolved by the time the library appears. Use `CMAKE_CXX_STANDARD_LIBRARIES`,
which is appended last.

### Also: drop `-Dconsteval=constexpr`

`build-clean-rel.sh` passes `-DCMAKE_CUDA_FLAGS="-Dconsteval=constexpr"`. That macro
redefines a C++ keyword and breaks CUDA's own CCCL headers — **even at the pinned
13.3.33**:

```
cccl/cuda/__cmath/ceil_div.h(76): internal error: assertion failed at "statements.c"
52 errors and 1 catastrophic error detected
```

The author's private base image must have shipped different CCCL headers. With
NVIDIA's public image the flag must be omitted. The golden gate confirms this is safe.

---

## Prerequisites

A machine with:

- **A real VM or bare metal — not a container.** The build runs Docker. A vast.ai
  *container* instance cannot do this (`no daemon`, `!cap_sys_admin`); a vast.ai
  **VM template** can. Verify with `systemd-detect-virt` (want `kvm`) and
  `docker info`.
- An NVIDIA GPU for the GPU probe. Not needed to compile; needed to validate.
- ~40 GB free disk (the CUDA images are ~7 GB each).
- More cores is better. BTX takes ~3 min on 192 threads, ~10 min on 15.

---

## Quick build

```bash
# 1. Sources
mkdir -p ~/git && cd ~/git
git clone --depth 1 https://github.com/baileyshero/btxluxminer.git
git clone --depth 1 --branch v0.34 https://github.com/btxchain/btx.git btx-034
git clone --depth 1 --branch v4.6.1 https://github.com/NVIDIA/cutlass.git cutlass461

# 2. Release image (Ubuntu 22.04 / glibc 2.35). See Dockerfile.jammy below.
cd ~/git/btxluxminer && docker build -t btxlux-build:jammy -f Dockerfile.jammy .

# 3. Stock BTX 0.34, inside the image so the toolchain matches
docker run --rm -v ~/git/btx-034:/btxsrc -w /btxsrc btxlux-build:jammy bash -lc '
  cmake -B build -S . -DCMAKE_BUILD_TYPE=Release \
    -DBTX_ENABLE_CUDA_EXPERIMENTAL=ON -DBTX_CUDA_ARCHITECTURES="80;86;89;90;120" \
    -DBUILD_GUI=OFF -DBUILD_TESTS=OFF -DBUILD_BENCH=OFF -DBUILD_FUZZ_BINARY=OFF
  cmake --build build -j $(nproc)'

# 4. miner
cd ~/git/btxluxminer/clean-stack
docker run --rm -e ARCH="80;86;89;90;120" -e VER=v0.9.31-btxlux -e JOBS=$(nproc) \
  -v $PWD:/src -v ~/git/btx-034/build:/btx -v ~/git/cutlass461:/cutlass:ro \
  -w /src btxlux-build:jammy bash -lc '
    L=/usr/local/cuda/targets/x86_64-linux/lib
    cmake -B build-jammy -S core \
      -DMATADOR_ENABLE_CUDA=ON -DMATADOR_CUDA_ARCH="$ARCH" \
      -DMATADOR_MINER_VERSION="$VER" -DCMAKE_BUILD_TYPE=Release \
      -DBTX_ARCHIVE_DIR=/btx -DMATADOR_CUTLASS_DIR=/cutlass \
      -DCMAKE_CXX_FLAGS="-fopenmp" \
      -DCMAKE_CXX_STANDARD_LIBRARIES="-L$L -lcublasLt -lcublas -lcudart -lgomp"
    cmake --build build-jammy --target rc_probe btxluxminer --parallel $JOBS
    ./build-jammy/rc_probe
    objdump -T ./build-jammy/btxluxminer | grep -oE "GLIBC_[0-9.]+" | sort -u'
```

Note what is **absent** from step 4 versus upstream: no `-Dconsteval=constexpr`.

---

## Dockerfile.jammy (release)

Ubuntu 22.04 so the binary links glibc 2.35 and runs on vast containers.

```dockerfile
FROM nvidia/cuda:13.3.0-devel-ubuntu22.04
# 13.3.0 == nvcc V13.3.33, the pinned toolchain. Do NOT use 13.3.1 (V13.3.73).

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential git pkg-config ca-certificates curl \
      libopenblas-dev liblapack-dev libcurl4-openssl-dev libssl-dev \
      zlib1g-dev libbz2-dev \
      libevent-dev libboost-dev libsqlite3-dev libzmq3-dev \
      python3 python3-pip xz-utils \
 && rm -rf /var/lib/apt/lists/*

# CMake 4.x: 3.x cannot express the CUDA20 dialect with nvcc 13.3
# ("CMake does not know the compile flags to use to enable CUDA20")
RUN curl -fsSL -o /tmp/cmake.tar.gz \
      https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-linux-x86_64.tar.gz \
 && tar xzf /tmp/cmake.tar.gz -C /opt \
 && mv /opt/cmake-4.3.2-linux-x86_64 /opt/cmake-4.3.2 \
 && ln -sf /opt/cmake-4.3.2/bin/cmake /usr/local/bin/cmake \
 && ln -sf /opt/cmake-4.3.2/bin/ctest /usr/local/bin/ctest \
 && ln -sf /opt/cmake-4.3.2/bin/cpack /usr/local/bin/cpack \
 && rm /tmp/cmake.tar.gz && cmake --version

WORKDIR /src
```

Verify after building:

```
nvcc  V13.3.33
cmake 4.3.2
gcc   11          # jammy; noble's gcc 13 is fine for a local 24.04 build
ldd   2.35
libcublasLt_static.a present
```

`Dockerfile.fork` is the same recipe on Ubuntu 24.04. Same nvcc. Do not ship those
binaries as the Linux release — they will not load on glibc 2.35 hosts.

---

## Patch 1: link the backend archive

`clean-stack/core/CMakeLists.txt` — add `libbtx_matmul_backend.a` ahead of
`libbitcoin_common.a` in **both** archive lists (`rc_attest` and `BTX_ARCHIVES`):

```diff
@@ target_link_libraries(rc_attest PRIVATE
     -Wl,--start-group
+    ${BTX_ARCHIVE_DIR}/lib/libbtx_matmul_backend.a
     ${BTX_ARCHIVE_DIR}/lib/libbitcoin_common.a

@@ set(BTX_ARCHIVES
+      ${BTX_ARCHIVE_DIR}/lib/libbtx_matmul_backend.a
       ${BTX_ARCHIVE_DIR}/lib/libbitcoin_common.a
```

Order matters — it must precede `libbitcoin_common.a`, which is what references it.

---

## The two gates

### Gate 1 — byte-exact (proves the maths)

```
$ ./build-rel/rc_probe
sigma  = 86c171d7ee6152a3a2a592a5c400adb9a680a06f3247b55f1e0935e129282fe2
digest = 5b1bff3c835b1c8e7816a2cccb181eb2fc30a99d97a971d73108c52a8238acd4
EXPECT = 5b1bff3c835b1c8e7816a2cccb181eb2fc30a99d97a971d73108c52a8238acd4
=> ENC_RC episode BYTE-EXACT (5b1bff3c)
```

If the digest does not match, **do not ship** — the proof-of-work maths has drifted.

On a CUDA build also run `rc_gpu_accel_probe`, which must report
`cpu==golden 1, gpu==golden 1, gpu==cpu 1`. The container needs `--gpus all`.
The CPU oracle alone cannot catch a drifted GPU backend.

> Any doc still quoting the v3 golden `1dad86f1` is stale.

### Gate 2 — A-B performance (non-negotiable)

Byte-exact does not mean equally fast. A byte-exact clean-stack build once ran 28%
slower than its predecessor. Always A-B against the previous binary in the **same GPU
state**, with clocks locked:

```bash
nvidia-smi -lgc 0,2600     # unlocked boost spread (~24ms) exceeds most lever effects
# then A/B/A on ep/s from the [stats] line, plus board power
```

`rc-active=0` means the RC height never latched — a configuration fault, not a slow
build.

---

## Release checklist

- [ ] `ARCH="80;86;89;90;120"` — all five. A single-arch build is for testing only.
- [ ] Gate 1 passes: digest `5b1bff3c`
- [ ] Gate 2 passes: no perf regression vs previous release, clocks locked
- [ ] `rc_gpu_accel_probe` green on real hardware
- [ ] Binary is ~95 MB. **~598 MB means CUTLASS was missed and cuBLASLt got statically
      linked** — the release path is supposed to refuse, so investigate rather than ship.
- [ ] Rebuilt against the current stock BTX tag
- [ ] `objdump -T` glibc symbols cap at `GLIBC_2.35` (no 2.36+)
- [ ] `sha256sum` published alongside the binary

### Per-release maintenance

Most BTX releases change consensus and networking, which matador inherits by rebuilding
against stock BTX. That loop is mechanical: pull the new tag → rebuild BTX → rebuild
matador → run both gates → publish.

Epoch transitions are different. If BTX moves Profile 1 → Profile 2, the golden digest
itself changes and the kernels may need real work.

**A miner that lags a consensus flag day produces invalid blocks.** Anyone running your
binary through a missed flag day mines a dead chain. Track BTX releases.

---

## Known deviations from upstream

| Upstream | Here | Why |
|---|---|---|
| `matador-build:pathb-deps` base | `nvidia/cuda:13.3.0-devel-ubuntu22.04` | upstream base was never published; jammy keeps glibc 2.35 |
| `-Dconsteval=constexpr` | omitted | breaks CCCL headers on the public image |
| 12 BTX archives | 13 (adds `libbtx_matmul_backend.a`) | nothing else defines its symbols |
| cuBLASLt not linked | linked dynamically, appended last | BTX's backend calls it; link order matters |
| — | `-fopenmp` | `GOMP_*` otherwise undefined |

All five are required. None changes the PoW maths — Gate 1 confirms it.

---

## Licence

MIT, Copyright (c) 2026 AM2 LLC. The MIT notice must be retained in this fork and in
anything derived from it. This fork exists because upstream stopped being maintained
and, as published, cannot be built.
