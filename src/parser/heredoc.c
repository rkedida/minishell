/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:45:57 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/01 18:06:27 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rkedida/Documents/minishell/includes/minishell.h"

char	*heredoc_expand(char *line)
{
	char	*var;
	int		var_pos;

	var = ft_strchr(line, DOLLAR);
	if (!var)
		return (line);
	var_pos = var - line;
	free(line);
	line = expand_single(line, var_pos, var, false);
	line = strndup(line, ft_strlen(line));
	return (line);
}

int	read_heredocs(char	*dlmtr)
{
	int			fd;
	char		*line;
	char		*heredoc;

	line = NULL;
	data()->n_heredocs++;
	heredoc = ft_strjoin("heredoc", ft_itoa(data()->n_heredocs));
	fd = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	data()->state = 2;
	line = readline("> ");
	if (data()->state == 0 && close(fd) != 99)
		return (-1);
	while (line && strcmp(line, dlmtr))
	{
		line = heredoc_expand(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	fd = open(heredoc, O_RDONLY);
	return (fd);
}

int	add_infiles(t_infiles **infile, char *file, int mode)
{
	while (*infile != NULL)
		infile = &(*infile)->next;
	*infile = malloc(sizeof(t_infiles));
	if (*infile == NULL)
		return (2);
	if (mode == LESS)
	{
		(*infile)->value = open(file, O_RDONLY);
		if ((*infile)->value == -1)
		{
			err_handle(3, "", file);
			return (3);
		}
		(*infile)->dlmtr = NULL;
	}
	else if (mode == LESS_LESS)
		(*infile)->value = read_heredocs(file);
	(*infile)->next = NULL;
	return (0);
}

int	add_outfiles(t_outfiles **outfile, char *file, int mode)
{
	while (*outfile != NULL)
		outfile = &(*outfile)->next;
	*outfile = malloc(sizeof(t_outfiles));
	if (*outfile == NULL)
		return (2);
	if (mode == GREATER)
		(*outfile)->value = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (mode == GREATER_GREATER)
		(*outfile)->value = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	(*outfile)->next = NULL;
	return (0);
}
