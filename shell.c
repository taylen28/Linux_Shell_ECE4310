#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main()
{   //vars
    char line[100];
    char *args[10];
    //input
    while(1)
    {
        printf("Shell > ");

        if(fgets(line,100,stdin) == NULL)
        {
            break;
        }
        line[strlen(line)-1] = '\0'; //removes the \n
        
    //input logic
        int i = 0;
        args[i] = strtok(line," ");
        while(args[i] != NULL)
        {
            ++i;
            args[i] = strtok(NULL," ");
        }
        
        //exit command
        if(strcmp(args[0], "exit") == 0)
        {
            break;
        }
    


    //Execution
        pid_t pid = fork();
        if(pid == 0)
        {
            char path[100] = "/usr/bin/";
            strcat(path, args[0]);
            execv(path, args);

            printf("command not found\n");
            _exit(1);
        }
        else
        {
            waitpid(pid,NULL,0);
        }

    //Delay
    }
    return 0;
    
}