#!/bin/bash

# Compile the program
make

# Counters for passed and failed tests
passed=0
failed=0

# Array to store names of failed test files
declare -a failed_tests

# Find all input files and iterate over them
for input_file in test/in*.txt; do
    # Extract the test number from the file name
    test_number=$(echo $input_file | sed 's/test\/in\([0-9]*\)\.txt/\1/')

    # Check if the corresponding output file exists
    output_file="test/out$test_number.txt"
    if [ ! -f $output_file ]; then
        echo "Output file for test $test_number not found."
        continue
    fi

    # Run the program with the input file and save the output to a temporary file
    # 10-second timeout using 'timeout' command
    start_time=$(date +%s)
    if timeout 10s ./out/main < $input_file > test/temp_out.txt; then
        end_time=$(date +%s)
        elapsed_time=$(( end_time - start_time ))

        if [ $elapsed_time -ge 10 ]; then
            echo "Test $test_number failed (timeout)"
            ((failed++))
            failed_tests+=($input_file)
        else
            # Compare the program's output with the expected output
            if diff -w -B -Z test/temp_out.txt $output_file > /dev/null; then
                echo "Test $test_number passed"
                ((passed++))
            else
                echo "Test $test_number failed"
                ((failed++))
                failed_tests+=($input_file)
                echo "Failed Test $test_number:"
                echo "Output Produced:"
                cat test/temp_out.txt
                echo "Expected Output:"
                cat $output_file
                echo "-------------------------"
            fi
        fi
    else
        # If the program did not finish before the timeout or if 'timeout' command fails
        echo "Test $test_number failed (timeout error)"
        ((failed++))
        failed_tests+=($input_file)
    fi
done

# Remove the temporary output file
rm test/temp_out.txt

# Display the number of passed and failed tests
echo "$passed tests passed"
echo "$failed tests failed"

# List the names of the files for the tests that failed
if [ $failed -ne 0 ]; then
    echo "Failed test files:"
    for file in "${failed_tests[@]}"; do
        echo $file
    done
fi
