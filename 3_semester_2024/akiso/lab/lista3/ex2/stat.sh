#!/bin/bash
# List system info every second (GNU Coreutils)
# Rafał Włodarczyk

# ====================
# Based on sysfs(5) and proc(5)
# 1.1 Current and average network throughput (via /proc/net/dev)
# 1.2 Graph of the last 10 seconds of network throughput
# 2.1 CPU usage for each core (via /proc/stat)
# 2.2 Current CPU core frequency (via /sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq)
# 3. Uptime (via /proc/uptime)
# 4. Battery status (via /sys/class/power_supply/BAT0/uevent) - if exists
# 5. System load (via /proc/loadavg)
# 6. Memory usage (via /proc/meminfo - first 3 rows)
# ====================

# ====================
# Configuration
# ====================

# Platform-specific variables
NETWORK_INTERFACE="wlan0"

# Universal paths
NETWORK_STATS_PATH="/proc/net/dev"
CPU_CORE_FREQ_PATH="/sys/devices/system/cpu/*cpu*/cpufreq/scaling_cur_freq"
CPU_CORE_STATS_PATH="/proc/stat"
BATTERY_STATS_PATH="/sys/class/power_supply/BAT0/uevent"
MEMINFO_PATH="/proc/meminfo"

# Constants
NETWORK_GRAPH_WIDTH=50
NETWORK_GRAPH_MAX_ROWS=10

# ====================
# Utility variables
# ====================

timer=0

old_received=0
old_transmitted=0
network_total_receive_speed=0
network_total_transmit_speed=0
network_receive_speed=0
network_transmit_speed=0
network_average_receive_speed=0
network_average_transmit_speed=0

declare -a previous_rx
declare -a previous_tx

for i in $(seq 0 $((${NETWORK_GRAPH_MAX_ROWS} - 1))); do
    previous_rx[i]=0
    previous_tx[i]=0
done

declare -a cpu_last_idle
declare -a cpu_last_total

for i in $(seq 0 $(($(nproc) - 1))); do
    cpu_last_total[i]=0
    cpu_last_idle[i]=0
done

# ====================
# Utility functions
# ====================

human_readable() {
    if [ -z "$1" ]; then
        echo "0"
    else
        # --to=iec for IEC binary prefixes (KiB, MiB, GiB, etc.)
        # --suffix=B for bytes, alternatively --suffix=b for bits
        # --padding=10 for padding to 10 characters (right-aligned whitespaces), not used here
        numfmt --to=iec --suffix=B $1
    fi
}

# ====================
# 1.1 Current and average network throughput (via /proc/net/dev)
# ====================

get_network_throughput() {
    local interface=$1
    local line=$(grep -e "${interface}" ${NETWORK_STATS_PATH})
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

    previous_rx=("${previous_rx[@]:1}" $network_receive_speed)
    previous_tx=("${previous_tx[@]:1}" $network_transmit_speed)

    echo "1.1 Net CUR TX: $(human_readable ${network_transmit_speed})/s RX: $(human_readable ${network_receive_speed})/s"
    echo "1.2 Net AVG TX: $(human_readable ${network_average_transmit_speed})/s RX: $(human_readable ${network_average_receive_speed})/s"
}

# ====================
# 1.2 Graph of the last NETWORK_GRAPH_MAX_ROWS (seconds) of network throughput
# ====================

print_bar() {
    local value=$1
    local max_value=$2
    if [ "${max_value}" -eq 0 ]; then
        local width=0
    else
        local width=$((value * NETWORK_GRAPH_WIDTH / max_value))
    fi

    for ((i = 0; i < width; i++)); do
        echo -n "█"
    done
    echo "| (${value} B/s)"
}

print_graph() {
    local max_value=0
    for value in "${previous_rx[@]}" "${previous_tx[@]}"; do
        ((value > max_value)) && max_value=$value
    done

    echo "Network Receive Speed (RX) over Time:"

    echo "^"
    for value in "${previous_rx[@]}"; do
        print_bar "$value" "$max_value"
    done

    echo "t (time)"

    echo "Network Transmit Speed (TX) over Time:"
    echo "^"
    for value in "${previous_tx[@]}"; do
        print_bar "$value" "$max_value"
    done

    echo "t (time)"
}

# ====================
# 2. CPU usage for each core (via /proc/stat)
# ====================

