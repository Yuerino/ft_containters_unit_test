#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, AssignFill) {
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

	TYPED_TEST(VectorTest, AssignRandomIter) {
		decltype(this->stdvector) stdvector2(rand() % TEST_SIZE, rand() % TEST_SIZE);
		this->ftvector.assign(stdvector2.begin(), stdvector2.end());
		this->stdvector.assign(stdvector2.begin(), stdvector2.end());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, AssignRandomIter) {
		decltype(this->stdvector) stdvector2(rand() % TEST_SIZE, rand() % TEST_SIZE);
		this->ftvector.assign(stdvector2.begin(), stdvector2.end());
		this->stdvector.assign(stdvector2.begin(), stdvector2.end());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(VectorTest, AssignFromArray) {
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		this->ftvector.assign(myints, myints + sizeof(myints) / sizeof(int));
		this->stdvector.assign(myints, myints + sizeof(myints) / sizeof(int));
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, AssignFromArray) {
		int myints[] = {43, 53, 23, 765, 45, 69, 42, 55, 0, -1, 55555};
		this->ftvector.assign(myints, myints + sizeof(myints) / sizeof(int));
		this->stdvector.assign(myints, myints + sizeof(myints) / sizeof(int));
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(VectorTest, AssignBiDirIter) {
		std::list<typename decltype(this->stdvector)::value_type> stdlist(rand() % TEST_SIZE, rand() % TEST_SIZE);
		this->ftvector.assign(stdlist.begin(), stdlist.end());
		this->stdvector.assign(stdlist.begin(), stdlist.end());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, AssignBiDirIter) {
		std::list<typename decltype(this->stdvector)::value_type> stdlist(rand() % TEST_SIZE, rand() % TEST_SIZE);
		this->ftvector.assign(stdlist.begin(), stdlist.end());
		this->stdvector.assign(stdlist.begin(), stdlist.end());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(VectorTest, AssignInputIter) {
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		this->ftvector.assign(first1, last);
		this->stdvector.assign(first2, last);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, AssignInputIter) {
		std::istringstream str1("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istringstream str2("54 34 5754 344 5 6456 345 0 -1 42 69 55123");
		std::istream_iterator<int> first1(str1);
		std::istream_iterator<int> first2(str2);
		std::istream_iterator<int> last;
		this->ftvector.assign(first1, last);
		this->stdvector.assign(first2, last);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};
}
