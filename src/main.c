/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:14:22 by rkedida           #+#    #+#             */
/*   Updated: 2022/08/13 22:11:25 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// write a parser for the command line

// char **parser(int ac, char **av)
// {
	
// }

// void parsing(int ac, char **av, char **envp)
// {
	
// }

int	check_qoutes(char *str, char opening_quote, int i)
{	
	while (str[i])
	{
		if (str[i] == opening_quote)
			return (1);
		i++;
	}
	return (0);
}

// write a function that read byte by byte from the command line

void	parser(char *line)
{
	int	i;
	int	j;
	int	quote_opened;

	i = 0;
	j = 0;
	quote_opened = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '\'')
		{
			i++;
			if (check_qoutes(line, '\'', i) == 0 && !quote_opened)
			{
				printf("minishell : : command not found\n");
				break ;
			}
			quote_opened = 1;
		}
		if (line[i] && line[i] == '\"')
		{
			i++;
			if (check_qoutes(line, '\"', i) == 0 && !quote_opened)
			{
				printf("minishell : : command not found\n");
				break ;
			}
			quote_opened = 1;
		}
		i++;
	}
}

void	prompt(int ac, char **av, char **envp)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	while (true)
	{
		s = readline("BALU > ");
		if (ft_strlen(s) > 0)
			add_history(s);
		parser(s);
		if (strcmp(s, ";") == 0)
		{
			printf("fuck you\n");
			break ;
		}
		// parsing(ac, av, envp);
		if (strcmp(s, "exit") == 0)
			break ;
	}
}

// int main(void)
int main(int ac, char **av, char **envp)
{
	char *tab;

	prompt(ac, av, envp);
	clear_history();
	// rl_on_new_line()
	return (0);
}
