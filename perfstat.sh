#!/bin/bash

perf stat -B -e \
	task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,cache-misses ./bin/example_hello f
perf stat -B -e \
	task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,cache-misses ./bin/example_hello v
perf stat -B -e \
	task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,cache-misses ./bin/example_hello F
perf stat -B -e \
	task-clock,context-switches,cpu-migrations,page-faults,cycles,instructions,branches,branch-misses,cache-misses ./bin/example_hello V
