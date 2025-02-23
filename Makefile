SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
SERVER_OBJ = server.o 
OBJ = ft_printf.o ft_putunbr_base.o ft_putaddress.o \
	  ft_strlen.o ft_putnbr.o ft_putchar.o ft_putstr.o ft_strchr.o ft_atoi.o \

CLIENT_OBJ = client.o
CLIENT_BONUS_OBJ = ./bonus/client_bonus.o
SERVER_BONUS_OBJ = ./bonus/server_bonus.o
BONUS_OBJ =./bonus/ft_printf_bonus.o ./bonus/ft_putunbr_base_bonus.o ./bonus/ft_putaddress_bonus.o \
	  ./bonus/ft_strlen_bonus.o ./bonus/ft_putnbr_bonus.o ./bonus/ft_putchar_bonus.o ./bonus/ft_putstr_bonus.o ./bonus/ft_strchr_bonus.o ./bonus/ft_atoi_bonus.o


all: $(CLIENT) $(SERVER)

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT): $(CLIENT_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(OBJ) -o $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(OBJ) -o $(SERVER)


$(CLIENT_BONUS): $(CLIENT_BONUS_OBJ) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(BONUS_OBJ) -o $(CLIENT_BONUS)
$(SERVER_BONUS): $(SERVER_BONUS_OBJ) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(BONUS_OBJ) -o $(SERVER_BONUS)

./bonus/%.o: ./bonus/%.c ./bonus/server_bonus.h ./bonus/ft_printf_bonus.h ./bonus/client_bonus.h ./bonus/libft_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c server.h ft_printf.h client.h libft.h
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)
	rm -f $(CLIENT_OBJ)
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_BONUS_OBJ)
	rm -f $(SERVER_BONUS_OBJ)
fclean: clean
	rm -f $(SERVER)
	rm -f $(CLIENT)
	rm -f $(SERVER_BONUS)
	rm -f $(CLIENT_BONUS)

re : fclean all