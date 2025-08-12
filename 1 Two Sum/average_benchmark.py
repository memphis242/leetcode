#!/usr/bin/env python3
"""
Script to average parameterized benchmark runs from Google Benchmark JSON output.

Usage:
1. Run your benchmark with JSON output: ./bench --benchmark_format=json --benchmark_out=results.json
2. Run this script: python average_benchmark.py results.json
"""

import json
import sys
from collections import defaultdict
from typing import Dict, List, Any


def load_benchmark_results(filename: str) -> Dict[str, Any]:
    """Load benchmark results from JSON file."""
    try:
        with open(filename, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")
        sys.exit(1)
    except json.JSONDecodeError:
        print(f"Error: Invalid JSON in file '{filename}'.")
        sys.exit(1)


def extract_base_name(benchmark_name: str) -> str:
    """Extract base benchmark name by removing parameter suffix."""
    # Google Benchmark appends parameters like "/0", "/1", etc.
    if '/' in benchmark_name:
        return benchmark_name.split('/')[0]
    return benchmark_name


def calculate_averages(results: Dict[str, Any]) -> Dict[str, Dict[str, float]]:
    """Calculate averages for parameterized benchmark runs."""
    # Group benchmarks by base name
    grouped_benchmarks = defaultdict(list)
    
    for benchmark in results.get('benchmarks', []):
        base_name = extract_base_name(benchmark['name'])
        grouped_benchmarks[base_name].append(benchmark)
    
    # Calculate averages for each group
    averages = {}
    
    for base_name, benchmarks in grouped_benchmarks.items():
        if len(benchmarks) <= 1:
            # No parameterization, just use the single result
            if benchmarks:
                b = benchmarks[0]
                averages[base_name] = {
                    'real_time': b.get('real_time', 0),
                    'cpu_time': b.get('cpu_time', 0),
                    'iterations': b.get('iterations', 0),
                    'count': 1
                }
            continue
        
        # Calculate averages across all parameterized runs
        total_real_time = sum(b.get('real_time', 0) for b in benchmarks)
        total_cpu_time = sum(b.get('cpu_time', 0) for b in benchmarks)
        total_iterations = sum(b.get('iterations', 0) for b in benchmarks)
        count = len(benchmarks)
        
        averages[base_name] = {
            'real_time': total_real_time / count,
            'cpu_time': total_cpu_time / count,
            'iterations': total_iterations / count,
            'count': count
        }
    
    return averages


def format_time(nanoseconds: float) -> str:
    """Format time from nanoseconds to human-readable format."""
    if nanoseconds >= 1e9:
        return f"{nanoseconds / 1e9:.3f} s"
    elif nanoseconds >= 1e6:
        return f"{nanoseconds / 1e6:.3f} ms"
    elif nanoseconds >= 1e3:
        return f"{nanoseconds / 1e3:.3f} μs"
    else:
        return f"{nanoseconds:.0f} ns"


def print_results(averages: Dict[str, Dict[str, float]]):
    """Print formatted average results."""
    print("\n" + "="*80)
    print("BENCHMARK AVERAGES (across all parameterized test cases)")
    print("="*80)
    
    # Find the longest benchmark name for formatting
    max_name_len = max(len(name) for name in averages.keys()) if averages else 0
    
    print(f"{'Benchmark':<{max_name_len}} {'Count':<6} {'Avg Real Time':<15} {'Avg CPU Time':<15} {'Avg Iterations':<15}")
    print("-" * (max_name_len + 6 + 15 + 15 + 15))
    
    for name, stats in sorted(averages.items()):
        real_time_str = format_time(stats['real_time'])
        cpu_time_str = format_time(stats['cpu_time'])
        iterations_str = f"{stats['iterations']:.0f}"
        count_str = str(stats['count'])
        
        print(f"{name:<{max_name_len}} {count_str:<6} {real_time_str:<15} {cpu_time_str:<15} {iterations_str:<15}")


def main():
    if len(sys.argv) != 2:
        print("Usage: python average_benchmark.py <benchmark_results.json>")
        print("\nTo generate the JSON file, run your benchmark with:")
        print("  ./bench --benchmark_format=json --benchmark_out=results.json")
        sys.exit(1)
    
    filename = sys.argv[1]
    results = load_benchmark_results(filename)
    averages = calculate_averages(results)
    print_results(averages)
    
    print(f"\nProcessed {len(results.get('benchmarks', []))} benchmark runs")
    print(f"Found {len(averages)} unique benchmark functions")


if __name__ == "__main__":
    main()
