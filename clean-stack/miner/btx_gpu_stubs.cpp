// CPU fallbacks for node GPU row-leaf hooks pulled in by libbitcoin_common.
// The miner's ENC_RC path is CUTLASS inside matador_core; we do not link
// libbtx_matmul_backend.a (that archive is cuBLASLt and blows the HiveOS zip).
// Matching btx src/cuda/matmul_v4_rc_rowleaf_gpu_stub.cpp: Available()==0
// makes the node code take the CPU row-leaf path.

#include <cstdint>

extern "C" int BtxGpuRowLeafAvailable(void) { return 0; }
extern "C" int BtxGpuRowLeafSetConstants(const uint64_t*, const uint64_t*, const uint64_t*) { return -1; }
extern "C" int BtxGpuRowLeafBegin(uint32_t, void**) { return -1; }
extern "C" int BtxGpuRowLeafBeginTyped(uint32_t, const uint64_t[4], void**) { return -1; }
extern "C" int BtxGpuRowLeafAbsorb(void*, const uint64_t*, uint32_t, uint64_t) { return -1; }
extern "C" int BtxGpuRowLeafFinalize(void*, uint64_t, uint64_t*) { return -1; }
extern "C" void BtxGpuRowLeafRelease(void*) {}
