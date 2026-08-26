# btxluxminer

**GPU miner for [BTX](https://github.com/btxchain/btx) — MatMul v4 / ENC_RC.**

A maintained fork of [`vanities/matador-miner`](https://github.com/vanities/matador-miner)
(MIT, © 2026 AM2 LLC), created after upstream stopped being maintained.

---

## Why this fork exists

Upstream is MIT-licensed and publicly readable, but **as published it cannot be built
by anyone other than its original author.** A clean clone hits three separate blockers:

1. The build image `matador-build:pathb-deps` was never pushed to any public registry —
   `docker build` fails with `pull access denied, repository does not exist`.
2. `clean-stack/core/CMakeLists.txt` omits `libbtx_matmul_backend.a` from its link list,
   which is the only archive defining the `matmul_v4::cuda::*` symbols the miner needs.
3. The `-Dconsteval=constexpr` compatibility flag breaks CUDA's CCCL headers on every
   publicly available CUDA image.

This fork fixes all three. The build is reproducible from public sources, and every
change is documented in [BUILDING.md](BUILDING.md).

**Nothing here changes the proof-of-work maths.** The byte-exact gate (`rc_probe`
printing `5b1bff3c…`) is unchanged and must pass before any release ships.

---

## Drop-in replacement

btxluxminer keeps matador's runtime interface. If you already run matador, swap the
binary and keep your existing flags, environment variables and config:

```bash
# before
matador-miner --mode=solo --backend=cuda --payoutaddress=btx1z...

# after — identical
btxluxminer --mode=solo --backend=cuda --payoutaddress=btx1z...
```

`MATADOR_*` environment variables still work. `matador.json` is still read.

---

## Quick start — solo mining

Point it at your own synced `btxd`:

```bash
btxluxminer \
  --mode=solo \
  --backend=cuda \
  --solver-threads=1 \
  --payoutaddress=btx1z...YOUR_ADDRESS \
  --rpcuser=USER --rpcpassword=PASS \
  --rpcconnect=127.0.0.1 --rpcport=19334
```

Healthy output looks like:

```
[stats-all] gpus=4/4 ep/s=5.999 acc=0 rej=0 | per-gpu ep/s: 1.500 1.500 1.500 1.500
[gbt] template height=... prevhash=... bits=... rc-active=1
```

- **`ep/s`** is episodes per second — one full ENC_RC episode per nonce. Fractional is
  normal (~1.5/s on a 5090).
- **`rc-active=0`** means the RC height never latched. That is a configuration fault,
  not a slow miner.
- **`acc`** only ticks when you *win a block*. Solo is lumpy.

Multi-GPU is automatic — it fans out to every visible device, partitioning work by
coinbase extranonce and a randomised 64-bit nonce base, so one payout address across
your own rigs is safe.

---

## Hardware

| | |
|---|---|
| **Mining** | NVIDIA Turing and newer. Built for `sm_80;86;89;90;120`. An RTX 3090 (sm_86) mines; the workload's matmul is INT8. |
| **Driver** | **580+** required. The miner links CUDA 13.0; on older drivers it connects, takes jobs, and never engages the GPU — which looks exactly like unsupported hardware and isn't. |
| **Not supported** | Pre-Turing. ENC_RC is tensor-core-bound. |

> Validating BTX nodes are a separate question with stricter requirements — that is
> `btxd`'s ExactReplay path, not this miner.

---

## Building

See **[BUILDING.md](BUILDING.md)**. Summary:

- Needs a real VM or bare metal, **not a container** — the build runs Docker.
- Uses `nvidia/cuda:13.3.0-devel-ubuntu24.04`, which carries the pinned **nvcc V13.3.33**.
  Do not substitute 13.3.1 (V13.3.73) — it breaks the build.
- CUTLASS v4.6.1 is mandatory. Without it the binary balloons from ~95 MB to ~598 MB.
- Two gates must pass: byte-exact digest, and an A-B performance comparison with clocks
  locked.

---

## Keeping current

BTX ships consensus changes with flag-day activation heights. **A miner that lags a
flag day produces invalid blocks** — you burn power on a chain nobody accepts.

This fork tracks BTX releases and rebuilds against each stock tag. If you are running
it, watch the release page here as well as BTX's.

Current: built against BTX **v0.33.4.2**.

---

## Credits

Original work by [vanities](https://github.com/vanities) / **AM2 LLC**, MIT licensed.
All of the hard engineering — the ENC_RC solver, the CUDA kernels, the multi-GPU
fan-out, the byte-exact gating discipline — is theirs. This fork exists to keep that
work usable and current, not to claim it.

The MIT licence and copyright notice are retained in [LICENSE](LICENSE), as required.

---

## Licence

MIT. See [LICENSE](LICENSE).

Provided as-is with no warranty. Mining is a lottery; nothing here promises returns.
