#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_LEN 512

void handler(int signo)
{
    if (signo == SIGINT)
        printf("Don't try to kill this program with signal! You have 'exit' command!\n");
}

int main (int argc, char **argv)
{
    int nsec;
    int ctp[2], ptc[2];
    pid_t pid, ppid;
    char inbuf[MSG_LEN];
    static struct sigaction act;

    /* Signal Handling */
    /* Your Code */

    /* Pipe communications. */
    /* Your Code */

    switch (pid = fork()) {
        case -1:
            perror("fork call");
            exit(2);
        case 0:
            ppid = getppid();
            while(1) {
    		    fgets(inbuf, 512, stdin);
                cmd = strtok(inbuf, "\n");
                
            }
            break;
        default:
	    /* Signal Handling */
	    /* Your Code */

            while(1) {
	    	/* Your Code */
            }
            wait(NULL);
    }
    return 0;
}
