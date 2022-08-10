#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(RandomizeVectorTest, PopBack) {
		for (int i = 0; i < TEST_SIZE / 2; ++i) {
			this->ftvector.pop_back();
			this->stdvector.pop_back();
		}

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};
}
