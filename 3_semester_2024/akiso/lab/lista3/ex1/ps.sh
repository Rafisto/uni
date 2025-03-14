#!/bin/bash
# List processes by fetching /proc/PID/stat files
# Rafał Włodarczyk

# ====================
# Based on proc_pid_stat(5) https://man7.org/linux/man-pages/man5/proc_pid_stat.5.html
# (1) pid - process ID
# (2) comm - command name
# (3) state - state (R: running, S: sleeping, D: uninterruptible sleep, Z: zombie, T: traced or stopped, I: idle)
# (4) ppid - parent process ID
# (5) pgrp - process group ID - same as PID for single-threaded processes, PID of the thread group leader for multithreaded processes
# (6) session - session ID - shell session ID
# (7) tty_nr - controlling terminal
# (24) rss - resident set size - number of pages the process has in real memory
# lsof - number of open file descriptors - via /proc/PID/fd
# ====================

clear
output=""

for pid in $(ls /proc | grep -E '^[0-9]+$'); do
    tput cup 0 && echo "PS Processing PID: $pid" # display currently processed PID

    if [ -f /proc/$pid/stat ]; then
        stat_file="/proc/$pid/stat"

        stat_content=$(< "$stat_file")

        pid=$(echo "$stat_content" | awk '{print $1}') # {} for each line or record of input get the 1st field (split by whitespace by default)
        # match first ( and then everything until the last ) and then get the content in between
        comm=$(echo "$stat_content" | sed -e 's/.*(\(.*\)).*/\1/')

        # match everything after the last )
        rest_of_fields=$(echo "$stat_content" | sed -E 's/.*\)//')

        state=$(echo "$rest_of_fields" | awk '{print $1}') # 3-2 State
        ppid=$(echo "$rest_of_fields" | awk '{print $2}') # 4-2 Parent PID
        pgid=$(echo "$rest_of_fields" | awk '{print $3}') # 5-2 Process Group ID
        sid=$(echo "$rest_of_fields" | awk '{print $4}') # 6-2 Session ID
        tty=$(echo "$rest_of_fields" | awk '{print $5}') # 7-2 Controlling Terminal ID
        rss=$(echo "$rest_of_fields" | awk '{print $22}') # 24-2 Resident Set Size

        lsof=$(ls /proc/$pid/fd 2> /dev/null | wc -l) # count number of open file descriptors, if unable to read directory then 0
        
        output+="${pid}\t${ppid}\t${comm}\t${state}\t${tty}\t${rss}\t${pgid}\t${sid}\t${lsof}\n"
    fi
done 

echo -e $output | column -t -N pid,ppid,comm,state,tty,rss,pgid,sid,lsof -s $'\t'