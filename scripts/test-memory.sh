#!/bin/sh

#
# Initialisation
#

# Configurable variables
output=chase.csv

# Generate a timestamp
timestamp=$(date +%Y%m%d-%H%M)

# Create a temporary directory
mkdir chase-$timestamp
cd chase-$timestamp

# Save some system information
uname -a > kernel.txt
cat /proc/cpuinfo > cpuinfo.txt
cat /proc/meminfo > meminfo.txt


#
# Benchmark
#

echo Benchmark initiated at $(date +%Y%m%d-%H%M) | tee -a chase.log

chase -o hdr | tee $output
for chain_size in 8k 16k 64k 256k 512k 1m 2m 3m 6m 12m
do
    for loop_size in 0 25 100 500 2500
    do
		for access in random "forward 1"
		do
            for prefetch in none nta t0 t1 t2
            do
                chase -c $chain_size -g $loop_size -a $access -f $prefetch -s 1.0 -e 5 -o csv | tee -a $output
            done
        done
    done
done

echo Benchmark ended at $(date +%Y%m%d-%H%M) | tee -a chase.log

