/*
    Rafał Włodarczyk
    Routines for inserting syscall breakpoints and performing syscalls in the tracee's context.

    Used in the rdr.c program are the syscalls OPEN, CLOSE and DUP2:

    id | name      | rax                | rdi                | rsi          |
    2  | sys_open  | unsigned int fd    | const char *buf    | size_t count |
    3  | sys_close | unsigned int fd    |                    |              |
    33 | sys_dup2  | unsigned int oldfd | unsigned int newfd |              |

    See x86_64 syscall numbers at https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
*/

#ifndef UTILS_OPERATIONS_H
#define UTILS_OPERATIONS_H

#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#include "macros.h"

static char insert_code[] = "\x0f\x05\xcc"; // syscall + int3 (breakpoint)
typedef unsigned long long int u128int_t;

/*
    Calculate the size of the memory to be backed up.
    The size is the length of the path to the file to be opened + 1 (null terminator) + size of the inserted code.
    The size is then aligned to the word size.

    @param outpath - Path to the file to be opened
*/
size_t calculate_backup_size(const char *outpath)
{
    size_t result = strlen(outpath) + 1 + sizeof(insert_code);
    result += (result % word_size);
    return result;
}

/*
    Insert a syscall with a breakpoint at the specified address in the tracee's memory.

    @param pid - PID of the tracee
    @param rip_address - Address of the instruction pointer
    @param outpath - Path to the file to be opened
    @param outpath_len - Length of the path to the file to be opened
*/
void insert_syscall_with_breakpoint(pid_t pid, void *rip_address, const char *outpath, size_t outpath_len)
{
    size_t size = outpath_len + sizeof(insert_code);

    void *data = (void *)calloc(1, size);
    if (!data)
    {
        rfail("Failed to allocate memory");
        return;
    }

    memcpy(data, outpath, outpath_len);
    memcpy((void *)((u128int_t)data + outpath_len), insert_code, sizeof(insert_code));

    putils_push_data(pid, rip_address, data, size);

    free(data);
}

/*
    Perform a syscall in the tracee's context.

    @param pid - PID of the tracee
    @param regs - General-purpose registers of the tracee
    @param syscall_num - Number of the syscall to be performed
    @param rdi - First argument of the syscall
    @param rsi - Second argument of the syscall
    @param rdx - Third argument of the syscall
    @param rip_address - Address of the instruction pointer

    @return 0 on success, -1 on failure with a message;
*/
int perform_syscall(pid_t pid, struct user_regs_struct *regs, u128int_t syscall_num, u128int_t rdi, u128int_t rsi, u128int_t rdx, void *rip_address)
{
    int rc;

    regs->rip = (u128int_t)(rip_address);
    regs->rax = syscall_num;
    regs->rdi = rdi;
    regs->rsi = rsi;
    regs->rdx = rdx;

    if ((rc = ptrace(PTRACE_SETREGS, pid, NULL, regs)))
        rfail("Unable to set registers during syscall %lld", syscall_num);
    if ((rc = ptrace(PTRACE_CONT, pid, NULL, NULL)))
        rfail("Unable to continue during syscall %lld", syscall_num);
    waitpid(pid, NULL, 0);

    if ((rc = ptrace(PTRACE_GETREGS, pid, NULL, regs)))
        rfail("Unable to get registers during syscall %lld", syscall_num);

    if (regs->rax > -4096u)
        rfail("Syscall %lld error: %s", syscall_num, strerror(-regs->rax));

    return rc;
}

#endif // UTILS_OPERATIONS_H