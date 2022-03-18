NONE			=	\033[0;0m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
PURPLE			=	\033[0;35m

CXX				=	clang++
CXXFLAGS		=	-Wall -Wextra -Werror -std=c++98
CXXFLAGS		=	-fsanitize=address
RM				=	rm -rf

NAME_SERVER		=	server

OBJDIR			=	./obj/
HEADERDIR		=	./includes/

SRC_MAIN_DIR	=	./src/
SRC_MAIN		=	webserver.cpp
OBJ_MAIN		=	$(addprefix $(OBJDIR), $(SRC_MAIN:.cpp=.o))

SRC_SERVER_DIR	=	./src/server/
SRC_SERVER		=	Server.cpp Socket.cpp ListeningSocket.cpp BoundSocket.cpp wrapsock.cpp
OBJ_SERVER		=	$(addprefix $(OBJDIR), $(SRC_SERVER:.cpp=.o))
HEADER_SERVER	=	$(addprefix $(HEADERDIR), Server.hpp Socket.hpp ListeningSocket.hpp BoundSocket.hpp)

SRC_HTTP_DIR	=	./src/http/
SRC_HTTP		=	HttpRequest.cpp HttpResponse.cpp
OBJ_HTTP		=	$(addprefix $(OBJDIR), $(SRC_HTTP:.cpp=.o))
HEADER_HTTP		=	$(addprefix $(HEADERDIR), HttpRequest.hpp HttpResponse.hpp)

SRC_UTILS_DIR	=	./src/utils/
SRC_UTILS		=	error.cpp stringUtils.cpp
OBJ_UTILS		=	$(addprefix $(OBJDIR), $(SRC_UTILS:.cpp=.o))
HEADER_UTILS	=	$(addprefix $(HEADERDIR), utils.hpp)


all: $(NAME_SERVER)

$(NAME_SERVER): $(OBJDIR)  $(OBJ_MAIN) $(OBJ_SERVER) $(OBJ_UTILS) $(OBJ_HTTP) $(HEADER_SERVER) $(HEADER_UTILS) $(HEADERDIR)
	$(CXX) $(CXXFLAGS) $(OBJ_MAIN) $(OBJ_SERVER) $(OBJ_HTTP) $(OBJ_UTILS) -o $@
	@echo "$(PURPLE) $@ has been created $(NONE)"

$(OBJDIR):
	mkdir -p $(OBJDIR)

###############################
##    server compilation    ##
###############################

$(OBJ_SERVER): $(OBJDIR)%.o: $(SRC_SERVER_DIR)%.cpp $(HEADER_SERVER) Makefile
	$(CXX) $(CXXFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for server has been created $(NONE)"

############################
##    http compilation    ##
############################

$(OBJ_HTTP): $(OBJDIR)%.o: $(SRC_HTTP_DIR)%.cpp $(HEADER_HTTP) Makefile
	$(CXX) $(CXXFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for http has been created $(NONE)"

##############################
##    utils compilation     ##
##############################

$(OBJ_UTILS): $(OBJDIR)%.o: $(SRC_UTILS_DIR)%.cpp $(HEADER_UTILS) Makefile
	$(CXX) $(CXXFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for utils has been created $(NONE)"

############################
##    main compilation    ##
############################

$(OBJ_MAIN): $(OBJDIR)%.o: $(SRC_MAIN_DIR)%.cpp Makefile
	$(CXX) $(CXXFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for utils has been created $(NONE)"


clean:
	$(RM) $(OBJDIR)
	@echo "$(RED) $(OBJDIR) has been deleted $(NONE)"

fclean: clean
	$(RM) $(NAME_SERVER)
	@echo "$(RED) $(NAME_SERVER) has been deleted $(NONE)"

re:	fclean all

.PHONY: all clean fclean re