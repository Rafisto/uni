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

LINUX

```bash
# handle signals
gcc signals.c -o signals.out
# kill process by PID
gcc killpid.c -o killpid.out

# queue and receive
gcc queue.c -o queue.out
gcc receive.c -o receive.out
```

XV6

Taking into consideration the following code we can see that the `kill` syscall is implemented in `proc.c`:
- Running `kill` on pid 1 will kill the system (failure), on pid 2 will kill the shell.

```c
// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}
```


# Exercise 3-5

```bash
gcc lsh.c -o lsh.out
```

Tests:

ex3

```bash
ls -l 
sleep 2
sleep 2 &
^D
exit
cd ..
pwd
cd ex3-5
# sigchld solves zombie problem
```

ex4

```bash
ps | grep sh | wc -l
echo abc | cat | cat
wc -l < lsh.c
ps > out.txt 
cat out.txt
rm out.txt
fdisk -l 2> err.txt > out.txt 
cat err.txt
ps 2> err.txt > out.txt
sleep 10 
^C
ps | grep sh > out.txt
cat < out.txt | cut -f 1 -d /
```

ex5

fg, bg, jobs, ^Z

```bash
sleep 5
^Z
jobs
fg <pid> # wait
jobs # should be empty

sleep 10
^Z
bg <pid>
jobs # should be visible
# ...
jobs # should be empty
```

# Exercise 6

1. Modify the code to add two additional syscalls

2. Create `testsyscall.c`

```c
int main(int argc, char *argv[])
{
    // invoke the hello() syscall
    hello();

    // invoke the getppid() syscall
    printf(1, "Parent PID via getppid() syscall: %d\n", getppid());

    exit();
}
```

3. Run `make` to compile the code and run `testsyscall` to print hello and parent PID