#!/usr/bin/env bash

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SIM="$ROOT/simulator.exe"
[ ! -f "$SIM" ] && make -C "$ROOT" > /dev/null 2>&1

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cd "$TMP" || exit 1

printf "1\n0 0\n0 1\n1 0\n1 1\n" | "$SIM" > /dev/null 2>&1

echo "Testing AND Gate:"
passed=0
total=0

while IFS=',' read -r step a b out; do
    [ "$step" = "Step" ] && continue
    total=$((total + 1))
    exp=$((a & b))
    if [ "$out" -eq "$exp" ]; then
        passed=$((passed + 1))
        echo "  PASS: ($a, $b) -> $out"
    else
        echo "  FAIL: ($a, $b) -> got $out, expected $exp"
    fi
done < "$TMP/simulation_results.csv"

echo "Result: $passed/$total passed."
[ "$passed" -eq "$total" ]
