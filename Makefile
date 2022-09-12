GTEST_DIR		=	./googletest/googletest
GMOCK_DIR		=	./googletest/googlemock

GTEST_SRCS		=	$(GTEST_DIR)/src/gtest-all.cc
GTEST_OBJS		=	$(GTEST_SRCS:.cc=.o)

NAME			=	unit_test

USER_HEADERS	=	..

TEST_HEADERS	=	./include

CXX				=	g++

CPPFLAGS		+=	-isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include \
					-isystem $(GTEST_DIR) -isystem $(GMOCK_DIR) \
					-isystem $(TEST_HEADERS) -isystem . -I$(USER_HEADERS)

CXXFLAGS		+=	-g -Wall -Wextra -Werror -pthread -std=c++17 # -DTEST_EXACT -DVECTOR_DEBUG

SRC				=	main.cpp
OBJ				=	$(SRC:.cpp=.o)

.PHONY: all clean fclean re run run_valgrind test

all: $(NAME)

$(NAME): $(GTEST_OBJS) $(OBJ) Makefile
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) -lpthread $(GTEST_OBJS) $(OBJ) -o $(NAME)

run:
		$(MAKE) re
		./$(NAME) --gtest_brief=1

run_valgrind:
		$(MAKE) re
		valgrind -q --log-file=output --leak-check=full --trace-children=yes ./$(NAME) --gtest_brief=1

clean:
		$(RM) $(NAME) $(OBJ)

fclean: clean
		$(RM) $(GTEST_OBJS)

re: clean all
