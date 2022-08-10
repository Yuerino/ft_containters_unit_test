#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, Swap) {
		// All iterators (exclude end()) are still valid but now point to
		// elements in other vector
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(num1, num2);
		decltype(this->stdvector) stdvector2(num1, num2);
		typename decltype(this->ftvector)::iterator it1 = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2 = ftvector2.begin();

		this->ftvector.swap(ftvector2);
		this->stdvector.swap(stdvector2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_THAT(ftvector2, ft::ContainerEq(stdvector2));
		EXPECT_TRUE(it1 == ftvector2.begin());
		EXPECT_TRUE(it2 == this->ftvector.begin());
	};

	TYPED_TEST(VectorTest, StdSwap) {
		// All iterators (exclude end()) are still valid but now point to
		// elements in other vector
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(num1, num2);
		decltype(this->stdvector) stdvector2(num1, num2);
		typename decltype(this->ftvector)::iterator it1 = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2 = ftvector2.begin();

		std::swap(this->ftvector, ftvector2);
		std::swap(this->stdvector, stdvector2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_THAT(ftvector2, ft::ContainerEq(stdvector2));
		EXPECT_TRUE(it1 == ftvector2.begin());
		EXPECT_TRUE(it2 == this->ftvector.begin());
	};

	TYPED_TEST(VectorTest, FtSwap) {
		// This may not be a requirement for the project. I think you should add
		// specialization of std::swap for ft::vector instead

		// All iterators (exclude end()) are still valid but now point to
		// elements in other vector
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(num1, num2);
		decltype(this->stdvector) stdvector2(num1, num2);
		typename decltype(this->ftvector)::iterator it1 = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2 = ftvector2.begin();

		ft::swap(this->ftvector, ftvector2);
		std::swap(this->stdvector, stdvector2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_THAT(ftvector2, ft::ContainerEq(stdvector2));
		EXPECT_TRUE(it1 == ftvector2.begin());
		EXPECT_TRUE(it2 == this->ftvector.begin());
	};

	TYPED_TEST(RandomizeVectorTest, Swap) {
		// All iterators (exclude end()) are still valid but now point to
		// elements in other vector
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(num1, num2);
		decltype(this->stdvector) stdvector2(num1, num2);
		typename decltype(this->ftvector)::iterator it1 = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2 = ftvector2.begin();

		this->ftvector.swap(ftvector2);
		this->stdvector.swap(stdvector2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_THAT(ftvector2, ft::ContainerEq(stdvector2));
		EXPECT_TRUE(it1 == ftvector2.begin());
		EXPECT_TRUE(it2 == this->ftvector.begin());
	};

	TYPED_TEST(RandomizeVectorTest, StdSwap) {
		// All iterators (exclude end()) are still valid but now point to
		// elements in other vector
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(num1, num2);
		decltype(this->stdvector) stdvector2(num1, num2);
		typename decltype(this->ftvector)::iterator it1 = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2 = ftvector2.begin();

		std::swap(this->ftvector, ftvector2);
		std::swap(this->stdvector, stdvector2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_THAT(ftvector2, ft::ContainerEq(stdvector2));
		EXPECT_TRUE(it1 == ftvector2.begin());
		EXPECT_TRUE(it2 == this->ftvector.begin());
	};

	TYPED_TEST(RandomizeVectorTest, FtSwap) {
		// This may not be a requirement for the project. I think you should add
		// specialization of std::swap for ft::vector instead

		// All iterators (exclude end()) are still valid but now point to
		// elements in other vector
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(num1, num2);
		decltype(this->stdvector) stdvector2(num1, num2);
		typename decltype(this->ftvector)::iterator it1 = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2 = ftvector2.begin();

		ft::swap(this->ftvector, ftvector2);
		std::swap(this->stdvector, stdvector2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_THAT(ftvector2, ft::ContainerEq(stdvector2));
		EXPECT_TRUE(it1 == ftvector2.begin());
		EXPECT_TRUE(it2 == this->ftvector.begin());
	};
}
