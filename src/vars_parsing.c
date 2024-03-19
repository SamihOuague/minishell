/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:54:09 by souaguen          #+#    #+#             */
/*   Updated: 2024/03/18 23:58:57 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int     count_vars(char *str)
{
        int     i;
        int     c;

        i = 0;
        c = 0;
        while (*(str + i) != '\0')
        {
                if (*(str + i) == '$')
                        c++;
                i++;
        }
        return (c);
}

char    *var_to_str(char *str)
{
        char    *tmp;
        char    *new_str;
        char    **vars;
        char    **spl;
        t_list  *n_str;
        t_list  *cursor;
        int             i;
        int             j;
        int             k;
        long            n;

        n_str = NULL;
        if (ft_strchr(str, '$') == NULL)
                return (str);
        j = count_vars(str) + 1;
        vars = malloc(sizeof(char *) * j);
        vars[j - 1] = NULL;
        i = 0;
        j = 0;
        new_str = NULL;
        while (*(str + i) != '\0')
        {
                if (*(str + i) == '$')
                {
                        n = i + 1;
                        k = 0;
                        while (*(str + n) != '\0')
                        {
                                if (ft_strchr(" $", *(str + n)))
                                        break ;
                                n++;
                                k++;
                        }
                        vars[j] = malloc(sizeof(char) * (k + 1));
                        ft_memcpy(vars[j], (str + i + 1), k + 1);
                        vars[j][k] = '\0';
                        j++;
                }
                if (*(str + i) != '\0')
                        i++;
        }
        j = 0;
        while (vars[j] != NULL)
        {
                new_str = getenv(vars[j]);
                free(vars[j]);
                vars[j] = new_str;
                j++;
        }

        i = 0;
        new_str = str;
        j = 0;
        while (*(str + i) != '\0')
        {
                if (*(str + i) == '$')
                {
                        *(str + i) = '\0';
                        ft_lstadd_back(&n_str, ft_lstnew(ft_strdup(str)));
                        ft_lstadd_back(&n_str, ft_lstnew(vars[j]));
                        while (*(str + i + 1) != '\0' && *(str + i + 1) != ' ' && *(str + i + 1) != '$')
                                i++;
                        str = (str + i + 1);
                        i = -1;
                        j++;
                }
                i++;
        }
        new_str = ft_strdup("");
        if (str != NULL)
                ft_lstadd_back(&n_str, ft_lstnew(str));
        cursor = n_str;
        while (cursor != NULL)
        {
                if ((*cursor).content != NULL)
                {
                        tmp = new_str;
                        new_str = ft_strjoin(new_str, (char *)(*cursor).content);
                        free(tmp);
                }
                cursor = (*cursor).next;
        }
        return (new_str);
}
