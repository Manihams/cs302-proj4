#!/bin/bash

# Print table header with aligned formatting
printf "| %-5s | %-18s | %-18s |\n" "N" "Elapsed Time (s)" "Memory Usage (KB)"
printf "|%s|\n" "-------|--------------------|--------------------"

for N in 10 20 50 100 200 500 1000
do
    total_time=0
    total_mem=0

    for i in {1..5}
    do
        ./generate_map $N > map.txt

        # Capture output of time command
        output=$( { /usr/bin/time -f "%e %M" ./src/dijkstras < map.txt > /dev/null; } 2>&1 )

        # Extract time and memory values correctly
        time=$(echo "$output" | awk '{print $1}')
        mem=$(echo "$output" | awk '{print $2}')

        # Make sure values are numeric
        if [[ "$time" =~ ^[0-9.]+$ ]] && [[ "$mem" =~ ^[0-9]+$ ]]; then
            total_time=$(echo "$total_time + $time" | bc -l)
            total_mem=$(echo "$total_mem + $mem" | bc)
        else
            continue
        fi
    done

    # Calculate averages
    avg_time=$(echo "scale=4; $total_time / 5" | bc -l)
    avg_mem=$(echo "$total_mem / 5" | bc)

    # Print aligned row
    printf "| %-5d | %-18.4f | %-18d |\n" "$N" "$avg_time" "$avg_mem"
done

