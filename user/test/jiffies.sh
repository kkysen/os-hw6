#!/usr/bin/env bash

cd $(dirname $0)

if [[ ! -x jiffies ]]; then
    linux=/lib/modules/$(uname -r)/build
    if [[ ! -d $linux ]]; then
        linux=../../linux
    fi
    include=$linux/include
    echo '#include <stdio.h>' > jiffies.c
    rg '#define HZ' $include/uapi/asm-generic/param.h >> jiffies.c
    rg '#define INITIAL_JIFFIES' $include/linux/jiffies.h >> jiffies.c
    echo 'int main() { printf("%lu\n", INITIAL_JIFFIES); return 0; }' >> jiffies.c
    gcc jiffies.c -o jiffies
fi
initial_jiffies=$(./jiffies)
HZ=$(getconf CLK_TCK)
jiffies=$(sudo cat /proc/timer_list | rg '^jiffies: ([0-9]+)$' --replace '$1' | head -n 1)

seconds=$(python3 -c "print(($jiffies - $initial_jiffies) / $HZ)")
uptime=$(cut -f1 -d' ' /proc/uptime)
time=$(date +'%M:%S')

# echo "uptime = $uptime"
# echo "seconds = $seconds"
# echo "jiffies = $jiffies"
# echo "initial_jiffies = $initial_jiffies"
# echo "HZ = $HZ"
echo "uptime = $uptime, seconds = $seconds, time = $time"
