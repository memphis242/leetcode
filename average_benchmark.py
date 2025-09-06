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


def calculate_stats(results: Dict[str, Any]) -> Dict[str, Dict[str, float]]:
    """Calculate averages and min/max for parameterized benchmark runs."""
    # Group benchmarks by base name
    grouped_benchmarks = defaultdict(list)
    
    for benchmark in results.get('benchmarks', []):
        base_name = extract_base_name(benchmark['name'])
        grouped_benchmarks[base_name].append(benchmark)
    
    # Calculate averages and min/max for each group
    stats = {}
    
    for base_name, benchmarks in grouped_benchmarks.items():
        if len(benchmarks) <= 1:
            # No parameterization, just use the single result
            if benchmarks:
                b = benchmarks[0]
                real_time = b.get('real_time', 0)
                cpu_time = b.get('cpu_time', 0)
                stats[base_name] = {
                    'real_time': real_time,
                    'cpu_time': cpu_time,
                    'min_real_time': real_time,
                    'max_real_time': real_time,
                    'min_cpu_time': cpu_time,
                    'max_cpu_time': cpu_time,
                    'iterations': b.get('iterations', 0),
                    'count': 1
                }
            continue
        
        # Calculate averages and min/max across all parameterized runs
        real_times = [b.get('real_time', 0) for b in benchmarks]
        cpu_times = [b.get('cpu_time', 0) for b in benchmarks]
        total_iterations = sum(b.get('iterations', 0) for b in benchmarks)
        count = len(benchmarks)
        
        stats[base_name] = {
            'real_time': sum(real_times) / count,
            'cpu_time': sum(cpu_times) / count,
            'min_real_time': min(real_times),
            'max_real_time': max(real_times),
            'min_cpu_time': min(cpu_times),
            'max_cpu_time': max(cpu_times),
            'iterations': total_iterations / count,
            'count': count
        }
    
    return stats


def format_time(nanoseconds: float) -> str:
    """Format time from nanoseconds to human-readable format."""
    if nanoseconds >= 1e9:
        return f"{nanoseconds / 1e9:.3f} s"
    elif nanoseconds >= 1e6:
        return f"{nanoseconds / 1e6:.3f} ms"
    elif nanoseconds >= 1e3:
        return f"{nanoseconds / 1e3:.3f} us"
    elif nanoseconds < 1.0:
        return f"{nanoseconds:.3f} ns"
    else:
        return f"{nanoseconds:.0f} ns"


def print_results(stats: Dict[str, Dict[str, float]]):
    """Print formatted average results."""
 
    # Find the longest benchmark name for formatting
    max_name_len = max(len(name) for name in stats.keys()) if stats else 0

    print("\n")
    print("-" * (max_name_len + 10 + 6 + 15*6 + 12 + 7))
    print("AGGREGATED BENCHMARK RESULTS (across all parameterized test cases)")
    print("-" * (max_name_len + 10 + 6 + 15*6 + 12 + 7))
    
    # Find fastest and slowest by real_time
    if stats:
        real_times = [(name, s['real_time']) for name, s in stats.items()]
        min_time = min(real_times, key=lambda x: x[1])[1]
        max_time = max(real_times, key=lambda x: x[1])[1]
        fastest = {name for name, t in real_times if t == min_time}
        slowest = {name for name, t in real_times if t == max_time}
    else:
        fastest = slowest = set()
    
    GREEN = '\033[92m'
    RED = '\033[91m'
    RESET = '\033[0m'
    
    # Header line
    print(f"{'Benchmark':<{max_name_len + 10}} {'Count':<6} {'Avg Real':<15} {'Min Real':<15} {'Max Real':<15} " +
          f"{'Avg CPU':<15} {'Min CPU':<15} {'Max CPU':<15} {'Iterations':<12}")
    print("-" * (max_name_len + 10 + 6 + 15*6 + 12 + 7))
    
    for name, stat in sorted(stats.items()):
        color = GREEN if name in fastest else RED if name in slowest else ''
        reset = RESET if color else ''
        
        print(f"{color}{name:<{max_name_len + 10}} {stat['count']:<6} " +
              f"{format_time(stat['real_time']):<15} " +
              f"{format_time(stat['min_real_time']):<15} " +
              f"{format_time(stat['max_real_time']):<15} " +
              f"{format_time(stat['cpu_time']):<15} " +
              f"{format_time(stat['min_cpu_time']):<15} " +
              f"{format_time(stat['max_cpu_time']):<15} " +
              f"{stat['iterations']:,.0f}{reset}")


def main():
    if len(sys.argv) != 2:
        print("Usage: python average_benchmark.py <benchmark_results.json>")
        print("\nTo generate the JSON file, run your benchmark with:")
        print("  ./bench --benchmark_format=json --benchmark_out=results.json")
        sys.exit(1)

    filename = sys.argv[1]
    results = load_benchmark_results(filename)
    stats = calculate_stats(results)
    print_results(stats)

    print(f"\nProcessed {len(results.get('benchmarks', []))} benchmark runs")
    print(f"Found {len(stats)} unique benchmark functions")


if __name__ == "__main__":
    main()
