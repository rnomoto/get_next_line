#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	index;
	size_t	count;
	char	*tmp;

	count = nmemb * size;
	if ((size != 0 && nmemb != 0) && SIZE_MAX / nmemb < size)
		return (NULL);
	else if (size == 0 || nmemb == 0)
		count = 1;
	index = 0;
	tmp = (char *)malloc(count);
	if (tmp == NULL)
		return (NULL);
	while (index < count)
	{
		tmp[index] = 0;
		index++;
	}
	return (tmp);
}

char *double_buf(char *old_buf, size_t size)
{
    char *new_buf;
    int i = 0;

    new_buf = (char *)ft_calloc(sizeof(char), size * 2);
    if (new_buf == NULL)
        return (NULL);
    while (i < size)
    {
        new_buf[i] = old_buf[i];
        i++;
    }
    free(old_buf);
    return new_buf;
}

int main(void)
{
    int i = 0;

    char *mem = (char *)malloc(sizeof(char) * 10);
    //error handle omit
    while (i < 10)
    {
        mem[i] = 'a';
        i++;
    }
    mem = double_buf(mem, 10);
    while (i < 20)
    {
        mem[i] = 'b';
        i++;
    }
    printf("%s\n", mem);
    free(mem);

    return 0;
}