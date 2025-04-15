CC := cc
CFLAGS := -MMD -Wall -Wextra -Werror
LDLIBS := -pthread

RM := rm -f
RMDIR := rm -rf

NAME := philo
SRCS := main.c data.c rules.c forks.c philos.c actions.c death.c time.c \
		print.c utils.c debug.c
BUILD_DIR := build
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:%.c=$(BUILD_DIR)/%.d)


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)/%.d Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@


%.d: ;

-include $(DEPS)


clean:
	$(RMDIR) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all