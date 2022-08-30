#pragma once
#include "vector_helper.hpp"

#define COMPARE(a1, b1, a2, b2) ({ \
	EXPECT_EQ(a1 == b1, a2 == b2); \
	EXPECT_EQ(a1 != b1, a2 != b2); \
	EXPECT_EQ(a1 < b1, a2 < b2); \
	EXPECT_EQ(a1 <= b1, a2 <= b2); \
	EXPECT_EQ(a1 > b1, a2 > b2); \
	EXPECT_EQ(a1 >= b1, a2 >= b2); \
})

namespace {
	TYPED_TEST(VectorTest, RelationalOp) {
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(num1, num2);
		decltype(this->stdvector) stdvector2(num1, num2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_THAT(ftvector2, ft::ContainerEq(stdvector2));

		COMPARE(this->ftvector, ftvector2, this->stdvector, stdvector2);
	};

	TYPED_TEST(RandomizeVectorTest, RelationalOp) {
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(num1, num2);
		decltype(this->stdvector) stdvector2(num1, num2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_THAT(ftvector2, ft::ContainerEq(stdvector2));

		COMPARE(this->ftvector, ftvector2, this->stdvector, stdvector2);
	};
}
