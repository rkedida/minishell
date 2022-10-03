/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:35:43 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 12:49:56 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bashify_exit_status(void)
{
	if (data()->exit_state == 2)
		data()->exit_state = 130;
	if (data()->exit_state >= 256)
		data()->exit_state >>= 8;
	return (data()->exit_state);
}

int	get_infile(t_simple_cmd *simple_cmd, int fdin)
{
	char		*line;
	t_infiles	*infile;

	infile = simple_cmd->infile;
	line = NULL;
	while (infile)
	{
		close(fdin);
		fdin = infile->value;
		if (fdin == -1)
			return (-1);
		infile = infile->next;
	}
	return (fdin);
}

int	get_outfile(t_simple_cmd *simple_cmd, int fd[4], int order)
{
	int			fdpipe[2];
	t_outfiles	*outfile;

	outfile = simple_cmd->outfile;
	while (outfile && outfile->next)
		outfile = outfile->next;
	if (outfile)
		fd[OUT] = outfile->value;
	else if (simple_cmd->next == NULL)
		dup2(fd[STDOUT_INIT], fd[OUT]);
	if (simple_cmd->next != NULL)
	{
		if (pipe(fdpipe) == -1)
			return (4);
		fd[IN] = fdpipe[0];
		fd[OUT] = fdpipe[1];
	}
	if (outfile != NULL)
		dup2(outfile->value, STDOUT_FILENO);
	else
		dup2(fd[OUT], STDOUT_FILENO);
	close(fd[OUT]);
	return (0);
}

int	exec_cmd(t_simple_cmd *simple_cmd, int fd[4], int order)
{
	int	ret;

	ret = 0;
	fd[IN] = get_infile(simple_cmd, fd[IN]);
	if (fd[IN] == -1 && close(fd[IN]) && close(fd[OUT]))
		return (2);
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	get_outfile(simple_cmd, fd, order);
	data()->state = 1;
	if (is_builtin(simple_cmd->cmd))
		data()->exit_state = exec_builtin(simple_cmd);
	else
	{
		ret = fork();
		if (ret == 0)
		{
			close(fd[IN]);
			child_process(simple_cmd);
		}
	}
	return (ret);
}

int	xecute(void)
{
	int				fd[4];
	t_simple_cmd	*simple_cmd;
	int				ret;
	int				i;

	ret = 0;
	i = 0;
	simple_cmd = data()->cmds;
	if (simple_cmd != NULL)
		init_fds(fd);
	else
		return (2);
	while (simple_cmd != NULL && ++i)
	{
		if (!simple_cmd->error && simple_cmd->cmd)
			ret = exec_cmd(simple_cmd, fd, i);
		if (ret == 2)
			return (2);
		simple_cmd = simple_cmd->next;
	}
	reset_fds(fd);
	while (i--)
		wait(&data()->exit_state);
	return (bashify_exit_status());
}
