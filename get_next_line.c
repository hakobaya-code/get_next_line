/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:18:33 by hakobaya          #+#    #+#             */
/*   Updated: 2023/09/26 17:08:46 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	read_number(int fd);
char	*read_line(int fd, char *buf);


char	*get_next_line(int fd)
{
	static char	*save;
	char		buf[BUFFER_SIZE + 1];
	char		*ret;
	ssize_t		read_len;
	char		*tail;

	while (1) //改行があるか読むものがなくなるまで
	{
		if (save) //staticのなかみをしらべる
		{
			tail = ft_strchr(save, '\n');
			if (tail) //改行があった時
			{
				ret = ft_calloc(sizeof(char), tail - save + 2);
				ret = ft_memcpy(ret, save, tail - save + 1); //文字列＋改行
				save = ft_strdup(tail + 1);                  //staticの更新　残りを突っ込む
				if (*save == '\0')
				//saveが終端ならNULLにしておく
					save = NULL;
				return (ret);
			}
		}
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == 0)
			break ;
		buf[read_len] = '\0';
		if (save == NULL) //１かいめの処理,bufをそのままsaveにいれる、
			save = ft_strdup(buf);
		else //saveとbufを結合してsaveに入れる
			save = ft_strjoin(save, buf);
	}
	if (save) //改行がなかった時buffsizeよりも文字数多い時
	{
		ret = ft_strdup(save);
		save = NULL;
		return (ret);
	}
	return (NULL); //saveもNULLのため終了
}

char	*read_line(int fd, char *buf)
{
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ret;

	if (size != 0 && count >= SIZE_T_MAX / size)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (count * size));
	if (!ret)
		return (NULL);
	while (ret)
		*ret++ = '\0';
	return (ret);
}

//char	*get_next_line(int fd)
//{
//	static char	*save;
//	char		buf[BUFFER_SIZE + 1];
//	char		*ret;
//	ssize_t		read_len;
//	char		*tail;

//	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
//		return (NULL);
//	while (1)
//	{
//		read_len = read(fd, buf, BUFFER_SIZE);
//		if (read_len <= 0)
//		{
//			//if (read_len == 0 && len(save) == 0)
//			//	return (NULL);
//			break ;
//		}
//		buf[read_len] = '\0';
//		save = ft_strjoin(save, buf);
//		if (new_line_ptr = ft_strchr(save, '\n'))
//		{
//			ret = (char *)malloc(sizeof(char) * (new_line_ptr - save + 1));
//			ret = ft_memcpy(ret, save, new_line_ptr - save + 1);
//			ret[new_line_ptr - save + 1] = '\0';
//			save = ft_strdup(new_line_ptr + 1);
//			//saveのなかにあと何個改行入っているかの処理
//			//123\n456¥0
//			//printf("aa %s\n", save);
//			break ;
//		}
//	}
//	//if (!buf)
//	//	return (NULL);
//	// = read_line(fd);
//	//while (*buf != '\n')
//	//{
//	//	save = read_line(fd);
//	//	ft_strjoin(save, buf);
//	//}
//	return (ret);
//}

//size_t	read_number(int fd)
//{
//	size_t	read_len;
//	char	*buffer;
//	char	*read_ptr;

//	read_len = 0;
//	read_ptr = read(fd, buffer, 1);
//	while (&read_ptr != '\n' || read_len < BUFFER_SIZE)
//	{
//		read_ptr = read(fd, buffer, 1);
//		read_ptr++;
//		read_len++;
//	}
//	read_ptr -= read_len;
//	return (read_len);
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
