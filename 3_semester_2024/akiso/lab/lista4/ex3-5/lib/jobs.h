#ifndef LSH_LIB_JOBS
#define LSH_LIB_JOBS

#include <sys/types.h>
#include <unistd.h>

// Define job states
typedef enum {
    RUNNING,
    STOPPED,
    COMPLETED
} job_state_t;

// Define job struct
typedef struct job {
    pid_t pid;            // Process ID
    job_state_t state;    // State of the job (RUNNING, STOPPED, COMPLETED)
    char *command;        // Command associated with the job
    struct job *next;     // Pointer to the next job
} job_t;

// Job manager functions
void job_manager_cleanup(void);
int job_add(pid_t pid, const char *command);
int job_bg(pid_t pid);
int job_fg(pid_t pid);
int job_suspend(pid_t pid);
int job_resume(pid_t pid);
int job_remove(pid_t pid);
void job_list(void);

#endif // LSH_LIB_JOBS
