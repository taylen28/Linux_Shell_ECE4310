/*
    This program demonstrates the use of fork() system call to create a child process. 
    The child process will print its own process ID and its parent's process ID, 
    while the parent process will wait for the child process to finish before printing
    its own process ID and its parent's process ID.
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int fork_pid;
    int myID;
    int myParentID;
    int state;

    printf("\n\nSTART\n");
    printf("\n\n");

    //create a child process using fork() system call
    fork_pid = fork();
    switch(fork_pid)
    {
        case 0:
            // this block of code will be executed by the child process
            myID = getpid();
            myParentID= getppid();
            
            printf("\n[ForkPID printed from the child or subprocess= %d; myID = %d; myParentID = %d]\n", fork_pid, myID, myParentID);
            /*execute the ls command in the child process (Use which ls command to find 
            the path of the ls command in your system)
            */
            execl("/usr/bin/ls","/usr/bin/ls", (char *) NULL);
            break;

        case -1:
            // this block of code will be executed if the fork() system call fails
            printf("\n[ForkPID printed from the main process/ parent %d]\n", fork_pid);
            break;

        default:
            // this block of code will be executed by the parent process
            myID = getpid();
            myParentID= getppid();

            // wait for the child process to finish before printing the message from the parent process
            waitpid(fork_pid,&state, 0);
            printf("\n[ForkPID printed from the main process/ parent %d; myID = %d; myParentID = %d]\n", fork_pid, myID, myParentID);
            break;
    }
    printf("\n\n");
    


    return 0;
}