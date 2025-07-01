/*
** EPITECH PROJECT, 2025
** B-PSU-200-LYN-2-1-minishell2-lucas.sangkhavongs
** File description:
** redirection
*/
#include "my.h"

int check_redirections(mainstruct_t mainstruct)
{
    int i = 0;
    int redir = 0;

    while (mainstruct.line[i] != '\0') {
        if (mainstruct.line[i] == '>' && mainstruct.line[i + 1] != '>'
            && mainstruct.line[i - 1] != '>')
            redir++;
        if (mainstruct.line[i] == '<' && mainstruct.line[i + 1] != '<'
            && mainstruct.line[i - 1] != '<')
            redir++;
        if (mainstruct.line[i] == '>' && mainstruct.line[i + 1] == '>')
            redir++;
        if (mainstruct.line[i] == '<' && mainstruct.line[i + 1] == '<')
            redir++;
        if (mainstruct.line[i] == ';' || mainstruct.line[i] == '|')
            redir++;
        i++;
    }
    return redir;
}

static void fill_command_fields(command_t *cmd, char *token)
{
    cmd->command = my_strdup(token);
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_file = NULL;
}

static int count_commands(char *line)
{
    int count = 0;
    char *token;
    char *saveptr;
    char *line_copy = my_strdup(line);

    token = strtok_r(line_copy, "|;", &saveptr);
    while (token != NULL) {
        count++;
        token = strtok_r(NULL, "|;", &saveptr);
    }
    free(line_copy);
    return count;
}

static void parse_command_array(command_t *commands, char *line, int count,
    char *original_line)
{
    char *token;
    char *saveptr;
    char *line_copy = my_strdup(line);
    char *current_pos = original_line;
    char *next_pos = NULL;

    for (int i = 0; i < count; i++) {
        token = strtok_r((i == 0 ? line_copy : NULL), "|;", &saveptr);
        if (!token)
            break;
        fill_command_fields(&commands[i], token);
        next_pos = current_pos + my_strlen(token);
        commands[i].is_pipe = (*next_pos == '|') ? 1 : 0;
        current_pos = next_pos + 1;
        parse_redirections(&commands[i]);
    }
    free(line_copy);
}

command_t *parse_command_line(char *line, int *cmd_count)
{
    int count = count_commands(line);
    command_t *commands = malloc(sizeof(command_t) * (count + 1));
    char *original_line = my_strdup(line);

    if (!commands) {
        free(original_line);
        return NULL;
    }
    *cmd_count = count;
    parse_command_array(commands, line, count, original_line);
    free(original_line);
    return commands;
}

static void parse_input(command_t *cmd, char **saveptr)
{
    char *input_pos = my_strstr(cmd->command, "<");
    char *token = NULL;

    if (!input_pos)
        return;
    *input_pos = '\0';
    token = strtok_r(input_pos + 1, " \t", saveptr);
    if (token)
        cmd->input_file = my_strdup(token);
}

static void parse_output(command_t *cmd, char **saveptr)
{
    char *append_pos = my_strstr(cmd->command, ">>");
    char *output_pos = NULL;
    char *token = NULL;

    if (append_pos) {
        *append_pos = '\0';
        token = strtok_r(append_pos + 2, " \t", saveptr);
        if (token)
            cmd->append_file = my_strdup(token);
    } else {
        output_pos = my_strstr(cmd->command, ">");
        if (output_pos) {
            *output_pos = '\0';
            token = strtok_r(output_pos + 1, " \t", saveptr);
        }
        if (token && output_pos)
            cmd->output_file = my_strdup(token);
    }
}

static void clean_and_finalize_command(command_t *cmd)
{
    char *cleaned = clean_str(cmd->command);

    free(cmd->command);
    cmd->command = cleaned;
}

void parse_redirections(command_t *cmd)
{
    char *saveptr;

    parse_input(cmd, &saveptr);
    parse_output(cmd, &saveptr);
    clean_and_finalize_command(cmd);
}

void free_commands(command_t *commands, int cmd_count)
{
    if (!commands)
        return;
    for (int i = 0; i < cmd_count; i++) {
        free(commands[i].command);
        free(commands[i].input_file);
        free(commands[i].output_file);
        free(commands[i].append_file);
    }
    free(commands);
}
