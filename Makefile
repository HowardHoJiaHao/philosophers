NAME    = philo
CC      = gcc

# Add -g for debugging, -pthread for threading
CFLAGS  = -Wall -Werror -Wextra 
# -pthread -g
# Optional: -fsanitize=address,thread

# Source files
SRC     = philosopher.c argvalidation.c error_handling.c utils.c work.c checking_philo.c timeprocess.c

# Object files
OBJS    = $(SRC:.c=.o)

all: $(NAME)

# Compile each .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link all .o files
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean