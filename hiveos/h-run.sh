#!/usr/bin/env bash
# Launch btxluxminer in the foreground. Working dir is the custom miner folder.
cd "$(dirname "$0")" || exit 1
. ./h-manifest.conf

export LD_LIBRARY_PATH="$(pwd)/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
# Host driver 13.0 vs image 13.3: do not refuse to start.
export NVIDIA_DISABLE_REQUIRE=1

# glibc floor: this binary needs GLIBC_2.34 (Ubuntu 22.04). Stock HiveOS 20.04 dies here.

conf="${CUSTOM_CONFIG_FILENAME:-./btxluxminer.conf}"
log="${CUSTOM_LOG_BASENAME:-./btxluxminer}.log"
mkdir -p "$(dirname "$log")"

if [[ ! -x ./btxluxminer ]]; then
  echo "btxluxminer binary missing or not executable in $(pwd)"
  exit 1
fi
if [[ ! -f "$conf" ]]; then
  echo "no config $conf — h-config.sh did not run"
  exit 1
fi

mapfile -t need < <(ldd ./btxluxminer 2>/dev/null | awk '/not found/{print}')
if ((${#need[@]})); then
  echo "missing libraries:"
  printf '  %s\n' "${need[@]}"
  echo "Need glibc 2.34+ (HiveOS 22.04 image) and bundled lib/libcublasLt.so.13"
  exit 1
fi

# Read flags; one flag per line from h-config.sh.
mapfile -t args < "$conf"
exec ./btxluxminer "${args[@]}" >>"$log" 2>&1
