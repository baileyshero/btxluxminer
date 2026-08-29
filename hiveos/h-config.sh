#!/usr/bin/env bash
# HiveOS flight sheet -> btxluxminer argv. Sourced by /hive/bin/custom.

[[ -z $CUSTOM_NAME ]] && CUSTOM_NAME=btxluxminer
conf="${CUSTOM_CONFIG_FILENAME:-/hive/miners/custom/${CUSTOM_NAME}/btxluxminer.conf}"
mkdir -p "$(dirname "$conf")" "/var/log/miner/${CUSTOM_NAME}"

template="${CUSTOM_TEMPLATE:-}"
wallet="${template%%.*}"
worker="${template#*.}"
if [[ -z $wallet ]]; then
  wallet="$template"
fi
if [[ -z $worker || $worker == "$template" ]]; then
  worker="${WORKER_NAME:-hive}"
fi

url="${CUSTOM_URL:-}"
url="${url#stratum+tcp://}"
url="${url#stratum+ssl://}"
url="${url#ssl://}"
url="${url#tls://}"

extra="${CUSTOM_USER_CONFIG:-}"
pass="${CUSTOM_PASS:-x}"

{
  echo "--no-auto-update"
  echo "--api-port"
  echo "4060"
  echo "--api-listen"
  echo "127.0.0.1"
  if [[ $extra == *"--mode solo"* || $extra == *"--mode=solo"* ]]; then
    echo "--mode"
    echo "solo"
    [[ -n $wallet ]] && { echo "--payoutaddress"; echo "$wallet"; }
  else
    echo "--mode"
    echo "pool"
    [[ -n $wallet ]] && { echo "--payoutaddress"; echo "$wallet"; }
    [[ -n $worker ]] && { echo "--worker"; echo "$worker"; }
    [[ -n $url ]] && { echo "--pool"; echo "$url"; }
    [[ -n $pass ]] && { echo "--pool-pass"; echo "$pass"; }
  fi
} > "$conf"

# Extra flags last (Hive "extra config arguments"), one token per line if possible.
# shellcheck disable=SC2086
if [[ -n $extra ]]; then
  # Keep as a single trailing line of tokens; h-run maps file to argv.
  printf '%s\n' $extra >> "$conf"
fi

chmod 644 "$conf"
echo "[btxluxminer] wrote $conf"
cat "$conf"
