#pragma once
#include "vector_helper.hpp"

namespace {
	TEST(VectorDefaultCtorTest, Integral) {
		ft::vector<int> v1;
		EXPECT_EQ(0, v1.size());
		EXPECT_EQ(0, v1.capacity());
	};

	TEST(VectorDefaultCtorTest, NonIntegral) {
		ft::vector<DerivedInt> v1;
		EXPECT_EQ(0, v1.size());
		EXPECT_EQ(0, v1.capacity());
	};

	TEST(VectorFillCtorTest, IntegralWithoutValue) {
		int num = rand() % TEST_SIZE;
		ft::vector<int> v1(num);
		std::vector<int> _v1(num);
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorFillCtorTest, NonIntegralWithoutValue) {
		int num = rand() % TEST_SIZE;
		ft::vector<DerivedInt> v1(num);
		std::vector<DerivedInt> _v1(num);
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorFillCtorTest, IntegralWithValue) {
		int num = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		ft::vector<int> v1(num, num2);
		std::vector<int> _v1(num, num2);
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorFillCtorTest, NonIntegralWithValue) {
		int num = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		ft::vector<DerivedInt> v1(num, num2);
		std::vector<DerivedInt> _v1(num, num2);
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorRangeCtorTest, FromVectorIteratorIntegral) {
		// vector iterator is random access type
		std::vector<int> v(rand() % TEST_SIZE, rand() % TEST_SIZE);

		ft::vector<int> v1(v.begin(), v.end());
		EXPECT_THAT(v1, ft::ContainerEq(v));
	};

	TEST(VectorRangeCtorTest, RandomAccessIteratorNonIntegral) {
		// vector iterator is random access type
		std::vector<DerivedInt> v(rand() % TEST_SIZE, rand() % TEST_SIZE);

		ft::vector<DerivedInt> v1(v.begin(), v.end());
		EXPECT_THAT(v1, ft::ContainerEq(v));
	};

	TEST(VectorRangeCtorTest, FromArrayIntegral) {
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		ft::vector<int> v1(myints, myints + sizeof(myints) / sizeof(int));
		ft::vector<int> _v1(myints, myints + sizeof(myints) / sizeof(int));
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorRangeCtorTest, FromArrayNonIntegral) {
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		ft::vector<DerivedInt> v1(myints, myints + sizeof(myints) / sizeof(int));
		ft::vector<DerivedInt> _v1(myints, myints + sizeof(myints) / sizeof(int));
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorRangeCtorTest, BiDirIteratorIntegral) {
		// list iterator is bidirectional type
		std::list<int> l(rand() % TEST_SIZE, rand() % TEST_SIZE);
		ft::vector<int> v1(l.begin(), l.end());
		std::vector<int> _v1(l.begin(), l.end());
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorRangeCtorTest, BiDirIteratorNonIntegral) {
		// list iterator is bidirectional type
		std::list<int> l(rand() % TEST_SIZE, rand() % TEST_SIZE);
		ft::vector<DerivedInt> v1(l.begin(), l.end());
		std::vector<DerivedInt> _v1(l.begin(), l.end());
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorRangeCtorTest, InputIteratorIntegral) {
		// stream iterator is input type
		std::istringstream str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream _str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str);
		std::istream_iterator<int> first2(_str);
		std::istream_iterator<int> last;
		ft::vector<int> v1(first1, last);
		std::vector<int> _v1(first2, last);
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorRangeCtorTest, InputIteratorNonIntegral) {
		// stream iterator is input type
		std::istringstream str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream _str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str);
		std::istream_iterator<int> first2(_str);
		std::istream_iterator<int> last;
		ft::vector<DerivedInt> v1(first1, last);
		std::vector<DerivedInt> _v1(first2, last);
		EXPECT_THAT(v1, ft::ContainerEq(_v1));
	};

	TEST(VectorRangeCtorTest, Constructible) {
		typedef std::is_constructible<ft::vector<int>, DerivedInt, DerivedInt> isConstructibleWithNonIteratorIntegral;
		EXPECT_FALSE(isConstructibleWithNonIteratorIntegral::value);

		typedef std::is_constructible<ft::vector<DerivedInt>, DerivedInt, DerivedInt> isConstructibleWithNonIteratorNonIntegral;
		EXPECT_FALSE(isConstructibleWithNonIteratorNonIntegral::value);
	}

	TEST(VectorCopyCtorTest, Integral) {
		int num = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		ft::vector<int> v(num, num2);
		std::vector<int> _v(num, num2);

		ft::vector<int> v1(v);
		EXPECT_THAT(v1, ft::ContainerEq(_v));
	};

	TEST(VectorCopyCtorTest, NonIntegral) {
		int num = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		ft::vector<DerivedInt> v(num, num2);
		std::vector<DerivedInt> _v(num, num2);

		ft::vector<DerivedInt> v1(v);
		EXPECT_THAT(v1, ft::ContainerEq(_v));
	};

	TEST(VectorAssignOpTest, Integral) {
		int num = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		ft::vector<int> v(num, num2);
		std::vector<int> _v(num, num2);

		ft::vector<int> v1;
		v1 = v;
		EXPECT_THAT(v1, ft::ContainerEq(_v));
	};

	TEST(VectorAssignOpTest, NonIntegral) {
		int num = rand() % TEST_SIZE;
		int num2 = rand() % TEST_SIZE;
		ft::vector<DerivedInt> v(num, num2);
		std::vector<DerivedInt> _v(num, num2);

		ft::vector<DerivedInt> v1;
		v1 = v;
		EXPECT_THAT(v1, ft::ContainerEq(_v));
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
