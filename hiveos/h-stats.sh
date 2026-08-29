#!/usr/bin/env bash
# HiveOS agent include: must set $khs and $stats.
# BTX unit is episode/s. khs is episode/s * 1000 so the dashboard has a number;
# hs[] + hs_units=hs is the honest per-GPU figure.

khs=0
stats='{"hs":[0],"hs_units":"hs","temp":[],"fan":[],"uptime":0,"ver":"0.9.31","ar":[0,0],"algo":"matmul"}'

sum="$(curl -fsS --max-time 2 http://127.0.0.1:4060/summary 2>/dev/null || true)"
[[ -z $sum ]] && { return 0 2>/dev/null || true; }

eval "$(printf '%s' "$sum" | python3 -c '
import json, sys
raw = sys.stdin.read()
try:
    d = json.loads(raw)
except Exception:
    print("khs=0")
    raise SystemExit(0)
rate = float((d.get("rate") or {}).get("episode_per_s") or 0)
shares = d.get("shares") or {}
acc = int(shares.get("accepted") or 0)
rej = int(shares.get("rejected") or 0)
up = int(d.get("uptime_sec") or 0)
ver = str(d.get("version") or "0.9.31")
gpus = d.get("gpu_runtime") or []
if isinstance(gpus, str):
    try:
        gpus = json.loads(gpus)
    except Exception:
        gpus = []
hs, temp, fan = [], [], []
if isinstance(gpus, list) and gpus:
    n = max(len(gpus), 1)
    per = rate / n
    for g in gpus:
        hs.append(round(per, 4))
        if isinstance(g, dict):
            temp.append(int(g.get("temp_c") or 0))
            fan.append(int(g.get("fan_pct") or 0))
else:
    hs = [round(rate, 4)]
stats = {
    "hs": hs,
    "hs_units": "hs",
    "temp": temp,
    "fan": fan,
    "uptime": up,
    "ver": ver,
    "ar": [acc, rej],
    "algo": "matmul",
}
print("khs=%s" % (rate * 1000.0))
print("stats=%r" % json.dumps(stats, separators=(",", ":")))
')"
