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
# include <sys/types.h>
# include <sys/stat.h>

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
# define SYNTAX_ERROR 2
# define UNCLOSED_QUOTE 5
# define UNEXPECTED 6

// Define errors for cd command;
# define TOOMANY 3
# define NOTSETHOME 2
# define ERRNO 1

# define MAX64BITS "+9223372036854775807"
# define MIN64BITS "-9223372036854775808"

enum e_error
{
	NOFILE,
	MINI_EACCES,
	MINI_EISDIR,
	NUMARGREQUIRED,
	TOOMANYARG
};

enum e_type
{
	H_DOC = 1,
	APPEND,
	PIPE,
	R_OUT,
	R_IN,
	WORD,
	ASSIGNMENT_WORD,
	IO_FILE,
	H_DEL
};

typedef struct s_token
{
	enum e_type		type;
	char			*lex;
	char			*heredoc_file;
	long int		metadata[4];
}	t_token;

typedef struct s_dlist
{
	t_token			*tok;
	struct s_dlist	*next;
	struct s_dlist	*prev;
	int				pipes;
}	t_dlist;

typedef struct s_ast
{
	enum e_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*path;
	char			**cmd_matrix;
	char			***files;
	int				redir_fds[2];
	struct s_ast	*first_leaf;
}	t_ast;

typedef struct s_exec_aux
{
	int	pipe_fds[2];
	int	forks[2];
}	t_exec_aux;

// Auxiliary functions
char			**creat_file_mat(t_dlist *tokens, int result, enum e_type type,
					enum e_type typ);
char			**hook_environ(char **envp, int free);
char			*format_string(char *s, char *s1, char *s2, char *s3);
char			*ft_strndup(char const *s, unsigned int start, size_t len);
char			*ft_isspace(char *input, int fd);
char			*catch_cwd(void);
char			*hook_pwd(char *n_pwd, int to_free);
char			*set_entrance(void);
char			*ft_getenv(char *varname);
void			closing_process(t_ast *root);
void			free_struct_token(t_token *tok);
void			ft_free_ast(t_ast *root);
void			ft_free_matrix(void **matrix);
void			ft_destructor_struct(t_dlist **struct_to_clean);
void			ft_cpy_array_data(long int *dst, long int *src, int size);
void			skip_single_quotes(char *lexeme, long int *position);
void			handling_pipe(t_dlist **head, char **lexemes, int *index);
void			write_err_msg_status(char *file,
					enum e_error error, int status_err);
int				ft_open_fd(char *path, int flags);
int				ft_have_char(char *str, char c);
int				ft_have_op(char *input);
int				pipe_count(t_dlist *tokens);
int				ft_is_redirect(enum e_type type);
int				get_ret_process(int pid);
int				last_exit_status(int exit_status);
int				run_program(void);
int				ft_matrix_count(char **matrix);
int				ft_strcmp(const char *s1, const char *s2);
int				heredoc_file_counter(int filenum);
int				its_in_heredoc(int it_is);
int				after_prompt(int is_after);
int				heredoc_file_counter(int filenum);
int				received_sigint_in_heredoc(int status);
int				is_process(int consult_or_change);
int				ft_isexpansion(int c);
t_dlist			*free_chunk_list(t_dlist *tokens);
t_dlist			*go_to_pipe_or_first(t_dlist *aux_t);
t_dlist			*go_to_first_word(t_dlist *tokens);

// dlist procedures
void			ft_append_dlist(t_dlist **head, t_dlist *node);
t_dlist			*ft_dlst_last(t_dlist *node);
t_dlist			*ft_newnode_dlist(char *lexeme, enum e_type type,
					long int *metadata);
t_dlist			*ft_add_next(t_dlist *token, t_dlist *new_token, int iteration);

// Here document
void			heredoc(t_token *heredoc_tok, char *delimiter);
int				open_fds_heredoc(char *file, int *fds);
int				is_delimiter(char *delimiter, char *input);
int				heredoc_file_counter(int filenum);
int				warn_heredoc(char *input, char *delimiter);
int				received_sigint(int *fds, char *input);
int				has_expansion_heredoc(char *lex, long int *index);

