
import ssl
import socket

keylog_file = '/tmp/keylog.txt'

context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
context.keylog_filename = keylog_file

context.load_cert_chain(certfile='/certs/self-signed.crt', 
                        keyfile='/certs/self-signed.key')