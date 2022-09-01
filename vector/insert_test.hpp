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
		// Strong guarantee in case of no reallocation, inserting single element
		// and position is the end iterator
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
		// Strong guarantee in case of no reallocation, inserting single element
		// and position is the end iterator
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
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.end(), 1, 69));
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.end(), 1, 69));
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

	TYPED_TEST(VectorTest, InsertRangeRandomIterNoReallocation) {
		// In case of no reallocation, invalidate all iterators from position iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		decltype(this->stdvector) stdvector2(10, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.at(idx);

		this->ftvector.insert(this->ftvector.begin() + idx, stdvector2.begin(), stdvector2.end());
		this->stdvector.insert(this->stdvector.begin() + idx, stdvector2.begin(), stdvector2.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.at(5));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.begin() + idx; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, InsertRangeRandomIterNoReallocationException) {
		// Basic guarantee in case of no reallocation and position is not end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		decltype(this->stdvector) stdvector2(10, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, stdvector2.begin(), stdvector2.end()));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, stdvector2.begin(), stdvector2.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TEST_F(VectorExceptionTest, InsertRangeRandomIterNoReallocationLastException) {
		// Strong guarantee in case of no reallocation, inserting single element
		// and position is the end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		decltype(this->stdvector) stdvector2(1, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.end(), stdvector2.begin(), stdvector2.end()));
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.end(), stdvector2.begin(), stdvector2.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(VectorTest, InsertRangeRandomIterReallocation) {
		// In case of reallocation, invalidate all iterators
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		decltype(this->stdvector) stdvector2(10, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.insert(this->ftvector.begin() + idx, stdvector2.begin(), stdvector2.end());
		this->stdvector.insert(this->stdvector.begin() + idx, stdvector2.begin(), stdvector2.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_GT(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, InsertRangeRandomIterReallocationException) {
		// Strong guarantee in case of reallocation
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		decltype(this->stdvector) stdvector2(10, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, stdvector2.begin(), stdvector2.end()));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, stdvector2.begin(), stdvector2.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, InsertRangeRandomIter) {
		// Test with randomized values
		int idx = rand() % (TEST_SIZE - 1);
		decltype(this->stdvector) stdvector2(rand() % TEST_SIZE, rand() % TEST_SIZE);

		this->ftvector.insert(this->ftvector.begin() + idx, stdvector2.begin(), stdvector2.end());
		this->stdvector.insert(this->stdvector.begin() + idx, stdvector2.begin(), stdvector2.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	}

	TYPED_TEST(VectorTest, InsertRangeFromArrayNoReallocation) {
		// In case of no reallocation, invalidate all iterators from position iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.at(idx);

		this->ftvector.insert(this->ftvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int));
		this->stdvector.insert(this->stdvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int));

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.at(5));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.begin() + idx; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, InsertRangeFromArrayNoReallocationException) {
		// Basic guarantee in case of no reallocation and position is not end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int)));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int)));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TEST_F(VectorExceptionTest, InsertRangeFromArrayNoReallocationLastException) {
		// Strong guarantee in case of no reallocation, inserting single element
		// and position is the end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int myints[] = {43};
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.end(), myints, myints + sizeof(myints) / sizeof(int)));
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.end(), myints, myints + sizeof(myints) / sizeof(int)));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(VectorTest, InsertRangeFromArrayReallocation) {
		// In case of reallocation, invalidate all iterators
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.insert(this->ftvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int));
		this->stdvector.insert(this->stdvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int));

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_GT(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, InsertRangeFromArrayReallocationException) {
		// Strong guarantee in case of reallocation
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int)));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int)));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, InsertRangeFromArray) {
		// Test with randomized values
		int idx = rand() % (TEST_SIZE - 1);
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};

		this->ftvector.insert(this->ftvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int));
		this->stdvector.insert(this->stdvector.begin() + idx, myints, myints + sizeof(myints) / sizeof(int));

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	}

	TYPED_TEST(VectorTest, InsertRangeBiDirIterNoReallocation) {
		// In case of no reallocation, invalidate all iterators from position iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		std::list<typename decltype(this->stdvector)::value_type> stdlist(10, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.at(idx);

		this->ftvector.insert(this->ftvector.begin() + idx, stdlist.begin(), stdlist.end());
		this->stdvector.insert(this->stdvector.begin() + idx, stdlist.begin(), stdlist.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.at(5));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.begin() + idx; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, InsertRangeBiDirIterNoReallocationException) {
		// Basic guarantee in case of no reallocation and position is not end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		std::list<typename decltype(this->stdvector)::value_type> stdlist(10, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, stdlist.begin(), stdlist.end()));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, stdlist.begin(), stdlist.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TEST_F(VectorExceptionTest, InsertRangeBiDirIterNoReallocationLastException) {
		// Strong guarantee in case of no reallocation, inserting single element
		// and position is the end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		std::list<typename decltype(this->stdvector)::value_type> stdlist(1, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.end(), stdlist.begin(), stdlist.end()));
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.end(), stdlist.begin(), stdlist.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(VectorTest, InsertRangeBiDirIterReallocation) {
		// In case of reallocation, invalidate all iterators
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		std::list<typename decltype(this->stdvector)::value_type> stdlist(10, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.insert(this->ftvector.begin() + idx, stdlist.begin(), stdlist.end());
		this->stdvector.insert(this->stdvector.begin() + idx, stdlist.begin(), stdlist.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_GT(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, InsertRangeBiDirIterReallocationException) {
		// Strong guarantee in case of reallocation
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		std::list<typename decltype(this->stdvector)::value_type> stdlist(10, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, stdlist.begin(), stdlist.end()));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, stdlist.begin(), stdlist.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, InsertRangeBiDirIter) {
		// Test with randomized values
		int idx = rand() % (TEST_SIZE - 1);
		std::list<typename decltype(this->stdvector)::value_type> stdlist(rand() % TEST_SIZE, rand() % TEST_SIZE);

		this->ftvector.insert(this->ftvector.begin() + idx, stdlist.begin(), stdlist.end());
		this->stdvector.insert(this->stdvector.begin() + idx, stdlist.begin(), stdlist.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	}

	TYPED_TEST(VectorTest, InsertRangeInputIterNoReallocation) {
		// In case of no reallocation, invalidate all iterators from position iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.at(idx);

		this->ftvector.insert(this->ftvector.begin() + idx, first1, last);
		this->stdvector.insert(this->stdvector.begin() + idx, first2, last);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.at(5));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.begin() + idx; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TEST_F(VectorExceptionTest, InsertRangeInputIterNoReallocationException) {
		// Basic guarantee in case of no reallocation and position is not end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		int idx = 5;
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, first1, last));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, first2, last));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TEST_F(VectorExceptionTest, InsertRangeInputIterNoReallocationLastException) {
		// Strong guarantee in case of no reallocation, inserting single element
		// and position is the end iterator
		this->ftvector.assign(10, 42);
		this->ftvector.reserve(50);
		this->stdvector.assign(10, 42);
		this->stdvector.reserve(50);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		std::istringstream str1("54");
		std::istringstream str2("54");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.end(), first1, last));
		::DerivedInt::to_throw = 0;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.end(), first2, last));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(VectorTest, InsertRangeInputIterReallocation) {
		// In case of reallocation, invalidate all iterators
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();

		this->ftvector.insert(this->ftvector.begin() + idx, first1, last);
		this->stdvector.insert(this->stdvector.begin() + idx, first2, last);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_GT(this->ftvector.capacity(), old_capacity);
		EXPECT_NE(it, this->ftvector.begin());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, InsertRangeInputIterReallocationException) {
		// Strong guarantee in case of reallocation
		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		// Ensure next insert will reallocate
		EXPECT_EQ(this->ftvector.size(), this->ftvector.capacity());

		int idx = 5;
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::size_type old_capacity = this->ftvector.capacity();
		typename decltype(this->ftvector)::size_type old_size = this->ftvector.size();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.insert(this->ftvector.begin() + idx, first1, last));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.insert(this->stdvector.begin() + idx, first2, last));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(this->ftvector.capacity(), old_capacity);
		EXPECT_EQ(this->ftvector.size(), old_size);
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end(); it2 != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, InsertRangeInputIter) {
		// Test with randomized values
		int idx = rand() % (TEST_SIZE - 1);
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;

		this->ftvector.insert(this->ftvector.begin() + idx, first1, last);
		this->stdvector.insert(this->stdvector.begin() + idx, first2, last);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	}
}
