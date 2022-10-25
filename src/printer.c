/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:31:01 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/24 09:58:53 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// printer for infiles

void	print_infiles(t_infiles *infile)
{
	while (infile != NULL)
	{
		printf("infile: %d dlmtr: %s ", infile->value, infile->dlmtr);
		infile = infile->next;
	}
}

// printer for outfiles

void	print_outfiles(t_outfiles *outfile)
{
	while (outfile != NULL)
	{
		printf("outfile: %d\n", outfile->value);
		outfile = outfile->next;
	}
}

// printer for heredocs

void	print_heredocs(t_heredocs *heredocs)
{
	while (heredocs != NULL)
	{
		printf("heredocs: %d\n", heredocs->value);
		heredocs = heredocs->next;
	}
}

// printer for error

void	print_error(t_simple_cmd *simple_cmd)
{
	while (simple_cmd != NULL)
	{
		printf("error: %i\n", simple_cmd->error);
		simple_cmd = simple_cmd->next;
	}
}

// printer for simple_cmd

void	print_simple_cmd(t_simple_cmd *simple_cmd)
{
	int	i;

	while (simple_cmd != NULL)
	{
		printf("cmd: %s ", simple_cmd->cmd);
		i = 0;
		while (simple_cmd->args != NULL)
		{
			printf("args[%d]: |%s| space: %d\n", i++, simple_cmd->args->value, simple_cmd->args->space);
			// i++;
			simple_cmd->args = simple_cmd->args->next;
		}
		print_infiles(simple_cmd->infile);
		print_outfiles(simple_cmd->outfile);
		print_heredocs(simple_cmd->heredocs);
		print_error(simple_cmd);
		simple_cmd = simple_cmd->next;
	}
}

// printer for cmds

void	print_cmds(void)
{
	t_simple_cmd	*simple_cmd;

	simple_cmd = data()->cmds;
	print_simple_cmd(simple_cmd);
}

void	print_token(t_token *token)
{
	t_token *tmp = token;
	int		i;

	i = 0;
	while (tmp != NULL)
	{
		printf("count = [%d] : value = [%s] : type = [%d] : split = [%i] : error = [%i] : expansion = [%i]\n", i++, tmp->value, tmp->type, tmp->split, tmp->error, tmp->expansion);
		tmp = tmp->next;
	}
	data()->tokens = NULL;
	// printf("\n");
}