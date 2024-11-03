/*
    Rafał Włodarczyk
    Routines for attaching, detaching, reading and writing data to the tracee's memory.

    Based on ptrace(2) — Linux manual page https://linux.die.net/man/2/ptrace
    and http://omeranson.github.io/blog/2018/04/08/ptrace-magic-redirect-a-running-programme
*/

#ifndef UTILS_PTRACE_H
#define UTILS_PTRACE_H

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdint.h>

typedef uint32_t word_t;
#define word_size sizeof(word_t)

/*
    Attach to the process specified in pid, making it a tracee
    of the calling process.  The tracee is sent a SIGSTOP, but
    will not necessarily have stopped by the completion of
    this call; use waitpid(2) to wait for the tracee to stop.

    @param pid - PID of the tracee
*/
int putils_attach(pid_t pid)
{
    int rc;
    if ((rc = ptrace(PTRACE_ATTACH, pid, NULL, NULL)))
        return rc;
    waitpid(pid, NULL, 0);
    return 0;
}

/*
    Detach from the tracee.

    @param pid - PID of the tracee
*/
int putils_detach(pid_t pid)
{
    int rc;
    if ((rc = ptrace(PTRACE_DETACH, pid, NULL, NULL)))
        return rc;
    return 0;
}

/*
    Copy the tracee's general-purpose registers, respectively, to the address data in the tracer.
    See <sys/user.h> for information on the format of this data (*user_regs_struct).

    @param pid - PID of the tracee
    @param regs - General-purpose registers of the tracee
*/
int putils_get_registers(pid_t pid, struct user_regs_struct *regs)
{
    int rc;
    if ((rc = ptrace(PTRACE_GETREGS, pid, NULL, regs)))
        return rc;

    return 0;
}

/*
    Copy (read) all word data from the address addr in the tracee's memory.

    @param child - PID of the tracee
    @param addr - First word address in the tracee's memory
    @param len - Length of the data to be copied
    @param str - Data to be copied
*/
void putils_get_data(pid_t child, const word_t *addr, word_t *str, int len)
{
    int i;
    int j = (len + word_size - 1) / word_size;
    for (i = 0; i < j; i++)
    {
        *str++ = ptrace(PTRACE_PEEKDATA, child, addr++, NULL);
    }
}

/*
    Copy (push) all word data to the address addr in the tracee's memory.

    @param child - PID of the tracee
    @param addr - First word address in the tracee's memory
    @param len - Length of the data to be copied
    @param str - Data to be copied
*/
void putils_push_data(pid_t child, const word_t *addr, const word_t *str, int len)
{
    int i;
    int j = (len + word_size - 1) / word_size;
    for (i = 0; i < j; i++)
    {
        ptrace(PTRACE_POKEDATA, child, addr++, *str++);
    }
}

#endif // UTILS_PTRACE_H