CC = cc
CFLAGS = -Wall -Wextra -Werror

#dossiers
SRC_DIR = ./src
OBJ_DIR = ./obj

#fichiers source
SRC = main.c utils.c init.c routine.c routine2.c time.c messages.c watcher.c

#objets
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

#nom de l'executable
NAME = philo

#regles de compilation
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
