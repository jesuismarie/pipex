/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:25:59 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/22 21:14:44 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**ep;
	char	**path;
	int		fd1;
	int		fd2;
}	t_pipex;

void	free_malloc(char **str);
void	err(void);
void	close_fds(t_pipex data, int **fds);
char	*path_find(char **envp);
char	*find_cmd(t_pipex data, char **cmd);
void	pipex_heredoc(t_pipex data);
char	*get_next_line(int fd);

#endif
