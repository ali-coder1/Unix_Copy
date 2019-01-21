#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define K 1024



/*
 *
 * This main function copies files specified on the command line to the directory destination at
 * the end of the command line with open()/read()/write() system calls
 *
*/

int main (int argc, char *argv[]) { 

 char buf[K];


 if (argc > 3 ) {
 
 printf ("Usage: cp src dst\n");
 exit(0);
 }

 char *src = argv[1];
 char *dst = argv[2];

 int infd = open (src, O_RDONLY);

 if (infd < 0 ) {

 fprintf (stderr, "cp: Unable to open %s for copying.\n", src);
 exit(1);
 }

 char *new_path = (char *) malloc (1 + strlen(src) + strlen(dst) );


 if (new_path == NULL ) {
 
 fprintf (stderr, "Unable to allocate new memory. \n");
 exit(1);
 } 

 strcpy (new_path, dst);
 strcat (new_path, "/");
 strcat (new_path, src);



 int outfd = open (new_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);

 if (outfd < 0) {
 
 fprintf (stderr, "cp: Unable to create %s to copy to\n", dst);
 exit(1);
 }


 int reading;

 while ((reading = read(infd, buf, K)) > 0) {
  write(outfd, buf, reading);
 }



 close(infd);
 close(outfd);
 return 0;

}
