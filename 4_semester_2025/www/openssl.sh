openssl req -x509 -nodes -days 365 \
 -newkey rsa:2048 \
 -keyout self-signed.key -out self-signed.crt \
 -config openssl.cnf