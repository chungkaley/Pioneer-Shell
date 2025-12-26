#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "pish.h"

static char pish_history_path[1024] = {'\0'};

/*
 * Set history file path to ~/.pish_history.
 */
static void set_history_path()
{
    const char *home = getpwuid(getuid())->pw_dir;
    strncpy(pish_history_path, home, 1024);
    strcat(pish_history_path, "/.pish_history");
}

void add_history(const struct pish_arg *arg)
{
    // set history path if needed
    if (!(*pish_history_path)) {
        set_history_path();
    }

    /* 
     * TODO:
     * - open (and create if needed) history file at pish_history_path.
     * - write out the command stored in `arg`; argv values are separated
     *   by a space.
     */

	if (arg->argc == 0) {
        return;
    }

	FILE *fp = fopen(pish_history_path, "a"); // open history file
	//3.6
	if (fp == NULL){
		perror("open"); 
		return;
	}

	for (int i = 0; i < arg->argc; i++){
		fprintf(fp, "%s", arg->argv[i]);
		if (i < arg->argc - 1) {
            fputc(' ', fp);
		}
		

	}

	fputc('\n', fp); //single char
	fclose(fp);

}

void print_history()
{
    // set history path if needed
    if (!(*pish_history_path)) {
        set_history_path();
    }

    /* TODO: read history file and print with index */
	//3.13
	FILE *fp = fopen(pish_history_path, "r");	
	
	if (fp == NULL){
		perror("open");
		return; 		
	}

	char line[1024];
    int count = 1;

	 while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0'; // remove newline
        printf("%d %s\n", count, line);
        count++;
    }

    fclose(fp);
}
