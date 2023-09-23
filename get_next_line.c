/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:18:33 by hakobaya          #+#    #+#             */
/*   Updated: 2023/09/24 06:23:17 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	read_number(int fd);
char	*read_line(int fd);
#include <string.h>

char	*get_next_line(int fd)
{
	char		*buf;
	char		*ret;
	char		*new_line_ptr;
	static char	*save;
	ssize_t		rd_num;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (save == NULL)
		save = ft_strdup("");
	while (1)
	{
		rd_num = read(fd, buf, BUFFER_SIZE);
		if (rd_num <= 0)
		{
			//if (rd_num == 0 && ft_strlen(save) == 0)
			//	return (NULL);
			break ;
		}
		buf[rd_num] = '\0';
		save = ft_strjoin(save, buf);
		if (new_line_ptr = ft_strchr(save, '\n'))
		{
			ret = (char *)malloc(sizeof(char) * (new_line_ptr - save + 1));
			ret = ft_memcpy(ret, save, new_line_ptr - save + 1);
			ret[new_line_ptr - save + 1] = '\0';
			save = ft_strdup(new_line_ptr + 1);
			//saveのなかにあと何個改行入っているかの処理
			//123\n456¥0
			//printf("aa %s\n", save);
			break ;
		}
	}
	//if (!buf)
	//	return (NULL);
	// = read_line(fd);
	//while (*buf != '\n')
	//{
	//	save = read_line(fd);
	//	ft_strjoin(save, buf);
	//}
	return (ret);
}

//size_t	read_number(int fd)
//{
//	size_t	rd_num;
//	char	*buffer;
//	char	*read_ptr;

//	rd_num = 0;
//	read_ptr = read(fd, buffer, 1);
//	while (&read_ptr != '\n' || rd_num < BUFFER_SIZE)
//	{
//		read_ptr = read(fd, buffer, 1);
//		read_ptr++;
//		rd_num++;
//	}
//	read_ptr -= rd_num;
//	return (rd_num);
//}

char	*read_line(int fd)
{
	size_t	i;
	char	*buffer;

	i = 0;
	buffer = read(fd, buffer, 1);
	while (&buffer != '\n' || i < BUFFER_SIZE)
	{
		buffer = read(fd, buffer, 1);
		i++;
		buffer++;
	}
	return (buffer);
}

int	main(void)
{
	int		fd;
	int		index;
	char	*gnl;

	index = 0;
	fd = open("text.txt", O_RDONLY);
	//while (1)
	for (int i = 0; i < 10; i++)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break ;
		printf("(%d): %s\n", index++, gnl);
		free(gnl);
	}
	printf('\n');
	close(fd);
}
