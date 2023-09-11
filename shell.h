#ifndef SHELL_H
#define SHELL_H

#define UNUSED(x) (void)(x)

#define CTRL_D -2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
extern char prompt[];
extern size_t prompt_size;

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


void handle_ctrl_c(int signum);




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

char **strsplit(const char *str, const char *delimiter);




Node *add_node_end(Node **head, const char *dir);
void free_list(Node *head);
Node *get_path_dir(char *paths);



char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);


#endif
