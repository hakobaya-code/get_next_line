/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_junk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 10:34:58 by hakobaya          #+#    #+#             */
/*   Updated: 2023/09/23 10:22:32 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#define BUFFER 42 //BUFFERは引数で実行する

//int	buf_error(char *buf)
//{
//	if (buf == NULL)
//		return (-1);
//}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (c == '\0')
	{
		i = ft_strlen(str);
		return (&str[i]);
	}
	if (c < 0)
		c = c % 128 + 128;
	if (c > 127)
		c %= 128;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1) + 1;
	dup = (char *)malloc(sizeof(char) * len);
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	read_fd(int fd, const char *save)
{
	size_t	i;
	size_t	len;
	ssize_t	ret;
	char	*buf;
	size_t	count;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	ret = read(fd, buf, BUFFER_SIZE);
	printf("%d\n", ret);
	i = 0;
	count = 0;
	//if (*save)
	//{
	//	while (*save != '\0')
	//		count++;
	//		save++;
	//}
	while (buf[i] != '\0' && i < BUFFER_SIZE)
	{
		if (buf[i] == '\n')
			break ;
		save[i] = buf[i];
		i++;
	}
}

//void	find_new_line(int fd, char **line, char **st_arr, char *buf)
//{

//}

char	*get_next_line(int fd)
{
	char		*buf;
	const char	*save;
	static char	*line;
	char		*ret;

	save = (char *)malloc(sizeof(char) * 100);
	//buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	//error = buf_error(buf);
	if (!buf)
		return (NULL);
	read_fd(fd, save);
	//{
	//	buf[ret] = '\0';
	//	if (!*line)
	//		tmp = ft_strdup(buf);
	//	else
	//		tmp = ft_strjoin(buf);
	//	if (*line)
	//		free(*line);
	//	if (ft_strchr(buf, '\n'))
	//		break ;
	//}
	return (save);
	//return (line);
}

//fd = open("text.txt", O_RDONLY);
//if (fd == -1)
//{
//	ft_printf("error");
//	return (NULL);
//}
//while (fd != EOF)
//{
//	read_fd(fd, line, save);
//	if (*buf == '\n')
//		find_new_line(fd, line, save);
//}
//free(buf);

#include <stdio.h>

int	main(void)
{
	char	*moji;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	moji = get_next_line(fd);
	printf("%s\n", moji);
	close(fd);
	return (0);
}
