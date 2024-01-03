#ifndef MAIN_H
#define MAIN_H

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

/*more function prototypes coming soon..*/
void putstr(char *str);
char *take_command(void);
void execute_command(char *command, char *shellname);

#endif
