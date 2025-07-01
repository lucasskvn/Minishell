/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** redirections_handler
*/
#include "my.h"

static void open_input(const char *file)
{
    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        write(2, file, my_strlen(file));
        write(2, ": No such file or directory.\n", 29);
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

static void open_output(const char *file, int flags)
{
    int fd = open(file, O_WRONLY | O_CREAT | flags, 0644);

    if (fd == -1) {
        write(2, file, my_strlen(file));
        write(2, ": Cannot create file.\n", 22);
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void handle_file_redirections(command_t *cmd)
{
    if (cmd->input_file)
        open_input(cmd->input_file);
    if (cmd->output_file)
        open_output(cmd->output_file, O_TRUNC);
    if (cmd->append_file)
        open_output(cmd->append_file, O_APPEND);
}
