/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:35:48 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/24 19:29:05 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int ifile, int ofile, char **av, char **envp)
{
	int		pipe_fd[2];
	int		stat1;
	//int		stat2;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipe_fd) == -1)
		exit(-1);
	child1 = fork();
	if (child1 < 0)
		exit(-1);
	if (child1 == 0)
		execute(av[2], ifile, pipe_fd[1], envp);
	child2 = fork();
	if (child2 < 0)
		exit(-1);
	if (child2 == 0)
		execute(av[3], pipe_fd[0], ofile, envp);
	waitpid(child1, &stat1, 0);
	close(pipe_fd[1]);
	//waitpid(child2, &stat2, 0);
	//close(pipe_fd[0]);
}

int	main(int ac, char **av, char **envp)
{
	int	ifile;
	int	ofile;

	if (ac != 5)
		return (-1);
	ifile = open(av[1], O_RDONLY);
	ofile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ifile < 0 || ofile < 0)
		return (-1);
	pipex(ifile, ofile, av, envp);
	close(ifile);
	close(ofile);
	return (0);
}
