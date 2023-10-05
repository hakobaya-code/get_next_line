/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobaya <hakobaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 10:35:50 by hakobaya          #+#    #+#             */
/*   Updated: 2023/10/06 04:49:41 by hakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

#include <stdio.h>

#ifndef DEBUG_MODE
# define DEBUG_MODE            1 //0 or 1
#endif
#define COLOR_RED           "\e[31m"
#define COLOR_RESET         "\e[0m"
#define COLOR_BOLD          "\e[1m"

#define PRINT_DEBUG_INFO    { static int call_count = 1; if (DEBUG_MODE) { \
                    dprintf(2, "%s%s#%s in %s: %s :(%d)    called (%d)\n", \
                    COLOR_RED, COLOR_BOLD, COLOR_RESET, __func__, __FILE__, __LINE__, call_count++);}};



//int        main(int argc, char *argv[])
//{
//    PRINT_DEBUG_INFO
//    int        i = 0;

//    while (argv[i])
//    {
//        PRINT_DEBUG_INFO
//        f(argv[i]);
//        i++;
//    }
//}

/*
** # 標準出力とエラー出力を一緒に出す場合
** ./a.out
**
** # エラー出力をlogファイルにリダイレクトして、ターミナルに標準出力のみを表示する
** ./a.out 2> log
**
** # DEBUGを切る
** (1)
** #define DEBUG_MODE    0
** (2)
** gcc $(FILE).c -D DEBUG_MODE=0
**
**# DEBUGを入れる
** (1)
** #define DEBUG_MODE    1
** (2)
** gcc $(FILE).c -D DEBUG_MODE=1
**
*/
# define DEBUG_F printf("LINE %d: FILE %s FUNC %s\n", __LINE__, __FILE__, __func__);

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
//char	*ft_strnjoin(char const *s1, char const *s2, int n);
char	*ft_strdup(char const *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s1);
char	*get_line(char *save);
char	*read_file(int fd, char *save, char *buf);
char	*save_remainder(char *save);
void	*free2end(char **save);

#endif