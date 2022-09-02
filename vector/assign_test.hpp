#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(RandomizeVectorTest, AssignFillNoReallocation) {
		// Invalidate all iterators
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(RandomizeVectorExceptionTest, AssignFillNoReallocationException) {
		// Basic guarantee
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(10, 42));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(10, 42));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(VectorTest, AssignFillReallocation) {
		// Invalidate all iterators
		this->ftvector.push_back(696);
		this->ftvector.push_back(69);
		this->stdvector.push_back(696);
		this->stdvector.push_back(69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(10, 42);
		this->stdvector.assign(10, 42);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, AssignFillReallocationException) {
		// Basic guarantee
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(10, 42));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(10, 42));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(VectorTest, AssignFill) {
		// Test with randomized values
		int num1 = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		this->ftvector.assign(num1, num2);
		this->stdvector.assign(num1, num2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		num1 += rand() % TEST_SIZE;
		num2 = rand() % TEST_SIZE;
		this->ftvector.assign(num1, num2);
		this->stdvector.assign(num1, num2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		this->ftvector.assign(0, 0);
		this->stdvector.assign(0, 0);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		num1 = rand() % TEST_SIZE;
		num2 = rand() % TEST_SIZE;
		this->ftvector.reserve(num1);
		this->stdvector.reserve(num1);
		this->ftvector.assign(num1, num2);
		this->stdvector.assign(num1, num2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		num1 = (rand() % TEST_SIZE) + 3;
		num2 = rand() % TEST_SIZE;
		this->ftvector.resize(2, 42);
		this->stdvector.resize(2, 42);
		this->ftvector.assign(num1, num2);
		this->stdvector.assign(num1, num2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		num2 = rand() % TEST_SIZE;
		this->ftvector.assign(1, num2);
		this->stdvector.assign(1, num2);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, AssignRangeRandomIterNoReallocation) {
		// Invalidate all iterators
		decltype(this->stdvector) stdvector2(rand() % TEST_SIZE, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(stdvector2.begin(), stdvector2.end());
		this->stdvector.assign(stdvector2.begin(), stdvector2.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(RandomizeVectorExceptionTest, AssignRangeRandomIterNoReallocationException) {
		// Basic guarantee
		decltype(this->stdvector) stdvector2(rand() % TEST_SIZE, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(stdvector2.begin(), stdvector2.end()));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(stdvector2.begin(), stdvector2.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(VectorTest, AssignRangeRandomIterReallocation) {
		// Invalidate all iterators
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		decltype(this->stdvector) stdvector2(rand() % TEST_SIZE, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(stdvector2.begin(), stdvector2.end());
		this->stdvector.assign(stdvector2.begin(), stdvector2.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, AssignRangeRandomIterReallocationException) {
		// Basic guarantee
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		decltype(this->stdvector) stdvector2(rand() % TEST_SIZE, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(stdvector2.begin(), stdvector2.end()));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(stdvector2.begin(), stdvector2.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(RandomizeVectorTest, AssignRangeFromArrayNoReallocation) {
		// Invalidate all iterators
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(myints, myints + sizeof(myints) / sizeof(int));
		this->stdvector.assign(myints, myints + sizeof(myints) / sizeof(int));

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(RandomizeVectorExceptionTest, AssignRangeFromArrayNoReallocationException) {
		// Basic guarantee
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(myints, myints + sizeof(myints) / sizeof(int)));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(myints, myints + sizeof(myints) / sizeof(int)));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(VectorTest, AssignRangeFromArrayReallocation) {
		// Invalidate all iterators
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(myints, myints + sizeof(myints) / sizeof(int));
		this->stdvector.assign(myints, myints + sizeof(myints) / sizeof(int));

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, AssignRangeFromArrayReallocationException) {
		// Basic guarantee
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(myints, myints + sizeof(myints) / sizeof(int)));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(myints, myints + sizeof(myints) / sizeof(int)));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(RandomizeVectorTest, AssignRangeBiDirIterNoReallocation) {
		// Invalidate all iterators
		std::list<typename decltype(this->stdvector)::value_type> stdlist(rand() % TEST_SIZE, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(stdlist.begin(), stdlist.end());
		this->stdvector.assign(stdlist.begin(), stdlist.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(RandomizeVectorExceptionTest, AssignRangeBiDirIterNoReallocationException) {
		// Basic guarantee
		std::list<typename decltype(this->stdvector)::value_type> stdlist(rand() % TEST_SIZE, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(stdlist.begin(), stdlist.end()));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(stdlist.begin(), stdlist.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(VectorTest, AssignRangeBiDirIterReallocation) {
		// Invalidate all iterators
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		std::list<typename decltype(this->stdvector)::value_type> stdlist(rand() % TEST_SIZE, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(stdlist.begin(), stdlist.end());
		this->stdvector.assign(stdlist.begin(), stdlist.end());

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, AssignRangeBiDirIterReallocationException) {
		// Basic guarantee
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		std::list<typename decltype(this->stdvector)::value_type> stdlist(rand() % TEST_SIZE, rand() % TEST_SIZE);
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(stdlist.begin(), stdlist.end()));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(stdlist.begin(), stdlist.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(RandomizeVectorTest, AssignRangeInputIterNoReallocation) {
		// Invalidate all iterators
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(first1, last);
		this->stdvector.assign(first2, last);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(RandomizeVectorExceptionTest, AssignRangeInputIterNoReallocationException) {
		// Basic guarantee
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(first1, last));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(first2, last));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};

	TYPED_TEST(VectorTest, AssignRangeInputIterReallocation) {
		// Invalidate all iterators
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector.assign(first1, last);
		this->stdvector.assign(first2, last);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(old_num1 != this->ftvector.front());
		EXPECT_TRUE(old_num2 != this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, AssignRangeInputIterReallocationException) {
		// Basic guarantee
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.assign(first1, last));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.assign(first2, last));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) ++(*it).nbr;
	};
}
