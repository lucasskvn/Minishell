/*
** EPITECH PROJECT, 2024
** libmy.h
** File description:
** libmy.h for lib
*/
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <ctype.h>

#ifndef LIBMY_H
    #define LIBMY_H

    #define ISSEG(status) (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)

typedef struct mainstruct_s {
    int status;
    int exit;
    char *line;
    ssize_t read;
    char **env;
    int redir;
} mainstruct_t;


typedef struct command_s {
    char *command;
    char *input_file;   // For < redirection
    char *output_file;  // For > redirection
    char *append_file;  // For >> redirection
    int is_pipe;        // Indicates if command is piped to next
} command_t;

void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strdup(char const *src);
char **my_str_to_word_array(char const *str);
char *concat_params(int argc, char **argv);
int my_show_word_array(char *const *tab);
char *clean_str(char *str);
char *init_cleanstr(mainstruct_t mainstruct);
int removespaces(char *str, int i);
int writestr(char *tmp);
char *removetabs(char *str);
void find_env(char **environ, int index);
int unset_environment(mainstruct_t *mainstruct, char *line);
int addenv(mainstruct_t *mainstruct, char *name, char *value);
int my_setenv(mainstruct_t *mainstruct, char *name,
    char *value, int overwrite);
int set_environment(mainstruct_t *mainstruct, char *line);
int print_environment(mainstruct_t *mainstruct);
char *my_getenv(mainstruct_t *mainstruct, char *name);
int change_directory(mainstruct_t *mainstruct);
int exec(char **argv, mainstruct_t *mainstruct);
int segfault(mainstruct_t mainstruct);
mainstruct_t execute_other(mainstruct_t mainstruct);
int my_feof(ssize_t fd);
int commands(mainstruct_t *mainstruct, char *line);
mainstruct_t cleanexec(mainstruct_t mainstruct);
mainstruct_t init_mainstruct(void);
int modifenviron(mainstruct_t *mainstruct, int i, char *name, char *value);
int execerror(mainstruct_t *mainstruct);
char *my_strchr(const char *str, int c);
char *find_value(char *name);
int cdtohome(mainstruct_t *mainstruct, char *current_pwd);
int updatepwd(mainstruct_t *mainstruct,
    char abs_path[PATH_MAX], char *oldpwd);
int cdtoprev(mainstruct_t *mainstruct, char *current_pwd);
void init_env(mainstruct_t *mainstruct);
void sync_environ_with_mainstruct(mainstruct_t *mainstruct);
int check_redirections(mainstruct_t mainstruct);
char **get_path_directories(mainstruct_t *mainstruct);
char *find_command_path(mainstruct_t *mainstruct, char *command);
int mysh(mainstruct_t mainstruct);

command_t *parse_command_line(char *line, int *cmd_count);
int execute_pipeline(command_t *commands, int cmd_count,
    mainstruct_t *mainstruct);
void parse_redirections(command_t *cmd);
void handle_file_redirections(command_t *cmd);
command_t *parse_command_line(char *line, int *cmd_count);
void parse_arguments(char *line, char **argv);
int is_builtin_command(char *cmd);
int execute_builtin(char **argv, mainstruct_t *mainstruct);
void free_arguments(char **argv);
void free_environment(mainstruct_t *mainstruct);

int main(void);
#endif // LIBMY_H
