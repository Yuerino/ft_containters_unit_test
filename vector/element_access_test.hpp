#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(RandomizeVectorTest, At) {
		// Strong guarantee in case of out of bounds exception
		for (int i = 0; i < TEST_SIZE; ++i) {
			int idx = rand() % TEST_SIZE;
			EXPECT_EQ(this->ftvector.at(idx), this->stdvector.at(idx));
		}

		for (int i = 0; i < TEST_SIZE; ++i) {
			int idx = rand() % TEST_SIZE, num = rand() % TEST_SIZE;
			this->ftvector.at(idx) = num;
			this->stdvector.at(idx) = num;
		}
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));

		EXPECT_ANY_THROW(this->ftvector.at(TEST_SIZE + 1));
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, AtConst) {
		// Strong guarantee in case of out of bounds exception
		decltype(this->ftvector) const ftvector2(this->ftvector);

		for (int i = 0; i < TEST_SIZE; ++i) {
			int idx = rand() % TEST_SIZE;
			EXPECT_EQ(ftvector2.at(idx), this->stdvector.at(idx));
		}

		EXPECT_TRUE(std::is_const< std::remove_reference_t<decltype(ftvector2.at(0))> >::value);

		EXPECT_ANY_THROW(ftvector2.at(TEST_SIZE + 1));
		EXPECT_THAT(ftvector2, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, AccessOp) {
		// No-throw guarantee but undefined behaviour if out of bounds
		for (int i = 0; i < TEST_SIZE; ++i) {
			int idx = rand() % TEST_SIZE;
			EXPECT_EQ(this->ftvector[idx], this->stdvector[idx]);
		}

		for (int i = 0; i < TEST_SIZE; ++i) {
			int idx = rand() % TEST_SIZE, num = rand() % TEST_SIZE;
			this->ftvector[idx] = num;
			this->stdvector[idx] = num;
		}
		EXPECT_THAT(this->ftvector, ft::ContainerEq(this->stdvector));
	};

	TYPED_TEST(RandomizeVectorTest, AccessOpConst) {
		// No-throw guarantee but undefined behaviour if out of bounds
		decltype(this->ftvector) const ftvector2(this->ftvector);

		for (int i = 0; i < TEST_SIZE; ++i) {
			int idx = rand() % TEST_SIZE;
			EXPECT_EQ(ftvector2[idx], this->stdvector[idx]);
		}

		EXPECT_TRUE(std::is_const< std::remove_reference_t<decltype(ftvector2[0])> >::value);
	};

	TYPED_TEST(RandomizeVectorTest, Front) {
		// No-throw guarantee but undefined behaviour if empty
		EXPECT_EQ(this->ftvector.front(), this->stdvector.front());

		decltype(this->ftvector) const ftvector2(this->ftvector);
		EXPECT_EQ(ftvector2.front(), this->stdvector.front());
		EXPECT_TRUE(std::is_const< std::remove_reference_t<decltype(ftvector2.front())> >::value);
	};

	TYPED_TEST(RandomizeVectorTest, Back) {
		// No-throw guarantee but undefined behaviour if empty
		EXPECT_EQ(this->ftvector.back(), this->stdvector.back());

		decltype(this->ftvector) const ftvector2(this->ftvector);
		EXPECT_EQ(ftvector2.back(), this->stdvector.back());
		EXPECT_TRUE(std::is_const< std::remove_reference_t<decltype(ftvector2.back())> >::value);
	};

	TYPED_TEST(RandomizeVectorTest, Data) {
		// No-throw guarantee
		typename decltype(this->ftvector)::pointer ft_p = this->ftvector.data();
		typename decltype(this->stdvector)::pointer std_p = this->stdvector.data();

		for (int i = 0; i < TEST_SIZE; ++i, ++ft_p, ++std_p)
			EXPECT_EQ(*ft_p, *std_p);

		ft_p = this->ftvector.data();
		std_p = this->stdvector.data();
		for (int i = 0; i < TEST_SIZE; ++i, ++ft_p, ++std_p) {
			int num = rand() % TEST_SIZE;
			*ft_p = num;
			*std_p = num;
		}

		ft_p = this->ftvector.data();
		std_p = this->stdvector.data();
		for (int i = 0; i < TEST_SIZE; ++i, ++ft_p, ++std_p)
			EXPECT_EQ(*ft_p, *std_p);
	};

	TYPED_TEST(RandomizeVectorTest, DataConst) {
		// No-throw guarantee
		decltype(this->ftvector) const ftvector2(this->ftvector);
		typename decltype(ftvector2)::const_pointer ft_p = this->ftvector.data();
		typename decltype(this->stdvector)::pointer std_p = this->stdvector.data();

		for (int i = 0; i < TEST_SIZE; ++i, ++ft_p, ++std_p)
			EXPECT_EQ(*ft_p, *std_p);

		EXPECT_TRUE(std::is_const< std::remove_pointer_t<decltype(ftvector2.data())> >::value);
	};
}
