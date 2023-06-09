/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:53:23 by mnazarya          #+#    #+#             */
/*   Updated: 2023/06/09 13:21:49 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_malloc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

void	error(void)
{
	perror("Error👾");
	exit(1);
}

void	close_fds(t_pipex data, int **fds)
{
	int	i;

	i = 0;
	while (i < data.ac - 4)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		free(fds[i]);
		i++;
	}
	free(fds);
}

char	*path_find(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_strchr(envp[i], '/'));
		i++;
	}
	return (0);
}

char	*find_cmd(t_pipex data, char **cmd)
{
	char	*s;
	char	*tmp;
	int		i;

	i = -1;
	s = ft_strjoin("/", *cmd);
	while (data.path[++i])
	{
		tmp = ft_strjoin(data.path[i], s);
		if (!access(tmp, X_OK))
		{
			free(*cmd);
			free(s);
			return (tmp);
		}
		free(tmp);
	}
	free(s);
	return (*cmd);
}
