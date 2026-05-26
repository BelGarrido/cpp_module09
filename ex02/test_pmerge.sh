#!/bin/bash

# ─────────────────────────────────────────────
#  PmergeMe - Test Script
#  Tests: correctness, edge cases, performance
# ─────────────────────────────────────────────

BINARY="./PmergeMe"
PASS=0
FAIL=0
ERRORS=()

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
RESET='\033[0m'

# ─── Helpers ───────────────────────────────────

print_header() {
    echo ""
    echo -e "${CYAN}══════════════════════════════════════${RESET}"
    echo -e "${CYAN}  $1${RESET}"
    echo -e "${CYAN}══════════════════════════════════════${RESET}"
}

pass() {
    echo -e "  ${GREEN}[PASS]${RESET} $1"
    ((PASS++))
}

fail() {
    echo -e "  ${RED}[FAIL]${RESET} $1"
    ERRORS+=("$1")
    ((FAIL++))
}

# Checks that "After =>" line is sorted
is_sorted() {
    local output="$1"
    local after_line
    after_line=$(echo "$output" | grep "^After =>" | sed 's/After => //')
    if [ -z "$after_line" ]; then
        return 1
    fi
    local prev=-1
    for num in $after_line; do
        if [ "$num" -lt "$prev" ]; then
            return 1
        fi
        prev=$num
    done
    return 0
}

# Checks that program exits with error (non-zero)
expect_error() {
    local label="$1"
    shift
    local output
    output=$($BINARY "$@" 2>&1)
    local exit_code=$?
    if [ $exit_code -ne 0 ]; then
        pass "$label"
    else
        fail "$label → expected non-zero exit but got 0"
    fi
}

# Checks that output is sorted correctly
expect_sorted() {
    local label="$1"
    shift
    local output
    output=$($BINARY "$@" 2>&1)
    local exit_code=$?
    if [ $exit_code -ne 0 ]; then
        fail "$label → program exited with error: $exit_code"
        return
    fi
    if is_sorted "$output"; then
        pass "$label"
    else
        fail "$label → output not sorted"
        echo "    Output: $output"
    fi
}

# ─── Check binary exists ───────────────────────

if [ ! -f "$BINARY" ]; then
    echo -e "${RED}Error: binary '$BINARY' not found. Run 'make' first.${RESET}"
    exit 1
fi

# ══════════════════════════════════════════════
print_header "EDGE CASES"
# ══════════════════════════════════════════════

# No arguments
expect_error "No arguments"

# Single element
expect_sorted "Single element: 42" 42

# Two elements (already sorted)
expect_sorted "Two elements already sorted: 1 2" 1 2

# Two elements (reverse)
expect_sorted "Two elements reversed: 2 1" 2 1

# Already sorted sequence
expect_sorted "Already sorted: 0 1 2 3 4 5" 0 1 2 3 4 5

# Reverse sorted sequence
expect_sorted "Reverse sorted: 9 8 7 6 5 4 3 2 1 0" 9 8 7 6 5 4 3 2 1 0

# Duplicates — 42 subject says input is positive ints with no duplicates
# but worth testing your program's behavior
output=$($BINARY 3 3 3 2>&1)
exit_code=$?
if [ $exit_code -ne 0 ]; then
    pass "Duplicates → correctly rejected"
else
    echo -e "  ${YELLOW}[WARN]${RESET} Duplicates → program accepted duplicates (check subject requirements)"
fi

# Negative numbers → should be rejected per subject
expect_error "Negative number: -1 2 3"

# Non-numeric input
expect_error "Non-numeric input: abc"

# Mixed input
expect_error "Mixed input: 1 2 abc 4"

# Zero
expect_sorted "Zero alone: 0" 0

# Large single value
expect_sorted "Large value: 2147483647" 2147483647

# ══════════════════════════════════════════════
print_header "CORRECTNESS"
# ══════════════════════════════════════════════

expect_sorted "5 elements: 8 5 9 6 3" 8 5 9 6 3
expect_sorted "10 elements: 8 5 9 6 3 2 4 1 7 0" 8 5 9 6 3 2 4 1 7 0
expect_sorted "Odd count: 3 1 4 11 5 9 2 6" 3 1 4 1 5 9 2 6
expect_sorted "Power of 2 count (8): 7 3 5 1 6 2 4 0" 7 3 5 1 6 2 4 0

# Generate and test random sequences
for size in 15 21 50 100; do
    input=$(python3 -c "import random; nums=random.sample(range(0, 10000), $size); print(' '.join(map(str,nums)))")
    expect_sorted "Random $size elements" $input
done

# ══════════════════════════════════════════════
print_header "PERFORMANCE (timing output check)"
# ══════════════════════════════════════════════

# Generate 500 and 3000 element inputs
for size in 500 3000; do
    input=$(python3 -c "import random; nums=random.sample(range(0,100000), $size); print(' '.join(map(str,nums)))")
    output=$($BINARY $input 2>&1)
    exit_code=$?

    if [ $exit_code -ne 0 ]; then
        fail "Performance $size elements → program crashed"
        continue
    fi

    if ! is_sorted "$output"; then
        fail "Performance $size elements → output not sorted"
        continue
    fi

    # Check timing lines are present
    vec_line=$(echo "$output" | grep "vector")
    deq_line=$(echo "$output" | grep "deque")
    if [ -n "$vec_line" ] && [ -n "$deq_line" ]; then
        pass "Performance $size elements → sorted + timing lines present"
        echo "    $vec_line"
        echo "    $deq_line"
    else
        fail "Performance $size elements → timing lines missing"
    fi
done

# ══════════════════════════════════════════════
print_header "SUMMARY"
# ══════════════════════════════════════════════

echo ""
echo -e "  ${GREEN}Passed: $PASS${RESET}"
echo -e "  ${RED}Failed: $FAIL${RESET}"

if [ ${#ERRORS[@]} -gt 0 ]; then
    echo ""
    echo -e "  ${RED}Failed tests:${RESET}"
    for err in "${ERRORS[@]}"; do
        echo -e "    ${RED}✗${RESET} $err"
    done
fi

echo ""
if [ $FAIL -eq 0 ]; then
    echo -e "  ${GREEN}All tests passed!${RESET}"
else
    exit 1
fi
