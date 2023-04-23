/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:01:28 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/23 23:03:25 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	pipex_heredoc(t_pipex data)
{
	int		i;
	int		**fds;
	char	*str;
	char	*lim;

	i = -1;
	fds = malloc(sizeof(int *) * (data.ac - 4));
	while (++i < data.ac - 4)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (pipe(fds[i]) == -1)
			err();
	}
	lim = ft_strjoin(data.av[2], "\n");
	while (1)
	{
		write(1, ">", 1);
		str = get_next_line(0);
		if (!str || !ft_strcmp(lim, str))
			break ;
	}
	// i = 1;
	// while (++i < data.ac - 1)
	// 	pxik_heredoc(data, fds, i);
	free(lim);
	close_fds(data, fds);
}
