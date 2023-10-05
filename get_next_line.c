/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:15:13 by hakobaya          #+#    #+#             */
/*   Updated: 2023/10/06 05:53:57 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buf;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buf = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buf) //static? save をfree して　NULL詰め
		return (free2end(&save));
	save = read_file(fd, save, buf);
	free(buf);
	if (save == NULL || ft_strlen(save) == 0)
		return (free2end(&save));
	line = get_line(save);
	if (line == NULL)
		return (free2end(&save));
	if (ft_strchr(save, '\n') == NULL)
	{
		free2end(&save);
		return (line);
	}
	save = save_remainder(save);
	if (save == NULL)
		return (free2end(&line));
	return (line);
}

void	*free2end(char **save)
{
	free(*save);
	*save = NULL;
	return (NULL);
}

char	*read_file(int fd, char *save, char *buf)
{
	char	*tmp_save;
	ssize_t	read_len;

	if (save == NULL)
		save = (char *)ft_calloc(sizeof(char), 1);
	read_len = 0;
	while (save && !ft_strchr(save, '\n'))
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len < 0)
			return (free2end(&save));
		else if (read_len == 0)
			break ;
		else
		{
			buf[read_len] = '\0';
			tmp_save = ft_strjoin(save, buf);
			free(save);
			save = tmp_save;
		}
	}
	return (save);
}

//char	*read_file(int fd, char *save, char *buf)
//{
//	char	*tmp_save;
//	char	*new_save;
//	ssize_t	read_len;

//	if (save == NULL)
//		save = (char *)ft_calloc(sizeof(char), 1);
//	read_len = 0;
//	new_save = save;
//	while (new_save && !ft_strchr(new_save, '\n'))
//	{
//		read_len = read(fd, buf, BUFFER_SIZE);
//		if (read_len < 0)
//			return (free2end(&save));
//		else if (read_len == 0)
//			break ;
//		else
//		{
//			buf[read_len] = '\0';
//			tmp_save = ft_strjoin(new_save, buf);
//			free(new_save);
//			new_save = tmp_save;
//		}
//	}
//	return (new_save);
//}

char	*get_line(char *save)
{
	char	*line;
	char	*n_ptr;
	size_t	line_len;

	n_ptr = ft_strchr(save, '\n');
	if (!n_ptr)
	{
		line = (char *)ft_calloc(sizeof(char), ft_strlen(save) + 1);
		if (!line)
			return (NULL);
		return (ft_memcpy(line, save, ft_strlen(save)));
	}
	line_len = n_ptr - save + 1;
	if (n_ptr)
		line = (char *)ft_calloc(1, sizeof(char) * (line_len + 1));
	else
		return (save);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, save, line_len);
	return (line);
}

char	*save_remainder(char *save)
{
	char	*new_save;
	char	*n_ptr;
	size_t	save_len;
	size_t	rem_len;

	n_ptr = ft_strchr(save, '\n');
	save_len = ft_strlen(save);
	rem_len = ft_strlen(n_ptr + 1);
	new_save = ft_calloc(rem_len + 1, sizeof(char));
	if (new_save == NULL)
		return (free2end(&save));
	ft_memcpy(new_save, n_ptr + 1, rem_len);
	free(save);
	return (new_save);
}

int	main(void)
{
	int		fd;
	int		index;
	char	*gnl;

	printf("\n\n\n\n○○○○○○○○○○○○ START ○○○○○○○○○○○○\n\n\n\n");
	index = 1;
	fd = open("text3.txt", O_RDONLY);
	//fd = 10000;
	while (1)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break ;
		printf("(%d): %s", index++, gnl);
		free(gnl);
	}
	printf("\n");
	close(fd);
	printf("\n\n○○○○○○○○○○○○ END ○○○○○○○○○○○○\n\n");
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}
