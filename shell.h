#ifndef SHELL_H
#define SHELL_H

#define UNUSED(x) (void)(x)

#define SPLT_ERR -1
#define CTRL_D -2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;
extern char *program_name;
extern int history;

/**
 * struct Node - A new struct type defining a node in a linked list.
 *
 * @dir: A directory path.
 * @next: A pointer to another struct Node.
 */
struct Node
{
	char *dir;
	struct Node *next;
};
typedef struct Node Node;

/**
 * struct Builtin - A new struct type defining a builtin command.
 *
 * @name: The name of the builtin command.
 * @func: A function pointer to the builtin command's function.
 */
struct Builtin
{
	char *name;
	int (*func)(char **args);
};
typedef struct Builtin Builtin;




/* Signal handlers */
void handle_ctrl_c(int signum);


/* String helpers */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, int n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, int n);

char *_strchr(char *s, char c);
char *_strstr(char *haystack, char *needle);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, int n);
char *_strdup(char *str);

char **strsplit(char *str, const char *delimiter);


/* Helpers */
int num_len(int n);
char *int_to_str(int n);
int str_to_int(char *str);


/* Memory */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


/* Environment */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);


/* Linked list */
Node *add_node_end(Node **head, char *dir);
void free_list(Node *head);
Node *build_path_dirs(char *paths);


/* Get Location */
char *get_location(char *command);


/* Errors */
int write_error(char **args, int err);

char *error_126(char **args);
char *error_127(char **args);


/* Builtins */
int (*get_builtin(char *command))(char **args);
int fshell_exit(char **args);

#endif
