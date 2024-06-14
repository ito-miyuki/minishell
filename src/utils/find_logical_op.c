/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_logical_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:28:06 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/13 00:19:52 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*find_logical_op(const char *str)
{
	char	quote;
	int		depth;

	quote = 0;
	depth = 0;
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		if (*str == '(' && quote == 0)
			depth++;
		if (*str == ')' && quote == 0)
			depth--;
		if (*str == '&' && *(str + 1) == '&' && depth == 0 && quote == 0)
			return ((char *)str);
		if (*str == '|' && *(str + 1) == '|' && depth == 0 && quote == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
