# ========== [ Project files ]
#
# Adjust NAME and SRCS to your project.

# TODO set name
NAME		= libft
TARGET 		= $(NAME).a

INC_DIR 	= include
INC			= $(INC_DIR)

# TODO set sources
SRC_DIR		= src
SRCS 		= ft_atoi.c 				\
			  ft_bzero.c 				\
			  ft_calloc.c 				\
			  ft_isalnum.c 				\
			  ft_isalpha.c 				\
			  ft_isascii.c 				\
			  ft_isdigit.c 				\
			  ft_isprint.c 				\
			  ft_memchr.c 				\
			  ft_memcmp.c 				\
			  ft_memcpy.c 				\
			  ft_memmove.c 				\
			  ft_memset.c 				\
			  ft_strchr.c 				\
			  ft_strlcat.c 				\
			  ft_strlcpy.c 				\
			  ft_strlen.c 				\
			  ft_strncmp.c 				\
			  ft_strnstr.c 				\
			  ft_strrchr.c 				\
			  ft_tolower.c 				\
			  ft_toupper.c 				\
			  ft_strdup.c 				\
			  ft_substr.c 				\
			  ft_strjoin.c 				\
			  ft_strtrim.c 				\
			  ft_split.c 				\
			  ft_itoa.c 				\
			  ft_strmapi.c 				\
			  ft_striteri.c				\
			  ft_putchar_fd.c 			\
			  ft_putstr_fd.c 			\
			  ft_putendl_fd.c			\
			  ft_putnbr_fd.c			\
			  ft_lstnew.c 				\
			  ft_lstadd_front.c			\
			  ft_lstsize.c 				\
			  ft_lstlast.c 				\
			  ft_lstadd_back.c 			\
			  ft_lstdelone.c 			\
			  ft_lstclear.c				\
			  ft_lstiter.c 				\
			  ft_lstmap.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJ_DIR 	= obj
OBJS 		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ========== [ Compiler flags ]

CC 			= gcc

# TODO set extra compiler flags
CFLAGS 		=

# TODO set extra linker flags
CPPFLAGS	=

CFLAGS 		+= -Wall -Wextra -Werror -Wconversion
CPPFLAGS	+= $(INC:%=-I%)

# ========== [ Misc ]

RM 			= rm -rf

# ========== [ Recipe ]

all: $(TARGET)

sanitizer: CFLAGS += -fsanitize=address,undefined,signed-integer-overflow
sanitizer: $(TARGET)

$(TARGET): $(OBJS)
	@ar rcs $(TARGET) $(OBJS)
	@$(ECHO)"$(G)created$(END) $(END)$(TARGET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)$@"

clean:
	@[ -d $(OBJ_DIR) ] \
		&& $(RM) $(OBJ_DIR) && $(ECHO)"$(R)removed$(END) $(OBJ_DIR)/\n" || true

fclean: clean
	@[ -f "$(TARGET)" ] && $(RM) $(TARGET) && $(ECHO)"$(R)removed$(END) $(TARGET)\n" || true

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) sources\n"
	@norminette -R CheckDefine $(INC_DIR) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) headers\n"

update:
	@git pull
	@$(ECHO)"$(G)updated$(END)\n"

re: fclean all

.PHONY: all clean fclean norm update re

# ========== [ Stdout ]

R		= $(shell tput setaf 1)
G		= $(shell tput setaf 2)
Y		= $(shell tput setaf 3)
B		= $(shell tput setaf 4)
M		= $(shell tput setaf 5)
C		= $(shell tput setaf 6)
W		= $(shell tput setaf 7)
K		= $(shell tput setaf 8)
END		= $(shell tput sgr0)
ECHO  	= echo -n "\r\033[K$(NAME): "
