#include "vector_helper.hpp"

namespace {
	struct A {};

	TEST(VectorCtorTest, DefaultCtor) {
		ft::vector<int> v1;
		EXPECT_EQ(0, v1.size());
		EXPECT_EQ(0, v1.capacity());
	};

	TEST(VectorCtorTest, FillCtor) {
		int num = rand() % TEST_SIZE, num2;
		ft::vector<int> v1(num);
		std::vector<int> _v1(num);
		EXPECT_THAT(v1, ft::ContainerEq(_v1));

		num = rand() % TEST_SIZE;
		num2 = rand() % TEST_SIZE;
		ft::vector<int> v2(num, num2);
		std::vector<int> _v2(num, num2);
		EXPECT_THAT(v2, ft::ContainerEq(_v2));
	};

	TEST(VectorCtorTest, RangeCtor) {
		std::vector<int> v(rand() % TEST_SIZE, rand() % TEST_SIZE);

		ft::vector<int> v1(v.begin(), v.end());
		std::vector<int> _v1(v.begin(), v.end());
		EXPECT_THAT(v1, ft::ContainerEq(_v1));

		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		ft::vector<int> v2(myints, myints + sizeof(myints) / sizeof(int));
		ft::vector<int> _v2(myints, myints + sizeof(myints) / sizeof(int));
		EXPECT_THAT(v2, ft::ContainerEq(_v2));

		std::list<int> l(rand() % TEST_SIZE, rand() % TEST_SIZE);
		ft::vector<int> v3(l.begin(), l.end());
		std::vector<int> _v3(l.begin(), l.end());
		EXPECT_THAT(v3, ft::ContainerEq(_v3));

		std::istringstream str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream _str("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		ft::vector<int> v4(std::istream_iterator<int>(str), {});
		std::vector<int> _v4(std::istream_iterator<int>(_str), {});
		EXPECT_THAT(v4, ft::ContainerEq(_v4));

		typedef std::is_constructible<ft::vector<int>, A, A> isConstructibleWithNonIterator;
		EXPECT_FALSE(isConstructibleWithNonIterator::value);
	};

	TEST(VectorCtorTest, CopyCtor) {
		int num = rand() % TEST_SIZE, num2 = rand() % TEST_SIZE;
		ft::vector<int> v(num, num2);
		std::vector<int> _v(num, num2);

		ft::vector<int> v1(v);
		EXPECT_THAT(v1, ft::ContainerEq(_v));
	};

	TEST(VectorCtorTest, AssignOpTest) {
		int num = rand() % TEST_SIZE, num2 = rand() % TEST_SIZE;
		ft::vector<int> v(num, num2);
		std::vector<int> _v(num, num2);

		ft::vector<int> v1;
		v1 = v;
		EXPECT_THAT(v1, ft::ContainerEq(_v));
	};

	TEST(VectorCtorTest, ExplicitCtorTest) {
		// reason why typedef
		// https://stackoverflow.com/questions/38030048/too-many-arguments-provided-to-function-like-macro-invocation
		typedef std::is_convertible< std::allocator<int>, ft::vector<int> > isDefaultCtorImplicit;
		EXPECT_FALSE(isDefaultCtorImplicit::value);

		typedef std::is_convertible<int, ft::vector<int> > isFillCtorImplicit;
		EXPECT_FALSE(isFillCtorImplicit::value);
	};
}
