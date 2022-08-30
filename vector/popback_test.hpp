#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(RandomizeVectorTest, PopBack) {
		// nothrow guarantee, invalidate end iterator and iterator refer to the
		// removed element (last one)
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::value_type old_capacity = this->ftvector.capacity();

		this->ftvector.pop_back();
		this->stdvector.pop_back();

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(ite, this->ftvector.end());
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);

		for (int i = 0; i < TEST_SIZE / 2; ++i) {
			this->ftvector.pop_back();
			this->stdvector.pop_back();
		}

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};
}
