/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:56:21 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/16 19:42:38 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "libft.h"
#include "utils.h"

static t_redir_type	get_redir_type(const char *str, int redir_symbol)
{
	t_redir_type	rd;

	rd = REDIR_NO;
	while (*str != '\0' && *str != redir_symbol)
		str++;
	if (*str == '\0')
		return (rd);
	rd = REDIR_INPUT;
	if (*str == '>')
		rd = REDIR_OUTPUT;
	str++;
	if (*str == '<')
	{
		rd = REDIR_HEREDOC;
		str++;
	}
	else if (*str == '>')
	{
		rd = REDIR_APPEND;
		str++;
	}
	return (rd);
}

static char	*get_token(const char *str)
{
	const char	*start;
	char		*token;

	while (*str != '\0' && *str != '<' && *str != '>')
		str++;
	while (*str != '\0' && (*str == '<' || *str == '>' || ft_isspace(*str)))
		str++;
	if (*str == '\0')
		return (NULL);
	start = str;
	while (*str != '\0' && !ft_isspace(*str))
	{
		if (*str == '\'' || *str == '"')
		{
			str = ft_strchr(str + 1, *str);
			if (str == NULL)
				return (NULL);
		}
		str++;
	}
	token = ft_substr(start, 0, str - start);
	return (token);
}

static int	expand_token(t_redir_type type, char **token)
{
	if (type == REDIR_HEREDOC)
		return (0);
	if (expand_wildcard(token) < 0)
		return (-1);
	return (0);
}

t_io	*new_io(const char *str, int redir_symbol)
{
	t_io	*io;

	io = (t_io *)ft_calloc(1, sizeof(t_io));
	if (io == NULL)
		return (NULL);
	io->redi_type = get_redir_type(str, redir_symbol);
	if (io->redi_type == REDIR_NO)
		return (delete_io(io), NULL);
	io->token = get_token(str);
	if (io->token == NULL)
		return (delete_io(io), NULL);
	if (expand_token(io->redi_type, &io->token) < 0)
		return (delete_io(io), NULL);
	if (io->redi_type != REDIR_HEREDOC)
		ft_remove_quote_pair(io->token);
	return (io);
}
