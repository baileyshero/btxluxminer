#include <cstdint>
#include <string>
#include <vector>
#include "uint256.h"
#include "primitives/block.h"

namespace matmul { namespace v4 { namespace lt {
struct DigestOnlyResultLT { unsigned char _[256]; };
struct MxLaneProvenance { unsigned char _[256]; };
struct ExactGemmBackend { unsigned char _[64]; };
}}}
namespace btx { namespace cuda {
struct ComputeCompressedWordsLowRankBatch { unsigned char _[256]; };
struct ComputeCompressedWordsLowRankBatchMultiDevice { unsigned char _[256]; };
struct ComputeCompressedWordsLowRankDeviceBatch { unsigned char _[256]; };
struct ComputeCompressedWordsLowRankDeviceBatchMultiDevice { unsigned char _[256]; };
struct ComputeCompressedWordsLowRankVariableBaseDeviceBatchMultiDevice { unsigned char _[256]; };
struct ComputeProductDigestsLowRankVariableBaseDeviceBatchMultiDevice { unsigned char _[256]; };
struct ExpandCudaBatchSizeForSelectedDevices { unsigned char _[256]; };
struct GenerateMatMulInputsGPU { unsigned char _[256]; };
struct GenerateMatMulInputsGPUDevice { unsigned char _[256]; };
struct GenerateMatMulInputsGPUDeviceBatch { unsigned char _[256]; };
struct MatMulInputGenerationDeviceBatchRequest { unsigned char _[256]; };
struct MatMulInputGenerationRequest { unsigned char _[256]; };
struct MatMulLowRankCompressedWordsBatchRequest { unsigned char _[256]; };
struct MatMulLowRankCompressedWordsDeviceBatchRequest { unsigned char _[256]; };
struct MatMulLowRankVariableBaseDeviceBatchRequest { unsigned char _[256]; };
struct MatMulLowRankVariableBaseProductDigestDeviceBatchRequest { unsigned char _[256]; };
struct MatMulNonceSeedPreHashScanRequest { unsigned char _[256]; };
struct ProbeCudaRuntime { unsigned char _[256]; };
struct ProbeCudaTopology { unsigned char _[256]; };
struct ProbeMatMulDigestAcceleration { unsigned char _[256]; };
struct ScanMatMulNonceSeedPreHashGPU { unsigned char _[256]; };
enum MatMulCompressedWordsMode { kMode0 = 0 };
} }
namespace btx { namespace metal {
struct ComputeCanonicalTranscriptDigest { unsigned char _[256]; };
struct ComputeCanonicalTranscriptDigestVariableBaseBatch { unsigned char _[256]; };
struct GenerateMatMulInputsGPU { unsigned char _[256]; };
struct MatMulBaseMatricesRequest { unsigned char _[256]; };
struct MatMulDigestBatchRequest { unsigned char _[256]; };
struct MatMulDigestBatchSubmission { unsigned char _[256]; };
struct MatMulDigestRequest { unsigned char _[256]; };
struct MatMulDigestSubmission { unsigned char _[256]; };
struct MatMulInputGenerationRequest { unsigned char _[256]; };
struct MatMulNonceSeedPreHashScanRequest { unsigned char _[256]; };
struct MatMulVariableBaseDigestBatchRequest { unsigned char _[256]; };
struct ProbeMatMulDeviceInfo { unsigned char _[256]; };
struct ScanMatMulNonceSeedPreHashGPU { unsigned char _[256]; };
struct SubmitCanonicalTranscriptDigest { unsigned char _[256]; };
struct SubmitCanonicalTranscriptDigestBatch { unsigned char _[256]; };
struct UploadBaseMatrices { unsigned char _[256]; };
struct WaitForCanonicalTranscriptDigestBatchSubmission { unsigned char _[256]; };
struct WaitForCanonicalTranscriptDigestSubmission { unsigned char _[256]; };
enum MatMulCompressedWordsMode { kMode0 = 0 };
} }
namespace matmul_v4 { namespace ascend {
struct LtAscendDigestProvenance { unsigned char _[256]; };
} }
namespace matmul_v4 { namespace cuda {
struct LtCudaBatchProvenance { unsigned char _[256]; };
enum MatMulCompressedWordsMode { kMode0 = 0 };
} }
namespace matmul_v4 { namespace hip {
struct LtHipBatchProvenance { unsigned char _[256]; };
} }
extern "C" {
int BtxGpuRowLeafAvailable(void) { return 0; }
int BtxGpuRowLeafSetConstants(const uint64_t*, const uint64_t*, const uint64_t*) { return -1; }
int BtxGpuRowLeafBegin(uint32_t, void**) { return -1; }
int BtxGpuRowLeafBeginTyped(uint32_t, const uint64_t[4], void**) { return -1; }
int BtxGpuRowLeafAbsorb(void*, const uint64_t*, uint32_t, uint64_t) { return -1; }
int BtxGpuRowLeafFinalize(void*, uint64_t, uint64_t*) { return -1; }
void BtxGpuRowLeafRelease(void*) {}
int BtxGpuFp3LdeAvailable(void) { return 0; }
int BtxGpuFp3LdeBegin(uint32_t, const uint64_t*, uint32_t, const uint64_t*, uint32_t, uint64_t, void** ctx_out) {
    if (ctx_out) *ctx_out = nullptr; return -2;
}
int BtxGpuFp3LdeForward(void*, const uint64_t*, uint32_t, uint64_t*) { return -2; }
int BtxGpuFp3LdeInverse(void*, const uint64_t*, uint64_t*) { return -2; }
void BtxGpuFp3LdeRelease(void*) {}
}

