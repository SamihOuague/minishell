/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exitcode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:56:17 by souaguen          #+#    #+#             */
/*   Updated: 2024/06/17 17:57:12 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_exitcode_parsing(char *t, t_sys *sys)
{
	char	*token;
	char	*backup;
	char	*tmp[2];
	char	*e_code;

	token = t;
	if ((ft_strnstr(token, "$?", ft_strlen(token))
			&& !(*(token) == '\'' && *(token + ft_strlen(token) - 1) == '\''))
		|| ((*(token) == '\"' && *(token + ft_strlen(token) - 1) == '\"')
			&& ft_strnstr(token, "$?", ft_strlen(token))))
	{
		tmp[1] = ft_strnstr(token, "$?", ft_strlen(token)) + 2;
		*(tmp[1] - 2) = '\0';
		tmp[0] = token;
		e_code = ft_itoa((*sys).exit_code);
		token = ft_strjoin(tmp[0], e_code);
		backup = token;
		token = ft_strjoin(token, tmp[1]);
		free(backup);
		free(e_code);
		return (token);
	}
	return (t);
}

char	*ft_exitcode_handler(char *t, t_sys *sys)
{
	char	*old;
	char	*new;

	old = t;
	new = ft_exitcode_parsing(t, sys);
	if (old == NULL || new == NULL)
		return (NULL);
	while (ft_strncmp(old, new, ft_strlen(new)))
	{
		free(old);
		old = new;
		new = ft_exitcode_parsing(old, sys);
	}
	return (new);
}
