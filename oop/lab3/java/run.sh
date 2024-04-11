execute() {
    echo -e "\033[34m[*] Executing: $@\033[0m"
    "$@"
}

execute java Main 
execute java Main 012id
execute java Main o 10
execute java Main o -1
execute java Main o 18349
execute java Main c 1 1 1 1 90
execute java Main c 1 1 1 1 60
execute java Main c 1 1 0 0 90
execute java Main c 2 2 1 1 90
execute java Main p 1
execute java Main s 1
execute java Main p -1
execute java Main s -10
