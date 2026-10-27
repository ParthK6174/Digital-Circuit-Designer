#!/usr/bin/env bash
# ==============================================================================
# Automated Component Test: 2-Input AND Gate (Menu Choice 1)
# Verifies all 4 input combinations (00, 01, 10, 11)
# ==============================================================================

GREEN="\033[32m"
RED="\033[31m"
CYAN="\033[36m"
YELLOW="\033[33m"
BOLD="\033[1m"
RESET="\033[0m"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
SIMULATOR="$PROJECT_ROOT/simulator.exe"

# 1. Ensure simulator executable exists
if [ ! -f "$SIMULATOR" ]; then
    echo -e "${YELLOW}simulator.exe not found. Compiling via make...${RESET}"
    make -C "$PROJECT_ROOT" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "${RED}[ERROR] Compilation failed.${RESET}"
        exit 1
    fi
fi

# 2. Run simulation in isolated sandbox
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

echo -e "\n${BOLD}${CYAN}========================================================================${RESET}"
echo -e "${BOLD}${CYAN} Testing Component: 2-Input AND Gate (Menu Choice 1)${RESET}"
echo -e "${BOLD}${CYAN}========================================================================${RESET}"
printf "%-6s | %-14s | %-14s | %-14s | %-8s\n" "Case" "Inputs (A,B)" "Expected (Out)" "Actual (Out)" "Status"
echo "------------------------------------------------------------------------"

cd "$TMP_DIR" || exit 1
# Menu choice 1 (AND), all 4 input permutations
printf "1\n0 0\n0 1\n1 0\n1 1\n" | "$SIMULATOR" > /dev/null 2>&1

CSV_FILE="$TMP_DIR/simulation_results.csv"
if [ ! -f "$CSV_FILE" ]; then
    echo -e "${RED}[ERROR] simulation_results.csv was not generated.${RESET}"
    exit 1
fi

TOTAL_TESTS=0
TOTAL_PASSED=0
TOTAL_FAILED=0
STEP=0

while IFS=',' read -r csv_step in_a in_b out; do
    if [ "$csv_step" = "Step" ]; then continue; fi

    STEP=$((STEP + 1))
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    # AND logic: out = A & B
    exp_out=$(( in_a & in_b ))

    inputs="A=${in_a}, B=${in_b}"
    expected="Out=${exp_out}"
    actual="Out=${out}"

    if [ "$out" -eq "$exp_out" ]; then
        TOTAL_PASSED=$((TOTAL_PASSED + 1))
        printf "%-6s | %-14s | %-14s | %-14s | ${GREEN}%-8s${RESET}\n" "TC #$STEP" "$inputs" "$expected" "$actual" "PASS"
    else
        TOTAL_FAILED=$((TOTAL_FAILED + 1))
        printf "%-6s | %-14s | %-14s | %-14s | ${RED}%-8s${RESET}\n" "TC #$STEP" "$inputs" "$expected" "$actual" "FAIL"
    fi
done < "$CSV_FILE"

echo "------------------------------------------------------------------------"
echo -e "Summary: Total: ${TOTAL_TESTS} | Passed: ${GREEN}${TOTAL_PASSED}${RESET} | Failed: $([ "$TOTAL_FAILED" -gt 0 ] && echo -e "${RED}${TOTAL_FAILED}${RESET}" || echo -e "${GREEN}${TOTAL_FAILED}${RESET}")"

if [ "$TOTAL_FAILED" -eq 0 ]; then
    echo -e "${BOLD}${GREEN}>>> AND GATE TESTS PASSED! <<<${RESET}\n"
    exit 0
else
    echo -e "${BOLD}${RED}>>> AND GATE TESTS FAILED! <<<${RESET}\n"
    exit 1
fi
