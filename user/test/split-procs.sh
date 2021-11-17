#!/usr/bin/env bash

set -euox pipefail

pids=()

trap 'kill ${pids[@]}' SIGINT SIGTERM EXIT

for i in {1..10}; do
    [[ $i -le 5 ]] && nice=-7 || nice=-3
    taskset 1 nice $nice yes > /dev/null &
    pids+=($!)
done

wait
