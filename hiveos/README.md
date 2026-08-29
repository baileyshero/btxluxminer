# HiveOS custom miner — btxluxminer 0.9.31

Same layout as matador: one binary, `h-*.sh`, and a `runtime/` glibc 2.34 loader for stock HiveOS 20.04.

**Do not** ship `libcublasLt.so.13`. GEMM is CUTLASS in the binary.

## Flight sheet

Miner = **Custom**

| Field | Value |
|---|---|
| Miner name | `btxluxminer` |
| Installation URL | `https://github.com/baileyshero/btxluxminer/releases/download/v0.9.31-btxlux/btxluxminer-0.9.31.tar.gz` |
| Hash algorithm | `matmul` |
| Wallet and worker | `btx1z....%WORKER_NAME%` |
| Pool URL | your stratum host:port |

Solo extra config:

```
--mode solo --rpcconnect 127.0.0.1 --rpcport 19334 --p2pport 19335
```

`--no-auto-update` is already injected.

Do not hash until `getblockhash 199300` starts `029041a1`.

## Package layout

```
btxluxminer/
  btxluxminer
  runtime/          # glibc 2.34; used only when host < 2.34
  h-manifest.conf
  h-config.sh
  h-run.sh
  h-stats.sh
```
