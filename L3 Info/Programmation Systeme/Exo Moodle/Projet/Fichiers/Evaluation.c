#include "Evaluation.h"
#include "Shell.h"

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int redirectExpr(Expression *expr) {
    int input_backup = dup(STDIN_FILENO);
    int output_backup = dup(STDOUT_FILENO);
    int err_backup = dup(STDERR_FILENO);
    int filetype = expr->redirect.fd;
    if (expr->redirect.type == REDIR_IN) {
        if (!expr->redirect.toOtherFd) {
            expr->redirect.fd = open(expr->redirect.fileName, O_RDONLY);
            if (expr->redirect.fd == -1) {
                perror("open input");
                shellStatus = 1;
                exit(shellStatus);
            }
        }
    } else if(expr->redirect.type == REDIR_OUT) {
        if (!expr->redirect.toOtherFd) {
            expr->redirect.fd = open(expr->redirect.fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (expr->redirect.fd == -1) {
                perror("open output");
                shellStatus = 1;
                exit(shellStatus);
            } if (filetype == -1) {
                dup2(expr->redirect.fd, STDOUT_FILENO);
                filetype = STDERR_FILENO;
            }
        }
    } else if(expr->redirect.type == REDIR_APP) {
        if (!expr->redirect.toOtherFd) {
            expr->redirect.fd = open(expr->redirect.fileName, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (expr->redirect.fd == -1) {
                perror("open output append");
                shellStatus = 1;
                exit(shellStatus);
            }
        }
    } else {
        shellStatus = 1;
    }
    dup2(expr->redirect.fd, filetype);
    close(expr->redirect.fd);
    evaluateExpr(expr->left);
    dup2(input_backup, STDIN_FILENO);
    close(input_backup);
    dup2(output_backup, STDOUT_FILENO);
    close(output_backup);
    dup2(err_backup, STDERR_FILENO);
    close(err_backup);

    return shellStatus;
}

int simpleExpr(Expression *expr) {
    int status;
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        shellStatus = 1;
        exit(shellStatus);
    }

    if (pid == 0) {
        execvp(expr->argv[0], expr->argv);
        perror("exec");
        shellStatus = 1;
        exit(shellStatus);  
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            shellStatus = WEXITSTATUS(status);
        } if (WIFSIGNALED(status)) {
            shellStatus = 128 + WTERMSIG(status);
            if (shellStatus == 128) {
                shellStatus = 0;
            }
        }
    }
    return shellStatus;
}

int evaluateExpr(Expression *expr) {
    static int first = 1;
    
    if (first) {
        first = 0;
    }
    if (expr->type == ET_REDIRECT) {
        shellStatus = redirectExpr(expr);
    } else if (expr->type == ET_SIMPLE) {
        shellStatus = simpleExpr(expr);
    } else {
        shellStatus = shellStatus;
    }
    
    return shellStatus;
}
