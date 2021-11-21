#!/usr/bin/env bash

set -euo pipefail

cd $(dirname $0)

HZ=$(rg 'CONFIG_HZ=([0-9]+)' \
    --only-matching \
    --replace '$1' \
    /boot/config-$(uname -r) \
)

if [[ ! -x jiffies ]]; then
    linux=/lib/modules/$(uname -r)/build
    if [[ ! -d $linux ]]; then
        linux=../../linux
    fi
    include=$linux/include
    echo '#include <stdio.h>' > jiffies.c
    echo "#define HZ ${HZ}" >> jiffies.c
    rg '#define INITIAL_JIFFIES' $include/linux/jiffies.h >> jiffies.c
    echo 'int main() { printf("%lu\n", INITIAL_JIFFIES); return 0; }' \
        >> jiffies.c
    gcc jiffies.c -o jiffies
fi
initial_jiffies=$(./jiffies)

uptime=$(cut -f1 -d' ' /proc/uptime)
jiffies=$(sudo cat /proc/timer_list \
    | rg '^jiffies: ([0-9]+)$' --replace '$1' \
    | tail -n 1 \
)
time=$(date +'%M:%S')

seconds=$(python3 -c "print(($jiffies - $initial_jiffies) / $HZ)")

# echo "uptime = $uptime"
# echo "seconds = $seconds"
echo "jiffies = $jiffies"
echo "initial_jiffies = $initial_jiffies"
echo "HZ = $HZ"
echo "uptime = $uptime, seconds = $seconds, time = $time"
