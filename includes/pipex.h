/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:25:59 by mnazarya          #+#    #+#             */
/*   Updated: 2023/04/20 20:30:37 by mnazarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**ep;
	char	**path;
	int		fd1;
	int		fd2;
}	t_pipex;


#endif
