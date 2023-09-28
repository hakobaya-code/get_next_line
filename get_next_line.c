/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:18:33 by hakobaya          #+#    #+#             */
/*   Updated: 2023/09/28 18:36:50 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*ret;
	ssize_t		read_len;

	//read(save);
	//line = getline(save)
	//save = get_new_save(save)

	while (1) //改行があるか読むものがなくなるまで
	{
		if (save) //staticのなかみをしらべる
		{
			ret = line_combination(fd, save);
			//
			if (ret)
				return (ret);
		}
		read_len = read_line(fd, buf);
		if (read_len == 0)
			break ;
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

ssize_t	read_line(int fd, char *buf)
{
	ssize_t	read_len;

	read_len = read(fd, buf, BUFFER_SIZE);
	if (read_len == 0)
		return (0);
	buf[read_len] = '\0';
	return (read_len);
}

char	*line_combination(int fd, char *save)
{
	char	*tail;
	char	*ret;

	tail = ft_strchr(save, '\n');
	if (tail) //改行があった時
	{
		ret = ft_calloc(sizeof(char), tail - save + 2);
		ret = ft_memcpy(ret, save, tail - save + 1); //文字列＋改行
		save = ft_strdup(tail + 1); //staticの更新　残りを突っ込む
		if (*save == '\0')//saveが終端ならNULLにしておく
			save = NULL;
		return (ret);
	}
	return (NULL);  //改行がなかった時の返すやつ
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

int	main(void)
{
	int		fd;
	int		index;
	char	*gnl;

	index = 0;
	fd = open("text.txt", O_RDONLY);
	for (int i = 0; i < 10; i++)
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
