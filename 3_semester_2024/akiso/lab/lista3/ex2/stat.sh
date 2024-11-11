#!/bin/bash
# List system info every second
# Rafał Włodarczyk

# Based on sysfs(5) and proc(5)
# 1.1 Current network throughput (via /proc/net/dev)
# 1.2 Average network throughput
# 2.1 CPU usage for each core (via /proc/stat)
# 2.2 Current CPU core frequency (via /sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq)
# 3. Uptime (via /proc/uptime)
# 4. Battery status (via /sys/class/power_supply/BAT0/uevent) - if exists
# 5. System load (via /proc/loadavg)
# 6. Memory usage (via /proc/meminfo - first 3 rows)

# Platform-specific variables
NETWORK_INTERFACE="enp0s31f6"

# Universal paths
NETWORK_STATS_PATH="/proc/net/dev"
CPU_CORE_STATS_PATH="/proc/stat"

human_readable() {
    if [ -z "$1" ]; then
        echo "0"
    else
        numfmt --to=iec --suffix=B --padding=10 $1
    fi
}

old_received=0
old_transmitted=0
network_total_receive_speed=0
network_total_transmit_speed=0
network_receive_speed=0
network_transmit_speed=0
network_average_receive_speed=0
network_average_transmit_speed=0

# 1. Current and medium network throughput (via /proc/net/dev)
get_network_throughput() {
    local interface=$1
    local line=$(grep -e "${NETWORK_INTERFACE}" ${NETWORK_STATS_PATH})
    if [ -z "${line}" ]; then
        echo "No such network interface: ${interface}"
        return
    fi

    if [ "${old_received}" -eq 0 ]; then
        old_received=$(echo "${line}" | awk '{print $2}')
        old_transmitted=$(echo "${line}" | awk '{print $10}')
    fi

    local received=$(echo "${line}" | awk '{print $2}')
    local transmitted=$(echo "${line}" | awk '{print $10}')

    network_receive_speed=$((received - old_received))
    network_transmit_speed=$((transmitted - old_transmitted))

    old_received=${received}
    old_transmitted=${transmitted}

    network_total_receive_speed=$((network_total_receive_speed + network_receive_speed))
    network_total_transmit_speed=$((network_total_transmit_speed + network_transmit_speed))

    network_average_receive_speed=$((network_total_receive_speed / timer))
    network_average_transmit_speed=$((network_total_transmit_speed / timer))

    echo "1.1 Net CUR TX: $(human_readable ${network_transmit_speed})/s RX: $(human_readable ${network_receive_speed})/s"
    echo "1.2 Net AVG TX: $(human_readable ${network_average_transmit_speed})/s RX: $(human_readable ${network_average_receive_speed})/s"
}

# 2.1 CPU usage for each core (via /proc/stat)
get_core_usage() {
    echo -n "2.1 CPU usage: "
    for i in $(seq 0 1 $(($(nproc) - 1))); do
        local cpu_now=($(grep -e "cpu${i}" ${CPU_CORE_STATS_PATH}))
        local cpu_sum="${cpu_now[@]:1}"
        local cpu_sum=$((${cpu_sum// /+}))
        local cpu_delta=$((cpu_sum - cpu_last_sum))
        local cpu_idle=$((cpu_now[4]- cpu_last[4]))
        local cpu_used=$((cpu_delta - cpu_idle))
        if [ -z $"{cpu_delta}" ] || [ "${cpu_delta}" -eq 0 ]; then
            # echo "CPU${i}=0% "
            continue
        fi
        local cpu_usage=$((100 * cpu_used / cpu_delta))
        # echo -n "CPU${i}=${cpu_usage}% "
    done 
    echo ""
}

timer=0

main() {
    while true; do
        clear
        timer=$(($timer + 1))
        echo "Timer: ${timer}"
        get_network_throughput $NETWORK_INTERFACE
        get_core_usage
        sleep 1
    done
}

main
