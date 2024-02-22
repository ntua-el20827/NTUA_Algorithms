#!/bin/bash

cpp_program="visit"
data_dir="visit_data"

# Compile the C++ program
g++ -o "$cpp_program" "$cpp_program.cpp" -std=c++11

if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi
# Initialize counters for correct and wrong cases
correct_count=0
wrong_count=0

# Iterate over input files
for input_file in $data_dir/input*.txt; do
    # Extract the test case number from the input file name
    test_case=$(basename "$input_file" .txt | sed 's/input//')

    # Form the corresponding output file name
    expected_output_file="$data_dir/output${test_case}.txt"

    # Run the C++ program with the current input file
    output=$("./$cpp_program" < "$input_file")

    # Read the expected output from the file
    expected_output=$(cat "$expected_output_file")

    # Compare the actual output with the expected output
    if [ "$output" == "$expected_output" ]; then
        echo "Test case $test_case: Correct"
        ((correct_count++))
    else
        echo "Test case $test_case: Wrong"
        ((wrong_count++))
    fi
done

# Print the final result
echo "Correct cases: $correct_count"
echo "Wrong cases: $wrong_count"