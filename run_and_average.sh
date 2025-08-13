#!/bin/bash

# Example usage script for the benchmark averaging tool

echo "Running benchmark with JSON output..."
./"$1"/bench --benchmark_format=json --benchmark_out=results.json > /dev/null

echo "Calculating averages..."
python average_benchmark.py results.json | tee ./"$1"/average_results.log

echo "Done! Results have been averaged across all parameterized test cases."
