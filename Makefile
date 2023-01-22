CFLAGS = -Wall -Wextra -Werror
SOURCES = $(wildcard *.c)
NAME = $(patsubst %.c,%,$(SOURCES))

all: $(NAME)

$(NAME): %: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all
