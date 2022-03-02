# ========== [ Project files ]

# TODO set name
NAME		= pipex

# TODO set libriaires
LIB_DIR		= 
LIB			= 
LIB			:= $(LIB:%=$(LIB_DIR)/%)

# TODO set frameworks
FRAMEWORK	=

INC_DIR		= include
INC			= $(INC_DIR) \
			  $(LIB:%=%/$(INC_DIR))

# TODO set sources
SRC_DIR		= src
SRCS		= mandatory/cmd.c						\
			  mandatory/free.c						\
			  mandatory/pipex.c						\
			  mandatory/process.c					\
			  mandatory/split.c						\
			  mandatory/string.c					\
			  mandatory/utils.c						
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJ_DIR 	= obj
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_BONUS_DIR		= src/bonus
SRCS_BONUS			= cmd_bonus.c							\
					  files_bonus.c							\
					  free_bonus.c							\
					  here_doc_bonus.c						\
					  itoa_bonus.c							\
					  pipex_bonus.c							\
					  string_bonus.c						\
					  split_bonus.c							\
					  utils_bonus.c							\
					  get_next_line/get_next_line.c			\
					  get_next_line/get_next_line_utils.c	
SRCS_BONUS			:= $(SRCS_BONUS:%=$(SRC_BONUS_DIR)/%)

OBJ_BONUS_DIR	 	= obj
OBJS_BONUS			= $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

# ========== [ Compiler flags ]
#
# Add a flag via the command line: 'make target VAR=flag'.

CC			= gcc

# TODO set extra compiler flags
CFLAGS		=

# TODO set extra linker flags
CPPFLAGS	=
LDFLAGS		=
LDLIBS		=

CFLAGS		+= -Wall -Wextra -Werror        									# -Wconversion  -Wsign-conversion
CPPFLAGS	+= $(INC:%=-I%)
LDFLAGS 	+= $(LIB:%=-L%) $(FRAMEWORK)
LDLIBS		+= $(LIB:$(LIB_DIR)/lib%=-l%)

# ========== [ Misc ]

RM		= rm -rf
MAKE	= make -C

# ========== [ Recipe ]

all: $(NAME)

debug: CPPFLAGS	+= -D PINFO=1
debug: NAME := $(NAME)-debug
debug: $(NAME)

sanitizer: CFLAGS += -fsanitize=address,undefined,signed-integer-overflow
sanitizer: debug

$(NAME): $(OBJS)
	@for f in $(LIB); do $(MAKE) $$f --no-print-directory; done
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	@$(ECHO)"$(G)created $(END)$(NAME)\n"

bonus: $(OBJS_BONUS)
	@for f in $(LIB); do $(MAKE) $$f --no-print-directory; done
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS_BONUS) $(LDLIBS) -o $(NAME)
	@$(ECHO)"$(G)created $(END)$(NAME)\n"

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)$@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)$@"

clean:
	@for f in $(LIB); do $(MAKE) $$f clean --no-print-directory; done
	@[ -d $(OBJ_DIR) ] \
		&& $(RM) $(OBJ_DIR) && $(ECHO)"$(R)removed$(END) $(OBJ_DIR)/\n" || true

fclean: clean
	@for f in $(LIB); do $(MAKE) $$f fclean --no-print-directory; done
	@[ -f $(NAME) ] \
		&& $(RM) $(NAME) && $(ECHO)"$(R)removed$(END) $(NAME)/\n" || true

norm:
	@for f in $(LIB); do $(MAKE) $$f norm --no-print-directory; done
	@norminette -R CheckForbiddenSourceHeader $(SRCS) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) sources\n"
	@norminette -R CheckDefine $(INC_DIR) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) headers\n"

update:
	@git pull
	@git submodule update
	@$(ECHO)"$(G)updated$(END)\n"

re : fclean all

.PHONY: all debug clean fclean norm update re

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
ECHO	= echo -n "\r\033[K$(NAME): "
