NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
RM			= rm -f

SRCDIR		= src
INCDIR		= include
OBJDIR		= obj

SOURCES		= main.c \
			  utils.c \
			  status.c \
			  sync.c \
			  init.c \
			  init_philos.c \
			  simulation.c \
			  philosopher.c \
			  forks.c \
			  actions.c \
			  monitor.c \
			  cleanup.c

SRCS		= $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS		= $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))
INCLUDES	= -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re