namespace btx { namespace cuda {
int ComputeCompressedWordsLowRankBatch(btx::cuda::MatMulLowRankCompressedWordsBatchRequest const&, btx::cuda::MatMulCompressedWordsMode) { return 0; }
int ComputeCompressedWordsLowRankBatchMultiDevice(btx::cuda::MatMulLowRankCompressedWordsBatchRequest const&, btx::cuda::MatMulCompressedWordsMode) { return 0; }
int ComputeCompressedWordsLowRankDeviceBatch(btx::cuda::MatMulLowRankCompressedWordsDeviceBatchRequest const&, btx::cuda::MatMulCompressedWordsMode) { return 0; }
int ComputeCompressedWordsLowRankDeviceBatchMultiDevice(btx::cuda::MatMulLowRankCompressedWordsDeviceBatchRequest const&, btx::cuda::MatMulCompressedWordsMode) { return 0; }
int ComputeCompressedWordsLowRankVariableBaseDeviceBatchMultiDevice(btx::cuda::MatMulLowRankVariableBaseDeviceBatchRequest const&, btx::cuda::MatMulCompressedWordsMode) { return 0; }
int ComputeProductDigestsLowRankVariableBaseDeviceBatchMultiDevice(btx::cuda::MatMulLowRankVariableBaseProductDigestDeviceBatchRequest const&) { return 0; }
int ExpandCudaBatchSizeForSelectedDevices(unsigned int, unsigned long) { return 0; }
int GenerateMatMulInputsGPU(btx::cuda::MatMulInputGenerationRequest const&) { return 0; }
int GenerateMatMulInputsGPUDevice(btx::cuda::MatMulInputGenerationRequest const&) { return 0; }
int GenerateMatMulInputsGPUDeviceBatch(btx::cuda::MatMulInputGenerationDeviceBatchRequest const&) { return 0; }
int ProbeCudaRuntime() { return 0; }
int ProbeCudaTopology() { return 0; }
int ProbeMatMulDigestAcceleration() { return 0; }
int ScanMatMulNonceSeedPreHashGPU(btx::cuda::MatMulNonceSeedPreHashScanRequest const&) { return 0; }
} }

