/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:01:28 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/24 20:52:26 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	err(t_pipex data, int **fds)
{
	perror("Error👾");
	close_fds(data, fds);
	exit(1);
}

void	pipe_error(int **fds, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		close(fds[j][0]);
		close(fds[j][1]);
		free(fds[j]);
	}
	free(fds[j]);
	free(fds);
}

static void	children_heredoc(t_pipex data, int **fds, int i)
{
	if (i == 3)
	{
		if (dup2(fds[0][0], STDIN_FILENO) == -1)
			err(data, fds);
		if (dup2(fds[i - 2][1], STDOUT_FILENO) == -1)
			err(data, fds);
	}
	else if (i == data.ac - 2)
	{
		if (dup2(fds[i - 3][0], STDIN_FILENO) == -1)
			err(data, fds);
		if (dup2(data.fd2, STDOUT_FILENO) == -1)
			err(data, fds);
	}
	else
	{
		if (dup2(fds[i - 3][0], STDIN_FILENO) == -1)
			err(data, fds);
		if (dup2(fds[i - 2][1], STDOUT_FILENO) == -1)
			err(data, fds);
	}
	close_fds(data, fds);
	close(data.fd2);
	free_malloc(data.path);
}

static void	pxik_heredoc(t_pipex data, int **fds, int i)
{
	pid_t	id;
	char	**cmd;

	cmd = ft_split(data.av[i], ' ');
	if (!cmd)
		err(data, fds);
	if (cmd[0] && !ft_strchr(cmd[0], '/'))
		*cmd = find_cmd(data, cmd);
	id = fork();
	if (id == -1)
		err(data, fds);
	if (!id)
	{
		children_heredoc(data, fds, i);
		execve(*cmd, cmd, data.ep);
		error();
	}
	free_malloc(cmd);
}

void	pipex_heredoc(t_pipex data)
{
	int		i;
	int		**fds;
	char	*str;
	char	*lim;

	fds = pipe_fds(data);
	lim = ft_strjoin(data.av[2], "\n");
	while (1)
	{
		write(1, ">", 1);
		str = get_next_line(0);
		if (!str || !ft_strcmp(lim, str))
			break ;
		ft_putstr_fd(str, fds[0][1]);
		free(str);
	}
	free(str);
	i = 2;
	while (++i < data.ac - 1)
		pxik_heredoc(data, fds, i);
	free(lim);
	close(data.fd2);
	close_fds(data, fds);
}
