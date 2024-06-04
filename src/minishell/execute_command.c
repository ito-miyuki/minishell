/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:26:28 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/04 20:15:13 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"
#include "utils.h"
#include "builtin.h"

static int	execute_builtin(t_command *cmd, t_minishell *minishell)
{
	const char	*cmd_name = cmd->argv[0];

	if (ft_strcmp(cmd_name, "cd") == 0)
		return (ft_cd(cmd, minishell->env_list));
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd_name, "env") == 0)
		return (ft_env(cmd, minishell->env_list));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (ft_exit(cmd, minishell->exit_status));
	if (ft_strcmp(cmd_name, "export") == 0)
		return (ft_export(cmd, minishell->env_list, minishell->export_list));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (ft_unset(cmd, minishell->env_list, minishell->export_list));
	return (0);
}

static int	execve_with_path(t_command *cmd, const char **path, char *const *envp)
{
	char	*cmd_path;
	int		status;

	status = 0;
	while (path != NULL && *path != NULL)
	{
		cmd_path = ft_join_strings(3, *path, "/", cmd->argv[0]);
		if (cmd_path == NULL)
		{
			ft_fprintf(2, "minishell: malloc: %s\n", strerror(errno));
			return (-1);
		}
		if (access(cmd_path, X_OK) == 0)
			status = execve(cmd_path, cmd->argv, envp);
		free(cmd_path);
		if (status == -1)
			return (-1);
		path++;
	}
	return (execve(cmd->argv[0], cmd->argv, envp));
}

static int	ft_execve(t_command *cmd, const char **path, char *const *envp)
{
	if (is_directory(cmd->argv[0]))
	{
		ft_fprintf(2, "minishell: %s: Is a directory", cmd->argv[0]);
		return (126);
	}
	if (ft_strchr(cmd->argv[0], '/') != NULL || ft_has_spaces_only(cmd->argv[0]))
		execve(cmd->argv[0], cmd->argv, envp);
	else
		execve_with_path(cmd, path, envp);
	ft_fprintf(2, "minishell: %s: ", cmd->argv[0]);
	if (errno == EACCES)
		return (ft_fprintf(2, "%s\n", strerror(errno)), 126);
	if (errno == ENOENT)
	{
		if (path == NULL)
			return (ft_fprintf(2, "%s\n", strerror(errno)), 127);
		else
		{
			if (ft_strchr(cmd->argv[0], '/') != NULL)
				return (ft_fprintf(2, "%s\n", strerror(errno)), 127);
			else
				return (ft_fprintf(2, "%s\n", "command not found"), 127);
		}
	}
	return (ft_fprintf(2, "%s\n", strerror(errno)), 1);
}

/**
 * The `execute_program()` will perform input & output redirection by
 * looking inside `t_command *cmd`.
 *
 * This function runs and acts as main function in child process
 *
 * @param cmd
 * @param minishell
 *
 * @returns Exit status code (0 - 255)
*/
int	execute_command(t_command *cmd, t_minishell *minishell)
{
	char *const	*envp = get_envp(minishell->env_list);
	const char	**path = get_path(minishell->env_list);
	int			status;

	if (cmd->is_builtin)
		status = execute_builtin(cmd, minishell);
	else
		status = ft_execve(cmd, path, envp);
	free((void *)envp);
	ft_array_delete((void *)path, sizeof(char *), count_str_array(path), free);
	return (status);
}
