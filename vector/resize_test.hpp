#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, ResizeShrink) {
		// In case of shrink should not realloc (capacity stays same) and only
		// invalidate iterators beyond new size
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.resize(7, 69);
		this->stdvector.resize(7, 69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Reallocation shouldn't happen
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		// Validate iterator up to new size
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, ResizeShrinkException) {
		// C++98 vector::resize can throw in case of shrink (no reallocation)
		// but is strong guarantee
		// Since C++11: shrink with no reallocate should not throw exception

		// Because we compiled this test with C++14 so standard vector won't
		// throw

		// In this test we simply don't care if it throws or not because either
		// way the vector should stay the same (strong guarantee)
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		g_vector_force_exception = ::ALL_EXCEPTION;
		try {
			this->ftvector.resize(8, 69);
			this->stdvector.resize(8, 69);
		} catch (...) { /* ignore */ }
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(VectorTest, ResizeExpandReallocation) {
		// In case of expands beyond capacity and reallocation happen then all
		// iterators should be invalidated
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.resize(17, 69);
		this->stdvector.resize(17, 69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_GT(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
	}

	TEST_F(VectorExceptionTest, ResizeExpandReallocationException) {
		// In case of expands beyond capacity and reallocation happen, there
		// should be no changes in vector in case of exception (Strong
		// guarantee)
		// (We only test with type that is copyable or no-throw movable)
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.resize(17, 69));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.resize(17, 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	}

	TYPED_TEST(VectorTest, ResizeExpandNoReallocation) {
		// In case of expands beyond size and no reallocation happen then no
		// iterators should be invalidated
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(20);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(20);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_GE(this->ftvector.capacity(), 20);
		ASSERT_GE(this->stdvector.capacity(), 20);

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.resize(17, 69);
		this->stdvector.resize(17, 69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		for (it2 = this->ftvector.begin(); it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	}

	TEST_F(VectorExceptionTest, ResizeExpandNoReallocationException) {
		// In case of expands beyond size and no reallocation happen, vector
		// should be in valid state and elements may change (Basic guarantee)
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(20);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(20);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_GE(this->ftvector.capacity(), 20);
		ASSERT_GE(this->stdvector.capacity(), 20);

		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.resize(17, 69));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.resize(17, 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		// Check if vector is valid
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		// Should not SEGFAULT or throw exception
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	}

	TYPED_TEST(RandomizeVectorTest, Resize) {
		// Test with some randomized values
		this->ftvector.resize(TEST_SIZE * 2);
		this->stdvector.resize(TEST_SIZE * 2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		this->ftvector.resize(TEST_SIZE / 2);
		this->stdvector.resize(TEST_SIZE / 2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int num = rand() % TEST_SIZE;
		this->ftvector.resize(TEST_SIZE, num);
		this->stdvector.resize(TEST_SIZE, num);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};
}
