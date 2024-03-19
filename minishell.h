/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:50:10 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/19 01:53:45 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"

typedef struct s_quote_str
{
        char    *str;
        int     quoted;
}       t_quote_str;

t_list	*remove_quotes(char *str);
t_list	*get_pipeline(t_list *lst);
char	*var_to_str(char *str);
int		count_vars(char *str);
#endif
