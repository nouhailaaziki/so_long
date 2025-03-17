COMPILER = cc

CFLAGS = -Wall -Wextra -Werror -Imlx

RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

MLX = -lmlx -framework OpenGL -framework AppKit

MANDATORY = mandatory/events.c \
			mandatory/card_parsing.c \
			mandatory/display.c \
			mandatory/motion.c \
			mandatory/so_long.c \
			mandatory/check_path.c \
			mandatory/get_next_line.c \
			mandatory/get_next_line_utils.c

BONUS = bonus/events_bonus.c \
		bonus/card_parsing_bonus.c \
		bonus/display_bonus.c \
		bonus/motion_bonus.c \
		bonus/so_long_bonus.c \
		bonus/check_path_bonus.c \
		bonus/get_next_line_bonus.c \
		bonus/get_next_line_utils_bonus.c \
		bonus/enemy_manager_bonus.c \
		bonus/enemy_motion_bonus.c

OBJM = ${MANDATORY:.c=.o}
OBJB = ${BONUS:.c=.o}

NAME = so_long
BONUS_NAME = so_long_bonus

LIBFT = libft/libft.a

HEADER = mandatory/so_long.h \
		libft/libft.h \
		mandatory/get_next_line.h

HEADER_BONUS = bonus/so_long_bonus.h \
				libft/libft.h \
				bonus/get_next_line_bonus.h

all: ${NAME}

${NAME} : ${OBJM} ${LIBFT}
	@echo "${RED}🚀 Launching compilation...${RESET}"
	${COMPILER} ${CFLAGS} ${OBJM} ${LIBFT} ${MLX} -o ${NAME}
	@echo "${GREEN}✅ ${NAME} successfully compiled!${RESET}"

bonus : ${OBJB} ${LIBFT}
	@echo "${RED}🚀 Launching compilation...${RESET}"
	${COMPILER} ${CFLAGS} ${OBJB} ${LIBFT} ${MLX} -o ${BONUS_NAME}
	@echo "${GREEN}✅ ${BONUS_NAME} successfully compiled!${RESET}"

mandatory/%.o: mandatory/%.c ${HEADER}
	${COMPILER} ${CFLAGS} -c $< -o $@

bonus/%.o: bonus/%.c ${HEADER_BONUS}
	${COMPILER} ${CFLAGS} -c $< -o $@

${LIBFT}:
	make -C libft

clean:
	${RM} ${OBJM} $(OBJB)
	make clean -C libft
	@echo "${RED}🗑 Object files removed!${RESET}"

fclean: clean
	${RM} ${NAME} ${BONUS_NAME}
	make fclean -C libft
	@echo "${RED}🔥 Executable removed!${RESET}"

re: fclean all

.PHONY: all clean fclean re
