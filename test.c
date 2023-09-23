#include <stdio.h>

#define DEGUG_F printf("LINE %d: FILE %s FUNC %s\n", __LINE__, __FILE__, __func__);

//HEAP
//0x0000000a0 [\0]
//
//0x0000000b0["a"]
//0x0000000b0["s"]
//0x0000000b0["\0"]
//
//
//
//
//str [0x000000b0]
//buffer ["as"]
//STACK
//
//
//BUFFER_SIZE 2
//
//
//text "asdfghjk"
//
//str = "asdf" 
//buffer = df
//
//"\0"
//
//gnl()
//{
// char buffer[BUFFER_SIZE + 1];
// int	ret;
// char *str = strdup("");
// static *save;
//
//	while (1)
//	{
//		ret = read(fd, buffer, buffer_size);
//		if (ret == 0)
//			return str;
//		buffer[ret] = '\0';
//      str = ft_strjoin(str, buffer);
//      //check \n
//	}
//}
//main()
// while 
// 	  str = gnl();
//
//

int		main()
{
	DEGUG_F
}
