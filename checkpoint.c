/*
    File: checkpoint.c
    Author: RPSB
    this file creates a checkpoint for the running c program 
*/
#include <stdio.h>
#include "signalHandler.c"
#include "memory.c"
//#include "context.c""

int init_chkpnt(char filename[100]){
    init_proc_maps(filename);
}
