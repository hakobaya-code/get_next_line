/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk_get_next_line_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:15:13 by hakobaya          #+#    #+#             */
/*   Updated: 2023/10/06 08:36:15 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*new_save;
	char		*line;
	char		*rem_save;

	if (fd < 0 || fd >= INT_MAX)
		return (NULL);
	if (save == NULL)
		save = ft_calloc(BUFFER_SIZE, 1);
	new_save = read_line(fd, save);
	if (!new_save) //終了条件
		return (NULL);
	line = get_line(new_save);
	if (line == NULL)
		return (NULL);
	rem_save = save_line(new_save);
	if (rem_save == NULL)
		return (NULL);
	save = rem_save;
	free(new_save);
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
	//char	*buf_head;
	char	*new_save;
	char	*tmp_save;
	size_t	read_len;

	read_len = 0;
	tmp_save = save;
	buf = (char *)ft_calloc(1, sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	//buf_head = buf;
	while (1)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len < 0)
		{
			free(buf);
			return (NULL);
		}
		if (read_len == 0)
		{
			free(buf);
			if (ft_strlen(save) == 0)
				return (NULL);
			return (save);
		}
		else
		{
			new_save = ft_strjoin(tmp_save, buf);
			free(tmp_save);
			tmp_save = new_save;
		}
		if (ft_strchr(tmp_save, '\n'))
			break ;
	}
	//new_save = ft_strdup(tmp_save);
	//buf = buf_head;
	free(buf);
	//free(save);
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
		line = (char *)ft_calloc(1, sizeof(char) * (line_len + 2));
	else
		return (save);
	if (line == NULL)
		return (NULL);
	ft_memcpy(line, save, line_len + 1);
	//line[line_len] = '\0';
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
	save_len = ft_strlen(save); // save = "aaa\naaa", save_len = 7
	/* original version
	i = 0;
	while (*save++ != '\n') // i = 3
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
	*/
	/* smatsuo version */
	char *n_ptr = ft_strchr(save, '\n');
	newsave_len = save_len - (n_ptr - save) - 1;
	new_save = ft_calloc(newsave_len + 1, sizeof(char));
	if (new_save == NULL)
		return (NULL);
	ft_memcpy(new_save, n_ptr + 1, newsave_len);
	return (new_save);
}

//int	main(void)
//{
//	int		fd;
//	int		index;
//	char	*gnl;

//	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n○○○○○○○○○○○○ START ○○○○○○○○○○○○\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//	index = 1;
//	fd = open("text.txt", O_RDONLY);
//	while (1)
//	{
//		gnl = get_next_line(fd);
//		if (gnl == NULL)
//			break ;
//		printf("(%d): %s\n", index++, gnl);
//		free(gnl);
//	}
//	printf("\n");
//	close(fd);
//	printf("\n\n○○○○○○○○○○○○ END ○○○○○○○○○○○○\n\n");
//}

//__attribute__((destructor))
//static void destructor() {
//    system("leaks -q a.out");
//}
