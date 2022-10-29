#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <time.h>
#include <fcntl.h>
#define stack_max_buff 32
#define history_max_buff 32
#define alias_max_buff 32
#define wild_card_buff 100
#define BUF_MAX 300
char *stack[stack_max_buff];
int stack_number = 0;
int history_number = 0;  
int alias_number = 0;
char history_command[history_max_buff][10];
char prompt_name[15] = "command";
struct Alias{
	int index;
	char new_name[10];
	char original_name[10];
}alias[alias_max_buff];


//char *history[history_max_buff];    // declare storage for history
//int history_number = 0;		// history counter


//Function Declarations for builtin shell commands:
 int _cd(char **args);
int _help(char **args);
int _exit(char **args);
int _pushd(char **args);
int _popd(char **args);
int _dirs(char **args);
int _history(char **args);
int _prompt(char **args);
int _alias(char **args);
int _unalias(char **args);
int _push(char **args);
int test(char **args);

//List of builtin commands, followed by their corresponding functions.
 char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "dirs",
  "history",
  "prompt",
  "pushd",
  "popd",
  "alias",
  "unalias",
  "push",
  "test"
};

//reference to functions in builtin_func[] array
int (*builtin_func[]) (char **) = {
  &_cd,
  &_help,
  &_exit,
  &_dirs,
  &_history,
  &_prompt,
  &_pushd,
  &_popd,
  &_alias,
  &_unalias,
  &_push,
  &test
};

//from Nuper

int pathcmd()
{
  pid_t pid = fork( );

  if( pid == 0 )
  {
    // Notice you can add as many NULLs on the end as you want
    int ret = execl( "/bin/ls", "ls", "-a", "-l", "-t", NULL, NULL, NULL, NULL );  
  
    if( ret == -1 )
    {
      perror("execl failed: ");
    }
  }
  else 
  {
    int status;
    wait( & status );
  }

  return 0;
}

//start of built in functions
int _num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
 
//from Khari
/*
int _cd(char **args)
{
  if (args[1] == NULL) {
  	//printf("NULL\n");
  	chdir("/home/");
    //fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}
*/

