#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(RandomizeVectorTest, ErasePosition) {
		// Invalidate all iterator from position iterator
		int idx = rand() % TEST_SIZE;
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.at(idx);

		it2 = this->ftvector.erase(this->ftvector.begin() + idx);
		this->stdvector.erase(this->stdvector.begin() + idx);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.at(idx));
		EXPECT_EQ(*it2, this->ftvector.at(idx));
		for (it2 = this->ftvector.begin(), ite = this->ftvector.begin() + idx; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, ErasePositionExcepetion) {
		// Basic guarantee if position is not the last element
		typedef typename decltype(this->ftvector)::value_type value_type;
		if (!std::is_same<value_type, DerivedInt>::value) return;

		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		int idx = rand() % (TEST_SIZE - 2) + 2;
		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.erase(this->ftvector.begin() + idx));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.erase(this->stdvector.begin() + idx));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) /* ignore */ ;
	};

	TYPED_TEST(RandomizeVectorTest, ErasePositionLastExcepetion) {
		// Nothrow guarantee in case in case position is last element
		typedef typename decltype(this->ftvector)::value_type value_type;
		if (!std::is_same<value_type, DerivedInt>::value) return;

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.back();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_NO_THROW(it2 = this->ftvector.erase(this->ftvector.end() - 1));
		::DerivedInt::to_throw = 0;
		ASSERT_NO_THROW(this->stdvector.erase(this->stdvector.end() - 1));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.back());
		EXPECT_EQ(it2, this->ftvector.end());
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end() - 1; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, ErasePositionRandom) {
		// Test with randomized values
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

	TYPED_TEST(RandomizeVectorTest, EraseRange) {
		// Invalidate all iterator from first iterator
		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.at(42);

		it2 = this->ftvector.erase(this->ftvector.begin() + 42, this->ftvector.begin() + 69);
		this->stdvector.erase(this->stdvector.begin() + 42, this->stdvector.begin() + 69);

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.at(42));
		EXPECT_EQ(*it2, this->ftvector.at(42));
		for (it2 = this->ftvector.begin(), ite = this->ftvector.begin() + 42; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, EraseRangeExcepetion) {
		// Basic guarantee if last is not the end iterator
		typedef typename decltype(this->ftvector)::value_type value_type;
		if (!std::is_same<value_type, DerivedInt>::value) return;

		typename decltype(this->ftvector)::iterator it;
		typename decltype(this->ftvector)::iterator ite;

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->ftvector.erase(this->ftvector.begin() + 42, this->ftvector.begin() + 69));
		::DerivedInt::to_throw = -2;
		ASSERT_ANY_THROW(this->stdvector.erase(this->stdvector.begin() + 42, this->stdvector.begin() + 69));
		g_vector_force_exception = ::NO_EXCEPTION;

		#ifdef TEST_EXACT
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		#endif
		EXPECT_GE(this->ftvector.capacity(), this->ftvector.size());
		for (it = this->ftvector.begin(), ite = this->ftvector.end(); it != ite; ++it) /* ignore */ ;
	};

	TYPED_TEST(RandomizeVectorTest, EraseRangeLastExcepetion) {
		// Nothrow guarantee in case in case last is end iterator
		typedef typename decltype(this->ftvector)::value_type value_type;
		if (!std::is_same<value_type, DerivedInt>::value) return;

		typename decltype(this->ftvector)::iterator it = this->ftvector.begin();
		typename decltype(this->ftvector)::iterator it2;
		typename decltype(this->ftvector)::iterator ite;
		typename decltype(this->ftvector)::value_type old_num = this->ftvector.back();

		g_vector_force_exception = ::ALL_EXCEPTION | ::THROW_ON_NBR;
		::DerivedInt::to_throw = 0;
		ASSERT_NO_THROW(it2 = this->ftvector.erase(this->ftvector.begin() + 69, this->ftvector.end()));
		::DerivedInt::to_throw = 0;
		ASSERT_NO_THROW(this->stdvector.erase(this->stdvector.begin() + 69, this->stdvector.end()));
		g_vector_force_exception = ::NO_EXCEPTION;

		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
		EXPECT_NE(old_num, this->ftvector.back());
		EXPECT_EQ(it2, this->ftvector.end());
		for (it2 = this->ftvector.begin(), ite = this->ftvector.end() - 1; it != ite; ++it, ++it2)
			EXPECT_EQ(it, it2);
	};

	TYPED_TEST(RandomizeVectorTest, EraseRangeRandom) {
		// Test with randomized values
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
