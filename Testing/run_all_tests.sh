#!/usr/bin/env bash

DIR="$(cd "$(dirname "$0")" && pwd)"
failed=0

for test_script in "$DIR"/test_*.sh; do
    [ -f "$test_script" ] || continue
    bash "$test_script" || failed=1
    echo ""
done

if [ $failed -eq 0 ]; then
    echo "All component tests passed."
    exit 0
else
    echo "Some component tests failed."
    exit 1
fi
