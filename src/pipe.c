/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** pipe
*/
#include "my.h"

static void prepare_pipe(int *pipefds, int *prev_read)
{
    if (pipe(pipefds) == -1) {
        perror("pipe");
        if (*prev_read != -1)
            close(*prev_read);
    }
}

static void close_if_needed(int fd)
{
    if (fd != -1)
        close(fd);
}

static void setup_io(command_t *cmd, int prev_read, int *pipefds)
{
    if (prev_read != -1) {
        dup2(prev_read, STDIN_FILENO);
        close(prev_read);
    }
    if (cmd->is_pipe) {
        close(pipefds[0]);
        dup2(pipefds[1], STDOUT_FILENO);
        close(pipefds[1]);
    }
}

static void handle_exec(char **argv, mainstruct_t *mainstruct)
{
    char *cmd_path = NULL;
    int result = 0;

    if (is_builtin_command(argv[0])) {
        result = execute_builtin(argv, mainstruct);
        free_arguments(argv);
        exit(result);
    }
    execve(argv[0], argv, mainstruct->env);
    cmd_path = find_command_path(mainstruct, argv[0]);
    if (cmd_path) {
        execve(cmd_path, argv, mainstruct->env);
        free(cmd_path);
    }
    write(2, argv[0], my_strlen(argv[0]));
    write(2, ": Command not found.\n", 21);
    free_arguments(argv);
    exit(1);
}

static void execute_child(command_t *cmd, mainstruct_t *mainstruct,
    int prev_read, int *pipefds)
{
    char **argv = NULL;

    setup_io(cmd, prev_read, pipefds);
    handle_file_redirections(cmd);
    argv = malloc(sizeof(char *) * (my_strlen(cmd->command) + 1));
    if (!argv)
        exit(1);
    parse_arguments(cmd->command, argv);
    if (!argv[0]) {
        free_arguments(argv);
        exit(1);
    }
    handle_exec(argv, mainstruct);
}

static int handle_fork_error(int prev_read, int *pipefds, int is_pipe)
{
    perror("fork");
    close_if_needed(prev_read);
    if (is_pipe) {
        close(pipefds[0]);
        close(pipefds[1]);
    }
    return 1;
}

static void manage_pipes(command_t *cmd, int *pipefds, int *prev_read)
{
    if (cmd->is_pipe)
        prepare_pipe(pipefds, prev_read);
}

static int spawn_child(command_t *cmd, mainstruct_t *m, int prev, int *pipefds)
{
    pid_t pid = fork();

    if (pid == -1)
        return handle_fork_error(prev, pipefds, cmd->is_pipe);
    if (pid == 0)
        execute_child(cmd, m, prev, pipefds);
    return pid;
}

static void update_pipe_state(command_t *cmd, int *prev, int *pipefds)
{
    close_if_needed(*prev);
    if (cmd->is_pipe) {
        close(pipefds[1]);
        *prev = pipefds[0];
    } else
        *prev = -1;
}

int execute_pipeline(command_t *cmds, int count, mainstruct_t *mainstruct)
{
    int pipefds[2];
    int prev_read = -1;
    int status = 0;

    for (int i = 0; i < count; i++) {
        manage_pipes(&cmds[i], pipefds, &prev_read);
        if (spawn_child(&cmds[i], mainstruct, prev_read, pipefds) == -1)
            return 1;
        update_pipe_state(&cmds[i], &prev_read, pipefds);
    }
    while (count > 0) {
        wait(&status);
        count--;
    }
    close_if_needed(prev_read);
    return WEXITSTATUS(status);
}
