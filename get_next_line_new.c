/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:15:13 by hakobaya          #+#    #+#             */
/*   Updated: 2023/09/28 20:27:18 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	save = read_line(fd, save);
	line = get_line(save);
	save = save_line(save);

	return (line);ß
}

char	*read_line(int fd, char *save)
{
	char	*buf;
	size_t	read_len;
	size_t	flag; // flagは改行あったら1

	flag = 0;
	while (1)
	{
		if (flag == 1)
			break ;
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
		read_len = read(fd, buf, BUFFER_SIZE);
		buf[read_len] = '\0';
		if (!save)
			save = ft_strdup(buf);
		else
			save = ft_strjoin(save, buf);
		free(buf); //これ必要か確認
		flag = ft_strchr(save, '\n');
	}
	return (save);
}

