# Points to the root of Google Test, relative to where this file is.
GTEST_DIR		=	./googletest/googletest

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS		+=	-isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS		+=	-g -Wall -Wextra -Werror -pthread -std=c++14

# GCC Compiler
CXX				=	clang++

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS	=	$(GTEST_DIR)/include/gtest/*.h \
					$(GTEST_DIR)/include/gtest/internal/*.h

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_		=	$(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# Name of tester
NAME			=	unit_test

# Where to find user test code.
TEST_DIR		=	.

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TEST_SRC		=	is_integral_test.cpp

.PHONY: all clean re

all: $(NAME)

clean:
		rm -rf $(NAME) gtest.a gtest_main.a *.o *.dSYM

re: clean all

# Builds gtest.a and gtest_main.a.

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o: $(GTEST_SRCS_)
		$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_SRCS_)
		$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a: gtest-all.o
		$(AR) $(ARFLAGS) $@ $^

gtest_main.a: gtest-all.o gtest_main.o
		$(AR) $(ARFLAGS) $@ $^

$(NAME): $(TEST_SRC) $(GTEST_HEADERS) gtest_main.a
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread gtest_main.a $(TEST_SRC) -o $(NAME)
