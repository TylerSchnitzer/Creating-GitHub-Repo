#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{ int fd[3][2];

  char *commandline = args;
  char **lsh_split_line(char *line);

  for (int i=0; i < 3; i++)
  {
    if (pipe(fd[i]) < 0)
    {
      printf("Error with exit pipe()\n");
      return 1;
    }
  }
  
  int pid1 = fork();
  if (pid1 < 0){
    return 1;
  }

  if (pid1 == 0){
    //Child Process 1
    close(fd[0][1]);
    close(fd[1][0]);
    close(fd[2][0]);
    close(fd[2][1]);
    int x;
    if (read(fd[0][0], &args, sizeof(int)) < 0){
      return 1; 
    }
    
    if (write(fd[1][1], &x, sizeof(int)) < 0){
      return 1;
    }
    close(fd[0][0]);
    close(fd[1][1]);
    return 0; 
  }

  int pid2 = fork();
  if (pid2 < 0){
    return 1;
  }

  if (pid2 == 0){
    //Child process 2
    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][1]);
    close(fd[2][0]);
    int x;
    if (read(fd[1][0], &x, sizeof(int)) < 0){
      return 1; 
    }
    x += 5;
    if (write(fd[2][1], &x, sizeof(int)) < 0){
      return 1;
    }
    close(fd[1][0]);
    close(fd[2][1]);
    return 0;
  }
  //Parent process
  close(fd[0][0]);
  close(fd[1][0]);
  close(fd[1][1]);
  close(fd[2][1]);
  int x = 0;
  if (write(fd[0][1], &x, sizeof(int)) < 0){
    return 1;
  }
  if (read(fd[2][0], &x, sizeof(int)) < 0){
    return 1;
  }
  //printf("Result is %d\n", x);
  //printf("%s\n", line);
  close(fd[0][1]);
  close(fd[2][0]);

  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
