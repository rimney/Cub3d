/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 23:46:21 by rimney            #+#    #+#             */
/*   Updated: 2023/01/23 23:35:22 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
size_t  src_len(const unsigned char *src)
{
        size_t  lent;

        lent = 0;
        while (src[lent] != '\0')
                lent++;
        return (lent - 1);
}

void    *ft_memmove(void *dst, const void *src, size_t n)
{
        unsigned char    *s;
        unsigned char           *d;

        d = (unsigned char *)dst;
        s = (unsigned char *)src;
        n--;
        while (n > 0)
        {
                        d[n] = s[n];
                n--;
        }
        d[n] = s[n];
        return (d);
}

int	main()
{
	char x[10] = "ab";
	char y[10] =  "12cd";
	char *p = ft_memmove(y, x, 4);
	printf("%s", p);
	return(0);
}
