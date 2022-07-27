#include <cstdio>
#include <cstdlib>

#include "gtest/gtest.h"

class RandomSeedEnvironment : public ::testing::Environment {
public:
	void SetUp() override {
		int _seed = ::testing::UnitTest::GetInstance()->random_seed();
		std::srand(_seed);
		std::cerr << "[ INFO     ] SEED: " << _seed << std::endl;
	}
};

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from %s\n", __FILE__);
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(new RandomSeedEnvironment);
	return RUN_ALL_TESTS();
}
