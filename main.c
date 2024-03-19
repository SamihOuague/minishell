/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:24:00 by  souaguen         #+#    #+#             */
/*   Updated: 2024/03/19 05:37:29 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


t_list	*get_cmds(char *str)
{
	t_list	*lst;
	t_list	*pipeline;
	t_list	*cursor;
	char		*tmp;

	lst = remove_quotes(str);	
	pipeline = get_pipeline(lst);
	cursor = pipeline;
	while (cursor != NULL)
	{
		tmp = (*cursor).content;
		(*cursor).content = ft_split((*cursor).content, ' ');
		free(tmp);
		cursor = (*cursor).next;
	}
	ft_lstclear(&lst, &free);
	return (pipeline);
}

void	read_list(t_list *lst)
{
	t_list	*cursor;

	cursor = lst;
	while (cursor != NULL)
	{
		printf("%s\n", (char *)(*(t_quote_str *)(*cursor).content).str);
		cursor = (*cursor).next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;
	t_list	*cursor;
	char		*command;
	int		exit_status;
	
	lst = NULL;
	command = readline("Minishell $> ");
	while (command != NULL && ft_strncmp(command, "exit", 5))
	{
		lst = remove_quotes(command);
		lst = get_pipeline(lst);
		cursor = lst;
		while (cursor != NULL)
		{
			printf("\n\nSTART\n\n");
			read_list((*cursor).content);	
			printf("\n\nEND\n\n");
			cursor = (*cursor).next;
		}
		add_history(command);
		free(command);
		command = readline("Minishell $> ");
	}
	free(command);
	return (0);
}
