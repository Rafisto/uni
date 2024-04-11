execute() {
    echo -e "\033[34m[*] Executing: $@\033[0m"
    "$@"
}

execute ./app.out 
execute ./app.out 012id
execute ./app.out o 10
execute ./app.out o -1
execute ./app.out o 18349
execute ./app.out c 1 1 1 1 90
execute ./app.out c 1 1 1 1 60
execute ./app.out c 1 1 0 0 90
execute ./app.out c 2 2 1 1 90
execute ./app.out p 1
execute ./app.out s 1
execute ./app.out p -1
execute ./app.out s -10
