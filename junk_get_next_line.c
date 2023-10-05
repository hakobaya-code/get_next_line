/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:15:13 by hakobaya          #+#    #+#             */
/*   Updated: 2023/10/06 08:34:04 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*new_save;
	char		*line;
	char		*rem_save;

	printf("\n\n\n\n////////////////////////////////\n\n\n\n");
	printf("◆◆◆ gnl		start gnl : save[%s]\n", save);
	if (fd < 0 || fd >= INT_MAX)
		return (NULL);
	if (save == NULL)
	{
		PRINT_DEBUG_INFO
		save = ft_calloc(1, 1);
	}
	PRINT_DEBUG_INFO
	new_save = read_line(fd, save);
	if (!new_save) //終了条件
		return (NULL);
	PRINT_DEBUG_INFO
	printf("◆◆◆ gnl		after read_line : new_save[%s]\n", new_save);
	line = get_line(new_save);
	PRINT_DEBUG_INFO
	printf("◆◆◆ gnl		after get_line : line[%s]\n", line);
	printf("◆◆◆ gnl		after get_line : new_save[%s]\n", new_save);
	rem_save = save_line(new_save);
	if (rem_save == NULL)
		return (NULL);
	PRINT_DEBUG_INFO
	printf("◆◆◆ gnl		after save_line : rem_save[%s]\n", rem_save);
	save = ft_strdup(rem_save);
	free(new_save);
	free(rem_save);
	printf("◆◆◆ gnl		before return : save[%s]\n", save);
	printf("◆◆◆ gnl		before return : line[%s]\n", line);
	return (line);
}

//char	*tmp_save(char *save)
//{
//	char	*new_save;

//	new_save = ft_strdup(save);
//	free(save);
//	return (new_save);
//}

char	*read_line(int fd, char *save)
{
	char	*buf;
	char	*new_save;
	char	*tmp_save;
	size_t	read_len;

	read_len = 0;
	tmp_save = save;
	printf("\n\n○○○ read_line	start : save [%s]\n\n", save);
	buf = ft_calloc(BUFFER_SIZE, 1);
	if (!buf)
		return (NULL);
	printf("○○○ read_line	before read : buf [%s]\n", buf);
	printf("○○○ read_line	before roop : tmp_save [%s]\n", tmp_save);
	while (1)
	{
		read_len = read(fd, buf, BUFFER_SIZE + 1);
		printf("○○○ read_line	after read : buf [%s]\n", buf);
		//printf("read_line : read_len [%zu]", read_len);
		if (read_len < 0)
		{
			free(buf);
			return (NULL);
		}
		if (read_len == 0)
		{
			free(buf);
			return (save);
		}
		else
		{
			new_save = ft_strjoin(tmp_save, buf);
			//printf("○○○ read_line	in roop : new_save [%s]\n", new_save);
			tmp_save = new_save;
			printf("○○○ read_line	in roop : tmp_save [%s]\n", tmp_save);
		}
		//printf("read_line brefore break : new_save[%s]\n", new_save);
		if (ft_strchr(tmp_save, '\n'))
			break ;
	}
	printf("\n○○○ read_line	/// break roop///\n\n");
	new_save = ft_strdup(tmp_save);
	printf("buf pointer [%s]\n", buf);
	printf("○○○ read_line	before free  : buf [%s]\n", buf);
	free(buf);
	printf("buf pointer [%s]\n", buf);
	printf("○○○ read_line	after free  : buf [%s]\n", buf);
	free(save);
	//free(buf);
	printf("○○○ read_line	before return  : read_len [%zu]\n", read_len);
	printf("○○○ read_line	before return : new_save [%s]\n", new_save);
	return (new_save);
}

char	*get_line(char *save)
{
	char	*line;
	char	*n_ptr;
	size_t	line_len;

	n_ptr = ft_strchr(save, '\n');
	line_len = n_ptr - save;
	if (n_ptr)
		line = (char *)malloc(sizeof(char) * (line_len + 2));
	else
		return (save); //OK?
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, save, line_len);
	line[line_len] = '\0';
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
	save_len = ft_strlen(save);
	i = 0;
	while (*save++ != '\n')
		i++;
	newsave_len = save_len - i + 1;
	new_save = (char *)malloc(sizeof(char) * (newsave_len + 1));
	if (!new_save)
		return (NULL);
	i = 0;
	while (i < newsave_len)
	{
		new_save[i] = save[i];
		i++;
	}
	new_save[i] = '\0';
	save = head;
	return (new_save);
}



int	main(void)
{
	int		fd;
	int		index;
	char	*gnl;

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n○○○○○○○○○○○○ START ○○○○○○○○○○○○\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	index = 1;
	fd = open("text.txt", O_RDONLY);
	while (1)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break ;
		printf("\n\n\nMAIN	(%d): %s\n", index++, gnl);
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
