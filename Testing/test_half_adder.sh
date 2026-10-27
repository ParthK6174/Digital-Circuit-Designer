#!/usr/bin/env bash

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SIM="$ROOT/simulator.exe"
[ ! -f "$SIM" ] && make -C "$ROOT" > /dev/null 2>&1

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT
cd "$TMP" || exit 1

printf "6\n0 0\n0 1\n1 0\n1 1\n" | "$SIM" > /dev/null 2>&1

echo "Testing Half Adder:"
passed=0
total=0

while IFS=',' read -r step a b sum carry; do
    [ "$step" = "Step" ] && continue
    total=$((total + 1))
    exp_sum=$((a ^ b))
    exp_carry=$((a & b))
    if [ "$sum" -eq "$exp_sum" ] && [ "$carry" -eq "$exp_carry" ]; then
        passed=$((passed + 1))
        echo "  PASS: ($a, $b) -> sum=$sum, carry=$carry"
    else
        echo "  FAIL: ($a, $b) -> got (sum=$sum, carry=$carry), expected (sum=$exp_sum, carry=$exp_carry)"
    fi
done < "$TMP/simulation_results.csv"

echo "Result: $passed/$total passed."
[ "$passed" -eq "$total" ]
