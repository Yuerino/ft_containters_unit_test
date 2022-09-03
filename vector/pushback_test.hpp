#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, PushBackNoAllocation) {
		// In case of no reallocation, only the end iterator is invalidated
		this->ftvector.assign(10, -42);
		this->ftvector.reserve(100);
		this->stdvector.assign(10, -42);
		this->stdvector.reserve(100);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.push_back(69);
		this->stdvector.push_back(69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(ite, this->ftvector.end());
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end() - 1; it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, PushBackNoAllocationException) {
		// In case of no reallocation, strong guarantee
		this->ftvector.assign(10, -42);
		this->ftvector.reserve(100);
		this->stdvector.assign(10, -42);
		this->stdvector.reserve(100);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->ftvector.push_back(69));
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->stdvector.push_back(69));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(ite, this->ftvector.end());
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end() - 1; it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(VectorTest, PushBackAllocation) {
		// In case of reallocation, invalidate all iterators
		this->ftvector.assign(10, -42);
		this->stdvector.assign(10, -42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::value_type old_capacity = this->ftvector.capacity();

		this->ftvector.push_back(69);
		this->stdvector.push_back(69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_GT(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, PushBackAllocationException) {
		// In case of reallocation, basic guarantee
		this->ftvector.assign(10, -42);
		this->stdvector.assign(10, -42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->ftvector.push_back(69));
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->stdvector.push_back(69));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(RandomizeVectorTest, PushBack) {
		// Test with randomized values
		for (int i = 0; i < TEST_SIZE; ++i) {
			int num = rand();
			this->ftvector.push_back(num);
			this->stdvector.push_back(num);
		}

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};
}
