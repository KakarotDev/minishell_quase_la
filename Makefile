# program name #
NAME = minishell

# shell #
SHELL := /bin/bash

# misc #
COUNT = -1
SLEEP := sleep 0.2

# colors #
DEFAULT=\033[39m
BLACK=\033[30m
DARK_RED=\033[31m
DARK_GREEN=\033[32m
DARK_YELLOW=\033[33m
DARK_BLUE=\033[34m
DARK_MAGENTA=\033[35m
DARK_CYAN=\033[36m
LIGHT_GRAY=\033[37m
DARK_GRAY=\033[90m
RED=\033[91m
GREEN=\033[92m
ORANGE=\033[93m
BLUE=\033[94m
MAGENTA=\033[95m
CYAN=\033[96m
WHITE=\033[97m
BG_DEFAULT=\033[49m
BG_BLACK=\033[40m
BG_DARK_RED=\033[41m
BG_DARK_GREEN=\033[42m
BG_DARK_YELLOW=\033[43m
BG_DARK_BLUE=\033[44m
BG_DARK_MAGENTA=\033[45m
BG_DARK_CYAN=\033[46m
BG_LIGHT_GRAY=\033[47m
BG_DARK_GRAY=\033[100m
BG_RED=\033[101m
BG_GREEN=\033[102m
BG_ORANGE=\033[103m
BG_BLUE=\033[104m
BG_MAGENTA=\033[105m
BG_CYAN=\033[106m
BG_WHITE=\033[107m
RESET=\033[0m
RESET_TERM=\r\033[K

# messages #
MANDATORY = Program compiled
LBONUS = Bonus Program compiled
CLEAN = Objects delete
FCLEAN = Program delete
LIBNAME = minishell
BLIBNAME = minishell_bonus
COMP = Compiling

# debug and normal flags #
DFLAGS = -Wall -Wextra -Werror -g3 # TO DEBBUG
CFLAGS = -Wall -Werror -Wextra -g3 -pedantic -flto -MD -MP # FOR DEPENDENCIES
LFLAGS = -march=native # TO OPTIMIZE FOR SPECIFIC ARCHITECTURE
FFLAGS = -lreadline # FLAGS THAT ONLY WORK AT THE END OF LINE (AFTER OBJECTS)

# paths #
SRC = src
BONUS = $(SRC)/bonus
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
CFILES += $(addprefix $(AST)/, ast_organizer.c ast.c ast_aux_functions.c)
CFILES += $(addprefix $(AUXILIARY)/, is_an_address.c go_to.c ft_close_fds.c ft_how_many_pipes.c temp_functions.c \
	free_struct_token.c ft_count_tokens.c ft_cpy_array_data.c ft_destructor_struct.c ft_free_ast.c \
	ft_free_matrix.c ft_have_char.c ft_have_op.c ft_is_redirect.c ft_open_fd.c ft_open_fork.c ft_print_ast.c ft_print_dlist.c \
	ft_print_matrix.c ft_strndup.c get_ret_process.c hook_environ.c last_exit_status.c syntax_error.c hook_pwd.c set_entrance.c \
	skip_single_quotes.c validating_varname.c ft_isspace.c ft_getenv.c ft_strcmp.c ft_matrix_count.c handling_pipe.c \
	its_in_heredoc.c heredoc_file_counter.c received_sigint_in_heredoc.c is_process.c)
CFILES += $(addprefix $(BUILTINS)/, cd.c export.c echo.c pwd.c env.c export_utils.c exit.c unset.c)
CFILES += $(addprefix $(DLST_PROCEDURES)/, ft_add_next.c ft_append_dlist.c ft_cpy_dlst.c ft_cpy_node.c ft_dlist_delete_from.c \
	ft_dlist_have_type.c ft_dlist_last_occur.c ft_dlst_last.c ft_newnode_dlist.c)
CFILES += $(addprefix $(ENVIRONMENT)/, copy_environ.c read_var.c)
CFILES += $(addprefix $(ERRORS)/, path_validation.c)
CFILES += $(addprefix $(EXECUTION)/, redirect_errors.c redirect_aux_functions.c redirect.c cmds_paths.c builtins_caller.c)
CFILES += $(addprefix $(EXPANSIONS)/, expansion.c expansion_utils.c quote_removal.c)
CFILES += $(addprefix $(LEXER)/, lexer.c generate_tokens.c quote_validation.c)
CFILES += $(addprefix $(PARSER)/, parser.c check_redirections.c check_pipes.c parser_validation.c)
CFILES += $(addprefix $(SIGNAL)/, signal.c interrupt_program.c)
CFILES += $(addprefix $(START)/, run_program.c)
CFILES += $(addprefix $(HEREDOC)/, heredoc.c heredoc_utils.c)

VAL = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt
VAL_TXT = valgrind-out.txt

# obj dir #
OBJECT = $(CFILES:%.c=$(OBJ)/%.o)
BIN_OBJ = $(MAIN_SRC:%.c=$(OBJ)/%.o)

# define bonus #
ifdef WITH_BONUS
	NAME = $(BLIBNAME)
	compile = compile_bonus
	MANDATORY = $(LBONUS)
	MAGENTA = $(YELLOW)
	LIBNAME = $(BLIBNAME)
endif


# define debbug #
ifdef WITH_DEBBUG
	CFLAGS = $(DFLAGS)
endif

# functions #
define create_objects_dir
	mkdir -p $(dir $@)
endef

define compile
	$(CC) -o $(NAME) $(CFLAGS) $(LFLAGS) $(INCLUDES) $(LINCLUDES) $(OBJECT) $(BIN_OBJ) $(LIBFT) $(FFLAGS)
	$(SLEEP)
	printf "\n$(MAGENTA)$(MANDATORY)\n$(RESET)"
endef

define compile_bonus
	$(CC) -o $(NAME) $(CFLAGS) $(LFLAGS) $(INCLUDES) $(LINCLUDES) $(OBJECT) $(BIN_OBJ) $(LIBFT) $(FFLAGS)
	$(SLEEP)
	printf "\n$(MAGENTA)$(MANDATORY)\n$(RESET)"
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

define bonus
	@make WITH_BONUS=TRUE -s
endef

define debug
	$(call clean)
	$(call fclean)
	$(MAKE) WITH_DEBBUG=TRUE -s
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

bonus:
	$(call bonus)

debug:
	$(call debug)

.PHONY: all bonus clean fclean re debug Makefile
.DEFAULT_GOAL := all
.SILENT: