/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:15:13 by hakobaya          #+#    #+#             */
/*   Updated: 2023/10/01 18:24:46 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*new_save;
	char		*line;
	char		*head;

	if (fd < 0 || fd >= INT_MAX)
		return (NULL);
	save = (char *)malloc(sizeof(char) * 1);
	save[0] = '\0';
	save = read_line(fd, save);
	//DEBUG_F
	//printf("save[%s]\n", save);
	line = get_line(save);
	//DEBUG_F
	//printf("save[%s]\n", save);
	//printf("line[%s]\n", line);
	new_save = save_line(save);
	if (new_save == NULL)
		return (NULL);
	//DEBUG_F
	//printf("save[%s]\n", save);
	//printf("new_save[%s]\n", new_save);
	//save = head;
	//DEBUG_F
	save = new_save;
	//DEBUG_F
	printf("save[%s]\n", save);
	//printf("line[%s]\n", line);
	return (line);
}

char	*read_line(int fd, char *save)
{
	char	*buf;
	char	*new_save;
	size_t	read_len;

	read_len = 0;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (1)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len < 0)
			return (NULL);
		if (read_len == 0)
			return (save);
		else if (!save)
			new_save = ft_strdup(buf);
		else
			new_save = ft_strjoin(save, buf);
		if (ft_strchr(new_save, '\n'))
			break ;
		//printf("new_save[%s]\n", new_save);
	}
	buf[read_len] = '\0';
	free(save);
	free(buf);
	return (new_save);
}

//char	*read_line(int fd, char *save)
//{
//	char	*buf;
//	char	*new_save;
//	size_t	read_len;

//	read_len = 0;
//	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
//	if (!buf)
//		return (NULL);
//	while (1)
//	{
//		read_len = read(fd, buf, BUFFER_SIZE);
//		if (read_len == 0)
//			return (NULL);
//		buf[read_len] = '\0';
//		if (!save)
//			new_save = ft_strdup(buf);
//		else
//			new_save = ft_strjoin(save, buf);
//		if (ft_strchr(save, '\n') || ft_strchr(save, '\0'))
//			break ;
//	}
//	free(save);
//	free(buf);
//	return (new_save);
//}

char	*get_line(char *save)
{
	char	*line;
	char	*newline;
	size_t	len;

	newline = ft_strchr(save, '\n');
	len = newline - save;
	//DEBUG_F
	//printf("%s\n", save);
	if (newline)
		line = (char *)malloc(sizeof(char) * (len + 2));
	else
		return (ft_strdup(save));
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, save, len);
	line[len] = '\0';
	return (line);
}

char	*save_line(char *save)
{
	char	*new_save;
	char	*head;
	size_t	save_len;
	size_t	newsave_len;
	size_t	i;

	head = save;
	//DEBUG_F
	//printf("save[%s]\n", save);
	//DEBUG_F
	//printf("head[%s]\n", head);
	//DEBUG_F
	save_len = ft_strlen(save);
	i = 0;
	while (*save++ != '\n')
		i++;
	//DEBUG_F
	//printf("save_len[%zu]\n", save_len);
	newsave_len = save_len - i + 1;
	//DEBUG_F
	//printf("newsave_len[%zu]\n", newsave_len);
	new_save = (char *)malloc(sizeof(char) * (newsave_len + 1));
	if (!new_save)
		return (NULL);
	//DEBUG_F
	//printf("head[%p]\n", head);
	//printf("save[%s]\n", save);
	i = 0;
	while (i < newsave_len)
	{
		new_save[i] = save[i];
		i++;
	}
	new_save[i] = '\0';
	//DEBUG_F
	//printf("new_save[%s]\n", new_save);
	save = head;
	//DEBUG_F
	//free(save); // saveの先頭ポインタ、同じ変数指定しないとダメかに戻らないとダメか確認できればhead指定したい
	//DEBUG_F
	//printf("after free save[%s]\n", save);
	//printf("brefore return new_save[%s]\n", new_save);
	return (new_save);
}



int	main(void)
{
	int		fd;
	int		index;
	char	*gnl;

	index = 1;
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

//__attribute__((destructor))
//static void destructor() {
//    system("leaks -q a.out");
//}
