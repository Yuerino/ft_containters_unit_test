#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "vector_helper.hpp"

#include <type_traits>

namespace {

	template<typename T>
	class DerivedAllocator : public std::allocator<T> {
		typedef std::allocator<T> Base;
		using Base::Base;
	};

	TEST(VectorCtorTest, DefaultCtor) {
		ft::vector<int> v1;
		EXPECT_EQ(0, v1.size());
		EXPECT_EQ(0, v1.capacity());

		ft::vector<int, DerivedAllocator<int> > v2;
		EXPECT_EQ(0, v2.size());
		EXPECT_EQ(0, v2.capacity());

		DerivedAllocator<int> alloc;
		ft::vector<int, DerivedAllocator<int> > v3(alloc);
		EXPECT_EQ(0, v3.size());
		EXPECT_EQ(0, v3.capacity());

		// reason why typedef
		// https://stackoverflow.com/questions/38030048/too-many-arguments-provided-to-function-like-macro-invocation
		typedef std::is_convertible< DerivedAllocator<int>, ft::vector<int> > isDefaultCtorImplicit;
		EXPECT_FALSE(isDefaultCtorImplicit::value);
	};

// TEST(VectorCtorTest, FillCtor) {
// 	// random size + with/without value (integral)
// 	// random size + with/without value (random type, class with and without copy ctor)
// 	// with allocator object
// 	// explicit
// }

// TEST(VectorCtorTest, RangeCtor) {
// 	// random access iter
// 	// array
// 	// bd iter (list)
// 	// input iter (istream_iterator)
// 	// assert that it doesnt work with non iter non integral type
// 	// with allocator object
// 	// implicit
// }

// TEST(VectorCtorTest, CopyCtor) {
// 	// vector with/without random value/type
// 	// implicit
// }

}
