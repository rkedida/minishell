/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:55:12 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/27 04:32:23 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2, int flag)
{
	char			*dst;

	if (s1 == 0 || s2 == 0)
		return (0);
	dst = malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == 0)
	{
		if (flag)
			free(s1);
		return (0);
	}
	ft_memcpy(dst, s1, ft_strlen(s1));
	ft_memcpy(dst + ft_strlen(s1), s2, ft_strlen(s2));
	dst[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (flag)
		free(s1);
	return (dst);
}

char	*ft_strjoin_withnull(char *s1, char *s2, int flag)
{
	char	*ret;
	char	*cp_ret;
	char	*cp_s;
	int		i;

	if (s2 == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (ft_strdup(s2));
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	cp_ret = ret;
	cp_s = s1;
	i = 0;
	while (cp_s[i])
	{
		*cp_ret++ = cp_s[i];
		i++;
	}
	cp_s = s2;
	i = 0;
	while (cp_s[i])
	{
		*cp_ret++ = cp_s[i];
		i++;
	}
	*cp_ret = '\0';
	if (flag && s1)
		free((void *)s1);
	else if (flag)
		free((void *)s2);
	return (ret);
}
