#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main(){
  struct stat *s = NULL;
  int fd = stat("main.c", s);
  if (fd < 0){
    printf("error number %d: %s\n",errno,strerror(errno));
    return 0;
  }
  printf("File size:%ld\n",s->st_size);
  printf("File mode:%o\n",s->st_mode);
  printf("Last time this file was accessed:%s\n",ctime(s->st_atime));

  printf("Size in bytes:");

  return 0;
}
