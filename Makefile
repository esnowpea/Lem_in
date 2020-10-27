# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 13:56:52 by esnowpea          #+#    #+#              #
#    Updated: 2020/10/27 15:35:56 by esnowpea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Lem_in
NAME_EXEC = lem-in
TABS = \t\t

CC = gcc
FLAGS = -O2 -Wall -Werror -Wextra
LIB_FLAGS = -L$(LIBFT_DIR) -lft -L$(LIBFTPRINTF_DIR) -lftprintf

INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEADERS) -I$(LIBFTPRINTF_HEADERS)

LIBFT = Lib_FT
LIBFT_EXEC = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./lib/Libft/
LIBFT_HEADERS = $(LIBFT_DIR)inc/

LIBFTPRINTF = Lib_FT_Printf
LIBFTPRINTF_EXEC = $(LIBFTPRINTF_DIR)libftprintf.a
LIBFTPRINTF_DIR = ./lib/Libftprintf/
LIBFTPRINTF_HEADERS = $(LIBFTPRINTF_DIR)inc/

HEADERS_LIST = $(NAME).h
HEADERS_DIR = ./inc/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_DIR = src/
SRC_LIST =	main.c \
			init.c \
			print.c \
			parsing.c \
			solution.c \
			terminate.c \
			print_result.c \
			parsing_add_edge.c \
			parsing_last_chek.c \
			parsing_add_vertex.c \
			print_current_position_ants.c \
			print_result_step_ants_room.c \
			print_result_start_step_ants.c \
			print_result_start_step_ants_2.c \
			print_result_start_step_ants_3.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GRN = \033[0;32m
RED = \033[0;31m
YEL = \033[1;33m
END = \033[0m

.PHONY: all clean fclean re

all: $(NAME_EXEC)

$(NAME_EXEC): $(LIBFT_EXEC) $(LIBFTPRINTF_EXEC) $(OBJ_DIR) $(OBJ)
	@$(CC) $(FLAGS) $(LIB_FLAGS) $(INCLUDES) $(OBJ) -o $(NAME_EXEC)
	@echo "\n$(NAME):$(TABS)$(GRN)*.o files created$(END)"
	@echo "$(NAME):$(TABS)$(GRN)$(NAME_EXEC) created$(END)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME):$(TABS)$(GRN)$(OBJ_DIR) created$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GRN).$(END)\c"

$(LIBFT_EXEC):
	@echo "$(NAME):$(TABS)$(GRN)Creating $(LIBFT)...$(END)"
	@$(MAKE) -C $(LIBFT_DIR)

$(LIBFTPRINTF_EXEC):
	@echo "$(NAME):$(TABS)$(GRN)Creating $(LIBFTPRINTF)...$(END)"
	@$(MAKE) -C $(LIBFTPRINTF_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(LIBFTPRINTF_DIR) clean
	@rm -rf $(OBJ_DIR)
ifneq ($(strip $(wildcard $(OBJ))),)
	@echo "$(NAME):$(TABS)$(RED)*.o files deleted$(END)"
	@echo "$(NAME):$(TABS)$(RED)$(OBJ_DIR) deleted$(END)"
endif

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(LIBFTPRINTF_DIR) fclean
	@rm -f $(NAME_EXEC)
	@rm -f input_data.txt
ifneq ($(strip $(wildcard $(NAME_EXEC))),)
	@echo "$(NAME):$(TABS)$(RED)$(NAME_EXEC) deleted$(END)"
endif

re: fclean all
