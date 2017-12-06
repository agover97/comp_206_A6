#ifndef SHARED_LIBS
    #define SHARED_LIBS
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include<sys/wait.h>
#endif

#ifndef CONS_HEAD
    #define CONS_HEAD
    #include "Consumer.h"
#endif

#ifndef PROD_HEAD
    #define PROD_HEAD
    #include "Producer.h"
#endif

/* Main function which initializes TURN.txt and forks the two children */
int main() {
    /* These ints will carry the pid numbers of the two children */
    int pidCons;
    int pidProd;

    /* Initializing TURN.txt to '0' (and then flushing init). Note Producer will act when c = '0', consumer when c = '1' */
    FILE *init = fopen("TURN.txt", "wt");
    fputc('0', init);
    fclose(init);

    switch( pidCons = fork() ) {
        case 0: /* This would be the consumer */
            puts("starting consumer");
            consumer();
            break;

        case -1: /* An error with forking to create the consumer process */
            printf("Something went wrong with the consumer");
            perror("fork_cons");
            exit(1);
            break;

        default:
            switch( pidProd = fork() ) {
                case 0: /* This would be the producer */
                    producer();
                    break;

                case -1: /* An error with forking to create the producer process */
                    printf("Something went wrong with the producer");
                    perror("fork_prod");
                    exit(1);
                    break;


                default:
                    /* The parent waits for the producer to finish, then it terminates (killing the consumer) */
                    wait(NULL); // pid_t waitpid (child_pid, &status, options);
                    // Use wait() instead?
            }
    }
    
    return 0;
}