# Philosophers Test Suite Documentation

This document provides a comprehensive overview of the test cases designed to validate the philosophers simulation program. Each test is carefully crafted to verify specific aspects of the implementation including synchronization, deadlock prevention, death detection, and meal completion logic.

## Table of Contents
1. [Test Categories](#test-categories)
2. [Basic Functionality Tests](#basic-functionality-tests)
3. [Edge Case Tests](#edge-case-tests)
4. [Performance and Stress Tests](#performance-and-stress-tests)
5. [Race Condition Tests](#race-condition-tests)
6. [Expected Outputs and Validation](#expected-outputs-and-validation)

---

## Test Categories

### 1. **Death Detection Tests**
Verify that the program correctly detects when a philosopher dies and terminates appropriately.

### 2. **Meal Completion Tests**
Ensure the program terminates when all philosophers have eaten the required number of meals.

### 3. **Synchronization Tests**
Test fork acquisition, release, and prevent deadlocks.

### 4. **Edge Case Tests**
Handle boundary conditions and unusual parameter combinations.

### 5. **Performance Tests**
Validate behavior under high load and tight timing constraints.

---

## Basic Functionality Tests

### Test 1: Single Philosopher Death
**Command:** `./philo 1 800 200 200`

**Purpose:** 
- Verify single philosopher scenario handling
- Test death detection with only one philosopher
- Validate that the philosopher cannot eat (no second fork available)

**Expected Output:**
```
0 1 has taken a fork
800 1 died
```

**Validation Criteria:**
- ✅ Philosopher takes one fork immediately
- ✅ Dies exactly at `time_to_die` (800ms)
- ✅ No eating actions occur
- ✅ Program terminates after death message

---

### Test 2: Basic Survival (No Meal Limit)
**Command:** `./philo 5 800 200 200`

**Purpose:**
- Test basic philosopher lifecycle (eat, sleep, think)
- Verify no deaths occur with reasonable timing
- Check proper fork acquisition and release
- Validate continuous operation without meal limits

**Expected Output Pattern:**
```
[timestamp] [id] has taken a fork
[timestamp] [id] has taken a fork  
[timestamp] [id] is eating
[timestamp] [id] is sleeping
[timestamp] [id] is thinking
```

**Validation Criteria:**
- ✅ All philosophers eat regularly
- ✅ No philosopher dies
- ✅ Fork acquisition follows proper order
- ✅ Time between meals < time_to_die for each philosopher
- ✅ Simulation runs indefinitely (manual termination required)

---

### Test 3: Meal Count Termination
**Command:** `./philo 5 800 200 200 7`

**Purpose:**
- Verify meal counting accuracy
- Test automatic termination when all philosophers finish eating
- Validate thread synchronization for meal completion detection

**Expected Behavior:**
- Each philosopher eats exactly 7 meals
- Program terminates automatically when all reach meal count
- No deaths occur

**Validation Criteria:**
- ✅ Each philosopher eats exactly 7 times
- ✅ Program terminates without manual intervention
- ✅ No death messages appear
- ✅ All philosophers participate in eating

---

## Edge Case Tests

### Test 4: Two Philosophers Critical
**Command:** `./philo 2 400 200 100`

**Purpose:**
- Test minimal philosopher count with potential deadlock
- Verify deadlock prevention mechanisms
- Check alternating eating pattern

**Expected Pattern:**
- Philosophers should alternate eating
- No deadlocks should occur
- Both philosophers should survive

**Validation Criteria:**
- ✅ No deadlocks occur
- ✅ Both philosophers eat regularly
- ✅ No philosopher starves
- ✅ Proper alternating access to shared forks

---

### Test 5: Tight Timing - Death Expected
**Command:** `./philo 4 310 200 100`

**Purpose:**
- Test death detection with tight timing
- Verify accurate time-based death detection
- Check program termination on first death

**Expected Behavior:**
- At least one philosopher should die
- Death should occur close to 310ms after last meal
- Program should terminate immediately after death

**Validation Criteria:**
- ✅ Death occurs within timing constraints
- ✅ Death message is accurate
- ✅ Program terminates on first death
- ✅ Death timing is precise (±10ms tolerance)

---

### Test 6: Tight Timing - Survival Expected
**Command:** `./philo 4 315 200 100`

**Purpose:**
- Test borderline survival conditions
- Verify precise timing calculations
- Check that philosophers can survive with minimal time margins

**Expected Behavior:**
- All philosophers should survive
- Eating should occur just before death threshold
- Continuous operation without deaths

**Validation Criteria:**
- ✅ No deaths occur
- ✅ All philosophers eat within time limits
- ✅ Time between meals < time_to_die consistently

---

## Performance and Stress Tests

### Test 7: Large Number of Philosophers
**Command:** `./philo 50 800 200 200 5`

**Purpose:**
- Test scalability with many philosophers
- Verify performance with increased thread count
- Check memory usage and resource management

**Expected Behavior:**
- All 50 philosophers complete 5 meals
- No resource starvation or deadlocks
- Reasonable performance (completion within 30 seconds)

**Validation Criteria:**
- ✅ All philosophers complete their meals
- ✅ No deadlocks with high contention
- ✅ Memory usage remains stable
- ✅ No race conditions cause data corruption

---

### Test 8: Fast Eating Cycle
**Command:** `./philo 10 1000 50 50 10`

**Purpose:**
- Test rapid state transitions
- Verify timing precision with short durations
- Check synchronization under high-frequency operations

**Expected Behavior:**
- Quick completion (under 10 seconds)
- All philosophers complete 10 meals
- Precise timing even with short intervals

**Validation Criteria:**
- ✅ All philosophers finish quickly
- ✅ Timing remains accurate with short intervals
- ✅ No race conditions in rapid state changes

---

### Test 9: Minimum Timing Stress
**Command:** `./philo 5 100 10 10 50`

**Purpose:**
- Test extreme timing conditions
- Verify system handles minimal time intervals
- Check precision at system timing limits

**Expected Behavior:**
- High-speed operation
- Potential for timing challenges
- May require system-dependent validation

**Validation Criteria:**
- ✅ System handles minimal timings gracefully
- ✅ No timing-related crashes
- ✅ Philosophers complete meals if possible

---

## Race Condition Tests

### Test 10: Concurrent Access Validation
**Command:** `./philo 8 500 100 100 20`

**Purpose:**
- Test multiple philosophers competing for resources
- Verify mutex protection for shared data
- Check for race conditions in meal counting

**Expected Behavior:**
- Clean competition for forks
- Accurate meal counting under contention
- No data corruption

**Validation Criteria:**
- ✅ Meal counts are accurate for all philosophers
- ✅ No fork state corruption
- ✅ Proper mutual exclusion

---

### Test 11: Quick Death Detection
**Command:** `./philo 3 200 150 50`

**Purpose:**
- Test rapid death detection
- Verify monitor thread responsiveness
- Check immediate termination on death

**Expected Behavior:**
- Quick death due to timing constraints
- Immediate program termination
- Accurate death reporting

**Validation Criteria:**
- ✅ Death detected within 50ms of occurrence
- ✅ Program terminates immediately
- ✅ Accurate death timing reported

---

## Expected Outputs and Validation

### Output Format Validation
All output should follow the format:
```
[timestamp_ms] [philosopher_id] [action]
```

**Valid Actions:**
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

### Timing Validation Rules

1. **Death Detection:** Death should occur when `current_time - last_meal_time >= time_to_die`
2. **Meal Duration:** Eating should last exactly `time_to_eat` milliseconds
3. **Sleep Duration:** Sleeping should last exactly `time_to_sleep` milliseconds
4. **Think Duration:** Thinking duration may vary for optimization

### Synchronization Validation

1. **Fork Consistency:** Each fork can only be held by one philosopher at a time
2. **Eating Prerequisite:** Philosophers must hold both adjacent forks to eat
3. **Death Termination:** Program must terminate immediately when any philosopher dies
4. **Meal Completion:** Program must terminate when all philosophers finish required meals

### Test Execution Commands

```bash
# Basic functionality
./philo 1 800 200 200                    # Single philosopher death
./philo 5 800 200 200                    # Basic survival
./philo 5 800 200 200 7                  # Meal count termination

# Edge cases
./philo 2 400 200 100                    # Two philosophers critical
./philo 4 310 200 100                    # Tight timing death
./philo 4 315 200 100                    # Tight timing survival

# Stress tests
./philo 50 800 200 200 5                 # Large number stress
./philo 10 1000 50 50 10                 # Fast eating cycle
./philo 5 100 10 10 50                   # Minimum timing stress

# Race conditions
./philo 8 500 100 100 20                 # Concurrent access
./philo 3 200 150 50                     # Quick death detection
```

### Automated Validation Script

```bash
#!/bin/bash
# test_validator.sh

validate_test() {
    local test_name="$1"
    local command="$2"
    local expected_result="$3"
    
    echo "Running test: $test_name"
    echo "Command: $command"
    
    # Run test with timeout
    timeout 30s $command > test_output.log 2>&1
    exit_code=$?
    
    # Validate based on expected result
    case $expected_result in
        "death")
            if grep -q "died" test_output.log; then
                echo "✅ PASS: Death detected"
            else
                echo "❌ FAIL: No death detected"
            fi
            ;;
        "completion")
            if [ $exit_code -eq 0 ] && ! grep -q "died" test_output.log; then
                echo "✅ PASS: Completed successfully"
            else
                echo "❌ FAIL: Unexpected termination"
            fi
            ;;
    esac
    
    rm -f test_output.log
}

# Run validation tests
validate_test "Single Philo Death" "./philo 1 800 200 200" "death"
validate_test "Basic Survival" "./philo 5 800 200 200" "survival"
validate_test "Meal Completion" "./philo 5 800 200 200 7" "completion"
```

---

## Test Result Analysis

### Success Indicators
- ✅ **No Data Races:** Consistent behavior across multiple runs
- ✅ **Accurate Timing:** Death/meal timing within ±10ms tolerance
- ✅ **Proper Termination:** Clean exit on death or meal completion
- ✅ **Resource Management:** No memory leaks or mutex issues
- ✅ **Scalability:** Performance remains reasonable with increased load

### Common Failure Patterns
- ❌ **Race Conditions:** Inconsistent meal counts or timing
- ❌ **Deadlocks:** Program hangs without progress
- ❌ **Timing Drift:** Death detection significantly off target
- ❌ **Memory Issues:** Segmentation faults or resource leaks
- ❌ **Synchronization Bugs:** Incorrect fork states or double-acquisition

This test suite provides comprehensive coverage of the philosophers simulation, ensuring robustness, correctness, and performance under various conditions.