int cd_command(char **args){

int cd(char *pathGiven);
int thisPrex(char const *, char const *);

   //buffer to store user input
char str[BUF_MAX];
//shown before input taken each time
char *promptShown = "USER_NAME>";
//token
char *token;
token = strtok(str," ");
//loop t take input
while(str != NULL){
//empty
bzero(str, BUF_MAX);
//this prints prompt rst each time
printf("%s",promptShown);
//this gets user input in str buffer
fgets(str, BUF_MAX, stdin);
//this checks for cd
if(thisPrex(str,"cd") == 0){
// this checks the path for cd command
token = strchr(str,' ');
//this parses the parameter to cd command
if(token) {
char *tempToken = token + 1;
token = tempToken;
char *Location_NewLine = strchr(token, '\n');
if(Location_NewLine) {
*Location_NewLine = '\0';
}

cd(token);
}
}
}
//return
return 0;
}
//this checks whether q is present in p or not as a prex
int thisPrex(char const *p, char const *q)
{
int i = 0;
for(i = 0;q[i];i++)
{
if(p[i] != q[i])
return -1;
}
return 0;
}
// user cd command
int cd(char *pth){
char path[BUF_MAX];
strcpy(path,pth);
char cwd[BUF_MAX];
if(pth[0] != '/'){
// its now true for the dir in current working directory
getcwd(cwd,sizeof(cwd));
strcat(cwd,"/");
strcat(cwd,path);
chdir(cwd);
}else{
chdir(pth);
}
return 0;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int _help(char **args)
{
  int i;
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < _num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

  /* dirs function */
int _dirs(char **args){
	int i=0;
	while(stack[i]!=NULL){
	printf("%d  %s\n",i,stack[i]);
	i++;
	}
	printf("\n");
	return 1;
}

  /* pushd functopn */
int _pushd(char **args){
	//printf("***** pushd function *****\n");
	stack[stack_number] = getcwd(NULL,0);
	//printf("dir has been saved, stack[%d] = %s\n",stack_number,stack[stack_number]);
	stack_number ++;
	return 1;
}
 
  /* popd functopn */
int _popd(char **args){
	//printf("***** popd function *****\n");
	stack_number--;
	stack[stack_number] = NULL;
	//printf("the dir has been removed\n");
}

int _push(char **args){
	//printf("push func!\n");
	//printf("push to %s\n",stack[atoi(args[1])]);
	chdir(stack[atoi(args[1])]);
	return 1;
}

	/* alias function*/
int _alias(char **args){
	//printf("before: args[1] = %s, args[2] = %s\n",args[1],args[2]);
	if(args[1]==NULL){
			//printf("All alias commands : \n");	
			for(int i=0;i<alias_number;i++){
				//printf("%s  %s\n",alias[i].new_name,alias[i].original_name);
			}	
			return 1;
	}
	//printf("***** alias function ****\n");
	alias[alias_number].index = alias_number;
	strcpy(alias[alias_number].new_name,args[1]);
	strcpy(alias[alias_number].original_name,args[2]);
	//printf("new command name has been saved!\n");
	//printf("alias[%d]: %s = %s\n",alias[alias_number].index,alias[alias_number].new_name,alias[alias_number].original_name);
	alias_number++;
	//printf("after free : args[1] = %d, args[2] = %d\n",args[1],args[2]);
	//printf("alias number = %d\n",alias_number);
	return 1;
}

	/* unalias function */
int _unalias(char **args){
	for(int i=0;i<alias_number;i++){
		if(strcmp(args[1],alias[i].new_name)==0){
			strcpy(alias[i].new_name,"");
			//printf("alias command %s has been romoved\n",args[1]);
		}
	}
}


 /* prompt function */
int _prompt(char **args){
	char *default_prompt;
	default_prompt = "command";
	if(*(args+1)=='\0'){*(args+1)=default_prompt;}//strcpy(args[1],"command");
	strcpy(prompt_name,args[1]);
	return 1;
}


int _history(char **args){
	print_history();
	return 1;
}

int print_history(){
	for(int i=0;i<history_number;i++) printf("%s\n",history_command[i]);
}

int test(char **args)
{
    printf("This is a test.\n");
    return 1;
}


// Tyler

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int _exit(char **args)
{
  int fd[3][2];

  char *commandline = args;
  char **_split_line(char *line);

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

  return 0; 
}

/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int _launch(char **args)
{
  
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  

  //from Khari
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
      int file = open("textResults.txt", O_WRONLY | O_CREAT, 0777);
      if (file == -1){
            return 2;
     }
     printf("The fd to textResults: %d\n", file);
     dup2(file, STDOUT_FILENO);
     close(file);
if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
    
  return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int _execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < _num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
    	//printf("find builtin function : %d\n",i);
      return (*builtin_func[i])(args);
    }
  }

  return _launch(args);
}

#define _RL_BUFSIZE 1024
/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *_read_line(void)
{
  int bufsize = _RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += _RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}



#define _TOK_BUFSIZE 64
#define _TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **_split_line(char *line)
{
  int bufsize = _TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char **tokens2 = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;
  int tokSize = (sizeof(tokens)/sizeof(tokens[0]));
  if (!tokens) {
    fprintf(stderr, " allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, _TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += _TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, " allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, _TOK_DELIM);

  }
  tokens[position] = NULL;
  for(int i=0; i<tokSize; i++){
    tokens2[i] = tokens[i];

  }
  
  for(int i = 0; i<tokSize; i++){
    if(strcmp(tokens2[i], "exit") == 0){
      printf("Less goo\n");
    }
    else{
      tokens[i] = tokens2[i];
    }
    //printf("We are here %s\n", tokens2[i]);
  }




  printf("token1: %s\n", tokens[0]);
  printf("token2: %s\n", tokens[1]);
  printf("token3: %s\n", tokens[2]);
  printf("token4: %s\n", tokens[3]);
  printf("token5: %s\n", tokens[4]);
  printf("token6: %s\n", tokens[5]);


  return tokens;
}

