#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_PARAMETERS 10

void type_prompt() {
    printf("451sh> ");
}

void read_command(char *command, char **parameters) {
    char input[MAX_COMMAND_LENGTH];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < MAX_PARAMETERS) {
        parameters[i++] = token;
        token = strtok(NULL, " ");
    }
    parameters[i] = NULL;

    strcpy(command, parameters[0]); // First parameter is the command
}

int main() {
    while (1) {
        type_prompt();

        char command[MAX_COMMAND_LENGTH];
        char *parameters[MAX_PARAMETERS];
        read_command(command, parameters);

        int status;
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            if (strcmp(command, "pid") == 0) {
                printf("Shell PID: %d\n", getpid());
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(command,"pid")==0)
            {
            	printf("Shell parent PID: %d\n",getppid());
            	exit(EXIT_SUCCESS);
            	
            }

            // If the command doesn't contain a path, construct a path
            // by appending "/bin/" to the command to use the system's executables
            char path[MAX_COMMAND_LENGTH * 2]; // Increased size to avoid truncation
            if (command[0] != '/') {
                snprintf(path, sizeof(path), "/bin/%s", command);
            } 
            else 
            {
                strcpy(path, command);
            }

            execve(path, parameters, NULL);

            perror("Command execution failed");
            exit(EXIT_FAILURE);
        } else { 
        // Parent process
            waitpid(pid, &status, 0);
            
                
            }
        }
    

    return 0;
}

