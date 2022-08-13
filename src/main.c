/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:14:22 by rkedida           #+#    #+#             */
/*   Updated: 2022/08/13 14:56:19 by rkedida          ###   ########.fr       */
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


void	prompt(int ac, char **av, char **envp)
{
	int		i;
	char	*s;
	char **tab;
	char *tmp;

	s = NULL;
	i = 0;
	while (true)
	{
		s = readline("BALU > ");
		if (ft_strlen(s) > 0)
			add_history(s);
		tab = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1));
		if (!tab)
			return ;
		while (i < ac)
		{
			tmp = s;
			tab = ft_split(tmp, ' ');
			tmp = tab[i];
			// printf("%s\n", s);
			printf("%s\n", tmp);
			printf("%s\n", tab[i]);
			i++;
		}
		// printf("%s\n", tab[i]);
		// i++;
		if (strcmp(s, ";") == 0)
				{printf("fuck you\n");
				break;}
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
