#!/usr/bin/env bash
# Launch btxluxminer. Same glibc trick as matador: if the host is < 2.34
# (stock HiveOS 20.04), run through bundled runtime/.
cd "$(dirname "$0")" || exit 1
. ./h-manifest.conf
[[ -n "${BTXLUX_HIVE_DIR:-}" && -e "$BTXLUX_HIVE_DIR/h-manifest.conf" ]] && \
    CUSTOM_CONFIG_FILENAME="$BTXLUX_HIVE_DIR/btxluxminer.conf"

export NVIDIA_DISABLE_REQUIRE=1

LOG_DIR=$(dirname "${CUSTOM_LOG_BASENAME:-./btxluxminer}")
mkdir -p "$LOG_DIR"

conf="${CUSTOM_CONFIG_FILENAME:-./btxluxminer.conf}"
if [[ ! -f "$conf" ]]; then
  echo "ERROR: miner config not found (run h-config.sh first): $conf"
  exit 1
fi
mapfile -t args < "$conf"

BIN=./btxluxminer
if [[ ! -x "$BIN" ]]; then
  echo "ERROR: miner binary missing or not executable: $BIN"
  exit 1
fi

CAPS=$(nvidia-smi --query-gpu=compute_cap --format=csv,noheader 2>/dev/null)
if [[ -n "$CAPS" ]]; then
  old_gpu=0
  modern=0
  while IFS= read -r cap; do
    cap="${cap// /}"
    [[ -z "$cap" ]] && continue
    major="${cap%%.*}"
    if [[ "$major" =~ ^[0-9]+$ ]]; then
      if (( major < 8 )); then old_gpu=$((old_gpu + 1)); else modern=$((modern + 1)); fi
    fi
  done <<< "$CAPS"
  if (( old_gpu > 0 && modern == 0 )); then
    echo "ERROR: every GPU on this rig is pre-Ampere (compute capability < 8.0)."
    echo "       BTX needs Ampere-or-newer tensor cores. This rig cannot mine."
    exit 1
  fi
fi

LOADER=()
GLIBC_MIN=2.34
host_glibc=$(ldd --version 2>/dev/null | head -1 | grep -oE '[0-9]+\.[0-9]+$')
if [[ -n "$host_glibc" && -x ./runtime/ld-linux-x86-64.so.2 ]]; then
  older=$(printf '%s\n%s\n' "$host_glibc" "$GLIBC_MIN" | sort -V | head -1)
  if [[ "$older" == "$host_glibc" && "$host_glibc" != "$GLIBC_MIN" ]]; then
    echo "host glibc $host_glibc is older than $GLIBC_MIN: using the bundled runtime"
    LOADER=(./runtime/ld-linux-x86-64.so.2 --library-path
            "./runtime:/usr/lib/x86_64-linux-gnu:/lib/x86_64-linux-gnu:/usr/local/lib")
  fi
fi

echo "starting: ${LOADER[*]} $BIN ${args[*]}"
if command -v stdbuf >/dev/null 2>&1; then
  stdbuf -i0 -o0 -e0 "${LOADER[@]}" "$BIN" "${args[@]}" 2>&1 | tee -a "${CUSTOM_LOG_BASENAME}.log"
else
  "${LOADER[@]}" "$BIN" "${args[@]}" 2>&1 | tee -a "${CUSTOM_LOG_BASENAME}.log"
fi
echo "Miner has exited"
