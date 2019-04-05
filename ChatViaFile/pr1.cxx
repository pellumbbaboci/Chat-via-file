#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXCHAR 1000

const char * LFILE = "/tmp/Chat.txt";
int pr2Id = 0;
bool pr2Idflag = false;

static void signal_catcher_1(int );
int main(int argc, char *argv[])
{

    if (signal(SIGUSR1, signal_catcher_1) == SIG_ERR){
        printf("Unable to create catcher for SIGUSR1\n");
    }
    printf("pid: %d\n", getpid() );
    while(1){
        pause();

            FILE *fpr;
            FILE *fpw;

            if(pr2Idflag == false){
                //open file if null write the pid
                fpr = fopen(LFILE, "r");
                if (fpr == NULL){
                    fpw = fopen(LFILE, "w+");
                    fprintf(fpw, "%d", getpid());
                    fclose(fpw);
                    continue;
                }
                //if not null read the content and store the id in pr2Id
                char str[MAXCHAR];
                fgets(str, MAXCHAR, fpr);
                pr2Id = atoi(str);
                pr2Idflag = true;

                printf("pid_2: %d\n\n",pr2Id);
                //open file write the pid
                fpw = fopen(LFILE, "w+");
                fprintf(fpw, "%d", getpid());
                fclose(fpw);
                //send signal to pr2
                kill(pr2Id, SIGUSR2);
                continue;

            }
            //reading the file take it and print it on the screen
            fpr = fopen(LFILE, "r");
            if (fpr == NULL){
                continue;
            }

            char str[MAXCHAR];
            fgets(str, MAXCHAR, fpr);
            printf("Message received from %d: %s \n",pr2Id, str);

            //required to enter input from user
            char line[MAXCHAR];
            printf("Enter: ");
            fgets(line, sizeof line, stdin);

            //writing in the file
            fpw = fopen(LFILE, "w");
            fputs(line, fpw);
            fclose(fpw);
            //send signal to pr2
            kill(pr2Id, SIGUSR2);
            printf(">>>>>> Please wait for the other process <<<<<< \n\n");

    }

    return 0;
}
static void signal_catcher_1(int sig)
{
    if (sig == SIGUSR1)
        printf("received SIGUSR1\n");
}
