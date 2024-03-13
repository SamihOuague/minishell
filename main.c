/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:24:00 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/13 03:35:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*cursor;

	lst = NULL;
	if (argc != 2)
		return (1);
	lst = remove_quotes(argv[1]);
	cursor = lst;
	while (cursor != NULL)
	{
		printf("%s\n", (char *)(*cursor).content);
		cursor = (*cursor).next;
	}
	ft_lstclear(&lst, &free);
	return (0);
}
