# Project name
NAME = libft.a

# tool macros
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(HEADER)

# path macros
SRC_PATH = src
OBJ_PATH = obj
HEADER = inc

FILES = ft_arg_check \
		ft_atoi \
		ft_bzero \
		ft_calloc \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_itoa \
		ft_lstadd_back \
		ft_lstadd_front \
		ft_lstlast \
		ft_lstnew \
		ft_lstsize \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_printf \
		ft_putchar_fd \
		ft_putchar \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putnbr_hex \
		ft_putnbr_int \
		ft_putnbr_p \
		ft_putnbr_unsigned_int \
		ft_putstr_fd \
		ft_putstr \
		ft_split \
		ft_strchr \
		ft_strdup \
		ft_striteri \
		ft_strjoin \
		ft_strlcat \
		ft_strlcpy \
		ft_strlen \
		ft_strmapi \
		ft_strncmp \
		ft_strnstr \
		ft_strrchr \
		ft_strtrim \
		ft_substr \
		ft_tolower \
		ft_toupper \
		get_next_line_utils \
		get_next_line

# Object files
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(FILES)))

all: $(NAME)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@ar rcs $@ $^

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf *$(NAME)

re: fclean all
