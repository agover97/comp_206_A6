#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void producer(void){
    FILE *mydata = fopen(MYDATA.txt, "rt");
    FILE *turn = NULL;
    int c;
    //the while loop goes forever until
    //we reach the end of file which causes the break
    while (1) {
        //will wait forever until turn can be read
        while((turn=fopen("TURN.txt",r))==NULL);
        //if its producer's turn continue
        if(fgetc(turn)==1){
            //scenario 1: it is producer's turn: must close turn
            fclose(turn);
            c = fgetc(mydata);
            if (feof(mydata)) {
                break;
            }
            FILE *data = fopen("DATA.txt", "wt");
            fprintf(data, "%c",c);
            fclose(data);
            //now its the consumer's turn
            FILE *newTurn = fopen("TURN.txt", "wt");
            fputc('1', newTurn);
            fclose(newTurn);
        }
        //scenario 2: not proudcers turn, but still must close turn
        //this is because in order for it to eventually become
        //producer's turn, consumer must write to turn
        //so we cant just leave it open
        else{
            fclose(turn);
        }
        
    }
}