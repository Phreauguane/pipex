/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:28:32 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/24 19:21:28 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H'
			&& envp[i][4] == '=')
			return (&(envp[i][5]));
		i++;
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_exec(char *cmd, char **envp)
{
	char	**paths;
	char	**s_cmd;
	char	*exec;
	int		i;

	paths = ft_split(get_paths(envp), ':');
	s_cmd = ft_split(cmd, ' ');
	i = -1;
	while (paths[++i])
	{
		paths[i] = str_addc(paths[i], '/');
		paths[i] = str_adds(paths[i], s_cmd[0], ft_strlen(s_cmd[0]));
		if (access(paths[i], F_OK | X_OK) == 0)
		{
			exec = ft_strdup(paths[i]);
			free_tab(paths);
			free_tab(s_cmd);
			return (exec);
		}
	}
	free_tab(paths);
	free_tab(s_cmd);
	return (cmd);
}

void	execute(char *cmd, int ifd, int ofd, char **envp)
{
	char	**cmd_args;
	char	*exec;

	dup2(ifd, STDIN_FILENO);
	dup2(ofd, STDOUT_FILENO);
	cmd_args = ft_split(cmd, ' ');
	exec = get_exec(cmd, envp);
	if (execve(exec, cmd_args, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd_args[0], STDERR_FILENO);
		free_tab(cmd_args);
		exit(-1);
	}
}
