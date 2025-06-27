NAME    := philosophers
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -pthread
RM      := rm -f

SRCDIR  := .
OBJDIR  := obj

SOURCES := 
SRCS    := $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS    := $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

GREEN   := \033[1;32m]
YELLOW  := \033[1;33m]
BLUE    := \033[1;34m]
RESET   := \033[0m]
CHECK   := ✓

all: title $(NAME)
	@echo "$(GREEN)[$(CHECK)] Build complete.$(RESET)"

$(NAME): $(OBJS)
	@echo "$(YELLOW)[~] Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c philosophers.h | $(OBJDIR)
	@echo "$(BLUE)[*] Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@$(RM) -r $(OBJDIR)
	@echo "$(BLUE)[x] Object files cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)[x] Binary removed.$(RESET)"

re: fclean all

title:
	@echo "$(BLUE)============================$(RESET)"
	@echo "$(GREEN)==  Building Philosophers ==$(RESET)"
	@echo "$(BLUE)============================$(RESET)"

.PHONY: all clean fclean re title