COMPILER = cc

CFLAGS = -Wall -Wextra -Werror -Imlx

RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

MLX = -lmlx -framework OpenGL -framework AppKit

MANDATORY = mandatory/events.c \
			mandatory/card_parsing.c \
			mandatory/initialization.c \
			mandatory/display.c \
			mandatory/motion.c \
			mandatory/main.c \
			mandatory/check_path.c \
			libraries/get_next_line/get_next_line.c \
			libraries/get_next_line/get_next_line_utils.c

OBJM = ${MANDATORY:.c=.o}

NAME = so_long

LIBFT = libraries/libft/libft.a

HEADER = mandatory/so_long.h \
		libraries/libft/libft.h \
		libraries/get_next_line/get_next_line.h

all: ${NAME}

${NAME} : ${OBJM} ${LIBFT}
	@echo "${RED}🚀 Launching compilation...${RESET}"
	${COMPILER} ${CFLAGS} ${OBJM} ${LIBFT} ${MLX} -o ${NAME}
	@echo "${GREEN}✅ ${NAME} successfully compiled!${RESET}"

mandatory/%.o: mandatory/%.c ${HEADER}
	${COMPILER} ${CFLAGS} -c $< -o $@

${LIBFT}:
	make -C libraries/libft

clean:
	${RM} ${OBJM}
	make clean -C libraries/libft
	@echo "${RED}🗑 Object files removed!${RESET}"

fclean: clean
	${RM} ${NAME}
	make fclean -C libraries/libft
	@echo "${RED}🔥 Executable removed!${RESET}"

re: fclean all

.PHONY: all clean fclean re
