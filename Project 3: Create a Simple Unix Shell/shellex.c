/* $begin shellmain */
#include "csapp.h"
#define MAXARGS   128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv); 
//For the getting the current directory
char* getcwd(char* buf, size_t size);
//For the signal handling
handler_t *signal(int signum, handler_t *sigint_handler);
void sigint_handler(int sig);

int main(int argc, char* argv[]) 
{
    char cmdline[MAXLINE]; /* Command line */
    char *prompt;

    while (1) {

	  /* SIGINT handler */
          if (signal(SIGINT, sigint_handler) == SIG_ERR) {

              unix_error("signal error");
          }
	
	   if (argc > 1) {
	       
		 //thrid element of argv will be the new prompt
		 printf(argv[2]);
		 fflush(stdout);

		 printf("> ");
         	 fflush(stdout);

        	 Fgets(cmdline, MAXLINE, stdin);
        		
			if (feof(stdin)) //control D
            		exit(0);

        	/* Evaluate */
        	eval(cmdline);

           }

	   if (argc == 1) {
	
		prompt = argv[0];
		
		prompt += 2;
		
		printf("%s", prompt);
		fflush(stdout);

		printf("> ");
		fflush(stdout);                   
		Fgets(cmdline, MAXLINE, stdin); 
			
			if (feof(stdin)) //control D
	    		exit(0);

		/* Evaluate */
		eval(cmdline);	
	   }

   }
}
/* $end shellmain */
  
/* SIGINT handler */
void sigint_handler(int sig) {

	printf("\nPlease use the exit command to leave the program, press enter to continue");
	fflush(stdout);
	signal(SIGINT, sigint_handler);	
}
/* SIGINT handler end*/

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    int status;
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv); 
    if (argv[0] == NULL)  
	return;   /* Ignore empty lines */

    if (!builtin_command(argv)) { 
        if ((pid = Fork()) == 0) {   /* Child runs user job */
            if ((execvp(argv[0], argv)) < 0) {
		printf("Execution failed\n");
                printf("%s: Command not found.\n", argv[0]);
		fflush(stdout);
		exit(1); //Make the exit status 1
            }
        }

	/* Parent waits for foreground job to terminate */
	if (!bg) {
	    if (waitpid(pid, &status, 0) < 0)
		unix_error("waitfg: waitpid error");
	}
	else
	    printf("%d %s", pid, cmdline);
	    fflush(stdout);

	    /* Get the Child's exit status */	
	    wait(&status); 
    		if (WIFEXITED(status)) { //use macros
	    	    printf("CHILD EXIT STATUS: %d\n", WEXITSTATUS(status)); 
		    fflush(stdout); 
		}
	}
    return;
}


/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit")) /* quit command */
	exit(0);  
    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
	return 1;

    /* Exists the shell, use the raise() system call */
    if (!strcmp(argv[0], "exit")) {
	raise(SIGTERM);
	fflush(stdout);
    }

    /* Prints the process id of the shell */
    if (!strcmp(argv[0],	"pid")) {
	printf("%d\n", getpid());
	fflush(stdout);
	return 1;
    }

    /* Prints the parent process id of the shell */
    if (!strcmp(argv[0], "ppid")) {
	printf("%d\n", getppid());
	fflush(stdout);
	return 1;
    }

    /* Prints developer name, usage information, refer user to use man */
    if(!strcmp(argv[0], "help")) {
    
	 printf("\nDEVELOPER\n");
	 	printf("    mcclearyke is the developer of this shell\n\n");
	 
	printf("USAGE INFORMATION\n");
		printf("    To Change Shell Prompt:\n");
			printf("          <executable> -p     <prompt>\n");
			printf("       Ex: ./my257sh   -p enternewprompthere\n");
		printf("    List of Built-In Commands:\n");
			   printf("       	  exit: Exits the shell\n");
			   printf("          pid: Prints the process id\n");
			   printf("          ppid: Prints the parent process id\n");	
			   printf("          cd: Prints current working directory\n");
			   printf("          cd <path>: Changes the current working directory\n\n");

	printf("NOT LOOKING FOR BUILT-IN COMMANDS?\n");
		 printf("    REFER to man to get information on the non-built-in commands you seek\n\n");
	fflush(stdout);
	return 1;
    }

    /* Prints the current working directory; whereas "cd <path>" will change the current working directory */
    if(!strcmp(argv[0], "cd")) {
	
	char buf[MAXLINE];
	
	//check to see if they want to change dir
	if(argv[1] != NULL) {
	
		//pass in the new directory
		chdir(argv[1]); //the directory will now be changed
		return 1;
	}

	//else - print the current working dir
	printf("%s\n", getcwd(buf, MAXLINE));
	fflush(stdout);
	return 1;

    }


    return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}
/* $end parseline */


