#!/usr/bin/env bash

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SIM="$ROOT/simulator.exe"
[ ! -f "$SIM" ] && make -C "$ROOT" > /dev/null 2>&1

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cd "$TMP" || exit 1

printf "7\n0 0 0\n0 0 1\n0 1 0\n0 1 1\n1 0 0\n1 0 1\n1 1 0\n1 1 1\n" | "$SIM" > /dev/null 2>&1

echo "Testing Full Adder:"
passed=0
total=0

while IFS=',' read -r step a b cin sum cout; do
    [ "$step" = "Step" ] && continue
    total=$((total + 1))
    exp_sum=$((a ^ b ^ cin))
    exp_cout=$(( ((a + b + cin) >= 2) ? 1 : 0 ))
    if [ "$sum" -eq "$exp_sum" ] && [ "$cout" -eq "$exp_cout" ]; then
        passed=$((passed + 1))
        echo "  PASS: ($a, $b, $cin) -> sum=$sum, cout=$cout"
    else
        echo "  FAIL: ($a, $b, $cin) -> got (sum=$sum, cout=$cout), expected (sum=$exp_sum, cout=$exp_cout)"
    fi
done < "$TMP/simulation_results.csv"

echo "Result: $passed/$total passed."
[ "$passed" -eq "$total" ]
