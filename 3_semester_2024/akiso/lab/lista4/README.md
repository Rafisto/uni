# Exercise 1

It works only if invoked directly from the terminal. Invoking as `strace ./runasroot` will not grant root permissions.

```bash
gcc runasroot.c -o runasroot.out
# File belongs to root
sudo chown root runasroot.out
# Set the SUID bit
sudo chmod u+s runasroot.out
```

# Exercise 2

```bash
# handle signals
gcc signals.c -o signals.out
# kill process by PID
gcc killpid.c -o killpid.out

# queue and receive
gcc queue.c -o queue.out
gcc receive.c -o receive.out
```

# Exercise 3

```bash
gcc lsh.c -o lsh.out
```