#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, Size) {
		// Nothrow guarantee
		EXPECT_EQ(this->ftvector.size(), this->stdvector.size());
	};

	TYPED_TEST(RandomizeVectorTest, Size) {
		// Nothrow guarantee
		EXPECT_EQ(this->ftvector.size(), this->stdvector.size());
	};

#ifdef TEST_EXACT
	TYPED_TEST(RandomizeVectorTest, MaxSize) {
		// Nothrow guarantee
		EXPECT_EQ(this->ftvector.max_size(), this->stdvector.max_size());
	}

	TYPED_TEST(RandomizeVectorTest, Capacity) {
		// Nothrow guarantee
		EXPECT_EQ(this->ftvector.capacity(), this->stdvector.capacity());
	}
#endif

	TYPED_TEST(VectorTest, Empty) {
		// Nothrow guarantee
		EXPECT_EQ(this->ftvector.empty(), this->stdvector.empty());
	};

	TYPED_TEST(RandomizeVectorTest, Empty) {
		// Nothrow guarantee
		EXPECT_EQ(this->ftvector.empty(), this->stdvector.empty());
	};

	TYPED_TEST(VectorTest, ReserveReallocation) {
		// In case of reallocation, invalidate all iterators
		this->ftvector.assign(10, -42);
		this->stdvector.assign(10, -42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		typename decltype(this->ftvector)::size_type size = TEST_SIZE * 3;
		this->ftvector.reserve(size);
		this->stdvector.reserve(size);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(this->ftvector.capacity() >= size);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, ReserveReallocationException) {
		// Basic guarantee in case of reallocation
		this->ftvector.assign(10, -42);
		this->stdvector.assign(10, -42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		typename decltype(this->ftvector)::size_type size = TEST_SIZE * 3;
		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.reserve(size));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.reserve(size));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		// Check if vector is valid
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		// Should not SEGFAULT or throw exception
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(VectorTest, ReserveNoReallocation) {
		// In case of no reallocation, this function shoudln't do anything, all
		// iterators should be valid
		this->ftvector.assign(10, -42);
		this->stdvector.assign(10, -42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		typename decltype(this->ftvector)::size_type size = this->ftvector.capacity() - 1;
		this->ftvector.reserve(size);
		this->stdvector.reserve(size);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(this->ftvector.capacity() >= size);
		for (it2 = this->ftvector.begin(); it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, ReserveNoReallocationException) {
		// Strong guarantee in case of no reallocation
		this->ftvector.assign(10, -42);
		this->stdvector.assign(10, -42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		typename decltype(this->ftvector)::size_type size = this->ftvector.capacity() - 1;
		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		try {
			this->ftvector.reserve(size);
		} catch (...) { /* ignore */ }
		::DerivedInt::to_throw = -2;
		try {
			this->stdvector.reserve(size);
		} catch (...) { /* ignore */ }
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, ReserveLengthError) {
		// throw length error if size is greater than max_size
		EXPECT_ANY_THROW(this->ftvector.reserve(this->ftvector.max_size() + 1));
	}

	TYPED_TEST(RandomizeVectorTest, Reserve) {
		// Test with randomized values
		typename decltype(this->ftvector)::size_type size = TEST_SIZE * 3;
		this->ftvector.reserve(size);
		this->stdvector.reserve(size);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(this->ftvector.capacity() >= size);
	};
}