get_core_usage() {
    echo "2.1 CPU usage and frequency:"

    for i in $(seq 0 $(($(nproc) - 1))); do
        local cpu_now=($(grep -w "cpu${i}" ${CPU_CORE_STATS_PATH}))

        local cpu_total=0
        for value in "${cpu_now[@]:1}"; do
            cpu_total=$((cpu_total + value))
        done
        local cpu_idle=${cpu_now[4]}

        local cpu_total_delta=$((cpu_total - cpu_last_total[i]))
        local cpu_idle_delta=$((cpu_idle - cpu_last_idle[i]))
        local cpu_used=$((cpu_total_delta - cpu_idle_delta))

        if [ -z "${cpu_total_delta}" ] || [ "${cpu_total_delta}" -eq 0 ]; then
            cpu_usage=0
        else
            local cpu_usage=$((100 * cpu_used / cpu_total_delta))
        fi

        local core_freq=$(cat /sys/devices/system/cpu/cpu${i}/cpufreq/scaling_cur_freq 2>/dev/null)
        core_freq=$((core_freq / 1000)) # MHz

        echo "CPU${i}=${cpu_usage}% @ ${core_freq}MHz"

        cpu_last_total[i]=$cpu_total
        cpu_last_idle[i]=$cpu_idle

    done
}

# ====================
# 3. Uptime (via /proc/uptime)
# ====================

get_uptime() {
    local uptime=$(cut -d' ' -f1 /proc/uptime)
    echo "3. Uptime: $(date -d@${uptime} -u +%H:%M:%S)"
}

# ====================
# 4. Battery status (via /sys/class/power_supply/BAT0/uevent) - if exists
# ====================

get_battery() {
    if [ -f "${BATTERY_STATS_PATH}" ]; then
        local battery_status=$(cat "${BATTERY_STATS_PATH}" | grep -e "POWER_SUPPLY_STATUS" | cut -d'=' -f2)
        local energy_full=$(cat "${BATTERY_STATS_PATH}" | grep -e "POWER_SUPPLY_ENERGY_FULL=" | cut -d'=' -f2)
        local energy_now=$(cat "${BATTERY_STATS_PATH}" | grep -e "POWER_SUPPLY_ENERGY_NOW=" | cut -d'=' -f2)
        local energy_percent=$((100 * ${energy_now} / ${energy_full}))
        echo "4. Battery: ${battery_status} ${energy_percent}%"
    else
        echo "4. Battery: No battery found"
    fi
}

# ====================
# 5. System load (via /proc/loadavg)
# ====================

get_system_load() {
    local loadavg=$(cat /proc/loadavg)
    local num_cpus=$(nproc)
    local load1=$(echo $loadavg | awk '{print $1}')
    local load5=$(echo $loadavg | awk '{print $2}')
    local load15=$(echo $loadavg | awk '{print $3}')

    local load1_percent=$(awk "BEGIN {print ($load1 / $num_cpus) * 100}") # percentage of load per all cores over 1 minute
    local load5_percent=$(awk "BEGIN {print ($load5 / $num_cpus) * 100}") # percentage of load per all cores over 5 minutes
    local load15_percent=$(awk "BEGIN {print ($load15 / $num_cpus) * 100}") # percentage of load per all cores over 15 minutes

    echo "5. System Load 1min: ${load1} (${load1_percent}%) 5min: ${load5} (${load5_percent}%) 15min: ${load15} (${load15_percent}%)"
}

# ====================
# 6. Memory usage (via /proc/meminfo - first 3 rows)
# ====================

get_memory_usage() {
    local meminfo=$(cat "${MEMINFO_PATH}")
    local memtotal=$(echo "${meminfo}" | grep -e "MemTotal" | awk '{print $2}')
    local memfree=$(echo "${meminfo}" | grep -e "MemFree" | awk '{print $2}')
    local memavailable=$(echo "${meminfo}" | grep -e "MemAvailable" | awk '{print $2}')

    memtotal=$((memtotal * 1024))
    memfree=$((memfree * 1024))
    memavailable=$((memavailable * 1024))

    local memavailable_percent=$((100 * memavailable / memtotal))

    echo "6. Memory $(human_readable $((memtotal - memavailable)))/$(human_readable ${memtotal}), $(human_readable ${memavailable}) (${memavailable_percent}%) is free"
}

main() {
    while true; do
        local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
        timer=$(($timer + 1))
        clear
        echo "System info at ${timestamp}, timer ${timer}"
        get_network_throughput $NETWORK_INTERFACE
        print_graph
        get_core_usage
        get_uptime
        get_battery
        get_system_load
        get_memory_usage
        sleep 1
    done
}

main
