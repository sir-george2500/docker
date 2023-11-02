#include <stdio.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <unistd.h>

// Usage: your_docker.sh run <image> <command> <arg1> <arg2> ...

int main(int argc, char *argv[]) {

  int pipe_stdout_c2p[2];

  int pipe_stderr_c2p[2];
  
  char *command = argv[3];

  int child_pid = fork();

  if (child_pid == -1) {

    printf("Error forking!");

    return 1;

  }

  if (pipe(pipe_stdout_c2p)) {

    fprintf(stderr, "Couldn't create child to parent pipe for stdout");

    return EXIT_FAILURE;

  }

  if (pipe(pipe_stderr_c2p)) {

    fprintf(stderr, "Couldn't create child to parent pipe for stderr");

    return EXIT_FAILURE;

  }

  // Disable output buffering

  setbuf(stdout, NULL);

  // You can use print statements as follows for debugging, they'll be visible

  // when running tests.


  // Uncomment this block to pass the first stage

  //


  if (child_pid == 0) {

    // Replace current program with calling program

    dup2(STDOUT_FILENO, pipe_stdout_c2p[0]);

    dup2(STDOUT_FILENO, pipe_stderr_c2p[0]);

    close(pipe_stdout_c2p[1]);

    close(pipe_stderr_c2p[1]);

    execv(command, &argv[3]);

  } else {

    // We're in parent

    close(pipe_stdout_c2p[0]);

    close(pipe_stderr_c2p[0]);

    dup2(STDIN_FILENO, pipe_stdout_c2p[1]);

    dup2(STDIN_FILENO, pipe_stderr_c2p[1]);

    wait(NULL);



  }

  return 0;

}
