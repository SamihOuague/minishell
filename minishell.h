/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:50:10 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/15 21:53:42 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_quote_str
{
        char    *str;
        int     quoted;
}       t_quote_str;

t_list	*remove_quotes(char *str);
#endif
