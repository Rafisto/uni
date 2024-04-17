execute() {
    echo -e "\033[34m[*] Executing: $@\033[0m"
    "$@"
}

execute java Main c 4 4 4 2 90
execute java Main c 8 8 4 4 90
