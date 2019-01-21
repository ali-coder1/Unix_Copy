#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define K	1024

/**
 * cp source destination
 */
int main(int argc, char *argv[])
{
  char buf[K];
  int r;

  if (argc < 3) {
    printf("Usage: cp src dst\n");
    exit(0);
  }
  char *src = argv[1];
  char *dst = argv[2];
  
  int infd = open(src, O_RDONLY);
  if (infd < 0) {
    fprintf(stderr,"cp: Unable to open %s for copying.\n", src);
    exit(1);
  }
  int outfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (outfd < 0) {
    fprintf(stderr,"cp: Unable to create %s to copy to.\n", dst);
    exit(1);
  }
  while((r = read(infd, buf, K)) > 0) {
    write(outfd, buf, r);
  }
  close(infd);
  close(outfd);
  return 0;
}