// Environment
char			**copy_environ(void);

// Environment procedures
char			*read_var(char **environment, char *var);

// Lexer
t_dlist			**lexer(char *input);
t_dlist			**generate_tokens(char *file);
char			**get_all_lexemes(char *file);
int				has_expansion(char *lex, long int *index, long int *is_quoted);
int				quote_validation(char *input);

// Signal
void			handle_signal(void);
void			handle_signal_heredoc(void);

// Expansions
void			expansion(t_dlist **tokens);
void			renewing_token(t_dlist *tok);
void			send_for_expansion(t_dlist *node);
char			*getting_variable(char *varname);
char			*getting_varname(char *lexeme, long int *expansion_metadata);
char			*getting_content(char *var);
t_dlist			*dealing_with_last_lexeme(char *lex, t_dlist *new,
					t_dlist *tok, int i);
void			write_with_quotes(t_dlist *token,
					char *content, char *varname, int heredoc);
void			renewing_heredoc_token(t_dlist *tok);
void			send_for_expansion_heredoc(t_dlist *node);

// Remove quotes
void			quote_removal(t_dlist **tokens);
void			send_for_quote_removal(t_dlist *token);

// Handle redirections
int				check_redirections(t_dlist **tokens);

// Handle pipes
int				check_pipes(t_dlist **tokens);

// Handle error
int				syntax_error(int type, t_dlist **tokens);
int				path_validation(char *path, char **matrix);

// Parser
void			parser(t_dlist **tokens);
int				parser_validation(t_dlist **tokens);

// AST procedures
void			tree_exec_pipe_procedure(t_ast *root, int pipe_fds[2]);
void			command_organizer(t_ast *root, int pipe_fds[2], int side);
void			tree_exec_termination(int pipe_fds[2], int forks[2]);
void			execve_error_exit(t_ast *root);
void			closing_only_child(t_ast *root);
void			only_child_functions(t_dlist **tokens);
void			brothers_functions(t_dlist **tokens);
t_ast			*create_cmd_leaf(t_dlist *tokens);
t_ast			*create_ast(t_dlist **tokens);

// Builtins
long long int	ft_atolli(const char *nptr);
int				finishing_program_exit(t_ast *root, int *std_fds,
					long long int exit_status);
int				builtins_checker(t_ast *root);
int				cd(char **matrix);
int				builtin_export(char **matrix);
int				echo(char **matrix);
int				pwd(void);
int				env(char **args);
int				builtin_exit(t_ast *root, int *stdout_fd);
int				write_err_msg_exit(enum e_error error, const char *arg);
int				report_error_export(void);
int				show_variables(char **envp);
int				unset(char **args);
int				biggest_character(char character, char comparator);
void			builtins_caller(t_ast *root);
void			verifying_math_symbol(const char *arg,
					int *is_negative, int *has_math_symbol);

// Interrupt program
int				interrupt_program(char *input);

// Exec
char			***have_redirect(t_dlist *tokens);
char			**have_append(t_dlist *tokens);
char			**files_in(t_dlist *tokens, char **matrix_err);
char			**files_out(t_dlist *tokens, char **matrix_err);
void			execv_only_child(t_ast *root);
void			exec_cmd(t_ast *root);
void			ast_function(t_dlist **tokens);
void			tree_exec(t_ast *root);
int				check_append(char **mat_append, char *ref);
int				redir_fds_control(t_ast *root);
int				files_out_control(t_ast *root);
int				files_in_control(t_ast *root);

// Exec errors
void			converse_index(char **matrix_err, int result);
void			ambiguous_redirect_validation(char **matrix_err,
					t_dlist *tok, int result, int std);
int				redirect_in_error(char **matrix_err, char *file, int index);
int				redirect_out_error(char **matrix_err, char *file, int index);

#endif
