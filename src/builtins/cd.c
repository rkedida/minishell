/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:13:49 by rkedida           #+#    #+#             */
/*   Updated: 2022/10/02 19:58:25 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(int dir, char *path, char *oldpath)
{
	dir = chdir(path);
	if (dir == -1)
	{
		err_handle(3, "cd", path);
		data()->exit_state = 1;
	}
	else
		add_env("OLDPWD", ft_strdup(oldpath));
}

int	ft_cd(int argc, char **argv, char **envp)
{
	int			dir;
	char		*path;
	char		*oldpath;

	dir = 0;
	path = argv[1];
	oldpath = getcwd(NULL, 0);
	if (argc == 1)
		path = "~";
	if (strcmp(path, "~") == 0)
		path = ft_getenv("HOME");
	if (strcmp(path, "-") == 0)
	{
		path = ft_getenv("OLDPWD");
		if (path)
			printf("%s\n", path);
	}
	if (path != NULL && *path)
		change_dir(dir, path, oldpath);
	free(oldpath);
	return (1);
}
