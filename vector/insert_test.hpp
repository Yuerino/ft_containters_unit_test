#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, InsertSingleNoReallocation) {
		// In case of no reallocation, invalidate all iterators from position iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(20);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(20);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		it2 = this->ftvector.insert(this->ftvector.begin() + idx, 69);
		this->stdvector.insert(this->stdvector.begin() + idx, 69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(*it2, 69);
		EXPECT_EQ(it2, this->ftvector.begin() + 5);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.begin() + idx; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, InsertSingleNoReallocationException) {
		// Basic guarantee in case of no reallocation and position is not end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(20);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(20);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, 69));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TEST_F(VectorExceptionTest, InsertSingleNoReallocationLastException) {
		// Strong guarantee in case of no reallocation and position is the end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(20);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(20);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.end(), 69));
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.end(), 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(VectorTest, InsertSingleReallocation) {
		// In case of reallocation, invalidate all iterators
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		it2 = this->ftvector.insert(this->ftvector.begin() + idx, 69);
		this->stdvector.insert(this->stdvector.begin() + idx, 69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_GT(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
		EXPECT_EQ(*it2, 69);
		EXPECT_EQ(it2, this->ftvector.begin() + 5);
	};

	TEST_F(VectorExceptionTest, InsertSingleReallocationException) {
		// Strong guarantee in case of reallocation
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, 69));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, InsertSingle) {
		// Test with randomized values
		typename decltype(this->ftvector)::iterator ft_it;
		typename decltype(this->stdvector)::iterator std_it;
		int idx = rand() % (TEST_SIZE - 1), num = rand() % TEST_SIZE;

		ft_it = this->ftvector.insert(this->ftvector.begin() + idx, num);
		std_it = this->stdvector.insert(this->stdvector.begin() + idx, num);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(*ft_it, *std_it);
	}

	TYPED_TEST(VectorTest, InsertFillNoReallocation) {
		// In case of no reallocation, invalidate all iterators from position iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.at(idx);

		this->ftvector.insert(this->ftvector.begin() + idx, 5, 69);
		this->stdvector.insert(this->stdvector.begin() + idx, 5, 69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.at(5));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.begin() + idx; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, InsertFillNoReallocationException) {
		// Basic guarantee in case of no reallocation and position is not end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, 5, 69));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, 5, 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TEST_F(VectorExceptionTest, InsertFillNoReallocationLastException) {
		// Strong guarantee in case of no reallocation and position is the end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.end(), 5, 69));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.end(), 5, 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(VectorTest, InsertFillReallocation) {
		// In case of reallocation, invalidate all iterators
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.insert(this->ftvector.begin() + idx, 5, 69);
		this->stdvector.insert(this->stdvector.begin() + idx, 5, 69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_GT(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, InsertFillReallocationException) {
		// Strong guarantee in case of reallocation
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, 5, 69));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, 5, 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, InsertFill) {
		// Test with randomized values
		int idx = rand() % (TEST_SIZE - 1), num = rand() % TEST_SIZE, size = rand() % TEST_SIZE;

		this->ftvector.insert(this->ftvector.begin() + idx, size, num);
		this->stdvector.insert(this->stdvector.begin() + idx, size, num);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	}
}
