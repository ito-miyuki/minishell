/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:24:04 by mito              #+#    #+#             */
/*   Updated: 2024/06/07 16:11:12 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_bool	is_flag(const char *str)
{
	if (!ft_starts_with(str, "-n"))
		return (false);
	str = str + 2;
	while (*str != '\0')
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

static int	print(char **argv, int is_flag_on)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (replace_wildcard(&argv[i]) < 0)
			return (1);
		if (ft_putstr_fd(argv[i], 1) < 0)
			return (1);
		if (argv[i + 1] != NULL)
			if (ft_putchar_fd(' ', 1) < 0)
				return (1);
		i++;
	}
	if (is_flag_on == 0)
	{
		if (ft_putchar_fd('\n', 1) < 0)
			return (1);
	}
	return (0);
}

int	ft_echo(t_command *cmd)
{
	int	i;
	int	is_flag_on;

	i = 1;
	is_flag_on = 0;
	while (cmd->argv[i] != NULL)
	{
		if (is_flag(cmd->argv[i]))
			is_flag_on = 1;
		else
			break ;
		i++;
	}
	return (print(&cmd->argv[i], is_flag_on));
}
