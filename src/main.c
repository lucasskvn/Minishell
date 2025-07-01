/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell1-lucas.sangkhavongs
** File description:
** main
*/
#include "my.h"

int my_feof(ssize_t fd)
{
    char buffer[1];
    int bytesRead = read(fd, buffer, 1);

    if (fd == -1)
        return -1;
    if (bytesRead == 0)
        return 1;
    if (bytesRead == -1)
        return -1;
    return 0;
}

int commands(mainstruct_t *mainstruct, char *line)
{
    if (my_strncmp(line, "setenv", 6) == 0) {
        set_environment(mainstruct, line);
        return 0;
    }
    if (my_strncmp(line, "unsetenv", 8) == 0) {
        unset_environment(mainstruct, line);
        return 0;
    }
    if (my_strcmp(line, "env") == 0) {
        print_environment(mainstruct);
        return 0;
    }
    return 1;
}

static void free_commands(command_t *commands, int cmd_count)
{
    for (int i = 0; i < cmd_count; i++) {
        free(commands[i].command);
        if (commands[i].input_file)
            free(commands[i].input_file);
        if (commands[i].output_file)
            free(commands[i].output_file);
        if (commands[i].append_file)
            free(commands[i].append_file);
    }
}

static mainstruct_t free_struct(mainstruct_t mainstruct)
{
    int cmd_count = 0;
    command_t *commands = parse_command_line(mainstruct.line, &cmd_count);

    if (commands) {
        mainstruct.status = execute_pipeline(commands, cmd_count, &mainstruct);
        free_commands(commands, cmd_count);
        free(commands);
        return mainstruct;
    }
    return mainstruct;
}

mainstruct_t cleanexec(mainstruct_t mainstruct)
{
    init_cleanstr(mainstruct);
    if (my_strcmp(mainstruct.line, "exit") == 0) {
        mainstruct.exit = 1;
        return mainstruct;
    }
    if (my_strncmp(mainstruct.line, "cd", 2) == 0) {
        mainstruct.status = change_directory(&mainstruct);
        return mainstruct;
    }
    if (commands(&mainstruct, mainstruct.line) == 0) {
        mainstruct.status = 0;
        return mainstruct;
    }
    if (mainstruct.redir > 0) {
        mainstruct = free_struct(mainstruct);
        return mainstruct;
    }
    if (my_strcmp(mainstruct.line, "") != 0)
        mainstruct = execute_other(mainstruct);
    return mainstruct;
}

int mysh(mainstruct_t mainstruct)
{
    size_t len = 0;

    while (1) {
        if (isatty(STDIN_FILENO))
            write(1, "<3 : ", 5);
        if (mainstruct.env == NULL)
            init_env(&mainstruct);
        mainstruct.read = getline(&mainstruct.line, &len, stdin);
        if (mainstruct.read == -1)
            return mainstruct.status;
        mainstruct.redir = check_redirections(mainstruct);
        mainstruct = cleanexec(mainstruct);
        if (mainstruct.exit == 1 || mainstruct.status == 139)
            return mainstruct.status;
    }
    if (mainstruct.line)
        free(mainstruct.line);
    return mainstruct.status;
}

int main(void)
{
    mainstruct_t mainstruct = init_mainstruct();

    mainstruct.status = mysh(mainstruct);
    if (mainstruct.line)
        free(mainstruct.line);
    free_environment(&mainstruct);
    return mainstruct.status;
}
