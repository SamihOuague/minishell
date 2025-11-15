/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:17:45 by  souaguen         #+#    #+#             */
/*   Updated: 2024/07/16 15:11:47 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ast.h"

t_tree	*ft_tree_new(void *content)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (node == NULL)
		return (NULL);
	(*node).content = content;
	(*node).left = NULL;
	(*node).right = NULL;
	return (node);
}

t_tree	*ft_break_expr(char *str, int index)
{
	t_tree	*node;
	char	*tmp;
	char	*op;
	char	bckup;

	tmp = ft_strdup(str);
	if (tmp == NULL)
		return (NULL);
	bckup = *(tmp + index + 2);
	*(tmp + index + 2) = '\0';
	op = ft_strdup((tmp + index));
	*(tmp + index + 2) = bckup;
	if (op == NULL)
		return (free(tmp), NULL);
	*(tmp + index) = '\0';
	node = ft_tree_new(op);
	if (node == NULL)
		return (free(tmp), free(op), NULL);
	(*node).left = ft_tree_new(ft_strtrim(tmp, " "));
	(*node).right = ft_tree_new(ft_strtrim(tmp + index + 2, " "));
	if ((*node).left == NULL || (*node).right == NULL)
		return (free(tmp), free(op), free(node), NULL);
	free(tmp);
	return (node);
}

void	ft_remove_parenthesis(t_tree **root)
{
	char	*expr;	
	char	*tmp;
	int		i;
	int		b;

	i = 0;
	b = 0;
	expr = (**root).content;
	while (*(expr + i) != '\0')
	{
		b += (*(expr + i) == '(') - (*(expr + i) == ')');
		if (ft_strchr("&|", *(expr + i)) == ft_strchr("&|", *(expr + i + 1))
			&& b == 0)
			return ;
		i++;
	}
	i = ft_strlen(expr) - 1;
	if (*(expr) == '(' && *(expr + i) == ')')
	{
		tmp = ft_substr(expr, 1, i - 1);
		free((**root).content);
		(**root).content = tmp;
	}
}

void	ft_skip_quoted(char *expr, int *i)
{
	char	b;

	if (*i > 0 && ft_strrchr(expr + *i - 1, *(expr + *i)))
	{
		b = *(expr + ((*i)--));
		while (*(expr + *i) != b)
			(*i)--;
	}
}

void	ft_str_to_tree(t_tree **root)
{
	char	*expr;
	int		i;
	int		bal;

	ft_remove_parenthesis(root);
	expr = (**root).content;
	i = ft_strlen(expr);
	bal = 0;
	while ((--i) >= 0)
	{
		if ((*(expr + i) == '\'' || *(expr + i) == '\"')
			&& ft_strchr(expr, *(expr + i)) != (expr + i))
			ft_skip_quoted(expr, &i);
		if (ft_strchr("&|", *(expr + i)) && bal == 0 && i > 0
			&& *(expr + i - 1) == *(expr + i))
		{
			free(*root);
			*root = ft_break_expr(expr, i - 1);
			free(expr);
			ft_str_to_tree(&(**root).left);
			ft_str_to_tree(&(**root).right);
			break ;
		}
		bal += (*(expr + i) == ')') - (*(expr + i) == '(');
	}
}
