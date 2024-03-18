/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:24:00 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/18 20:44:11 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

char	*replace_content(char *str, char *l_str)
{
	char	*tmp;
	char	*res;

	tmp = str;
	res = ft_strjoin(str, l_str);
	free(tmp);
	return (res);
}

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

t_quote_str	*ft_parse_vars(t_quote_str *quoted_str)
{
	t_quote_str	*q_str;
	char		*str;

	q_str = quoted_str;
	str = (*q_str).str;
	if ((*q_str).quoted != 1 && ft_strchr((*q_str).str, '$'))
		(*q_str).str = var_to_str((*q_str).str);
	return (q_str);
}

t_list	*get_pipeline(t_list *lst)
{
	t_quote_str	*q_str;
	t_list		*pipeline;
	t_list		*cursor;
	char			*tmp;
	char			*tmpp;
	char			*backup;

	cursor = lst;
	pipeline = NULL;
	tmp = ft_strdup("");
	while (cursor != NULL)
	{
		q_str = ft_parse_vars((*cursor).content);
		if ((*q_str).quoted == 0 && ft_strchr((*q_str).str, '|'))
		{
			backup = ft_strchr((*q_str).str, '|');
			*backup = '\0';	
			tmp = replace_content(tmp, (*q_str).str);
			ft_lstadd_back(&pipeline, ft_lstnew(tmp));
			tmp = (*q_str).str; 
			(*q_str).str = ft_strdup(backup + 1);
			free(tmp);
			tmp = ft_strdup("");
		}
		else
		{
			tmp = replace_content(tmp, (*q_str).str);
			free((*(t_quote_str *)(*cursor).content).str);
			cursor = (*cursor).next;
		}
	}
	ft_lstadd_back(&pipeline, ft_lstnew(tmp));
	return (pipeline);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*pipeline;
	t_list	*cursor;

	lst = NULL;
	if (argc != 2)
		return (1);
	lst = remove_quotes(argv[1]);	
	pipeline = get_pipeline(lst);
	cursor = pipeline;
	while (cursor != NULL)
	{
		printf("%s\n", (char *)(*cursor).content);
		cursor = (*cursor).next;
	}
	ft_lstclear(&pipeline, &free);	
	ft_lstclear(&lst, &free);
	return (0);
}
