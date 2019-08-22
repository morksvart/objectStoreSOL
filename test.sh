#!/bin/bash

sleep 1
numClient=50
for ((i = 1; i <= $numClient; i++)); do
    ./client usr_$i 1 &
    pids[$i]=$!
done

echo "... attendo"

for pid in ${pids[*]}; do
    wait $pid
done


echo "... retrive"
for ((i = 1; i <= $numClient - 20; i++)); do
    ./client usr_$i 2 &
    pids[$i]=$!
done

echo "...delete"
for ((i = 31; i <= $numClient; i++)); do
    ./client usr_$i 3 &
    pids[$i]=$!
done

echo "... attendo"

for pid in ${pids[*]}; do
    wait $pid
done

echo "test OK!"
exit 0
