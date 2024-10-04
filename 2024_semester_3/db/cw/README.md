### Create a new MariaDB via compose

```bash
export INIT_SQL_FILE=./lista-01-init.sql
docker compose up -d

# SQL console
docker exec -it mariadb-container mariadb -D db2024 -u rafisto -prafistopassword

# DB Logs
docker logs mariadb-container
```

### Stop MariaDB

```bash
INIT_SQL_FILE=./lista-01-init.sql docker compose down && docker volume rm cw_db_data
```