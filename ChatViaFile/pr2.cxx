#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXCHAR 1000

const char * LFILE = "/tmp/Chat.txt";
int pr1Id = 0;
bool pr1Idflag = false;

static void signal_catcher_2(int );
int main(int argc, char *argv[])
{

    if (signal(SIGUSR2, signal_catcher_2) == SIG_ERR){
        printf("Unable to create catcher for SIGUSR2\n");
    }
    printf("pid: %d\n", getpid() );
    while(1){
        pause();

            FILE *fpr;
            FILE *fpw;

            if(pr1Idflag == false){
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
                pr1Id = atoi(str);
                pr1Idflag = true;

                printf("pid_1: %d\n\n",pr1Id);
                //open file write the pid
                fpw = fopen(LFILE, "w+");
                fprintf(fpw, "%d", getpid());
                fclose(fpw);
                //send signal to pr1
                kill(pr1Id, SIGUSR1);
                continue;

            }
            //reading the file take it and print it on the screen
            fpr = fopen(LFILE, "r");
            if (fpr == NULL){
                continue;
            }

            char str[MAXCHAR];
            fgets(str, MAXCHAR, fpr);
            printf("Message received from %d: %s \n",pr1Id, str);

            //required to enter input from user
            char line[MAXCHAR];
            printf("Enter: ");
            fgets(line, sizeof line, stdin);

            //writing in the file
            fpw = fopen(LFILE, "w");
            fputs(line, fpw);
            fclose(fpw);
            //send signal to pr1
            kill(pr1Id, SIGUSR1);
            printf(">>>>>> Please wait for the other process <<<<<< \n\n");

    }

    return 0;
}
static void signal_catcher_2(int sig)
{
    if (sig == SIGUSR2)
        printf("received SIGUSR2\n");
}
