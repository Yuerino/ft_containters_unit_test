#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, Size) {
		EXPECT_EQ(this->ftvector.size(), this->stdvector.size());
	};

	TYPED_TEST(RandomizeVectorTest, Size) {
		EXPECT_EQ(this->ftvector.size(), this->stdvector.size());
	};

	TYPED_TEST(VectorTest, Empty) {
		EXPECT_EQ(this->ftvector.empty(), this->stdvector.empty());
	};

	TYPED_TEST(RandomizeVectorTest, Empty) {
		EXPECT_EQ(this->ftvector.empty(), this->stdvector.empty());
	};

	TYPED_TEST(VectorTest, Reserve) {
		typename decltype(this->ftvector)::size_type size = TEST_SIZE * 3;
		this->ftvector.reserve(size);
		EXPECT_TRUE(this->ftvector.capacity() >= size);

		EXPECT_ANY_THROW(this->ftvector.reserve(this->ftvector.max_size() + 1));
	};

	TYPED_TEST(RandomizeVectorTest, Reserve) {
		typename decltype(this->ftvector)::size_type size = TEST_SIZE * 3;
		this->ftvector.reserve(size);
		EXPECT_TRUE(this->ftvector.capacity() >= size);

		EXPECT_ANY_THROW(this->ftvector.reserve(this->ftvector.max_size() + 1));
	};
}
