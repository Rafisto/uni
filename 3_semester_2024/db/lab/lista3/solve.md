# Lab 3
## Rafał Włodarczyk 
### 2024-12-03

- [Lab 3](#lab-3)
  - [Rafał Włodarczyk](#rafał-włodarczyk)
    - [2024-12-03](#2024-12-03)
  - [Solves](#solves)
    - [Exercise 1](#exercise-1)


MariaDB Setup:

```yaml
services:
  mariadb:
    image: mariadb:latest
    container_name: mariadb-container
    environment:
      MYSQL_ROOT_PASSWORD: rootpassword
      MYSQL_DATABASE: db2024
      MYSQL_USER: rafisto
      MYSQL_PASSWORD: rafistopassword
    volumes:
      - db_data:/var/lib/mysql

    ports:
      - "3306:3306"
    networks:
      - mariadb-network

volumes:
  db_data:

networks:
  mariadb-network:
    driver: bridge
```

```bash
# Maintenance

## Up DB
docker compose up -d
## Down DB
docker compose down && docker volume rm lista3_db_data

# Execution

## Root user
docker exec -it mariadb-container mariadb -D aparaty -u root -prootpassword
```

## Solves

### Exercise 1