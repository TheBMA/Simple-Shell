#ifndef MAIN_H
#define MAIN_H
#define BUFFER_SIZE 1024

/*libraries based on the allowed functions*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/*environ is defined externally, used to access the environment variables*/
extern char **environ;

/*more function prototypes coming soon..*/
void putstr(char *str);
char *take_command(void);
void execute_command(char *command, char *shellname);
char *get_path(char *command);

/*string functions to be used*/
int _strlen(char *str);
char *_strdup(char *str);
char *_strcat(char *des, char *src);
char *_strcpy(char *des, char *src);
int _strcmp(const char *s1, const char *s2);
#endif
