/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 01:13:48 by  souaguen         #+#    #+#             */
/*   Updated: 2024/05/27 04:55:55 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "minishell.h"

t_tree	*ft_tree_new(void *content);
t_tree	*ft_break_expr(char *str, int index);
char	*ft_set_exec(char *cmd);
void	ft_str_to_tree(t_tree **root);
int		ft_del_first(t_list **stack);
int		ft_exec_tree(t_tree *root, t_sys *sys);
int		ft_isbalanced(char *str);
int		ft_op_out(char *expr);
#endif
