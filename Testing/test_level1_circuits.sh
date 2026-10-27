#!/usr/bin/env bash
# ==============================================================================
# Master Test Runner: All Level 1 Circuits (Basic Logic Gates)
# Runs: AND, OR, NOT, NOR, XOR
# ==============================================================================

GREEN="\033[32m"
RED="\033[31m"
CYAN="\033[36m"
BOLD="\033[1m"
RESET="\033[0m"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "\n${BOLD}${CYAN}########################################################################${RESET}"
echo -e "${BOLD}${CYAN}           RUNNING ALL LEVEL 1 CIRCUIT TESTS (LOGIC GATES)              ${RESET}"
echo -e "${BOLD}${CYAN}########################################################################${RESET}"

TOTAL_SCRIPTS=0
PASSED_SCRIPTS=0
FAILED_SCRIPTS=0

L1_SCRIPTS=(
    "$SCRIPT_DIR/test_and.sh"
    "$SCRIPT_DIR/test_or.sh"
    "$SCRIPT_DIR/test_not.sh"
    "$SCRIPT_DIR/test_nor.sh"
    "$SCRIPT_DIR/test_xor.sh"
)

for script in "${L1_SCRIPTS[@]}"; do
    if [ -f "$script" ]; then
        TOTAL_SCRIPTS=$((TOTAL_SCRIPTS + 1))
        bash "$script"
        if [ $? -eq 0 ]; then
            PASSED_SCRIPTS=$((PASSED_SCRIPTS + 1))
        else
            FAILED_SCRIPTS=$((FAILED_SCRIPTS + 1))
        fi
    fi
done

echo -e "\n${BOLD}========================================================================${RESET}"
echo -e "${BOLD} LEVEL 1 CIRCUITS SUMMARY: Passed: ${GREEN}${PASSED_SCRIPTS}/${TOTAL_SCRIPTS}${RESET} components${RESET}"
echo -e "========================================================================"

if [ "$FAILED_SCRIPTS" -eq 0 ]; then
    echo -e "${BOLD}${GREEN}>>> ALL LEVEL 1 CIRCUITS PASSED! <<<${RESET}\n"
    exit 0
else
    echo -e "${BOLD}${RED}>>> SOME LEVEL 1 CIRCUITS FAILED! <<<${RESET}\n"
    exit 1
fi
