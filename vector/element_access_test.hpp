#pragma once
#include "vector_helper.hpp"

namespace {
	TYPED_TEST(RandomizeVectorTest, At) {
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
	};

	TYPED_TEST(RandomizeVectorTest, AtConst) {
		decltype(this->ftvector) const ftvector2(this->ftvector);

		for (int i = 0; i < TEST_SIZE; ++i) {
			int idx = rand() % TEST_SIZE;
			EXPECT_EQ(ftvector2.at(idx), this->stdvector.at(idx));
		}

		EXPECT_TRUE(std::is_const< std::remove_reference_t<decltype(ftvector2.at(0))> >::value);

		EXPECT_ANY_THROW(ftvector2.at(TEST_SIZE + 1));
	};

	TYPED_TEST(RandomizeVectorTest, AccessOp) {
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
		decltype(this->ftvector) const ftvector2(this->ftvector);

		for (int i = 0; i < TEST_SIZE; ++i) {
			int idx = rand() % TEST_SIZE;
			EXPECT_EQ(ftvector2[idx], this->stdvector[idx]);
		}

		EXPECT_TRUE(std::is_const< std::remove_reference_t<decltype(ftvector2[0])> >::value);
	};

	TYPED_TEST(RandomizeVectorTest, Front) {
		EXPECT_EQ(this->ftvector.front(), this->stdvector.front());

		decltype(this->ftvector) const ftvector2(this->ftvector);
		EXPECT_EQ(ftvector2.front(), this->stdvector.front());
		EXPECT_TRUE(std::is_const< std::remove_reference_t<decltype(ftvector2.front())> >::value);
	};

	TYPED_TEST(RandomizeVectorTest, Back) {
		EXPECT_EQ(this->ftvector.back(), this->stdvector.back());

		decltype(this->ftvector) const ftvector2(this->ftvector);
		EXPECT_EQ(ftvector2.back(), this->stdvector.back());
		EXPECT_TRUE(std::is_const< std::remove_reference_t<decltype(ftvector2.back())> >::value);
	};
}
