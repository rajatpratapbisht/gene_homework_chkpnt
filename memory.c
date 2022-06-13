/*
    File: memory.c
    Author: RPSB
    this file reads, svaes and restores memory of our c program
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//##########################################################
// defining all the macros
#define NAME_LEN 80

//##########################################################
// creating a constructor capable of reading memory
struct proc_maps_line {
    void *start_adr;
    void *end_adr;
    char rwxp[4];
    char name[NAME_LEN];

};


//###########################################################
// This functions reads from proc/self/maps 
// using our constructor
int read_proc_maps (int proc_maps_fd, struct proc_maps_line *proc_maps_line, char *filename){

    unsigned long start, end;
    char rwxp[4];
    char tmp[10]

}

//###########################################################
// This functions opens file proc/self/maps 
// and calls read_proc_maps to read data 
int open_proc_maps( struct proc_maps_line proc_maps[]) {
    
    int proc_maps_fd = open("/proc/self/maps", O_RDONLY);
    
    char filename[100];    //for debugging
    int i = 0;
    int rc = -2;           // any value that doesn't terminate for loop

    for (i = 0; rc != EOF; i++) {
        rc = read_proc_maps(proc_maps_fd , &proc_maps[i], filename);
    }
    
    close(proc_maps_fd);
    return 0;
}

//##########################################################
// This functions writes into "chkpt_img.dat"
// file using our constructor
int write_proc_maps(){

}

//##########################################################
// This functions reads from "chkpt_img.dat" file
// using our constructor and writes it into our
// /proc/self/maps file
int restore_proc_maps(){

}