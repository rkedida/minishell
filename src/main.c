/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:36:34 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/24 22:33:13 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*prompt(void)
{
	char	*line;

	line = NULL;
	line = readline("minishell$");
	return (line);
}

int	end_session(void)
{
	// change_ctrlc_sym(true);
	// mem_free_all();
	// rl_clear_history();
	print_exit();
	free_env(data()->env_list);
	return (data()->exit_state);
}

int	refresh_session(char *envp[])
{
	if (!*envp)
		*envp = ("PATH=/");
	data()->envp = envp;
	data()->state = 0;
	data()->tokens = NULL;
	data()->cmds = NULL;
	data()->n_heredocs = 0;
	return (0);
}

void	handler()
{
	write (1, "\n", 1);
	rl_free_line_state();
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

int	init_session(char *envp[])
{
	data()->exit_state = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	init_env(envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	input = NULL;
	init_session(envp);
	if (argc > 1)
		printf("%s is ignored\n", argv[0]);
	while (true)
	{
		refresh_session(envp);
		input = prompt();
		if (input)
		{
			if (*input && ft_strlen(input) > 1)
				add_history(input);
			if (lexer(ft_strdup(input)) != 6 && !parse())
				xecute();
			data()->state = 0;
			free_tokens(data()->tokens);
			free_cmds(data()->cmds);
		}
		else
			break ;
		free(input);
	}
	return (end_session());
}
