CC := cc
LIB_CMD := ar rcs
CFLAGS := -Wall -Wextra -Werror
NAME := libftprintf.a
LIB_MANDATORY := -I mandatory/includes
LIB_BONUS := -I bonus/includes 

OBJ_DIR := obj
SRC_MAND := mandatory/src
SRC_BONUS := bonus/src

HEAD_M := mandatory/includes/ft_printf.h
HEAD_B := bonus/includes/ft_printf_bonus.h

SRCS_M := $(SRC_MAND)/ft_print_address.c $(SRC_MAND)/ft_print_char.c \
	$(SRC_MAND)/ft_printf.c $(SRC_MAND)/ft_print_hex.c \
	$(SRC_MAND)/ft_putnbr.c $(SRC_MAND)/ft_putstr.c \
    $(SRC_MAND)/ft_uputnbr.c $(SRC_MAND)/ft_helper.c

SRCS_B := $(SRC_BONUS)/ft_address_parser_bonus.c $(SRC_BONUS)/ft_char_parser_bonus.c \
	$(SRC_BONUS)/ft_hex_parser_bonus.c $(SRC_BONUS)/ft_printf_bonus.c $(SRC_BONUS)/ft_putnbr_bonus.c\
    $(SRC_BONUS)/ft_string_parser_bonus.c $(SRC_BONUS)/ft_uputnbr_bonus.c $(SRC_BONUS)/numbers_utiles_bonus.c \
	$(SRC_BONUS)/helper_functions_bonus.c

OBJ_M := $(patsubst $(SRC_MAND)/%.c, $(OBJ_DIR)/%.o, $(SRCS_M))
OBJ_B := $(patsubst $(SRC_BONUS)/%.c, $(OBJ_DIR)/%.o, $(SRCS_B))


ifdef IS_BONUS
	OBJS := $(OBJ_B)
	SRC := $(SRC_BONUS)
	OTHER := $(OBJ_M)
	LIB := $(LIB_BONUS)
	HEADER := $(HEAD_B)
else
	OBJS := $(OBJ_M)
	SRC := $(SRC_MAND)
	OTHER := $(OBJ_B)
	LIB := $(LIB_MANDATORY)
	HEADER := $(HEAD_M)
endif

all: $(NAME)
$(NAME): $(OBJS)
	@rm -f $(NAME)
	$(LIB_CMD) $@ $^
	@rm -f $(OTHER)
$(OBJ_DIR)/%.o: $(SRC)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LIB) -c $< -o $@

bonus: 
	@$(MAKE) --no-print-directory IS_BONUS=1

$(OBJ_DIR):
	@mkdir -p $@
clean:
	@rm -rf $(OBJ_DIR)
fclean: clean
	@rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean bonus re
