
GTEST_DIR		=	./googletest/googletest
GMOCK_DIR		=	./googletest/googlemock

GTEST_SRCS		=	$(GTEST_DIR)/src/gtest-all.cc
GTEST_OBJS		=	$(GTEST_SRCS:.cc=.o)

NAME			=	unit_test

USER_HEADERS	=	..

CXX				=	clang++

CPPFLAGS		+=	-isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include -I$(GTEST_DIR) -I$(GMOCK_DIR) -I$(USER_HEADERS)

CXXFLAGS		+=	-g -Wall -Wextra -Werror -pthread -std=c++14

SRC				=	main.cpp
OBJ				=	$(SRC:.cpp=.o)

# vector test
VECTOR_DIR		=	vector/
VECTOR_SRCS		=	ctor_test.cpp pushback_test.cpp
VECTOR_OBJS		=	$(addprefix $(VECTOR_DIR), $(VECTOR_SRCS:.cpp=.o))

.PHONY: all clean re

all: $(NAME)

$(NAME): $(VECTOR_OBJS) $(GTEST_OBJS) $(OBJ) Makefile
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) -lpthread $(VECTOR_OBJS) $(GTEST_OBJS) $(OBJ) -o $(NAME)

clean:
		$(RM) $(NAME) $(GTEST_OBJS) $(VECTOR_OBJS) $(OBJ)

re: clean all
