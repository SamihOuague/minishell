/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:19:48 by  souaguen         #+#    #+#             */
/*   Updated: 2024/05/27 04:51:39 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"

void	ft_null(void *content)
{
	(void)content;
	content = NULL;
	return ;
}

int	ft_isbalanced(char *str)
{
	char	quoted;
	int		i;
	int		bal;

	i = 0;
	bal = 0;
	quoted = '\0';
	while (*(str + i) != '\0' && bal >= 0)
	{
		if (quoted == '\0' && ft_strchr("\"\'", *(str + i)))
			quoted = *(str + i);
		else if (quoted != '\0' && *(str + i) == quoted)
			quoted = '\0';
		if (*(str + i) == '(' && quoted == '\0')
			bal++;
		else if (*(str + i) == ')' && quoted == '\0')
			bal--;
		i++;
	}
	return (!bal);
}