namespace btx { namespace metal {
int ComputeCanonicalTranscriptDigest(btx::metal::MatMulDigestRequest const&) { return 0; }
int ComputeCanonicalTranscriptDigestVariableBaseBatch(btx::metal::MatMulVariableBaseDigestBatchRequest const&) { return 0; }
int GenerateMatMulInputsGPU(btx::metal::MatMulInputGenerationRequest const&) { return 0; }
int ProbeMatMulDeviceInfo() { return 0; }
int ScanMatMulNonceSeedPreHashGPU(btx::metal::MatMulNonceSeedPreHashScanRequest const&) { return 0; }
int SubmitCanonicalTranscriptDigest(btx::metal::MatMulDigestRequest const&) { return 0; }
int SubmitCanonicalTranscriptDigestBatch(btx::metal::MatMulDigestBatchRequest const&) { return 0; }
int UploadBaseMatrices(btx::metal::MatMulBaseMatricesRequest const&) { return 0; }
int WaitForCanonicalTranscriptDigestBatchSubmission(btx::metal::MatMulDigestBatchSubmission&&) { return 0; }
int WaitForCanonicalTranscriptDigestSubmission(btx::metal::MatMulDigestSubmission&&) { return 0; }
} }

namespace matmul_v4 { namespace ascend {
int ComputeDigestAccel(CBlockHeader const&, unsigned int, unsigned int, uint256&, std::vector<unsigned char, std::allocator<unsigned char> >&) { return 0; }
int ComputeDigestsBMX4CAccel(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, unsigned int, std::vector<uint256, std::allocator<uint256> >&, std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >&) { return 0; }
int ComputeDigestsBatchedAccel(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, unsigned int, std::vector<uint256, std::allocator<uint256> >&, std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >&) { return 0; }
int ComputeDigestsOnlyLTAscend(CBlockHeader const&, unsigned int, unsigned long const*, unsigned long, std::vector<matmul::v4::lt::DigestOnlyResultLT, std::allocator<matmul::v4::lt::DigestOnlyResultLT> >&, matmul_v4::ascend::LtAscendDigestProvenance*) { return 0; }
int TryLaunchLtCubeGemmS32S8(std::vector<int, std::allocator<int> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&) { return 0; }
int TryLaunchLtCubeGemmS8S8(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&) { return 0; }
int TryLaunchLtCubeMxProjectRight(std::vector<signed char, std::allocator<signed char> > const&, std::vector<unsigned char, std::allocator<unsigned char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&, matmul::v4::lt::MxLaneProvenance*) { return 0; }
} }

