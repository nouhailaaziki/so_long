COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

MANDATORY =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
			ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_strjoin.c ft_split.c \
			ft_striteri.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_itoa.c \
			ft_isdigit.c ft_strmapi.c ft_strnstr.c ft_putchar_fd.c ft_strtrim.c

BONUS =	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
		ft_lstsize_bonus.c ft_lstadd_back_bonus.c ft_lstmap_bonus.c

OBJM = $(MANDATORY:.c=.o)

OBJB = $(BONUS:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME) : $(OBJM)
	ar rc $(NAME) $(OBJM)

bonus: $(OBJB)
	ar rc $(NAME) $(OBJB)

%.o: %.c libft.h
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJM) $(OBJB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