char *get_wildcard(char **args)
{
  struct stat    filestat;
  struct dirent *directory;
  DIR           *dp;
  static char str[wild_card_buff];

  dp = opendir(".");

  while((directory=readdir(dp))!=NULL){
    if(!strcmp(directory->d_name, ".") ||
       !strcmp(directory->d_name, ".."))
      continue;
    if(stat(directory->d_name,&filestat)==-1){
      perror("main");
      exit(1);
    }else{
      strcat(str,directory->d_name);
      strcat(str," ");
    }
  }
	//printf("%s\n",str);
  closedir(dp);
  return str;
   exit(0);
}



char *search_command_from_history(char *line){
	int i;
	char str[10];
	char *command;
	for(i=0;i<strlen(line);i++) str[i] = *(line+i+1);
	//printf("history command matching...\n");
	//printf("input line = %s\nstr = %s\n",line,str);
	//printf("history number = %d\n",history_number);
	for(i=history_number-1;i>=0;i--){
		//printf("history[%d] = %s\n",i,history_command[i]);
		if(strncmp(str,history_command[i],strlen(str))==0){
			 //strcpy(command,history_command[i]);
			 command = history_command[i];
			 //printf("matched to history[%d] = %s,command = %s\n",i,history_command[i],command);
			 break;
		}
	}
	if(command == NULL) printf("Error : can't find command in history!!\n");
	
	
	return command;

}

int get_args_number(char **args){
		int i=0;
		int command_number=0;
		while(*(args+i)!='\0'){
			i++;
			command_number++;
		}
		return command_number;
}

/**
   @brief Loop getting input and executing it.
 */
void _loop(void)
{	char *tmp;
  char *line;
  char **args;
  char args_tmp[10];
  int status;
  int args_number;
  int i;


  //stack[0] = getcwd(NULL,0);
  //printf("path = %s\n",stack[0]);

  do {
  	/* prompt */
    printf("%s: ",prompt_name);
    
    /* read command */
    line = _read_line();
    //printf("size = %d\n",strlen(line));
    
    /* history*/
		strcpy(history_command[history_number],line);
		//		printf("history[%d] = %s\n",history_number,history_command[history_number]);
		history_number++;
		
		/* check alias*/
		for(int i=0;i<alias_number;i++){
			if(strcmp(line,alias[i].new_name)==0){
				//printf("found command in alias : %s\n",alias[i].original_name);
				strcpy(line,alias[i].original_name);
			}
		}
		
		/* check the wildcard and !string */
		if(*line=='!'){
    	if(*(line+1)=='!'){
    		if(history_number==0) printf("Error, no previous command\n");
    		else args = lsh_split_line(history_command[history_number-2]);
    	
    	}else{
    		char *command;
    		command = search_command_from_history(line);
    		args = lsh_split_line(command);    	
    	}
    
    }else{
    		//printf("case 3\n");
				args = _split_line(line);
				//print_command(args);
				
    }
    
    /*get args number */
		args_number = get_args_number(args);
		//printf("args number = %d\n",args_number);
		
		
		/* copy the last args*/
		//printf("args[%d] = %s\n",args_number-1,args[args_number-1]);
		strcpy(args_tmp,args[args_number-1]);
		//printf("args[%d] = %s\n",args_number-1,args_tmp);
		
		/* check wild card */
		for(i=0;i<args_number;i++){
			if(strcmp(args[i],"*")==0){
				//printf("find star symble in args[%d] = %s\n",i,args[i]);
				char str[100];
				
				strcpy(str,args[0]);
				strcat(str," ");
				strcat(str,get_wildcard(args));
				strcat(str," ");
				strcat(str,args_tmp);
				//printf("string = %s\n",str);
				
				free(line);
				free(args);
				strcpy(line,str);
				//line = test();
				args = _split_line(line);
				//printf("line = %s\nargs = %s\n",line,args);
				break;
			}
		}
		
		//print_command(args);
    status = _execute(args);
    free(line);
    free(args);
  } while (status);

}

int print_command(char **args){
		int i=0;
		int command_number=0;
		while(*(args+i)!='\0'){
			printf("args[%d] = %s\n",i,*(args+i));
			i++;
			command_number++;
		}
		//printf("number of command = %d\n",command_number);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  _loop();
  //get_wildcard();

  

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
