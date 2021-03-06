#include "Producer.h"

void producer(void){
    FILE *mydata = fopen("mydata.txt", "rt");
    FILE *turn = NULL;
    int c;
    //the while loop goes forever until
    //we reach the end of file which causes the break
    while (1) {
        //will wait forever until turn can be read
        while((turn=fopen("TURN.txt","r+"))==NULL);
        //if its producer's turn continue
        if(fgetc(turn) == '0'){
            //scenario 1: it is producer's turn: must close turn
            //fclose(turn);
            c = fgetc(mydata);
            if (feof(mydata)) {
                // change to a 1
                fseek(turn, 0, SEEK_SET);
                fputc('1', turn);
                fclose(turn);
                // write the eof for consumer
                FILE *data = fopen("DATA.txt", "wt");
                fprintf(data, "%c",c);
                fclose(data);
                break;
            }
            FILE *data = fopen("DATA.txt", "wt");
            fprintf(data, "%c",c);
            fclose(data);
            //now its the consumer's turn
            fseek(turn, 0, SEEK_SET);
            fputc('1', turn);
            fclose(turn);
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