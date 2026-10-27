#!/usr/bin/env bash

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SIM="$ROOT/simulator.exe"
[ ! -f "$SIM" ] && make -C "$ROOT" > /dev/null 2>&1

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cd "$TMP" || exit 1

printf "8\n0 0 0\n0 0 1\n0 1 0\n0 1 1\n1 0 0\n1 0 1\n1 1 0\n1 1 1\n" | "$SIM" > /dev/null 2>&1

echo "Testing 2-Bit Shifter:"
passed=0
total=0

while IFS=',' read -r step shift d0 d1 out0 out1; do
    [ "$step" = "Step" ] && continue
    total=$((total + 1))
    if [ "$shift" -eq 0 ]; then
        exp0="$d0"
        exp1="$d1"
    else
        exp0=0
        exp1="$d0"
    fi
    if [ "$out0" -eq "$exp0" ] && [ "$out1" -eq "$exp1" ]; then
        passed=$((passed + 1))
        echo "  PASS: (shift=$shift, d0=$d0, d1=$d1) -> out0=$out0, out1=$out1"
    else
        echo "  FAIL: (shift=$shift, d0=$d0, d1=$d1) -> got ($out0, $out1), expected ($exp0, $exp1)"
    fi
done < "$TMP/simulation_results.csv"

echo "Result: $passed/$total passed."
[ "$passed" -eq "$total" ]
