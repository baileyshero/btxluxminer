# HiveOS custom miner — btxluxminer 0.9.31

**This is not a stock HiveOS 20.04 miner.** The binary needs **GLIBC 2.34** (Ubuntu 22.04) and **`libcublasLt.so.13`** (bundled in `lib/`).

Stock HiveOS images are still Ubuntu 20.04 / glibc 2.31. They will fail with `version 'GLIBC_2.34' not found`. Use a **HiveOS 22.04** image (`hive-replace --list`) and a driver that can load CUDA 13 (RTX 50: 570+ / 590). There is no glibc-2.31 build: CUDA 13.3 does not target Ubuntu 20.04.

## Flight sheet

Miner = **Custom**

| Field | Value |
|---|---|
| Miner name | `btxluxminer` |
| Installation URL | `https://github.com/baileyshero/btxluxminer/releases/download/v0.9.31-btxlux/btxluxminer-0.9.31.tar.gz` |
| Hash algorithm | `matmul` (informational) |
| Wallet and worker | `btx1z....%WORKER_NAME%` |
| Pool URL | your stratum host:port |
| Extra config | optional CLI flags |

Solo (GBT against a local/remote btxd) — put this in extra config:

```
--mode solo --rpcconnect 127.0.0.1 --rpcport 19334 --p2pport 19335
```

Remote Germany-style node: `--rpcconnect <ip> --rpcport 10200 --p2pport 40805` (whatever you mapped).

`--no-auto-update` is already injected.

Do not hash until `getblockhash 199300` starts `029041a1`.

## Package layout

```
btxluxminer/
  btxluxminer
  lib/libcublasLt.so.13
  h-manifest.conf
  h-config.sh
  h-run.sh
  h-stats.sh
```
