/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:47:04 by mito              #+#    #+#             */
/*   Updated: 2024/06/13 23:49:54 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

int	validate_input(char *str);
int	validate_quotes_closed(char *str);
int	has_valid_arrow(const char *str);
int	has_valid_vertical_bar(const char *str);
int	has_valid_ampersand(const char *str);

#endif
