/*
    Rafał Włodarczyk
    Redirect the standard output of a process to a file.
*/

#ifndef UTILS_REDIRECT_H
#define UTILS_REDIRECT_H

#include <sys/user.h>

#include "macros.h"
#include "ptrace.h"
#include "operations.h"

#define SYSCALL_OPEN 2
#define SYSCALL_CLOSE 3
#define SYSCALL_DUP2 33

/*
    Redirect the standard output of the process with the specified PID to the file specified by outpath.

    Function performs the following steps:
    1. Attach to the process
    2. Read the registers of the process
    3. Backup the memory at the instruction pointer
    4. Insert a syscall with a breakpoint at the instruction pointer
    5. Perform the open syscall
    6. Perform the dup2 syscall
    7. Perform the close syscall
    8. Restore the memory at the instruction pointer
    9. Restore the registers
    10. Detach from the process

    Each step is performed with error checking, thus any irregularities will cause the whole function to fail.

    @param pid - PID of the process
    @param fd - File descriptor to be redirected
    @param outpath - Path to the file to redirect the file descriptor to
*/
int redirect(pid_t pid, int fd, const char *outpath)
{
    struct user_regs_struct regs, oldregs;
    size_t size = calculate_backup_size(outpath);
    void *backup, *rip_address = NULL;
    size_t outpath_len = strlen(outpath) + 1;

    if (putils_attach(pid))
        rfail("Unable to attach to process %d", pid);
    rinfo("Attached to process %d", pid);

    if (putils_get_registers(pid, &regs))
        rfail("Unable to read registers from process %d", pid);
    rinfo("Read the registers and the instruction pointer: %llu", regs.rip);

    rip_address = (void *)regs.rip;
    backup = malloc(size);

    putils_get_data(pid, rip_address, backup, size);
    rinfo("Memory at register instruction pointer of size %zu backed up", size);

    insert_syscall_with_breakpoint(pid, rip_address, outpath, outpath_len);
    rinfo("Syscall with breakpoint inserted");

    memcpy(&oldregs, &regs, sizeof(regs));
    rinfo("Registers copied");

    int rc; // Return code
    void *instruction_rip_address = (void *)((u128int_t)rip_address + outpath_len);

    /* Open syscall */
    rc = perform_syscall(pid, &regs, SYSCALL_OPEN, (u128int_t)rip_address, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO, instruction_rip_address);
    rinfo("Perform SYSCALL_OPEN, result = %d, rax = %llu", rc, regs.rax);

    /* dup2 syscall */
    rc = perform_syscall(pid, &regs, SYSCALL_DUP2, regs.rax, fd, 0, instruction_rip_address);
    rinfo("Perform SYSCALL_DUP2, result: %d, rax = %llu", rc, regs.rax);

    /* close syscall */
    rc = perform_syscall(pid, &regs, SYSCALL_CLOSE, regs.rdi, 0, 0, instruction_rip_address);
    rinfo("Perform SYSCALL_CLOSE, result: %d, rax = %llu", rc, regs.rax);

    putils_push_data(pid, rip_address, backup, size);
    rinfo("Memory at register instruction pointer restored");

    free(backup);

    if (ptrace(PTRACE_SETREGS, pid, NULL, &oldregs))
        rfail("Unable to restore registers");
    rinfo("Registers reset");

    if (putils_detach(pid))
        rfail("Unable to detach from process %d", pid);
    rinfo("Detached from process %d", pid);

    rinfo("Operation completed successfully");
    return 0;
}

#endif // UTILS_REDIRECT_H