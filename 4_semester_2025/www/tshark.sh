#!/bin/bash

tshark -r ./logs/traffic.pcap -V -x -q \
    -o "tls.debug_file:ssldebug.log" \
    -o "tls.desegment_ssl_records: TRUE" \
    -o "tls.desegment_ssl_application_data: TRUE" \
    -o "tls.keys_list:certs/self-signed.key" \
    -o "tls.keylog_file:./logs/ssl_keylog" \
    -Y "http"