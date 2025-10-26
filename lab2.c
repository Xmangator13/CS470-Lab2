//Xavier Santiago
//CS470
//10/25/2025
//Honor Code: "I pledge that this submission is solely my work, and that I have neither given to nor received help from anyone other than the instructor or TA’s."
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	//Define 10 distinct commands for child processes
	char *commands[10][3] = {
		{"ls", "-l", NULL},
		{"echo", "Hello Xavier",NULL},
		{"date", NULL},
		{"whoami", NULL},
		{"pwd", NULL},
		{"uname", "-a", NULL},
		{"id", NULL},
		{"ps", NULL},
		{"hostname", NULL},
		{"uptime", NULL}
	};
	//Store child PIDS
	pid_t pids[10];
	//create child processes
	for(int i = 0; i < 10; i++){
		pid_t pid = fork();
		if(pid < 0){
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if(pid == 0){
			//child process
			printf("Child PID: %d executing command: %s\n", getpid(), commands[i][0]);
			execvp(commands[i][0], commands[i]);
			//execvp fails
			perror("execvp failed");
			exit(EXIT_FAILURE);
		}
		else{
			//parent process for child PID
			pids[i] = pid;
		}
	}
	//parents wait for all children
	for(int i = 0; i < 10; i++){
		int status;
		pid_t wpid = waitpid(pids[i], &status, 0);
		//handle the wpid fail
		if(wpid == -1){
			perror("waitpid failed");
			continue;
		}
		//check if child exited normally and print status
		if(WIFEXITED(status)){
			printf("Child %d exited normally with status %d\n", wpid, WIFEXITED(status));
		}
		//check if child was terminated by a signal and then print the signal number
		else if(WIFSIGNALED(status)){
			printf("Child %d terminated by signal %d\n", wpid, WTERMSIG(status));
		}
		//handle any other abnormal termination and print the message for it
		else{
			printf("Child %d ended abnormally\n", wpid);
		}
	}
return 0;
}
