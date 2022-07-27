#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "vector_helper.hpp"

namespace {

	TEST_F(VectorTest, PushBack) {
		for (int i=0; i < 1000; ++i) {
			int num = rand();
			ftvector.push_back(num);
			stdvector.push_back(num);
		}

		EXPECT_THAT(ftvector, ft::ContainerEq(stdvector));
	};

}
