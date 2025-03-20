.PHONY : NAME all real-all debug clean fclean re

MAKEFLAGS += --no-print-directory

NAME = pipex
CC = cc
CFLAGS = -Werror -Wextra -Wall
LIB = libft/libft.a

CFLAGS_DEBUG = -g3
DEBUG_MODE =

SRCS_DIR = src
SRCS =	$(SRCS_DIR)/fds.c \
		$(SRCS_DIR)/free_all.c \
		$(SRCS_DIR)/ft_error.c \
		$(SRCS_DIR)/initialize.c \
		$(SRCS_DIR)/pipex.c $(SRCS_DIR)/tmp.c
OBJ_DIR = obj
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADER_DIR = include
HEADER = $(HEADER_DIR)/

SRCS_LIB = $(shell make -s -C libft print_src)
HEADER_LIB = $(shell make -s -C libft print_header)

all : $(LIB) check-build

check-build :
	@if [ -f "$(NAME)" ] \
		&& [ -z "$$(find "$(OBJ_DIR)" -type f -newer "$(NAME)")" ] \
		&& [ -z "$$(find libft \( -name "*.c" -o -name "*.h" -o -name "Makefile" \) -newer "$(LIB)")" ] \
		&& [ -z "$$(find "$(SRCS_DIR)" -name "*.c" -newer "$(NAME)")" ] \
		&& [ -z "$$(find "$(HEADER_DIR)" -name "*.h" -newer "$(NAME)")" ] \
		&& [ -z "$$(find "$(LIB)" -type f -newer "$(NAME)")" ] \
		&& [ -z "$$(find . -name "Makefile" -newer "$(NAME)")" ]; then \
		echo "✅👌 Pipex déjà compilé ! 👌✅"; \
	else \
		$(MAKE) real-all; \
	fi

real-all : $(LIB) $(OBJ_DIR) $(OBJS) $(NAME)

$(OBJ_DIR) :
	@mkdir -p $@

$(OBJS) : $(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c Makefile $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(LIB) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
	@echo "🎊🥳 Pipex compilé !! 🥳🎊"

$(LIB) : $(addprefix libft/, $(SRCS_LIB) $(HEADER_LIB)) libft/Makefile
	@echo "🎶📳 Appel libft 📳🎶"
	@$(MAKE) -C libft

debug :
	@echo "🛠️ Compilation pipex avec $(CFLAGS) $(CFLAGS_DEBUG) 🛠️"
	@$(MAKE) debug -C libft
	@$(MAKE) re CFLAGS="$(CFLAGS) $(CFLAGS_DEBUG)" DEBUG_MODE=debug

clean :
	@rm -rf $(OBJ_DIR)
	@echo "💨🧹 Nettoyage objets 🧹💨"

fclean : clean
ifndef DEBUG_MODE
	@$(MAKE) fclean -C libft
endif
	@rm -rf $(NAME)
	@echo "🫧🧽 Tout est clean !!🧽🫧"

re : fclean all