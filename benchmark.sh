#!/bin/bash

echo "| N   | Elapsed Time (s) | Memory Usage (KB) |"
echo "|-----|------------------|-------------------|"

for N in 10 20 50 100 200 500 1000
do
    total_time=0
    total_mem=0

    for i in {1..5}
    do
        ./generate_map $N > map.txt

        # Capture output of time command
        output=$(/usr/bin/time -f "%e %M" ./dijkstras < map.txt 2>&1 >/dev/null)

        # Extract time and memory
        time=$(echo "$output" | head -n1)
        mem=$(echo "$output" | tail -n1)

        # Make sure values are numeric
        if [[ "$time" =~ ^[0-9.]+$ ]] && [[ "$mem" =~ ^[0-9]+$ ]]; then
            total_time=$(echo "$total_time + $time" | bc -l)
            total_mem=$(echo "$total_mem + $mem" | bc)
        else
            echo "⚠️  Warning: Skipped non-numeric output on N=$N run #$i: time=$time, mem=$mem"
        fi
    done

    # Average
    avg_time=$(echo "scale=4; $total_time / 5" | bc -l)
    avg_mem=$(echo "$total_mem / 5" | bc)

    echo "| $N | $avg_time | $avg_mem |"
done

