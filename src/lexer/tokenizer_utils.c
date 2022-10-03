/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:12:48 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/03 15:15:07 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data(void)
{
	static t_data	data;
	
	return (&data);
}

char *append_char_to_token(char *line, char c)
{
	int		i;
	int		len;
	char	*dest;

	if (c == '\0')
		return (line);
	i = 0;
	dest = NULL;
	if (line != NULL)
		len = ft_strlen(line);
	else
		len = 0;
	dest = malloc(sizeof(char) * (len + 2));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = line[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	return (dest);
}

t_token	*save_token(char *line, char *value, int state)
{
	bool	split;
	t_token	**token;
	t_token	*tmp;
	int		type;
	bool expansion;
	
	if (*line == DOLLAR)
		expansion = true;
	else
		expansion = false;
	if (check_operators(*line) && state == 0)
		type = OPERATOR;
	else
		type = TOKEN;
	if (state == DQUOTE)
		split = false;
	else
		split = true;
	token = &data()->tokens;
	while (*token != NULL)
		token = &((*token)->next);
	*token = malloc(sizeof(t_token));
	(*token)->value = value;
	(*token)->type = type;
	(*token)->split = split;
	(*token)->error = false;
	(*token)->expansion = expansion;
	(*token)->next = NULL;
	return (*token);
}