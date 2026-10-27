#!/usr/bin/env bash
# ==============================================================================
# Master Test Runner: All Level 2 Circuits (Modular Subcircuits)
# Runs: Half Adder, Full Adder, 2-Bit Shifter
#
# Usage:
#   ./Testing/test_level2_circuits.sh              # Run all Level 2 circuits
#   ./Testing/test_level2_circuits.sh half_adder   # Run only Half Adder
#   ./Testing/test_level2_circuits.sh full_adder   # Run only Full Adder
#   ./Testing/test_level2_circuits.sh shifter      # Run only 2-Bit Shifter
# ==============================================================================

GREEN="\033[32m"
RED="\033[31m"
CYAN="\033[36m"
BOLD="\033[1m"
RESET="\033[0m"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

TARGET="${1:-all}"

case "$TARGET" in
    "6"|"half_adder"|"ha")
        bash "$SCRIPT_DIR/test_half_adder.sh"
        exit $?
        ;;
    "7"|"full_adder"|"fa")
        bash "$SCRIPT_DIR/test_full_adder.sh"
        exit $?
        ;;
    "8"|"shifter"|"shift")
        bash "$SCRIPT_DIR/test_shifter.sh"
        exit $?
        ;;
    "all")
        echo -e "\n${BOLD}${CYAN}########################################################################${RESET}"
        echo -e "${BOLD}${CYAN}           RUNNING ALL LEVEL 2 CIRCUIT TESTS (SUBCIRCUITS)              ${RESET}"
        echo -e "${BOLD}${CYAN}########################################################################${RESET}"

        TOTAL_SCRIPTS=0
        PASSED_SCRIPTS=0
        FAILED_SCRIPTS=0

        L2_SCRIPTS=(
            "$SCRIPT_DIR/test_half_adder.sh"
            "$SCRIPT_DIR/test_full_adder.sh"
            "$SCRIPT_DIR/test_shifter.sh"
        )

        for script in "${L2_SCRIPTS[@]}"; do
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
        echo -e "${BOLD} LEVEL 2 CIRCUITS SUMMARY: Passed: ${GREEN}${PASSED_SCRIPTS}/${TOTAL_SCRIPTS}${RESET} components${RESET}"
        echo -e "========================================================================"

        if [ "$FAILED_SCRIPTS" -eq 0 ]; then
            echo -e "${BOLD}${GREEN}>>> ALL LEVEL 2 CIRCUITS PASSED! <<<${RESET}\n"
            exit 0
        else
            echo -e "${BOLD}${RED}>>> SOME LEVEL 2 CIRCUITS FAILED! <<<${RESET}\n"
            exit 1
        fi
        ;;
    *)
        echo "Usage: $0 [all|half_adder|full_adder|shifter]"
        exit 1
        ;;
esac
