#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, Clear) {
		this->ftvector.clear();
		this->stdvector.clear();

		EXPECT_EQ(this->ftvector.size(), 0);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, Clear) {
		this->ftvector.clear();
		this->stdvector.clear();

		EXPECT_EQ(this->ftvector.size(), 0);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};
}
