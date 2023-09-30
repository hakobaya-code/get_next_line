/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:15:13 by hakobaya          #+#    #+#             */
/*   Updated: 2023/09/30 16:57:23 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	size_t		disp_len;

	disp_len = 0;
	save = read_line(fd, save);
	//DEBUG_F
	//printf("%s\n", save);
	line = get_line(save, &disp_len);
	//printf("save[%s]\n", save);
	//printf("disp_len[%d]\n", disp_len);
	save += disp_len;
	//printf("save[%s]\n", save);
	//DEBUG_F
	//save = save_line(save);
	//DEBUG_F
	if (line == '\0')
		return (NULL);
	return (line);
}

char	*read_line(int fd, char *save)
{
	char	*buf;
	size_t	read_len;
	size_t	n_flag;

	read_len = 0;
	n_flag = 0;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (1)
	{
		if (n_flag == 1)
			break ;
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == 0)
			return (NULL);
		buf[read_len] = '\0';
		if (!save)
			save = ft_strdup(buf);
		else
			save = ft_strjoin(save, buf);
		if (ft_strchr(save, '\n') || ft_strchr(save, '\0'))
			n_flag = 1;
	}
	return (save);
}

char	*get_line(char *save, size_t *disp_len)
{
	char	*line;
	char	*head;
	char	*newline;

	newline = ft_strchr(save, '\n');
	//DEBUG_F
	//printf("%s\n", save);
	head = save;
	if (newline)
	{
		//DEBUG_F
		line = (char *)malloc(sizeof(char) * (newline - head + 2));
		if (line == NULL)
			return (NULL);
		line[newline - head - 1] = '\n';
		save += newline - head + 1;
		*disp_len = newline - head + 1;
	}
	else
		return (ft_strdup(save));
	//DEBUG_F
	line[newline - head] = '\0';
	ft_memcpy(line, head, newline - head);
	//DEBUG_F
	//printf("head[%s]\n", head);
	//printf("line[%s]\n", line);
	//printf("save[%s]\n", save);
	return (line);
}

char	*save_line(char *save)
{
	char	*new_save;
	size_t	len;

	DEBUG_F
	if (save == NULL)
		return (NULL);
	DEBUG_F
	while (1)
	{
		if (save == '\0')
			break ;
		*new_save++ = *save++;
	}
	return (new_save);
}

int	main(void)
{
	int		fd;
	int		index;
	char	*gnl;

	index = 0;
	fd = open("text.txt", O_RDONLY);
	while (1)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break ;
		printf("(%d): %s\n", index++, gnl);
		free(gnl);
	}
	printf("\n");
	close(fd);
}
