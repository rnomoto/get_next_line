#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 10

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

ssize_t find_char(const char *str, int c)
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

size_t ft_strlcpy(char *dst, const char* src, size_t size)
{
	size_t i;
	size_t check;

	i = 0;
	check = ft_strlen(src);
	if (size == 0)
		return check;
	while (src[i] != '\0' && size > 1)
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	dst[i] = '\0';
	return check;
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

char *strdup_double(char *mem, size_t old_size)
{
	char *new_mem;

	new_mem = (char *)malloc(sizeof(char) * (old_size * 2));
	if (new_mem == NULL)
	{
		free(mem);
		return NULL;
	}
	ft_memset(new_mem, 0, (old_size * 2));
    ft_strlcpy(new_mem, mem, ft_strlen(mem) + 1);
	free(mem);
	return new_mem;
}

ssize_t read_buf(int fd, char *buf, char *ret)
{
    ssize_t read_size;
    char *tmp_free;
    size_t total;

    read_size = read(fd, buf, BUFFER_SIZE);
    if (read_size == 0 && buf[0] == '\0')
        return 0;
    else if (read_size <= 0)
        return -1;
    // if ((ft_strlen(ret) + (size_t)read_size + 1) > sizeof(ret))
    total = ft_strlen(ret) + (size_t)read_size + 1;
    if (total > sizeof(ret))
    {
        tmp_free = ret;
        ret = strdup_double(ret, sizeof(ret));
        if (ret == NULL)
        {
            free(tmp_free);
            return -1;
        }
    }
    return read_size;
}

int put_buf(char *ret, char *buf, char *stock, ssize_t read_size)
{
    ssize_t enter_pos;

    enter_pos = find_char(buf, '\n');
    //printf("enter_pos: %zd\n", enter_pos);
    if (enter_pos == -1 && read_size == BUFFER_SIZE)
        ft_strlcpy((ret + ft_strlen(ret)), buf, (read_size + 1));
    else
    {
        if (enter_pos == -1)
            ft_strlcpy((ret + ft_strlen(ret)), buf, (read_size + 1));
        else
        {
            ft_strlcpy((ret + ft_strlen(ret)), buf, (enter_pos + 2));
            if (read_size == BUFFER_SIZE)
                ft_strlcpy(stock, (buf + enter_pos + 1), (read_size - enter_pos - 1));
        }
        return 0;
    }
    return 1;
}

char *read_put(int fd, char *ret, char *stock)
{
    char *buf;
    ssize_t read_size;
    int put_check;

    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    //buf = NULL;
    if (buf == NULL)
        return NULL;
    ft_memset(buf, '\0', (BUFFER_SIZE + 1));
    while (1)
    {
        read_size = read_buf(fd, buf, ret);
        //printf("read_size: %zd\n", read_size);
        if (read_size <= 0)
            break;
        put_check = put_buf(ret, buf, stock, read_size);
        //printf("put_check: %d\n", put_check);
        if (put_check <= 0)
            break;
    }
    //printf("read_size: %zd\n", read_size);
    free(buf);
    if (read_size == 0 || put_check == 0)
        return ret;
    return NULL;
}

int main(void)
{
    int fd = open("hello.txt", O_RDONLY);
    static char stock[] = "ABCDE";
    char *test = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    ft_memset(test, '\0', BUFFER_SIZE + 1);
    test = read_put(fd, test, stock);
    printf("%s\n", test);
    close(fd);
    free(test);

    return 0;
}