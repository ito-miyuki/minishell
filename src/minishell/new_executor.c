/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:27:14 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/04 00:04:56 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "utils.h"
#include "io.h"

static int	init_pipes(t_executor *executor, int pipes_count)
{
	int	i;

	if (pipes_count == 0)
		return (0);
	i = 0;
	executor->pipes = (int **)ft_calloc(pipes_count + 1, sizeof(int *));
	if (executor->pipes == NULL)
		return (perror("minishell: malloc"), -1);
	while (i < pipes_count)
	{
		executor->pipes[i] = (int *)malloc(2 * sizeof(int));
		if (executor->pipes[i] == NULL)
			return (perror("minishell: malloc"), -1);
		if (pipe(executor->pipes[i]) == -1)
		{
			perror("minishell: pipe");
			free(executor->pipes[i]);
			executor->pipes[i] = NULL;
			return (-1);
		}
		i++;
	}
	executor->num_of_pipes = pipes_count;
	return (0);
}

static int	init_pids(t_executor *executor, t_list *cmd_list)
{
	const t_command	*cmd = (t_command *)cmd_list->head->data;

	if (cmd_list->length == 1 && cmd->is_builtin)
		return (0);
	executor->pids = (pid_t *)malloc(cmd_list->length * sizeof(pid_t));
	if (executor->pids == NULL)
	{
		perror("minishell: malloc");
		return (-1);
	}
	executor->num_of_pids = cmd_list->length;
	return (0);
}

t_executor	*new_executor(const char *str)
{
	t_executor	*executor;

	executor = (t_executor *)ft_calloc(1, sizeof(t_executor));
	if (executor == NULL)
		return (NULL);
	executor->cmd_list = parse_cmd_list(str);
	if (executor->cmd_list == NULL)
		return (perror("minishell: malloc"), NULL);
	if (
		init_pipes(executor, executor->cmd_list->length - 1) < 0
		|| init_pids(executor, executor->cmd_list) < 0
	)
	{
		close_pipes(executor->pipes);
		delete_executor(executor);
		return (NULL);
	}
	return (executor);
}
