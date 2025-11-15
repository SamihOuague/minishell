/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:17:19 by  souaguen         #+#    #+#             */
/*   Updated: 2024/06/13 13:04:50 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	ft_dir_loop(t_list **f_list, t_list *wordlist)
{
	struct dirent	*dir;
	t_token			*token;
	DIR				*dirp;

	dirp = opendir("./");
	dir = readdir(dirp);
	while (dir != NULL)
	{
		if ((*dir).d_name[0] != '.'
			&& ft_wildcard_match(wordlist, (*dir).d_name))
		{
			token = ft_create_token((*dir).d_name, 1);
			ft_lstadd_back(f_list, ft_lstnew(token));
			dir = readdir(dirp);
			if (dir != NULL)
			{
				token = ft_create_token(" ", 0);
				ft_lstadd_back(f_list, ft_lstnew(token));
			}
		}
		else
			dir = readdir(dirp);
	}
	closedir(dirp);
}
