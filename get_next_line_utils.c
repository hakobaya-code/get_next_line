/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 10:45:35 by hakobaya          #+#    #+#             */
/*   Updated: 2023/06/25 11:39:59 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (c == '\0')
	{
		i = ft_strlen(str);
		return (&str[i]);
	}
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
}
