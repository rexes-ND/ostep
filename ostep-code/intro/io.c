#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /*
      O_WRONLY: write only
      O_CREAT: create file if it doesn't exist
      O_TRUNC: truncate file to 0 bytes if it exists

      S_IRUSR: user has read permission
      S_IWUSR: user has write permission
  */
  int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  assert(fd >= 0);
  char buffer[20];
  sprintf(buffer, "hello world\n");
  int rc = write(fd, buffer, strlen(buffer));
  assert(rc == (strlen(buffer)));
  fsync(fd);
  close(fd);
  return 0;
}
