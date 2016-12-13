/*
 * 2016 Mahdi-Robatipoor <mahdi.robatipoor@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>//umask
#include <sys/stat.h>//umask

int change_task_to_background() {

    pid_t child_pid, sid;

    child_pid = fork();
    if (child_pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (child_pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        perror("Can't create new sid");
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
        perror("Can't change to the root directory");
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    return 0;

}



