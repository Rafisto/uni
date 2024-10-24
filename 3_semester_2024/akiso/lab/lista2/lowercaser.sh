#!/bin/bash

# Rename files in currentdir to lowercase
# Usage: ./lowercaser.sh

for file in *; do
    if [ -f "${file}" ]; then
        # use tr - translate or delete characters
        newfile=$(echo "$file" | tr '[:upper:]' '[:lower:]')
        if [ "${file}" != "${newfile}" ]; then
            # filename is not lowercase
            echo "Renaming ${file} to ${newfile}"
            # bash -- is used to separate the command from the arguments
            mv -- "${file}" "${newfile}"
        else
            # filename is lowercase
            echo "File ${file} is already lowercase"
        fi
    fi
done