#!/bin/sh

#
# Initialisation
#

# Configurable variables
pgm='../chase'
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

echo Benchmark initiated at $(date +%Y%m%d-%H%M) > chase.log

$pgm -o hdr | tee $output
for page_size in 4k 8k 16k
do
    for threads in 1 2 4 8
    do
        for refs in 1 2 4
        do
            for access in random "forward 1"
            do
                for chain_size in 8k 16k 512k 8m
                do
                    for prefetch in t0 t1 t2 nta
                    do
                        for loop_size in 0 25 100 500 2500
                        do
                            $pgm -p $page_size -t $threads -r $refs -a $access -c $chain_size -f $prefetch -s 1.0 -e 5 -o csv | tee -a $output
                        done
                    done
                done
            done
        done
    done
done

echo Benchmark ended at $(date +%Y%m%d-%H%M) > chase.log
