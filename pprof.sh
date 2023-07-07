#!/bin/bash

env LD_PRELOAD="/usr/lib/libprofiler.so" \
	CPUPROFILE_FREQUENCY=10000 \
	CPUPROFILE=./hello_f.prof \
	./bin/example_hello f
pprof --text ./bin/example_hello ./hello_f.prof

env LD_PRELOAD="/usr/lib/libprofiler.so" \
	CPUPROFILE_FREQUENCY=10000 \
	CPUPROFILE=./hello_v.prof \
	./bin/example_hello v
pprof --text ./bin/example_hello ./hello_v.prof
