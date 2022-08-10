#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(VectorTest, ErasePosition) {
		typename decltype(this->ftvector)::iterator it;
		this->ftvector.push_back(69);
		this->stdvector.push_back(69);

		it = this->ftvector.erase(this->ftvector.begin());
		this->stdvector.erase(this->stdvector.begin());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(it == this->ftvector.end());
	};

	TYPED_TEST(RandomizeVectorTest, ErasePosition) {
		typename decltype(this->ftvector)::iterator ft_it;
		typename decltype(this->stdvector)::iterator std_it;

		ft_it = this->ftvector.erase(this->ftvector.begin());
		std_it = this->stdvector.erase(this->stdvector.begin());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(*ft_it, *std_it);

		int num = rand() % (TEST_SIZE - 2);
		ft_it = this->ftvector.erase(this->ftvector.begin() + num);
		std_it = this->stdvector.erase(this->stdvector.begin() + num);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(*ft_it, *std_it);

		num = (rand() % (TEST_SIZE - 3)) + 1;
		ft_it = this->ftvector.erase(this->ftvector.end() - num);
		std_it = this->stdvector.erase(this->stdvector.end() - num);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(*ft_it, *std_it);

		ft_it = this->ftvector.erase(this->ftvector.end() - 1);
		this->stdvector.erase(this->stdvector.end() - 1);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(ft_it == this->ftvector.end());
	};

	TYPED_TEST(VectorTest, EraseRange) {
		typename decltype(this->ftvector)::iterator it;
		this->ftvector.push_back(69);
		this->stdvector.push_back(69);
		it = this->ftvector.erase(this->ftvector.begin(), this->ftvector.end());
		this->stdvector.erase(this->stdvector.begin(), this->stdvector.end());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(it == this->ftvector.end());
	};

	TYPED_TEST(RandomizeVectorTest, EraseRange) {
		typename decltype(this->ftvector)::iterator ft_it;
		typename decltype(this->stdvector)::iterator std_it;

		ft_it = this->ftvector.erase(this->ftvector.begin(), this->ftvector.begin() + 69);
		std_it = this->stdvector.erase(this->stdvector.begin(), this->stdvector.begin() + 69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(*ft_it, *std_it);

		ft_it = this->ftvector.erase(this->ftvector.begin() + 42, this->ftvector.begin() + 69);
		std_it = this->stdvector.erase(this->stdvector.begin() + 42, this->stdvector.begin() + 69);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(*ft_it, *std_it);

		ft_it = this->ftvector.erase(this->ftvector.end() - 42, this->ftvector.end());
		this->stdvector.erase(this->stdvector.end() - 42, this->stdvector.end());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(ft_it == this->ftvector.end());

		ft_it = this->ftvector.erase(this->ftvector.end() - 69, this->ftvector.end() - 42);
		std_it = this->stdvector.erase(this->stdvector.end() - 69, this->stdvector.end() - 42);
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_EQ(*ft_it, *std_it);

		ft_it = this->ftvector.erase(this->ftvector.begin(), this->ftvector.end());
		this->stdvector.erase(this->stdvector.begin(), this->stdvector.end());
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_TRUE(ft_it == this->ftvector.end());
	};
}
