# program name #
NAME = minishell

# shell #
SHELL := /bin/bash

# misc #
COUNT = -1
SLEEP := sleep 0.2

# colors #
DEFAULT=\033[39m
DARK_RED=\033[31m
DARK_GREEN=\033[32m
RED=\033[91m
GREEN=\033[92m
RESET=\033[0m
RESET_TERM=\r\033[K

# messages #
MANDATORY = Program compiled
CLEAN = Objects delete
FCLEAN = Program delete
LIBNAME = minishell
COMP = Compiling

# debug and normal flags #
CFLAGS = -Wall -Werror -Wextra -g3 -pedantic -flto -MD -MP # FOR DEPENDENCIES
FFLAGS = -lreadline # FLAGS THAT ONLY WORK AT THE END OF LINE (AFTER OBJECTS)

# paths #
SRC = src
INC = inc
OBJ = obj

# includes #
HEADERS = $(addprefix $(INC)/, minishell.h)

# files path #
AST = $(SRC)/ast
AUXILIARY = $(SRC)/auxiliary
BUILTINS = $(SRC)/builtins
DLST_PROCEDURES = $(SRC)/dlst_procedures
ENVIRONMENT = $(SRC)/environment
ERRORS = $(SRC)/errors
EXECUTION = $(SRC)/execution
EXPANSIONS = $(SRC)/expansion
LEXER = $(SRC)/lexer
PARSER = $(SRC)/parser
SIGNAL = $(SRC)/signal
START = $(SRC)/start
HEREDOC = $(SRC)/heredoc

# libs #
INCLUDES = -I$(INC)/ -Ilib/libft/inc/
LINCLUDES = -L$(LIBFT_PATH) -lft

LIBFT = lib/libft/libft.a
LIBFT_PATH = lib/libft

# main #
MAIN_SRC = ./src/main.c

# files mandatory #
CFILES += $(addprefix $(AST)/, ast_creator.c ast_destructor.c ast_organizer.c)
CFILES += $(addprefix $(AUXILIARY)/, pipe_count.c creat_file_mat.c write_err_msg_status.c go_to.c\
	free_struct_token.c ft_cpy_array_data.c ft_destructor_struct.c \
	ft_free_ast.c ft_free_matrix.c ft_have_char.c ft_have_op.c ft_is_redirect.c ft_open_fd.c\
	ft_strndup.c get_ret_process.c hook_environ.c last_exit_status.c syntax_error.c hook_pwd.c set_entrance.c \
	skip_single_quotes.c ft_isspace.c ft_getenv.c ft_strcmp.c ft_matrix_count.c handling_pipe.c \
	its_in_heredoc.c heredoc_file_counter.c received_sigint_in_heredoc.c is_process.c)
CFILES += $(addprefix $(BUILTINS)/, cd.c export.c echo.c pwd.c env.c export_utils.c exit.c exit_utils.c unset.c)
CFILES += $(addprefix $(DLST_PROCEDURES)/, ft_add_next.c ft_append_dlist.c \
	ft_dlst_last.c ft_newnode_dlist.c)
CFILES += $(addprefix $(ENVIRONMENT)/, copy_environ.c read_var.c)
CFILES += $(addprefix $(ERRORS)/, path_validation.c)
CFILES += $(addprefix $(EXECUTION)/, ast_exec.c redirect_files_in.c redirect_files_out.c append_functions.c redirect_errors.c \
	redirect_errors_aux.c redirect.c cmds_paths.c builtins_caller.c)
CFILES += $(addprefix $(EXPANSIONS)/, expansion.c expansion_utils.c quote_removal.c)
CFILES += $(addprefix $(LEXER)/, lexer.c generate_tokens.c generate_tokens_utils.c quote_validation.c)
CFILES += $(addprefix $(PARSER)/, parser.c check_redirections.c check_pipes.c parser_validation.c)
CFILES += $(addprefix $(SIGNAL)/, signal.c interrupt_program.c)
CFILES += $(addprefix $(START)/, run_program.c)
CFILES += $(addprefix $(HEREDOC)/, heredoc.c heredoc_utils.c heredoc_expansion.c)

# obj dir #
OBJECT = $(CFILES:%.c=$(OBJ)/%.o)
BIN_OBJ = $(MAIN_SRC:%.c=$(OBJ)/%.o)

# functions #
define create_objects_dir
	mkdir -p $(dir $@)
endef

define compile
	$(CC) -o $(NAME) $(CFLAGS) $(INCLUDES) $(LINCLUDES) $(OBJECT) $(BIN_OBJ) $(LIBFT) $(FFLAGS)
	$(SLEEP)
	printf "\n$(GREEN)$(MANDATORY)\n$(RESET)"
endef

define compile_source
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	$(MAKE) -sC $(LIBFT_PATH)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<
	printf "$(RESET_TERM)%d%%  $(GREEN)$(COMP) $(notdir $<) -> $(notdir $@) to $(NAME) \r$(RESET)" $$(echo $$(($(COUNT) * 100 / $(words $(OBJECT)))))
endef

define clean
	$(MAKE) fclean -sC $(LIBFT_PATH)
	$(RM) -rf $(OBJ)/ && $(RM) -rf $(VAL_TXT)
	$(SLEEP)
	printf "$(RED)$(CLEAN)$(RESET)\n"
endef

define fclean
	$(call eraseBins)
	@$(SLEEP)
	@printf "$(RED)$(FCLEAN)$(RESET)\n"
endef

define eraseBins
	$(if $(NAME),@$(RM) $(NAME))
	$(if $(BLIBNAME),@$(RM) $(BLIBNAME))
endef

# rules #
all: $(NAME)

$(NAME): $(OBJECT) $(BIN_OBJ)
	$(call create_objects_dir)
	$(call compile)

$(OBJ)/%.o: %.c
	$(call create_objects_dir)
	$(call compile_source)

-include $(OBJECT:.o=.d)

clean:
	$(call clean)

fclean: clean
	$(call fclean)

re: fclean all

.PHONY: all clean fclean re Makefile
.DEFAULT_GOAL := all
.SILENT: