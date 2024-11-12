#!/bin/bash
# Display a random cat image with a Chuck Norris quote
# Rafał Włodarczyk

# ====================
# Configuration
# ====================

TEXT_API="https://api.chucknorris.io/jokes/random"
IMAGE_API="https://api.thecatapi.com/v1/images/search"

# ====================
# Main part
# ====================

QUOTE=$(curl -s "${TEXT_API}" | jq -r '.value')

IMAGE_URL=$(curl -s "${IMAGE_API}" | jq -r '.[0].url')

echo -e "IMAGE:"

curl -s ${IMAGE_URL} | catimg -w 80 -

echo -e "QUOTE: $QUOTE\n"