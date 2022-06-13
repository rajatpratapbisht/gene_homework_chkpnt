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
#include <assert.h>

//##########################################################
// defining all the macros
#define NAME_LEN 80

//##########################################################
// creating a constructor capable of reading memory
struct proc_maps_line {
    void *start;
    void *end;
    char rwxp[4];
    char name[NAME_LEN];

};


//###########################################################
// This functions reads from proc/self/maps 
// using our constructor
int read_proc_maps (int proc_maps_fd, struct proc_maps_line *proc_maps_line, char *filename){

    unsigned long int start, end;
  char rwxp[4];
  char tmp[10];
  int tmp_stdin = dup(0); // Make a copy of stdin
  dup2(proc_maps_fd, 0); // Duplicate proc_maps_fd to stain
  // scanf() reads stdin (fd:0). It's a dup of proc_maps_fd ('same struct file').
  int rc = scanf("%lx-%lx %4c %*s %*s %*[0-9 ]%[^\n]\n",
                 &start, &end, rwxp, filename);
  // fseek() removes the EOF indicator on stdin for any future calls to scanf().
  assert(fseek(stdin, 0, SEEK_CUR) == 0);
  dup2(tmp_stdin, 0); // Restore original stdin; proc_maps_fd offset was advanced.
  close(tmp_stdin);
  if (rc == EOF || rc == 0) { 
    proc_maps_line -> start = NULL;
    proc_maps_line -> end = NULL;
    return EOF;
  }
  if (rc == 3) { // if no filename on /proc/self/maps line:
    strncpy(proc_maps_line -> name,
            "ANONYMOUS_SEGMENT", strlen("ANONYMOUS_SEGMENT")+1);
  } else {
    assert( rc == 4 );
    strncpy(proc_maps_line -> name, filename, NAME_LEN-1);
    proc_maps_line->name[NAME_LEN-1] = '\0';
  }
  proc_maps_line -> start = (void *)start;
  proc_maps_line -> end = (void *)end;
  memcpy(proc_maps_line->rwxp, rwxp, 4);
  return 0;

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

//##########################################################
// This functions intiates memory checkpointing process
int init_proc_maps(char filename[100]){
    
    struct proc_maps_line proc_maps[1000];
    assert( open_proc_maps(proc_maps) == 0 );
    // We purposely call proc_self_maps twice.  'scanf()' might call mmap()
    //   during the first execution, above.  But it doesn't need to map
    //   in a second memory segment after that.  It just re-uses the original one.
    assert( open_proc_maps(proc_maps) == 0 );
    printf("    *** Memory segments of %s ***\n", filename);
    int i = 0;
    for (i = 0; proc_maps[i].start != NULL; i++) {
    /* printf("%s (%c%c%c)\t\t"
        "  Address-range: %p - %p\n",
           proc_maps[i].name,
           proc_maps[i].rwxp[0], proc_maps[i].rwxp[1], proc_maps[i].rwxp[2],
           proc_maps[i].start, proc_maps[i].end);
    */   printf("Address-range: %p - %p\t (%c%c%c)\t\t %s\n ",
           proc_maps[i].start, proc_maps[i].end,
           proc_maps[i].rwxp[0], proc_maps[i].rwxp[1], proc_maps[i].rwxp[2],
           proc_maps[i].name);
  
    }
    return 0;
}