namespace matmul_v4 { namespace cuda {
int ComputeDigestAccel(CBlockHeader const&, unsigned int, unsigned int, uint256&, std::vector<unsigned char, std::allocator<unsigned char> >&) { return 0; }
int ComputeDigestsBMX4CAccel(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, unsigned int, std::vector<uint256, std::allocator<uint256> >&, std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >&) { return 0; }
int ComputeDigestsBatchedAccel(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, unsigned int, std::vector<uint256, std::allocator<uint256> >&, std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >&) { return 0; }
int ComputeDigestsOnlyLTCuda(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, std::vector<matmul::v4::lt::DigestOnlyResultLT, std::allocator<matmul::v4::lt::DigestOnlyResultLT> >&, matmul_v4::cuda::LtCudaBatchProvenance*) { return 0; }
int IsLtImmaGemmAvailable() { return 0; }
int IsRcEpisodeCudaCompiled() { return 0; }
int IsRcExactReplayCudaAvailable() { return 0; }
int IsRcOzakiCudaCompiled() { return 0; }
int IsRcOzakiCudaExactPanelsQualified() { return 0; }
int IsRcOzakiCudaMxfp4Qualified() { return 0; }
int LaunchGemmS32S8(std::vector<int, std::allocator<int> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&) { return 0; }
int LaunchGemmS8S8(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&) { return 0; }
int LaunchProjectedRightMx(std::vector<signed char, std::allocator<signed char> > const&, std::vector<unsigned char, std::allocator<unsigned char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&, matmul::v4::lt::MxLaneProvenance*) { return 0; }
int LaunchRcExactReplayFusedFfn(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, uint256 const&, uint256 const&, unsigned int, unsigned int, unsigned int, unsigned int, std::vector<signed char, std::allocator<signed char> >&) { return 0; }
int LaunchRcExactReplayFusedFfnChain(std::vector<signed char, std::allocator<signed char> > const&, std::vector<std::vector<signed char, std::allocator<signed char> >, std::allocator<std::vector<signed char, std::allocator<signed char> > > > const&, std::vector<std::vector<signed char, std::allocator<signed char> >, std::allocator<std::vector<signed char, std::allocator<signed char> > > > const&, std::vector<uint256, std::allocator<uint256> > const&, std::vector<uint256, std::allocator<uint256> > const&, unsigned int, unsigned int, unsigned int, std::vector<std::vector<signed char, std::allocator<signed char> >, std::allocator<std::vector<signed char, std::allocator<signed char> > > >&) { return 0; }
int LaunchRcExactReplayFusedFfnChainSeeded(std::vector<signed char, std::allocator<signed char> > const&, std::vector<uint256, std::allocator<uint256> > const&, std::vector<uint256, std::allocator<uint256> > const&, std::vector<uint256, std::allocator<uint256> > const&, std::vector<uint256, std::allocator<uint256> > const&, unsigned int, unsigned int, unsigned int, std::vector<std::vector<signed char, std::allocator<signed char> >, std::allocator<std::vector<signed char, std::allocator<signed char> > > >&) { return 0; }
int LaunchRcExactReplayPhase1(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, uint256 const&, uint256 const&, unsigned int, unsigned int, unsigned int, std::vector<signed char, std::allocator<signed char> >&) { return 0; }
int LaunchRcExactReplayPhase1Seeded(uint256 const&, uint256 const&, uint256 const&, uint256 const&, uint256 const&, unsigned int, unsigned int, unsigned int, std::vector<signed char, std::allocator<signed char> >&) { return 0; }
std::string RcEpisodeCudaArchKey() { return {}; }
std::string RcOzakiCudaMxfp4ArchKey() { return {}; }
std::string RcOzakiCudaMxfp4Backend() { return {}; }
std::string RcOzakiCudaMxfp4Deficit() { return {}; }
int RcOzakiCudaMxfp4SelectedBackend() { return 0; }
int RcOzakiMxfp4Sm120aKernelLinked() { return 0; }
void ResetRcOzakiCudaQualForTest() {}
void SelfQualifyRcOzakiCudaExactPanelsOnce() {}
void SelfQualifyRcOzakiCudaMxfp4Once() {}
int TryLaunchRcOzakiExactPanelsGemmS8S8Int64(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<long, std::allocator<long> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >*) { return 0; }
int TryLaunchRcOzakiMxfp4GemmS8S8Int64(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<long, std::allocator<long> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >*) { return 0; }
} }

namespace matmul_v4 { namespace hip {
int ComputeDigestAccel(CBlockHeader const&, unsigned int, unsigned int, uint256&, std::vector<unsigned char, std::allocator<unsigned char> >&) { return 0; }
int ComputeDigestsBMX4CAccel(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, unsigned int, std::vector<uint256, std::allocator<uint256> >&, std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >&) { return 0; }
int ComputeDigestsBatchedAccel(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, unsigned int, std::vector<uint256, std::allocator<uint256> >&, std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >&) { return 0; }
int ComputeDigestsOnlyLTHip(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, std::vector<matmul::v4::lt::DigestOnlyResultLT, std::allocator<matmul::v4::lt::DigestOnlyResultLT> >&, matmul_v4::hip::LtHipBatchProvenance*) { return 0; }
int IsRcOzakiHipCompiled() { return 0; }
int IsRcOzakiHipExactPanelsQualified() { return 0; }
int IsRcOzakiHipMxfp4Qualified() { return 0; }
int LaunchGemmS32S8(std::vector<int, std::allocator<int> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&) { return 0; }
int LaunchGemmS8S8(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&) { return 0; }
int LaunchProjectedRightMx(std::vector<signed char, std::allocator<signed char> > const&, std::vector<unsigned char, std::allocator<unsigned char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&, matmul::v4::lt::MxLaneProvenance*) { return 0; }
std::string RcOzakiHipMxfp4ArchKey() { return {}; }
std::string RcOzakiHipMxfp4Backend() { return {}; }
std::string RcOzakiHipMxfp4Deficit() { return {}; }
void ResetRcOzakiHipQualForTest() {}
void SelfQualifyRcOzakiHipExactPanelsOnce() {}
void SelfQualifyRcOzakiHipMxfp4Once() {}
int TryLaunchRcOzakiHipExactPanelsGemmS8S8Int64(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<long, std::allocator<long> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >*) { return 0; }
int TryLaunchRcOzakiHipMxfp4GemmS8S8Int64(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<long, std::allocator<long> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >*) { return 0; }
} }

