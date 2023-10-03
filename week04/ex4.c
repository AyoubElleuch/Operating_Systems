#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char commands[100];
    char *arguments[10];
    int bg = 0;

    while (true) {
        printf("Shell> ");
        fgets(commands, sizeof(commands), stdin);
        commands[strcspn(commands, "\n")] = '\0';


        if (commands[strlen(commands) - 1]=='&') {
            bg = 1;
            commands[strlen(commands) - 1]='\0';
        } else {
            bg = 0;
        }

        char *token = strtok(commands, " ");
        int count = 0;
        while (token != NULL && count < 10) {
            arguments[count] = token;
            token = strtok(NULL, " ");
            count++;
        }
        arguments[count] = NULL;
        
        pid_t pid = fork();

        if (pid < 0) {
            printf("Failed fork.\n");
            return 1;
        } else if (pid == 0) {
            execvp(arguments[0], arguments);

            printf("Error in the command.\n");
            exit(1);
        } else {
            if (!bg) {
                wait(NULL);
            }
        }
    }

    return 0;
}
