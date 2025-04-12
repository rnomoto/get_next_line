#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

// pointer move inspect
// int main(void)
// {
//     char *str = "ABCDEFGHIJKLMN";
    
//     // char *mov = strchr(str, 'G');
//     // mov++;

//     printf("str: %s\n", str);
//     printf("%zu\n", strlen(str));
//     str += 3;
//     printf("%zu\n", strlen(str));
//     // printf("mov: %s\n", mov);
//     // printf("gap: %zd\n", mov - str);
    
//     return 0;
// }

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

ssize_t	find_char(const char *str, int c)
{
    ssize_t i;

    i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return i;
		i++;
	}
	if (str[i] == c)
		return i;
	return -1;
}

void	*ft_memset(void *mem, int c, size_t n) //if mem == NULL?
{
	size_t			i;
	unsigned char	*mem_cast;
	unsigned char	c_cast;

	i = 0;
	mem_cast = (unsigned char *)mem;
	c_cast = (unsigned char)c;
	while (i < n)
	{
		mem_cast[i] = c_cast;
		i++;
	}
	return (mem_cast);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	result;

	i = 0;
	// result = 0;
	result = ft_strlen(src);
	if (size == 0)
		return (result);
	while (src[i] != '\0' && size > 1)
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	dst[i] = '\0';
	return (result);
}

char	*put_stock(int fd, char *stock, char *ret)
{
    static int fd_check = -2;
    ssize_t enter_pos;
    char *tmp;

    tmp = (char *)malloc(sizeof(char) * (ft_strlen(stock) + 1));
    //tmp = NULL;
    if (tmp == NULL)
        return NULL;
    if (fd == fd_check)
    {
        enter_pos = find_char(stock, '\n');
        // printf("pos: %zd\n", enter_pos);
        ft_strlcpy(tmp, stock, (ft_strlen(stock) + 1));
        if (enter_pos == -1)
            ft_strlcpy(ret, tmp, (ft_strlen(stock) + 1));
        else
        {
            ft_strlcpy(ret, tmp, (enter_pos + 2));
            //printf("debug_ret: %s\n", ret);
            // tmp += (enter_pos + 1);
            //printf("debug_tmp: %s\n",tmp);
            ft_strlcpy(stock, (tmp + enter_pos + 1), (ft_strlen(tmp + enter_pos + 1) + 1));
            free(tmp);
            return ret;
        }
    }
    ft_memset(stock, '\0', (ft_strlen(stock) + 1));
    fd_check = fd;
    free(tmp);
    return ret;
}

int main(void)
{
    static char stock[] = "ABCDE\nGHIJ";
    char *ret;
    char *tmp;

    ret = (char *)malloc(sizeof(char) * (ft_strlen(stock) + 1));
    if (ret == NULL)
        return -1;
    tmp = ret;
    ret = put_stock(-2, stock, ret);
    if (ret == NULL)
    {
        free(tmp);
        return -1;
    }
    printf("ret: %s\n", ret);
    printf("sto: %s\n", stock);

    //free(tmp);
    free(ret);

    return 0;
}
	