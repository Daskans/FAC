#include "Evaluation.h"
#include "Shell.h"

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void redirectExpr(Expression *expr) {
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
}

void simpleExpr(Expression *expr) {
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
}

void pipeExpr(Expression *expr) {
    int input_backup = dup(STDIN_FILENO);
    int output_backup = dup(STDOUT_FILENO);
    int err_backup = dup(STDERR_FILENO);
    int tube[2];
     if (pipe(tube) == -1) {
        perror("pipe");
        shellStatus = 1;
        exit(shellStatus);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        shellStatus = 1;
        exit(shellStatus);
    }

    if (pid == 0) {
        printf("left 1\n");
        close(tube[0]);
        printf("left 2\n");
        dup2(tube[1], STDOUT_FILENO);
        printf("left 3\n");
        close(tube[1]);
        fprintf(stdout,"left 4\n");
        evaluateExpr(expr->left);
        fprintf(stdout,"left error\n");
        
    } else {
        printf("right 1\n");
        wait(NULL);
        printf("right 2\n");
        dup2(output_backup, STDOUT_FILENO);
        close(output_backup);
        close(tube[1]);
        printf("right 3\n");
        dup2(tube[0], STDIN_FILENO);
        printf("right 4\n");
        close(tube[0]);
        printf("right 5\n");
        evaluateExpr(expr->right);
        printf("right error\n");
    }
    dup2(input_backup, STDIN_FILENO);
    close(input_backup);
    dup2(output_backup, STDOUT_FILENO);
    close(output_backup);
    dup2(err_backup, STDERR_FILENO);
    close(err_backup);
}

int evaluateExpr(Expression *expr) {
    static int first = 1;
    
    if (first) {
        first = 0;
    }
    switch (expr->type) {
        case ET_SIMPLE:
            simpleExpr(expr);
            break;
        case ET_REDIRECT:
            redirectExpr(expr);
            break;
        case ET_SEQUENCE:
            evaluateExpr(expr->left);
            evaluateExpr(expr->right);
            break;
        case ET_SEQUENCE_AND:
            evaluateExpr(expr->left);
            if (shellStatus == 0) {
                evaluateExpr(expr->right);
            }
            break;
        case ET_SEQUENCE_OR:
            evaluateExpr(expr->left);
            if (shellStatus != 0) {
                evaluateExpr(expr->right);
            }
            break;
        case ET_PIPE:
            pipeExpr(expr);
            break;
        default:
            break;
    }
    
    return shellStatus;
}
