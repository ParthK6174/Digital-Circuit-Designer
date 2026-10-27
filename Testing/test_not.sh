#!/usr/bin/env bash

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SIM="$ROOT/simulator.exe"
[ ! -f "$SIM" ] && make -C "$ROOT" > /dev/null 2>&1

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cd "$TMP" || exit 1

printf "3\n0\n1\n" | "$SIM" > /dev/null 2>&1

echo "Testing NOT Gate:"
passed=0
total=0

while IFS=',' read -r step a out; do
    [ "$step" = "Step" ] && continue
    total=$((total + 1))
    exp=$((1 - a))
    if [ "$out" -eq "$exp" ]; then
        passed=$((passed + 1))
        echo "  PASS: ($a) -> $out"
    else
        echo "  FAIL: ($a) -> got $out, expected $exp"
    fi
done < "$TMP/simulation_results.csv"

echo "Result: $passed/$total passed."
[ "$passed" -eq "$total" ]