namespace matmul_v4 { namespace metal {
int ComputeDigestAccel(CBlockHeader const&, unsigned int, unsigned int, uint256&, std::vector<unsigned char, std::allocator<unsigned char> >&) { return 0; }
int ComputeDigestsBMX4CAccel(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, unsigned int, std::vector<uint256, std::allocator<uint256> >&, std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >&) { return 0; }
int ComputeDigestsBatchedAccel(std::vector<CBlockHeader, std::allocator<CBlockHeader> > const&, unsigned int, unsigned int, std::vector<uint256, std::allocator<uint256> >&, std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >&) { return 0; }
int ComputeDigestsOnlyLTMetal(CBlockHeader const&, unsigned int, unsigned long const*, unsigned long, std::vector<matmul::v4::lt::DigestOnlyResultLT, std::allocator<matmul::v4::lt::DigestOnlyResultLT> >&) { return 0; }
int IsMatMulLTMetalAvailable() { return 0; }
int IsRcExactReplayFusedMetalQualified() { return 0; }
int IsRcOzakiMetalCompiled() { return 0; }
int IsRcOzakiMetalExactPanelsQualified() { return 0; }
int LaunchGemmS32S8(std::vector<int, std::allocator<int> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&) { return 0; }
int LaunchGemmS8S8(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<int, std::allocator<int> >&) { return 0; }
int LaunchRcExactReplayExpandMx(uint256 const&, unsigned int, unsigned int, std::vector<signed char, std::allocator<signed char> >&) { return 0; }
int LaunchRcExactReplayFusedFfn(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, uint256 const&, uint256 const&, unsigned int, unsigned int, unsigned int, unsigned int, std::vector<signed char, std::allocator<signed char> >&) { return 0; }
int LaunchRcExactReplayFusedFfnChain(std::vector<signed char, std::allocator<signed char> > const&, std::vector<std::vector<signed char, std::allocator<signed char> >, std::allocator<std::vector<signed char, std::allocator<signed char> > > > const&, std::vector<std::vector<signed char, std::allocator<signed char> >, std::allocator<std::vector<signed char, std::allocator<signed char> > > > const&, std::vector<uint256, std::allocator<uint256> > const&, std::vector<uint256, std::allocator<uint256> > const&, unsigned int, unsigned int, unsigned int, std::vector<std::vector<signed char, std::allocator<signed char> >, std::allocator<std::vector<signed char, std::allocator<signed char> > > >&) { return 0; }
int LaunchRcExactReplayMerkleLeaves(unsigned char const*, unsigned int, unsigned long, std::vector<uint256, std::allocator<uint256> >&) { return 0; }
int LaunchRcExactReplayMerkleRoot(std::vector<uint256, std::allocator<uint256> > const&, uint256&) { return 0; }
int LaunchRcExactReplayPhase1(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, uint256 const&, uint256 const&, unsigned int, unsigned int, unsigned int, std::vector<signed char, std::allocator<signed char> >&) { return 0; }
int MakeMetalExactMxProjectionBackend() { return 0; }
std::string RcOzakiMetalDeficit() { return {}; }
std::string RcOzakiMetalExactPanelsBackend() { return {}; }
void ResetRcOzakiMetalQualForTest() {}
void SelfQualifyRcExactReplayFusedMetalOnce() {}
void SelfQualifyRcOzakiMetalExactPanelsOnce() {}
void SelfQualifyRcOzakiMetalMxfp4Once() {}
int TryLaunchRcOzakiMetalExactPanelsGemmS8S8Int64(std::vector<signed char, std::allocator<signed char> > const&, std::vector<signed char, std::allocator<signed char> > const&, unsigned int, unsigned int, unsigned int, std::vector<long, std::allocator<long> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >*) { return 0; }
} }
