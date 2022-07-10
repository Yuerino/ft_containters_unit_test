#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "../type_traits.hpp"

struct A {};

typedef ::testing::Types<bool,
						char,
						wchar_t,
						signed char,
						short,
						int,
						long,
						unsigned char,
						unsigned int,
						unsigned long>
						IntegralTypes;

typedef ::testing::Types<char16_t,
						char32_t,
						long long,
						unsigned long long>
						C11IntegralTypes;

typedef ::testing::Types<std::vector<int>,
						A>
						NonIntegralTypes;

template<typename T>
class IsIntegralTest : public ::testing::Test {
protected:
	IsIntegralTest() : _is_integral(ft::is_integral<T>()) {}
	~IsIntegralTest() override {}

	const ft::is_integral<T> _is_integral;
};

template<typename T>
class IsIntegralTest2 : public IsIntegralTest<T> {};

template<typename T>
class IsIntegralTest3 : public IsIntegralTest<T> {};

TYPED_TEST_SUITE(IsIntegralTest, IntegralTypes);
TYPED_TEST_SUITE(IsIntegralTest2, NonIntegralTypes);
TYPED_TEST_SUITE(IsIntegralTest3, C11IntegralTypes);

TYPED_TEST(IsIntegralTest, ReturnsTrueForIntegralTypes) {
	EXPECT_TRUE(this->_is_integral.value);
}

TYPED_TEST(IsIntegralTest2, ReturnsFalseForNonIntegralTypes) {
	EXPECT_FALSE(this->_is_integral.value);
}

TYPED_TEST(IsIntegralTest3, ReturnsFalseForC11IntegralTypes) {
	EXPECT_FALSE(this->_is_integral.value);
}
