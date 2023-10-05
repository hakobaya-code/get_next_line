/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:15:13 by hakobaya          #+#    #+#             */
/*   Updated: 2023/10/06 03:26:14 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buf;
	static int	flag;

	if (fd < 0 || fd >= INT_MAX || BUFFER_SIZE < 0 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	if (save == NULL && flag == 1)
		return (NULL);
	buf = (char *)calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	flag = 0;
	if (save == NULL)
		save = (char *)ft_calloc(sizeof(char), 1);
	save = read_file(fd, save, buf, &flag);
	free(buf);
	//printf("🔸 gnl		after read_line : save[%s]\n", save);
	line = get_line(save, &flag);
	//printf("🔸 gnl		after get_line : new_save[%s]\n", save);
	//printf("🔸 gnl		after get_line : line[%s]\n", line);
	save = get_remainder(save);
	//printf("🔸 gnl		after get_remainder : save[%s]\n", save);
	if (save == NULL && flag == 1)
		free(save);
	return (line);
}
//char	*get_next_line(int fd)
//{
//	static char	*save;
//	char		*new_save;
//	char		*line;
//	char		*rem_save;

//	if (fd < 0 || fd >= INT_MAX || BUFFER_SIZE < 0 || BUFFER_SIZE > SIZE_MAX)
//		return (NULL);
//	if (save == NULL)
//		save = ft_calloc(1, BUFFER_SIZE + 1);
//	new_save = read_file(fd, save);
//	printf("◆◆◆ gnl		after read_line : new_save[%s]\n", new_save);
//	if (new_save == save)
//		return (NULL);
//	if (new_save == NULL)
//		return (NULL);
//	line = get_line(new_save);
//	printf("◆◆◆ gnl		after get_line : new_save[%s]\n", new_save);
//	printf("◆◆◆ gnl		after get_line : line[%s]\n", line);
//	if (line == NULL)
//		return (NULL);
//	rem_save = get_remainder(new_save);
//	printf("◆◆◆ gnl		after get_remainder : rem_save[%s]\n", rem_save);
//	if (rem_save == NULL)
//		return (line);
//	save = rem_save;
//	free(new_save);
//	return (line);
//}

char	*read_file(int fd, char *save, char *buf, int *flag)
{
	char	*tmp_save;
	char	*new_save;
	size_t	read_len;
	int		l;

	read_len = 0;
	new_save = save;
	l = BUFFER_SIZE;
	while (!ft_strchr(new_save, '\n') && *flag == 0)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len < 0)
			return (NULL);
		else if (read_len == 0)
			*flag = 1;
		else
		{
			if (read_len < BUFFER_SIZE)
				l = read_len;
			tmp_save = ft_strnjoin(new_save, buf, ft_strlen(new_save) + l);
			free(new_save);
			new_save = tmp_save;
		}
	}
	return (new_save);
}

//char	*read_file(int fd, char *save, char *buf)
//{
//	char	*new_save;
//	char	*tmp_save;
//	char	*buf;
//	size_t	read_len;

//	read_len = 0;
//	tmp_save = save;
//	while (!ft_strchr(tmp_save, '\n'))
//	{
//		read_len = read(fd, buf, BUFFER_SIZE);
//		if (read_len < 0)
//			return (NULL);
//		else if (read_len == 0)
//			return (tmp_save);
//		else
//		{
//			new_save = ft_strjoin(tmp_save, buf);
//			free(tmp_save);
//			tmp_save = new_save;
//		}
//	}
//	//printf("read_file		after read_line : new_save[%s]\n", new_save);
//	return (tmp_save);
//}

char	*get_line(char *save, int *flag)
{
	char	*line;
	char	*n_ptr;
	size_t	line_len;

	n_ptr = ft_strchr(save, '\n');
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

char	*get_remainder(char *save)
{
	char	*new_save;
	char	*n_ptr;
	size_t	save_len;
	size_t	rem_len;

	n_ptr = ft_strchr(save, '\n'); //save = aaa\nbbbbb
	if (!n_ptr)
		return (NULL);
	save_len = ft_strlen(save); //save_len = 9
	rem_len = save_len - (n_ptr - save) - 1; //rem_len = 5  9-(4-1)-1
	new_save = ft_calloc(rem_len + 1, sizeof(char));
	if (new_save == NULL)
		return (NULL);
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
	fd = open("text2.txt", O_RDONLY);
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
	printf("\n\n○○○○○○○○○○○○ END ○○○○○○○○○○○○\n\n");
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}
