// Tyler Schnitzer . Rec 6 . CSCE3600.201
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) 
{
	pid_t pid;
	char *name;
	
	pid=fork();
	if (pid == 0)
	{
		printf("\nchild:%d\n",getpid());
		printf("child:...\n");
		sleep(25);
		printf("child has woke up\n");
		
	}
	else if(pid > 0)
	{
		printf("parent:%d",getpid());
	}
	else
		perror("fork error");
	
	name=(pid==0)?"child":"parent";
	printf("%s is terminating...",name);
	return 0;
}