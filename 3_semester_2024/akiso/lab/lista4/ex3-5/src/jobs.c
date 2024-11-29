#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include <jobs.h>

static job_t *job_list_head = NULL;

// Cleanup job manager resources
void job_manager_cleanup(void) {
    job_t *current = job_list_head;
    job_t *next;
    
    while (current) {
        next = current->next;
        free(current->command);
        free(current);
        current = next;
    }
}

// Add a job to the job list
int job_add(pid_t pid, const char *command) {
    job_t *new_job = (job_t *)malloc(sizeof(job_t));
    if (!new_job) {
        perror("malloc");
        return -1;
    }
    new_job->pid = pid;
    new_job->state = RUNNING;
    new_job->command = strdup(command);
    new_job->next = job_list_head;
    job_list_head = new_job;
    return 0;
}

// Bring a job to the foreground
int job_fg(pid_t pid) {
    job_t *job = job_list_head;
    while (job && job->pid != pid) {
        job = job->next;
    }

    if (!job) {
        fprintf(stderr, "Job not found\n");
        return -1;
    }

    if (job->state == STOPPED) {
        job->state = RUNNING;
        kill(pid, SIGCONT); // Resume the job
    }

    waitpid(pid, NULL, WUNTRACED); // Wait for the job to terminate or stop
    return 0;
}

// Send a job to the background
int job_bg(pid_t pid) {
    job_t *job = job_list_head;
    while (job && job->pid != pid) {
        job = job->next;
    }

    if (!job) {
        printf("bg: Job not found\n");
        return -1;
    }

    if (job->state == STOPPED) {
        job->state = RUNNING;
        kill(pid, SIGCONT); // Resume the job in the background
    }

    return 0;
}

// Suspend a job (send SIGTSTP)
int job_suspend(pid_t pid) {
    job_t *job = job_list_head;
    while (job && job->pid != pid) {
        job = job->next;
    }

    if (!job) {
        return -1;
    }

    if (job->state == RUNNING) {
        job->state = STOPPED;
        kill(pid, SIGSTOP); // Stop the job
    }

    return 0;
}

// Resume a stopped job
int job_resume(pid_t pid) {
    job_t *job = job_list_head;
    while (job && job->pid != pid) {
        job = job->next;
    }

    if (!job) {
        return -1;
    }

    if (job->state == STOPPED) {
        job->state = RUNNING;
        kill(pid, SIGCONT); // Resume the job
    }

    return 0;
}

// Remove a job from the list
int job_remove(pid_t pid) {
    job_t **job = &job_list_head;
    while (*job && (*job)->pid != pid) {
        job = &(*job)->next;
    }

    if (!*job) {
        return -1;
    }

    job_t *to_remove = *job;
    *job = (*job)->next;
    free(to_remove->command);
    free(to_remove);
    return 0;
}

// List all jobs
void job_list(void) {
    job_t *current = job_list_head;
    while (current) {
        const char *state_str = (current->state == RUNNING) ? "RUNNING" : (current->state == STOPPED) ? "STOPPED" : "COMPLETED";
        printf("PID: %d, State: %s, Command: %s\n", current->pid, state_str, current->command);
        current = current->next;
    }
}