#!/bin/bash
# DB Controller
# Rafal Wlodarczyk 2024

mode=$1
filename="./lista-01-init.sql"

if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters"
fi

if [ "${mode}" == "start" ]; then
    echo "Starting database with init_sql=${filename}"
    export INIT_SQL_FILE="${filename}"
    docker compose up -d
elif [ "${mode}" == "stop" ]; then
    echo "Stopping database"
    docker compose down
    docker volume rm cw_db_data
elif [ "${mode}" == "exec" ]; then
    docker exec -it mariadb-container mariadb -D db2024 -u rafisto -prafistopassword
else
    echo "Invalid mode. Use 'start' or 'stop'."
fi
