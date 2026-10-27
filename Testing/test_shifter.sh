#!/usr/bin/env bash
# ==============================================================================
# Automated Component Test: 2-Bit Combinational Shifter (Menu Choice 8)
# Verifies all 8 input combinations (000 through 111)
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
echo -e "${BOLD}${CYAN} Testing Component: 2-Bit Combinational Shifter (Menu Choice 8)${RESET}"
echo -e "${BOLD}${CYAN}========================================================================${RESET}"
printf "%-6s | %-18s | %-18s | %-18s | %-8s\n" "Case" "Inputs (S,D0,D1)" "Expected (O0,O1)" "Actual (O0,O1)" "Status"
echo "------------------------------------------------------------------------"

cd "$TMP_DIR" || exit 1
# Menu choice 8 (Shifter), all 8 input permutations
printf "8\n0 0 0\n0 0 1\n0 1 0\n0 1 1\n1 0 0\n1 0 1\n1 1 0\n1 1 1\n" | "$SIMULATOR" > /dev/null 2>&1

CSV_FILE="$TMP_DIR/simulation_results.csv"
if [ ! -f "$CSV_FILE" ]; then
    echo -e "${RED}[ERROR] simulation_results.csv was not generated.${RESET}"
    exit 1
fi

TOTAL_TESTS=0
TOTAL_PASSED=0
TOTAL_FAILED=0
STEP=0

while IFS=',' read -r csv_step shift d0 d1 out0 out1; do
    if [ "$csv_step" = "Step" ]; then continue; fi

    STEP=$((STEP + 1))
    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    # Shifter logic:
    # Shift=0: Pass-through (Out0=D0, Out1=D1)
    # Shift=1: Left shift with zero-fill (Out0=0, Out1=D0)
    exp_out0=0
    exp_out1=0
    if [ "$shift" -eq 0 ]; then
        exp_out0="$d0"
        exp_out1="$d1"
    else
        exp_out0=0
        exp_out1="$d0"
    fi

    inputs="S=${shift}, D0=${d0}, D1=${d1}"
    expected="O0=${exp_out0}, O1=${exp_out1}"
    actual="O0=${out0}, O1=${out1}"

    if [ "$out0" -eq "$exp_out0" ] && [ "$out1" -eq "$exp_out1" ]; then
        TOTAL_PASSED=$((TOTAL_PASSED + 1))
        printf "%-6s | %-18s | %-18s | %-18s | ${GREEN}%-8s${RESET}\n" "TC #$STEP" "$inputs" "$expected" "$actual" "PASS"
    else
        TOTAL_FAILED=$((TOTAL_FAILED + 1))
        printf "%-6s | %-18s | %-18s | %-18s | ${RED}%-8s${RESET}\n" "TC #$STEP" "$inputs" "$expected" "$actual" "FAIL"
    fi
done < "$CSV_FILE"

echo "------------------------------------------------------------------------"
echo -e "Summary: Total: ${TOTAL_TESTS} | Passed: ${GREEN}${TOTAL_PASSED}${RESET} | Failed: $([ "$TOTAL_FAILED" -gt 0 ] && echo -e "${RED}${TOTAL_FAILED}${RESET}" || echo -e "${GREEN}${TOTAL_FAILED}${RESET}")"

if [ "$TOTAL_FAILED" -eq 0 ]; then
    echo -e "${BOLD}${GREEN}>>> 2-BIT SHIFTER TESTS PASSED! <<<${RESET}\n"
    exit 0
else
    echo -e "${BOLD}${RED}>>> 2-BIT SHIFTER TESTS FAILED! <<<${RESET}\n"
    exit 1
fi
