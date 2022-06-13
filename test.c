/*
*   File: test.c
*   Author: RPSB
*   this file is a simple counter program that counts from 1-100000
*/

#include <stdio.h>
#include "checkpoint.c"

int main() {

    long int count = 0;

    if (signal(SIGINT, sigHandler) == SIG_ERR){
        printf ( "SIGNAL ERROR FOUND \n" );
    }
    while(count < 100000){
        printf("%ld \n" , count);
        count++;

        if (sigEncounter){
            printf ( "\nStarting checkpointing sequence...\n\n" );
            return 1;
        }

    }

    return 0;
}