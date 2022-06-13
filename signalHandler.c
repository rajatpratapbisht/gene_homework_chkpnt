/*
  File: signalHandler.c
  Author: RPSB 
  handler functions for signal.h
*/
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>


bool sigEncounter = 0;      //if signal is encountered the value becomes true

// signalHandler takes signo- signal number into the target function where it defines as to what to do after
//   signal is encountered
void sigHandler ( int signo ) {
    if ( signo == SIGINT ) {
        printf ( "Signal interrupt encountered \n" );
        sigEncounter = 1;
    }
}
////////////////////////////////////////////////////
