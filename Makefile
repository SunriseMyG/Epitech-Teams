##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile for printf
##

SHARED =	./shared/myrecv.c	\
			./shared/strtrim.c	\
			./shared/quote_parser.c \
			./shared/args_parser.c	\
			./shared/quote_remover.c	\

SERVER =	./server/main.c	\
			./server/help.c	\
			./server/uuid.c	\
			./server/init.c	\
			./server/loop.c	\
			./server/count_args.c \
			./server/command_handler.c \
			./server/message_handler.c \
			./server/getclientsocket.c \
			./server/commands/help_cli.c \
			./server/commands/login.c \
			./server/commands/logout.c \
			./server/commands/users.c \
			./server/commands/message.c \
			./server/commands/user.c \
			./server/commands/messages.c \
			./server/commands/subscribe.c \
            ./server/commands/subscribed.c \
            ./server/commands/unsubscribe.c \
			./server/commands/create.c \
			./server/commands/channel.c \
			./server/commands/thread.c \
			./server/commands/reply.c \
			./server/commands/set.c \
			./server/commands/list.c \
			./server/commands/info.c \
			./server/db/initdb.c \
			./server/db/getuser.c \
			./server/sendlog.c \
			${SHARED}	\

CLIENT =	./client/main.c	\
			./client/help.c	\
			./client/receive_message_handler.c	\
			./client/liblog_handler.c	\
			./client/log/login_logout.c	\
			./client/log/unknown_user.c	\
			./client/log/unknown_team.c	\
			./client/log/received.c	\
			./client/log/users.c	\
			./client/log/unauthorized.c	\
			./client/log/messages.c	\
			./client/log/un_subscribe.c	\
			./client/log/team.c \
			./client/log/channel.c \
			./client/log/thread.c \
			./client/log/list.c \
			./client/log/info.c \
			./client/log/reply.c \
			${SHARED}	\

LIB = -L./libs/myteams -lmyteams

DEBUG_FLAGS = -std=gnu17 -Wall -Wextra -g3

SERVER_EXECUTABLE_NAME =	myteams_server

CLIENT_EXECUTABLE_NAME =	myteams_cli

all:	build

build:
	@export LD_LIBRARY_PATH=libs/myteams/.
	@gcc $(SERVER) $(LIB) $(DEBUG_FLAGS) -o $(SERVER_EXECUTABLE_NAME)
	@gcc $(CLIENT) $(LIB) $(DEBUG_FLAGS) -o $(CLIENT_EXECUTABLE_NAME)

clean:
	@rm -rf *.o

fclean: clean
	@rm -f $(SERVER_EXECUTABLE_NAME)
	@rm -f $(CLIENT_EXECUTABLE_NAME)

re:	fclean build

coding-style:
	@coding-style . .
	@clear
	@cat coding-style-reports.log
	@rm -f coding-style-reports.log

.PHONY: all build clean fclean re coding-style
