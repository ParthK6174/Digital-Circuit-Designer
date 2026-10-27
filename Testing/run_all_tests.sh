#!/usr/bin/env bash
# ==============================================================================
# Master Test Runner: Runs All Circuit Component Tests (Level 1 + Level 2)
# ==============================================================================

GREEN="\033[32m"
RED="\033[31m"
CYAN="\033[36m"
BOLD="\033[1m"
RESET="\033[0m"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "\n${BOLD}${CYAN}========================================================================${RESET}"
echo -e "${BOLD}${CYAN}     DIGITAL ELECTRONICS CIRCUIT SIMULATOR - COMPLETE TEST SUITE        ${RESET}"
echo -e "${BOLD}${CYAN}========================================================================${RESET}"

TOTAL_COMPONENTS=0
PASSED_COMPONENTS=0
FAILED_COMPONENTS=0

COMPONENT_SCRIPTS=(
    # Level 1 Basic Logic Gates
    "$SCRIPT_DIR/test_and.sh"
    "$SCRIPT_DIR/test_or.sh"
    "$SCRIPT_DIR/test_not.sh"
    "$SCRIPT_DIR/test_nor.sh"
    "$SCRIPT_DIR/test_xor.sh"
    # Level 2 Modular Subcircuits
    "$SCRIPT_DIR/test_half_adder.sh"
    "$SCRIPT_DIR/test_full_adder.sh"
    "$SCRIPT_DIR/test_shifter.sh"
)

for script in "${COMPONENT_SCRIPTS[@]}"; do
    if [ -f "$script" ]; then
        TOTAL_COMPONENTS=$((TOTAL_COMPONENTS + 1))
        bash "$script"
        if [ $? -eq 0 ]; then
            PASSED_COMPONENTS=$((PASSED_COMPONENTS + 1))
        else
            FAILED_COMPONENTS=$((FAILED_COMPONENTS + 1))
        fi
    fi
done

echo -e "\n${BOLD}========================================================================${RESET}"
echo -e "${BOLD} OVERALL SIMULATOR TEST SUITE SUMMARY${RESET}"
echo -e "========================================================================"
echo -e " Total Circuit Components: ${BOLD}${TOTAL_COMPONENTS}${RESET}"
echo -e " Passed Components:        ${GREEN}${PASSED_COMPONENTS}${RESET}"
echo -e " Failed Components:        $([ "$FAILED_COMPONENTS" -gt 0 ] && echo -e "${RED}${FAILED_COMPONENTS}${RESET}" || echo -e "${GREEN}${FAILED_COMPONENTS}${RESET}")"
echo -e "========================================================================"

if [ "$FAILED_COMPONENTS" -eq 0 ]; then
    echo -e "${BOLD}${GREEN}>>> ALL CIRCUIT COMPONENT TESTS PASSED PERFECTLY! <<<${RESET}\n"
    exit 0
else
    echo -e "${BOLD}${RED}>>> SOME CIRCUIT COMPONENT TESTS FAILED! <<<${RESET}\n"
    exit 1
fi
