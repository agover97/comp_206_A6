#ifndef CONS_HEAD
    #define CONS_HEAD
    #include "Consumer.h"
#endif

/* This function will run until the parent terminates (due to the waitpid command) */
void consumer(void) {
    char c;
    int position;
    /* We create two file pointers, one to check TURN.txt, one to read from DATA*/
    FILE *checker = NULL;
    FILE *reader = NULL;
    
    /* Effectively running forever (until parent kills it) */
    while (1) {
        /* Busy wait until TURN.txt is readable and == 1 (signalling consumer) */
        while ((checker = fopen("TURN.txt", "r+")) == NULL);
        if (fgetc(checker) == '0') continue;

        /* Using the two fpointers, will 'fseek' to the pos-th character, read it, then write a '1' at SEEK_SET of TURN.txt */
        reader = fopen("DATA.txt", "rt");
        fseek(reader, position, SEEK_SET);
        c = fgetc(reader);
        if(feof(reader)) break; /* Quit the while loop if we've reached the end */
        fseek(checker, 0, SEEK_SET);
        fputc('0', checker);
        fclose(checker);
        fclose(reader);

        /* Print c to console, increment pos then continue the loop */
        printf("%c", c);
        position++;
    }
}