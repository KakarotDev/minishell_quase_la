/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:42:43 by myokogaw          #+#    #+#             */
/*   Updated: 2024/02/23 16:42:43 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <wait.h>
# include "libft.h"

// Boolean defines
# define TRUE 1
# define FALSE 0

// Open defines
# define OPEN_WR 1
# define OPEN_RD 2

// AST defines
# define RIGHT 3
# define LEFT 4

// Syntax error defines
# define UNCLOSED_QUOTE 5
# define UNEXPECTED 6

// Define errors for cd command;
# define TOOMANY 3
# define NOTSETHOME 2
# define ERRNO 1

enum e_type
{
	H_DOC = 1,
	APPEND,
	PIPE,
	R_OUT,
	R_IN,
	WORD,
	ASSIGNMENT_WORD,
	CMD,
	IO_FILE,
	H_DEL
};

typedef struct s_token {
	enum e_type		type;
	char			*lex;
	char			*heredoc_file;
	int				metadata[3];
}	t_token;

typedef struct s_dlist {
	t_token			*tok;
	struct s_dlist	*next;
	struct s_dlist	*prev;
	int				pipes;
}	t_dlist;

typedef struct s_r_fds
{
	int	r_fd_in;
	int	r_fd_out;
}	t_r_fds;

typedef struct s_ast
{
	enum e_type		type;
	struct s_ast	*esq;
	struct s_ast	*dir;
	char			*path;
	char			**cmd;
	int				index;
	char			***files;
	struct s_r_fds	r_fds;
	struct s_ast	*first;
}	t_ast;

typedef struct s_cmds
{
	char	**commands;
	char	***args;
}	t_cmds;

typedef struct s_paths
{
	char	**right_paths;
	char	*init_path;
	char	**mat_path;
	int		mat_len;
}	t_paths;

typedef struct s_aux
{
	int		i;
	int		j;
	int		k;
	char	*path;
}	t_aux;

typedef struct s_fd_files
{
	int	in;
	int	out;
}	t_fd_files;

typedef struct s_pipex
{
	t_cmds		cmds;
	t_paths		paths;
	t_fd_files	fd_files;
	enum e_type	id_t;
	char		**argv;
	int			argc;
	char		**envp;
	int			pipe_fd[2];
	int			fork_id;
	int			c;
	int			status;
	int			fd_exec[2];
	int			exit_fd;
	int			input_fd;
	int			f_id;
}	t_pipex;

// Print functions
void	ft_print_matrix(char **matrix);
void	ft_print_dlist(t_dlist **head);
void	ft_print_ast(t_ast **root);

// Auxiliary functions
char	**hook_environ(char **envp, int free);
char	*ft_strndup(char const *s, unsigned int start, size_t len);
char	*ft_isspace(char *input, int fd);
char	*get_content_var(char *var);
char	*catch_cwd(void);
char	*hook_pwd(char *n_pwd, int to_free);
char	*set_entrance(void);
char	*ft_getenv(char *var);
char	*validating_varname(char *varname, int *is_quoted);
char	*ft_getenv(char *varname);
char	*is_an_address(char *lex);
void	closing_process(t_pipex *p, t_ast *raiz);
void	free_tokens(t_dlist *tokens);
void	free_struct_token(t_token *tok);
void	ft_free_ast(t_ast *root);
void	ft_free_matrix_char(char **matrix);
void	ft_free_matrix(void **matrix);
void	ft_destructor_struct(t_dlist **struct_to_clean);
void	ft_cpy_array_data(int *dst, int *src, int size);
void	ft_close_fds(void);
void	close_fds(int fd_max);
void	skip_single_quotes(char *lexeme, int *position);
void	handling_pipe(t_dlist **head, char **lexemes, int *index);
int		ft_open_fd(char *path, int flags);
int		ft_have_char(char *str, char c);
int		ft_have_op(char *input);
int		have_pipe(t_dlist *tokens);
int		ft_open_fork(void);
int		ft_is_redirect(enum e_type type);
int		get_ret_process(int pid);
int		last_exit_status(int exit_status);
int		ft_count_tokens(t_dlist **exec_tokens);
int		run_program(void);
int		ft_matrix_count(char **matrix);
int		ft_strcmp(const char *s1, const char *s2);
int		heredoc_file_counter(int filenum);
int		its_in_heredoc(int it_is);
int		after_prompt(int is_after);
int		heredoc_file_counter(int filenum);
int		received_sigint_in_heredoc(int status);
size_t	matrix_len(char **mat);
t_dlist	*go_to_pipe_or_first(t_dlist *aux_t);
t_dlist	*go_to_first_word(t_dlist *tokens);

// dlist procedures
int		ft_dlist_have_type(t_dlist **tokens, enum e_type type);
void	ft_dlist_delete_from(t_dlist *start_node);
void	ft_append_dlist(t_dlist **head, t_dlist *node);
t_dlist	*ft_dlst_last(t_dlist *node);
t_dlist	*ft_newnode_dlist(char *lexeme, enum e_type type, int expansion_data[]);
t_dlist	*ft_add_next(t_dlist *token, t_dlist *new_token, int iteration);
t_dlist	*ft_cpy_node(t_dlist *node);
t_dlist	*ft_dlist_last_occur(t_dlist **tokens, enum e_type type);
t_dlist	**ft_cpy_dlst(t_dlist *start_point);

// Here document
void	handling_heredoc(t_dlist **head, char **lexemes, int *index);
void	heredoc(t_token *heredoc_tok, char *delimiter);
int		open_fds_heredoc(char *file, int *fds);
int		is_delimiter(char *delimiter, char *input);

// Here document utils
void	handling_heredoc(t_dlist **head, char **lexemes, int *i);
int		heredoc_file_counter(int filenum);
int		warning_heredoc(char *input, char *delimiter);
int		open_and_check_heredoc_file(char *file, int *fd);
int		input_validation(char *delimiter, char *input);
int		received_sigint(int *fds);

// Environment
char	**copy_environ(void);

// Environment procedures
char	*read_var(char **environment, char *var);

// Lexer
t_dlist	**lexer(char *input);
t_dlist	**generate_tokens(char *file);
char	**get_all_lexemes(char *file);
int		has_expansion(char *lex, int *index, int *is_quoted);
int		quote_validation(char *input);

// Signal
void	handle_signal(void);
void	handle_signal_heredoc(void);
void	receive_sig_int_heredoc(int sig);

// Expansions
void	expansion(t_dlist **tokens);
void	renewing_token(t_dlist *tok);
void	send_for_expansion(t_dlist *node);
char	*getting_variable(char *varname);
char	*getting_varname(char *lexeme, int expansion_metadata[]);
char	*getting_content(char *var);
t_dlist	*dealing_with_last_lexeme(char *lex, t_dlist *new, t_dlist *tok, int i);

// Remove quotes
void	quote_removal(t_dlist **tokens);
void	send_for_quote_removal(t_dlist *token);

// Handle redirections
int		check_redirections(t_dlist **tokens);

// Handle pipes
int		check_pipes(t_dlist **tokens);

// Handle error
int		syntax_error(int type, t_dlist **tokens);
int		command_not_found(char *path, char **matrix);

// Parser
void	parser(t_dlist **tokens);
int		parser_validation(t_dlist **tokens);

// AST procedures
void	ast_function(t_dlist **tokens);
void	exec_cmd(t_ast *raiz, t_pipex *p);
void	tree_exec(t_ast *raiz, t_pipex *p, int fd);
void	standard_command_organizer(t_ast *raiz, t_pipex *p);
void	first_command_organizer(t_ast *raiz, t_pipex *p);
void	closing_father(t_pipex *p, t_ast *raiz);
void	closing_only_child(t_pipex *p, t_ast *raiz, t_dlist *tokens);
void	only_child_functions(t_dlist **tokens, t_pipex *p);
void	brothers_functions(t_dlist **tokens, t_pipex *p);
t_ast	*cria_arvore(t_dlist **t, t_pipex *p);
t_ast	*adiciona_no(t_ast *raiz, t_ast *no);
t_ast	*cria_no_arv(t_dlist *tokens, t_pipex *p, int i, int t);
t_dlist	*free_chunk_list(t_dlist *tokens);

// Builtins
int		builtins_caller(char **matrix);
int		cd(char **matrix);
int		export(char **matrix);
int		echo(char **matrix);
int		pwd(void);
int		env(char **args);
int		builtin_exit(char **matrix);
int		report_error_export(void);
int		show_variables(char **envp);
int		unset(char **args);
void	format_and_print_export(char *variable);

// Interrupt program
int		interrupt_program(char *input);

// Exec
char	***have_redirect(t_dlist *tokens);
char	**have_append(t_dlist *tokens);
char	**creat_append_mat(t_dlist *aux_t, int size_append);
char	**cria_mat_cmds(t_dlist *tokens);
char	**tokens_to_args(t_ast *leaf);
char	*get_path(char *command, char **envp);
char	*cria_path(t_dlist *tokens, t_pipex *p);
char	*its_a_address(char *lex);
int		files_out_control(t_ast *raiz, t_pipex *p);
int		files_in_control(t_ast *raiz, t_pipex *p);
void	handle_pipe(t_ast *leaf);
void	execution(t_ast **ast);
void	get_paths(t_pipex *p);
t_ast	*cria_no_cmd(t_dlist *tokens, t_pipex *p, int i, int t);
t_r_fds	r_fds_control(t_ast *raiz, t_pipex *p);

// Exec errors
void	redirect_in_error(t_ast *raiz, t_pipex *p);
void	redirect_out_error(t_ast *raiz, t_pipex *p);

#endif
