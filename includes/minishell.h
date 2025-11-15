/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:14:05 by souaguen          #+#    #+#             */
/*   Updated: 2024/08/29 16:50:20 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define ERR_G 1
# define ERR_BLT 2
# define ERR_MEM 125
# define ERR_EXEC 126
# define ERR_NF 127

typedef struct s_file
{
	char	*name;
	char	*eof;
	int		io;
	int		a_mode;
}	t_file;

typedef struct s_pipeline
{
	char	**argv;
	char	*eof;
	t_list	*file;
	int		argc;
	int		fd_in;
	int		fd_out;
	int		a_mode;
	int		exit_code;
}	t_pipeline;

typedef struct s_token
{
	char	*str;
	int		quoted;
}	t_token;

typedef struct s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_sys
{
	t_list	*local_env;
	t_list	*pipeline;
	t_list	*backup;
	t_list	*lst;
	t_tree	*root;
	char	*input;
	void	*envp_backup;
	char	***envp;
	int		pipe;
	int		exit_code;
	t_list	*fds;
}	t_sys;

int		change_env_pwd(t_sys *sys, char *new_pwd, char *var);
int		change_env_local(t_list **local_env, char *new, char *name);
int		cmd_invalid_here(t_list *cmds, int *pipefd, t_sys *sys, int exit_code);
int		put_error(char *cmd, char *arg, char *error);
void	ft_null(void *content);
void	ft_free_pipeline(void *content);
//builtins
int		pwd(void);
int		cd(t_pipeline *pipe, t_sys *sys);
int		echo(t_pipeline *pipe);
int		env(t_pipeline *pipe, t_sys *sys);
int		check_valid_export(char *input);
int		export(t_sys *sys, t_pipeline *pipe, int i);
int		unset(t_sys *sys, t_pipeline *pipe, int i);

void	free_splitter(char **splitter);
int		exec(t_pipeline *pipe, t_sys *sys);
int		execve_error(const char *path);

void	free_pipeline(void *content);
int		error(char *err, int exit_code);
int		ft_next_token_check(t_list *lst);
int		ft_syntax_check(t_list *lst);
t_list	*parsing_init(char *cmd, t_sys *sys);
char	*ft_strtok(char **ptr, char *delim);
void	*ft_env(void *content);
void	free_quoted(void *ptr);
int		run(t_list *cmds, t_sys *sys);
int		end_shell(t_sys *sys);
void	read_file(int fd_to_read, int fd_to_write);
t_list	*ft_pipeline_init(t_list *parsed);
t_list	*get_next_pipe(t_list **lst);
t_list	*get_files(t_list *lst);
char	**lst_to_argv(t_list *lst);
void	ft_wildcard(t_list **lst);
t_sys	*init_sys(char ***envp);
int		child_process(t_pipeline *pip, int pipefd[2], t_sys *sys);
int		parent_process(t_list *cmds, int pipefd[], t_sys *sys, int pid);
int		next_pipe(t_list *cmds, int pipefd[], t_sys *sys);
int		last_pipe(t_pipeline *pip, t_sys *sys, int pipefd[2]);
int		ft_wildcard_match(t_list *lst, char *str);
char	*getname(char *var);
char	*ft_exitcode_parsing(char *t, t_sys *sys);
char	*get_name_fd(void);
char	*ft_exitcode_handler(char *token, t_sys *sys);
char	**new_env(void);
char	*ft_replace_env(t_token *token);
void	handler_here_doc_sigusr(int sig);
int		size_array(char **array);
t_list	*ft_extract_wildcard(t_list *lst);
void	free_envp(char **envp);
void	handler_child_sigusr(int sig);
void	handler_sigusr(int sig);
void	handler_parent_sigusr(int sig);
void	handler_sigquit(int sig);
t_sys	*get_sys(void);
int		ft_skip_null(t_list *lst);
int		exit_cmd(t_pipeline *pipe, t_sys *sys);
int		exit_without_exit(t_pipeline *pipe, t_sys *sys);
int		ft_new_argv(char *str, char **argv, char **path);
int		ft_next_token_check(t_list *lst);
int		ft_syntax_check(t_list *lst);
int		ft_check_tree(t_tree *root, t_sys *sys);
int		ft_token_checker(t_token *token);
int		ft_tree_checker(t_tree *root, t_list *lst, char c);
int		ft_io_syntax(t_sys *sys, int *i, int *b);
void	free_lst(t_list *lst);
void	ft_wildcard_null_check(t_list **w, t_list **s, t_list **l, t_list *c);
void	*ft_copy_content(void *content);
void	ft_wildcard_util(t_list **start, t_list **wildcard, t_list *lst);
void	ft_dir_loop(t_list **f_list, t_list *wordlist);
void	ft_join_free(char **ptr, char **argv, char *str);
void	free_tree(t_tree **root);
void	free_all(t_sys *sys);
char	*get_prompt(void);
char	*ft_join_next(t_list *cursor);
char	*ft_skip_whitespace(t_list **lst);
char	*ft_new_tmp(char *backup, t_token *token);
t_token	*ft_create_token(char *str, int quoted);
#endif
