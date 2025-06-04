## HTTP

- [HTTP](#http)
- [Running `server3.pl`](#running-server3pl)
  - [Installng Perl Dependencies](#installng-perl-dependencies)
  - [Running the Server](#running-the-server)
- [Analyzing `server3.pl`](#analyzing-server3pl)
- [Header responder](#header-responder)

## Running `server3.pl` 

### Installng Perl Dependencies

This is a perl script therefore we must install the required dependencies

```bash
cpan HTTP::Daemon HTTP::Status IO::File
```

### Running the Server

```bash
perl server.pl
[http] perl server.pl
Please contact me at: <URL:http://[fe80::90fa:507d:8ecc:3a6%25enp0s31f6]:4321/>

[http] curl http://\[fe80::90fa:507d:8ecc:3a6%25enp0s31f6\]:4321
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Index</title>
</head>
<body>
    <p>This is index.html</p>
</body>
</html>% 
```

## Analyzing `server3.pl`

Let's analyze the code step by step.

```perl
use HTTP::Daemon;
```

`HTTP::Daemon` is used to create an HTTP server - to open a socket, bind it to a port and listen for incoming connections.

```perl
my $d = HTTP::Daemon->new(
        LocalAddr => 'localkitty',
        LocalPort => 4321,
    )|| die;
```

We are constructing a new HTTP daemon `$d` that listens on the address `localkitty` (hostname) and port `4321`. If the socket fails to bind, or the address is invalid the script will die.

```perl
print "Please contact me at: <URL:", $d->url, ">\n";
```

This line informs the user where the server can be accessed.

```perl
while (my $c = $d->accept)
```

This is the main loop of the server. It waits until a client connects to the server.
`$c` object is an instance of `HTTP::Daemon::ClientConn`, which is fetched from the HTTP daemon.

```perl
while (my $r = $c->get_request)
```

After establishing a connection with the client, we enter another loop to handle requests from the client. 
`$r` is an instance of `HTTP::Request`, which represents the HTTP request sent by the client.

```perl
if ($r->method eq 'GET') {    
    $file_s= "./index.html";
    $c->send_file_response($file_s);
}
else {
    $c->send_error(RC_FORBIDDEN)
}
```

We check whether the client request method is `GET`. 
- Request method is GET, then we return the contents of `index.html`
- Request method is not GET, then we return an error with the status code `403 Forbidden`.

```perl
$c->close;
undef($c);
```

After handling the request, the connection is closed and the `$c` is freed from memory.

## Header responder

```
go mod init netlab-header
go get -u github.com/gin-gonic/gin
code main.go
```