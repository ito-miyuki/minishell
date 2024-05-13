/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:17:05 by mito              #+#    #+#             */
/*   Updated: 2024/05/10 16:59:38 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	buffer[PATH_MAX];
	
	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (-1);
	if (printf("%s\n", buffer) < 0)
		return (-1);
	return (0);
}
