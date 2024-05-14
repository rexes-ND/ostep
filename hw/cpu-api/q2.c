#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  /*
    Both parent and child can access the file descriptor.
    However, there seems to be no guarentee on ordering of write to the fd.
  */
  int fd = open("./q2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  if (fd < 0) {
    fprintf(stderr, "open failed\n");
    exit(1);
  }
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    assert(write(fd, "1", 1) == 1);
    assert(write(fd, "2", 1) == 1);
    assert(write(fd, "3", 1) == 1);
    assert(write(fd, "4", 1) == 1);
  } else {
    assert(write(fd, "5", 1) == 1);
    assert(write(fd, "6", 1) == 1);
    sleep(1);
    assert(write(fd, "7", 1) == 1);
    assert(write(fd, "8", 1) == 1);
  }
  return 0;
}
