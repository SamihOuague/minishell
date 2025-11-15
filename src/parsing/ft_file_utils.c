/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 05:05:38 by souaguen          #+#    #+#             */
/*   Updated: 2024/08/29 17:19:59 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

extern int	g_sig;

void	ft_here_routine(char *str, int quoted, int fd)
{
	t_token	token;

	token.str = str;
	token.quoted = 0;
	if (!quoted)
		token.str = ft_replace_env(&token);
	ft_putstr_fd(token.str, fd);
	ft_putstr_fd("> ", 2);
	free(str);
}

char	*ft_here_doc(char *eof, int quoted)
{
	char	*tmp;
	char	*str;
	int		len;
	int		fd;

	tmp = get_name_fd();
	fd = open(tmp, O_CREAT | O_APPEND | O_WRONLY, 0644);
	ft_putstr_fd("> ", 2);
	signal(SIGINT, handler_here_doc_sigusr);
	str = get_next_line(0);
	while (str != NULL && g_sig == 0)
	{
		len = ft_strlen(str);
		if ((int) ft_strlen(eof) == (len - 1)
			&& ft_strncmp(eof, str, len - 1) == 0)
			break ;
		ft_here_routine(str, quoted, fd);
		if (g_sig == 0)
			str = get_next_line(0);
	}
	free(str);
	close(fd);
	return (tmp);
}

void	ft_update_file(t_list **cursor, t_file **file, char *redirect)
{
	t_token	*token;
	t_list	*tmp;

	token = (**cursor).content;
	if (ft_strncmp((*token).str, redirect, 2) == 0
		&& *redirect == '>'
		&& (*token).quoted == 0)
	{
		(**file).a_mode = 1;
		tmp = *cursor;
		*cursor = (**cursor).next;
		free(tmp);
	}
	else if (ft_strncmp((*token).str, redirect, 2) == 0
		&& *redirect == '<'
		&& (*token).quoted == 0)
	{
		tmp = *cursor;
		(**file).eof = ft_skip_whitespace(&(**cursor).next);
		(**file).name = ft_here_doc((**file).eof,
				(*(t_token *)(*(*tmp).next).content).quoted);
		*cursor = (**cursor).next;
		free(tmp);
	}
}

t_file	*ft_init_file(t_list **lst, char *redirect)
{
	t_file	*file;
	t_list	*cursor;

	cursor = *lst;
	if (lst == NULL || *lst == NULL)
		return (NULL);
	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	(*file).eof = NULL;
	(*file).name = NULL;
	(*file).a_mode = 0;
	ft_update_file(&cursor, &file, redirect);
	if ((*file).name == NULL)
		(*file).name = ft_skip_whitespace(&cursor);
	(*file).io = (*redirect == '>');
	*lst = cursor;
	return (file);
}

t_list	*get_files(t_list *lst)
{
	t_token	*token;
	t_list	*cursor;
	t_list	*outfiles;
	t_file	*tmp;

	cursor = lst;
	outfiles = NULL;
	while (cursor != NULL)
	{
		token = (*cursor).content;
		if (ft_strncmp((*token).str, "<", 2) == 0 && (*token).quoted == 0)
		{
			tmp = ft_init_file(&(*cursor).next, "<");
			ft_lstadd_back(&outfiles, ft_lstnew(tmp));
		}
		if (ft_strncmp((*token).str, ">", 2) == 0 && token->quoted == 0)
		{
			tmp = ft_init_file(&(*cursor).next, ">");
			ft_lstadd_back(&outfiles, ft_lstnew(tmp));
		}
		cursor = (*cursor).next;
	}
	return (outfiles);
}
