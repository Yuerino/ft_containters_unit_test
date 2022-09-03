#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, DefaultCtor) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		ft::vector<value_type> v;

		EXPECT_EQ(0, v.size());
		EXPECT_EQ(0, v.capacity());
	};

	TYPED_TEST(VectorTest, FillCtorNoValue) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		int size = rand() % TEST_SIZE;

		ft::vector<value_type> ftv(size);
		std::vector<value_type> stdv(size);

		EXPECT_THAT(ftv, ft::ContainerEq(stdv));
	};

	TEST_F(VectorExceptionTest, FillCtorNoValueException) {
		// Strong guarantee here just means the vector didn't constructed and
		// free all memory properly
		typedef typename decltype(this->ftvector)::value_type value_type;
		int size = (rand() % TEST_SIZE) + 3;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(ft::vector<value_type> ftv(size));
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TYPED_TEST(VectorTest, FillCtorWithValue) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		int size = rand() % TEST_SIZE, num = rand() % TEST_SIZE;

		ft::vector<value_type> ftv(size, num);
		std::vector<value_type> stdv(size, num);

		EXPECT_THAT(ftv, ft::ContainerEq(stdv));
	};

	TEST_F(VectorExceptionTest, FillCtorValueException) {
		// Strong guarantee here just means the vector didn't constructed and
		// free all memory properly
		typedef typename decltype(this->ftvector)::value_type value_type;
		int size = (rand() % TEST_SIZE) + 3, num = rand() % TEST_SIZE;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(ft::vector<value_type> ftv(size, num));
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TYPED_TEST(VectorTest, RangeCtorRandomIter) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		decltype(this->stdvector) stdvector2(rand() % TEST_SIZE, rand() % TEST_SIZE);

		ft::vector<value_type> ftv(stdvector2.begin(), stdvector2.end());
		std::vector<value_type> stdv(stdvector2.begin(), stdvector2.end());

		EXPECT_THAT(ftv, ft::ContainerEq(stdv));
	};

	TEST_F(VectorExceptionTest, RangeCtorRandomIterException) {
		// Strong guarantee here just means the vector didn't constructed and
		// free all memory properly
		typedef typename decltype(this->ftvector)::value_type value_type;
		decltype(this->stdvector) stdvector2((rand() % TEST_SIZE) + 3, rand() % TEST_SIZE);

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(ft::vector<value_type> ftv(stdvector2.begin(), stdvector2.end()));
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TYPED_TEST(VectorTest, RangeCtorFromArray) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};

		ft::vector<value_type> ftv(myints, myints + sizeof(myints) / sizeof(int));
		std::vector<value_type> stdv(myints, myints + sizeof(myints) / sizeof(int));

		EXPECT_THAT(ftv, ft::ContainerEq(stdv));
	};

	TEST_F(VectorExceptionTest, RangeCtorFromArrayException) {
		// Strong guarantee here just means the vector didn't constructed and
		// free all memory properly
		typedef typename decltype(this->ftvector)::value_type value_type;
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(ft::vector<value_type> ftv(myints, myints + sizeof(myints) / sizeof(int)));
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TYPED_TEST(VectorTest, RangeCtorBiDirIter) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		std::list<int> l(rand() % TEST_SIZE, rand() % TEST_SIZE);

		ft::vector<value_type> ftv(l.begin(), l.end());
		std::vector<value_type> stdv(l.begin(), l.end());

		EXPECT_THAT(ftv, ft::ContainerEq(stdv));
	};

	TEST_F(VectorExceptionTest, RangeCtorBiDirIterException) {
		// Strong guarantee here just means the vector didn't constructed and
		// free all memory properly
		typedef typename decltype(this->ftvector)::value_type value_type;
		std::list<int> l((rand() % TEST_SIZE) + 3, rand() % TEST_SIZE);

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(ft::vector<value_type> ftv(l.begin(), l.end()));
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TYPED_TEST(VectorTest, RangeCtorInputIter) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		std::istringstream str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream _str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str);
		std::istream_iterator<int> first2(_str);
		std::istream_iterator<int> last;

		ft::vector<value_type> ftv(first1, last);
		std::vector<value_type> stdv(first2, last);

		EXPECT_THAT(ftv, ft::ContainerEq(stdv));
	};

	TEST_F(VectorExceptionTest, RangeCtorInputIterException) {
		// Strong guarantee here just means the vector didn't constructed and
		// free all memory properly
		typedef typename decltype(this->ftvector)::value_type value_type;
		std::istringstream str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str);
		std::istream_iterator<int> last;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(std::vector<value_type> ftv(first1, last));
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TYPED_TEST(VectorTest, CtorConstructible) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		typedef std::is_constructible<ft::vector<value_type>, DerivedInt, DerivedInt> isConstructible;
		EXPECT_FALSE(isConstructible::value);
	};

	TYPED_TEST(VectorTest, CopyCtor) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		int size = (rand() % TEST_SIZE) + 1, num = rand() % TEST_SIZE;
		ft::vector<value_type> ftvector(size, num);
		std::vector<value_type> stdvector(size, num);

		ft::vector<value_type> ftv(ftvector);
		std::vector<value_type> stdv(stdvector);

		EXPECT_THAT(ftv, ft::ContainerEq(stdv));
	};

	TEST_F(VectorExceptionTest, CopyCtorExcpetion) {
		typedef typename decltype(this->ftvector)::value_type value_type;
		int size = (rand() % TEST_SIZE) + 3, num = rand() % TEST_SIZE;
		ft::vector<value_type> ftvector(size, num);

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(ft::vector<value_type> ftv(ftvector));
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TYPED_TEST(RandomizeVectorTest, AssignOpNoReallocation) {
		// Invalidate all iterators
		decltype(this->ftvector) ftvector2(10, -42);
		decltype(this->stdvector) stdvector2(10, -42);
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector = ftvector2;
		this->stdvector = stdvector2;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num1, this->ftvector.front());
		EXPECT_NE(old_num2, this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(RandomizeVectorExceptionTest, AssignOpNoReallocationException) {
		// Basic guarantee
		decltype(this->ftvector) ftvector2(10, -42);

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector = ftvector2);
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TYPED_TEST(VectorTest, AssignOpReallocation) {
		// Invalidate all iterators
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		this->stdvector.push_back(-42);
		this->stdvector.push_back(-69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		ASSERT_LT(this->ftvector.capacity(), 10);

		int size = (rand() % TEST_SIZE) + 11, num = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(size, num);
		decltype(this->stdvector) stdvector2(size, num);
		typename decltype(this->ftvector)::value_type old_num1 = this->ftvector.front();
		typename decltype(this->ftvector)::value_type old_num2 = this->ftvector.back();
		typename decltype(this->ftvector)::iterator ite = this->ftvector.end();

		this->ftvector = ftvector2;
		this->stdvector = stdvector2;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num1, this->ftvector.front());
		EXPECT_NE(old_num2, this->ftvector.back());
		EXPECT_NE(ite, this->ftvector.end());
	};

	TEST_F(VectorExceptionTest, AssignOpReallocationException) {
		// Basic guarantee
		this->ftvector.push_back(-42);
		this->ftvector.push_back(-69);
		ASSERT_LT(this->ftvector.capacity(), 10);

		int size = (rand() % TEST_SIZE) + 11, num = rand() % TEST_SIZE;
		decltype(this->ftvector) ftvector2(size, num);

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector = ftvector2);
		g_vector_force_exception = ::NO_EXCEPTION;
	};

	TEST(VectorExplicitCtorTest, NotImplicit) {
		// reason why typedef
		// https://stackoverflow.com/questions/38030048/too-many-arguments-provided-to-function-like-macro-invocation
		typedef std::is_convertible< std::allocator<int>, ft::vector<int> > isDefaultCtorImplicitIntegral;
		EXPECT_FALSE(isDefaultCtorImplicitIntegral::value);
		typedef std::is_convertible< std::allocator<DerivedInt>, ft::vector<DerivedInt> > isDefaultCtorImplicitNonIntegral;
		EXPECT_FALSE(isDefaultCtorImplicitNonIntegral::value);

		typedef std::is_convertible<int, ft::vector<int> > isFillCtorImplicitIntegral;
		EXPECT_FALSE(isFillCtorImplicitIntegral::value);
		typedef std::is_convertible<DerivedInt, ft::vector<DerivedInt> > isFillCtorImplicitNonIntegral;
		EXPECT_FALSE(isFillCtorImplicitNonIntegral::value);
	};
}
