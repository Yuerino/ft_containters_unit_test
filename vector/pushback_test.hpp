#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, PushBack) {
		for (int i = 0; i < TEST_SIZE; ++i) {
			int num = rand();
			this->ftvector.push_back(num);
			this->stdvector.push_back(num);
		}

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, PushBack) {
		for (int i = 0; i < TEST_SIZE; ++i) {
			int num = rand();
			this->ftvector.push_back(num);
			this->stdvector.push_back(num);
		}

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};
}
