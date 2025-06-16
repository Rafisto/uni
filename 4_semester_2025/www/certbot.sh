#!/bin/bash

# Usage: ./get-cert.sh example.com

DOMAIN="$1"
EMAIL="admin@$DOMAIN"
CERTS_DIR="./certs/$DOMAIN"

if [ -z "$DOMAIN" ]; then
  echo "Usage: $0 <domain>"
  exit 1
fi

mkdir -p "$CERTS_DIR"

docker run -it --rm \
  -v "$CERTS_DIR:/etc/letsencrypt" \
  -v "/var/lib/letsencrypt:/var/lib/letsencrypt" \
  -v "/var/log/letsencrypt:/var/log/letsencrypt" \
  -p 80:80 \
  certbot/certbot certonly \
  --standalone \
  --non-interactive \
  --agree-tos \
  --email "$EMAIL" \
  -d "$DOMAIN"
