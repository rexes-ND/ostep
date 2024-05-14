#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  /*
    e - An array of pointers to env vars is explicitly passed to the process
    l - Cmdline args are passed individually (a list) to the function
    p - Uses PATH env var to find the file named in the file arg to be executed
    v - Cmdline args are passed to the function as an array (vector) of
    pointers

    I think these variants exist for convenience.
  */
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    char *myargs[3];
    myargs[0] = strdup("ls");
    myargs[1] = strdup("-la");
    myargs[2] = NULL;

    // execvp(myargs[0], myargs);

    execv("/usr/bin/ls", myargs);

    // execlp("ls", "ls", "-la", NULL);

    // execl("/usr/bin/ls", "ls", "-la", NULL);
  } else {
    wait(NULL);
  }
  return 0;
}
