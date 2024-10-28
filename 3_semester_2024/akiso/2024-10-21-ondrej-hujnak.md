# Web Security - Ondrej Hujnak

- [Web Security - Ondrej Hujnak](#web-security---ondrej-hujnak)
  - [RW notes](#rw-notes)
  - [Web timeline](#web-timeline)
  - [HTTP](#http)
    - [HTTP Sniffing](#http-sniffing)
  - [Web applications](#web-applications)
  - [Securing the web](#securing-the-web)
    - [Symmetric key - same key for encryption and decryption](#symmetric-key---same-key-for-encryption-and-decryption)
    - [Asymmetric key](#asymmetric-key)
      - [Content protection](#content-protection)
      - [Digital signature](#digital-signature)
  - [Kerckhoff's principle](#kerckhoffs-principle)
  - [TLS - Transport Layer Security](#tls---transport-layer-security)
    - [Ownership verification](#ownership-verification)
    - [Validity](#validity)
    - [LetsEncrypt](#letsencrypt)
  - [Penetration testing](#penetration-testing)
    - [High level web service attack vectors](#high-level-web-service-attack-vectors)
    - [OWASP - Open web application security project](#owasp---open-web-application-security-project)
  - [Exmaple vulnerabilities](#exmaple-vulnerabilities)
    - [Path traversal](#path-traversal)
      - [Path traversal mitigation](#path-traversal-mitigation)
    - [Insufficient access control](#insufficient-access-control)
      - [Insufficient access control mitigation](#insufficient-access-control-mitigation)
    - [SQL injection](#sql-injection)
      - [SQL injection mitigation](#sql-injection-mitigation)
    - [Cookie stealing](#cookie-stealing)
    - [XSS - Cross-site scripting](#xss---cross-site-scripting)
      - [Cross-site scripting mitigation](#cross-site-scripting-mitigation)
  - [Tools](#tools)
    - [Zed Attack Proxy](#zed-attack-proxy)
    - [Burp Suite](#burp-suite)

World Wide Web was invented by Tim Berners-Lee in CERN.

- hyperlinks
- http + html - hypertext transfer protocol, hypertext markup language

## RW notes

- no JWT, no OAuth in the presentation

## Web timeline

1. PC Era (prior)

- Email, FTP, USENET, IRC (Internet Relay Chat), BBS (BulletinBoardSystem)

2. World Wide Web (1990)

- HTTP, HTML, File server, Website, Online Database

3. Social web (2000)

- Javascript, ~~Flash~~, ~~XML~~
- Weblogs, Collaboraition, Social Networking

4. Semantic Web (2010)

- RDF (Resource Description Framework), OWL (Web Ontology Language), Atom
- Semantic Search (document interconnections), Semantic DBs, Widgets

5. Meta Web (Combine the sources)

- Distributed Search
- Personal Intelligence
- Agents

Progressive Web Apps ~~died~~ (I presume because of SaaS)

## HTTP

Methods:

- Simple excahnge of static pages: `GET`, `HEAD`, `POST`
- Stateless protocol (no way to connect to the protocol) - cookies to add state
- No security provided

```http
HTTP POST username=user, password=secret
```

### HTTP Sniffing

- Wireshark

## Web applications

- Applications run in the web browser
- Almost exclusively Client - Server architecture
- Critical applications were transferred to web: Financial applications, Internal systems
- Inherits all web security issues

> NodeJS was invented because of greed, employing a single person (a full-stack) is cheaper than employing a full team of developers.

## Securing the web

Data protection _en route_ (between the user and the web server): - Confidentiality - Integrity - Authentication (one way)

Cryptography (hidden text - kryptos graphein) - transformation of plaintext to ciphertext and back

### Symmetric key - same key for encryption and decryption

```
secret -> encryption (w/ key) -> ciphertext -> decryption (w/ key) -> secret
```

### Asymmetric key

- public key for encryption - used by everyone to verify the data
- private key for decryption - if compromised the whole system is compromised

```
secret -> encryption (w/ public key) -> ciphertext -> decryption (w/ private key) -> secret
```

#### Content protection

```
public key encryption -> ciphertext -> private key decryption -> secret
(only a person with the private key can read the message)
```

#### Digital signature

```
private key encryption -> ciphertext -> public key decryption -> secret
(only a person with the private key can send a message)
```

## Kerckhoff's principle

> The encryption procedure must not require secrecy and it must always be assumed that it can easily fall into enemy lands.

The security has to depend only on the secrecy of the key.

## TLS - Transport Layer Security

The root of trust is the CA list in the browser.

> SSL (invented by Netscape) ~ TLS.

- SSL (Secure Socket Layer):
  - HTTPS - Hypertext Transfer Protocol Secure
  - Asymmetric handshake + symmetric encryption
- Server is authenticated based on it's certificate

### Ownership verification

Asymmetric encryption is used to verify the ownership of the server, the server knows the public key.

### Validity

We trust the third party - CA (Certification Authority) - to verify the validity of the certificate.

### LetsEncrypt

- Free SSL certificates, for short periods of time (3 months) to be used for online services.
- Use self-signed for offline services.

## Penetration testing

An approved attempt to break into the system to find vulnerabilities.

- White box - full knowledge of the system
- Black box - no knowledge of the system

Different type of penetration testing:
- White Hats - good guys
- Black Hats - bad guys (Hackers)

### High level web service attack vectors

- Social engineering
- Computer or browser breach
- Web application exploitation
- Networking attacks (redirection)
- Runtme environment attacks:
  - Web server misconfiguration or implementation errors
  - Database server misconfiguration or implementation errors
  - Direct access to the filesystem

### OWASP - Open web application security project

- Top 10 web application security risks

## Exmaple vulnerabilities

### Path traversal

Modified URL to access files outside of the web root.

```
http://example.com/index.php?file=../../../../etc/passwd
http://example.com/test/../../../../etc/passwd
```

#### Path traversal mitigation

- Chroot jail
- Proper server configuration
- Use whitelisting and disallow custom paths
- Input sanitization

### Insufficient access control

Insufficient access control to the resources.

```
http://example.com/admin
http://example.com/admin/secret
```

#### Insufficient access control mitigation

- Use authorization

### SQL injection

Misuse of SQL query to perform unintended operation:

- Change of the query semantics
- Obtaining restricted information

```sql
SELECT * FROM users WHERE username='admin' AND password='password'
-- breaks the query
SELECT * FROM users WHERE username='admin' --' AND password='password'
```

#### SQL injection mitigation

- Prepared queries (PREPARE)

```sql
PREPARE query FROM 'SELECT * FROM users WHERE username=? AND password=?';
EXECUTE query USING @username, @password;
```

- Bound variables

```sql
EXEC :user := '$user';
EXEC :pass := '$pass';
SELECT * FROM users WHERE username=:user AND password=:pass;
```

- Query sanitization

```sql
SELECT * FROM users WHERE username="maria\-" AND password="passw\"ord";
```

### Cookie stealing

Cookies are just plaintext files.
- Anyone can capture the cookie and use it to impersonate the user.

**Secure flag**: sent only over HTTPS
**HttpOnly flag**: not accessible by Javascript

### XSS - Cross-site scripting

Injecting malicious code into the web page, works client side:
- Reflected XSS - the code is reflected back to the user
- Stored XSS - the code is stored in the database and executed on the client

Used to steal cookies, rogue advertinsing, redirecting to malicious sites, mine cryptocurrencies.

#### Cross-site scripting mitigation

- Input sanitization (escape special characters)

Content security policy:
- Special HTTP header
- Executables are limited to the specified domain

Same-Origin Policy:
- Enforced by the browser
- The data is accessible only from the same [ protocol, domain, port ]

## Tools

### Zed Attack Proxy

Made by OWASP

### Burp Suite

Made by PortSwigger