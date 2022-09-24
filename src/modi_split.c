/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modi_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:09:51 by rkedida           #+#    #+#             */
/*   Updated: 2022/08/18 19:10:00 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wordlen_until_char(char *str, char quotes, char split_char)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != quotes)
	{
		if (quotes == split_char && str[i] == '\''
			&& ft_strchr(&(str[i + 1]), '\'') != NULL)
			i += wordlen_until_char(&(str[i + 1]), '\'', split_char);
		else if (quotes == split_char && str[i] == '\"'
			&& ft_strchr(&(str[i + 1]), '\"') != NULL)
			i += wordlen_until_char(&(str[i + 1]), '\"', split_char);
		else
			i++;
	}
	while (str[i] != '\0' && str[i] != split_char)
		i++;
	return (i);
}

int	wordlen_quotes(char *str, char c)
{
	int	size;

	size = 0;
	if (*str == '\'' && ft_strchr(str + 1, '\'') != NULL)
		size = wordlen_until_char(str + 1, '\'', c);
	else if (*str == '\"' && ft_strchr(str + 1, '\"') != NULL)
		size = wordlen_until_char(str + 1, '\"', c);
	else
		size = wordlen_until_char(str, c, c);
	return (size);
}

char	*modi_word_cpy(char *str, char c)
{
	char	*dest;
	int		i;
	int		size;

	i = 0;
	size = wordlen_quotes(str, c);
	dest = (char *)malloc(size + 1);
	while (i < size)
	{
		dest[i++] = *str;
		str++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*jump_word(char *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = wordlen_quotes(str, c);
	while (i < size)
	{
		str++;
		i++;
	}
	return (str);
}

char	*jump_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str != NULL && *str == c && *str != '\0')
	{
		str++;
		i++;
		if (c == '|' && i > 2)
			return (NULL);
	}
	return (str);
}

int	modi_count_words(char *str, char c)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		str = jump_char(str, c);
		if (str == NULL && c == '|')
		{
			free(str);
			return (0);
		}
		if (*str != '\0')
			i++;
		str = jump_word(str, c);
	}
	return (i);
}

char	**modi_split(char *s, char c)
{
	char	**dest;
	int		i;
	int		size;

	if (s == NULL)
		return (NULL);
	i = 0;
	size = modi_count_words(s, c);
	dest = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dest)
	{
		free(dest);
		return (NULL);
	}
	while (i < size)
	{
		s = jump_char(s, c);
		if (s[i] != '\0')
		{
			dest[i] = modi_word_cpy(s, c);
			s = jump_word(s, c);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

// void	print_split(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		if (i != 0)
// 			printf(" ");
// 		printf("<%s>", str[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

// int main ()
// {
// 	char *test1 = "echo hello | cat -e";
// 	char *test2 = "echo \"hello   a\" | cat -e";
// 	char *test3 = "echo \"hello   a |\" cat -e";
// 	char *test4 = "echo \'hello   a |\' cat -e";
// 	char *test5 = "echo hello | cat -e";
// 	char **str = modi_split(test1, '|');
// 	print_split(str);
// 	str = modi_split(test2, '|');
// 	print_split(str);
// 	str = modi_split(test3, '|');
// 	print_split(str);
// 	str = modi_split(test4, '|');
// 	print_split(str);
// 	str = modi_split(test5, '|');
// 	print_split(str);
// }
