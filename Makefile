NAME 			= irctester
CC				= c++

CLASSES_SRCS	= Client.cpp Command.cpp
COMMANDS_SRCS	= 
UTILS_SRCS		= 
MAIN_SRCS		= 

SOURCES			= $(addprefix srcs/classes/, $(CLASSES_SRCS)) \
				  $(addprefix srcs/commands/, $(COMMANDS_SRCS)) \
				  $(addprefix srcs/utils/, $(UTILS_SRCS)) \
				  $(addprefix srcs/, $(MAIN_SRCS))
OBJECTS			= $(SOURCES:.cpp=.o)
OBJECTS_FOLDER  = $(addprefix objs/, $(OBJECTS))

CMD_HEADERS		= 
HEADERS_FILES	= 

HEADERS			= $(addprefix includes/commands/, $(CMD_HEADERS)) \
				  $(addprefix includes/, $(HEADERS_FILES))

FLAGS 			= -Wall -Wextra -Werror -std=c++98
OPTIONS 		= -I includes -I includes/commands

ifeq ($(DEBUG), true)
	FLAGS += -g3
endif

#################################################################################

RED 	 = '\033[0;31m'
GREEN 	 = '\033[0;32m'
YELLOW 	 = '\033[0;33m'
BLUE 	 = '\033[0;34m'
PURPLE 	 = '\033[0;35m'
NC 		 = '\033[0m'

#################################################################################

objs/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $(OPTIONS) $< -o $@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME): $(OBJECTS_FOLDER) $(HEADERS)
	@$(CC) $(FLAGS) $(OPTIONS) -o $@ $(OBJECTS_FOLDER)
	@echo $(BLUE)✅ $@ built! $(NC)

all: $(NAME)

clean:
	@rm -rf objs
	@echo $(YELLOW)🗑️ objs directory deleted! $(NC)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)🗑️ $(NAME) deleted! $(NC)

re: fclean all

.PHONY: all clean fclean re
