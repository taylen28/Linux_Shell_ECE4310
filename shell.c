/* This program is a simple linux shell that runs commands in the /usr/bin directory
    By Taylen, Andrew, and Joshua
    2 extra commands were added "exit" and "add"
*/
#include <stdio.h> //needed for printf, fgets, stdin
#include <unistd.h> //needed for fork, execv, _exit
#include <sys/wait.h> //needed for wait and waitpid
#include <string.h> //needed for all the string functions
#include <stdlib.h> //needed for atoi

/* FUNCTIONS USED
fgets: reads the line of text that we type in
strlen: returns the length of a string
strcmp: compares 2 different strings
strcat: concantenates a string onto another (ex. Hello and World become Hello World)
strtok: splits a string into pieces (tokens) using things like spaces
fork: creates a new process that is a duplicate of the current process
execv: replaces current process with new one, returns -1 if it cannot start it
waitpid: makes the parent wait for a child process to finish
*/

int main()
{   //vars
    char line[100]; //line that the user will type in
    char *args[10]; //array of argument pointers, used in execv

    //input
    printf("to add 2 numbers, type in [add x y]\n");
    while(1)
    {
        printf("Shell > "); //input line

        if(fgets(line,100,stdin) == NULL) //reads the line from stdin, returns NULL at the end of the file or an error
        {
            break;
        }
        line[strlen(line)-1] = '\0'; //removes the \n from fgets so a command like "exit" doesn't turn into "exit \n"
        
    //input logic
        int i = 0;
        args[i] = strtok(line," "); //gets the first token seperates it by finding spaces " "
        if (args[0] == NULL) { 
            continue; //allows shell to keep making a new "input line" if enter keeps getting hit
        }
        while(args[i] != NULL) //keeps going until the null pointer token from the last strtok is reached
        {
            ++i;
            args[i] = strtok(NULL," "); //gets the next token
        }
        /* 
        ex. if "ls -1" is typed,
        args[0] = ls (this is the process to run)
        args[1] = -1 (the argument passed into ls)
        args[2] = NULL (end of the argument list)
        */
        
        //exit command if "exit" is typed
        if(strcmp(args[0], "exit") == 0) //strcmp compares the input with "exit" to break out of shell 0 means they are the same
        {
            break;
        }
    
    //adding numbers custom command
        if (strcmp(args[0], "add") == 0) { //checks to see if "add" was typed
            if (args[1] == NULL || args[2] == NULL) { //checks if an invalid input like a space was given
                printf("wrong format entered: enter add x y (ex. add 1 2)\n");
                continue;
            }

            printf("%d\n", atoi(args[1]) + atoi(args[2])); //adds numbers together
            continue;
        }


    //Execution
        pid_t pid = fork(); //returns 0 in child, child PID in parent, -1 on error
        if(pid == 0)
        {
            char path[100] = "/usr/bin/"; //creates a path using usr/bin/command
            strcat(path, args[0]); //adds the command to the path
            execv(path, args); //replaces the child with the program in that path, returns -1 only if it fails to start

            printf("command not found\n"); //returns if execv fails
            _exit(1);
        }
        else
        {
            waitpid(pid,NULL,0); //wait for child to finish
        }

    //Delay
    }
    return 0;
    
}
