execute() {
    echo -e "\033[34m[*] Executing: $@\033[0m"
    "$@"
}

execute ./app.out c 4 4 4 2 90
execute ./app.out c 8 8 4 4 90