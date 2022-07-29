#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <type_traits>
#include <memory>
#include <list>
#include <sstream>

#include "vector.hpp"
#include <vector>

#ifndef TEST_SIZE
#define TEST_SIZE 1000
#endif

// Fixture for testing
namespace {
	class VectorTest : public ::testing::Test {
	protected:
		ft::vector<int> ftvector;
		std::vector<int> stdvector;
	};
}

namespace ft {
	template<typename T>
	std::ostream& operator<<(std::ostream& os, const ft::vector<T>& v) {
		os << "ft::vector: size: " << v.size() << ", capacity: " << v.capacity() << ", max size: " << v.max_size() << "\n[ ";
		for (typename ft::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
			os << *it << " ";
		os << "]";
		return os;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
		os << "std::vector: size: " << v.size() << ", capacity: " << v.capacity() << ", max size: " << v.max_size() << "\n[ ";
		for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); ++it)
			os << *it << " ";
		os << "]";
		return os;
	}

	template<typename Container>
	class ContainerEqMatcher {
	public:
		typedef ::testing::internal::StlContainerView<Container>	View;
		typedef typename View::type									StlContainer;
		typedef typename View::const_reference						StlContainerReference;

		static_assert(!std::is_const<Container>::value, "Container type must not be const");
		static_assert(!std::is_reference<Container>::value, "Container type must not be a reference");

	public:
		explicit ContainerEqMatcher(const Container& expected) : expected_(View::Copy(expected)) {}

		void DescribeTo(std::ostream* os) const {
			*os << "equals ";
			::testing::internal::UniversalPrint(expected_, os);
		}

		void DescribeNegationTo(std::ostream* os) const {
			*os << "does not equal ";
			::testing::internal::UniversalPrint(expected_, os);
		}

		template <typename LhsContainer>
		bool MatchAndExplain(const LhsContainer& lhs, ::testing::MatchResultListener* listener) const {
			typedef ::testing::internal::StlContainerView<typename std::remove_const<LhsContainer>::type> LhsView;
			typedef typename LhsView::type LhsStlContainer;
			typedef typename LhsView::const_reference LhsStlReference;

			LhsStlReference lhs_stl_container = LhsView::ConstReference(lhs);
			if (lhs_stl_container == expected_)
				return true;

			std::ostream* const os = listener->stream();
			if (os != nullptr) {
				bool printed_header = false;
				for (typename LhsStlContainer::const_iterator it = lhs_stl_container.begin(); it != lhs_stl_container.end(); ++it) {
					if (::testing::internal::ArrayAwareFind(expected_.begin(), expected_.end(), *it) == expected_.end()) {
						if (printed_header) {
							*os << ", ";
						} else {
							*os << "which has these unexpected elements: ";
							printed_header = true;
						}
						::testing::internal::UniversalPrint(*it, os);
					}
				}

				// Now check for missing values.
				bool printed_header2 = false;
				for (typename StlContainer::const_iterator it = expected_.begin(); it != expected_.end(); ++it) {
					if (::testing::internal::ArrayAwareFind(lhs_stl_container.begin(), lhs_stl_container.end(), *it) == lhs_stl_container.end()) {
						if (printed_header2) {
							*os << ", ";
						} else {
							*os << (printed_header ? ",\n\tand" : "which") << " doesn't have these expected elements: ";
							printed_header2 = true;
						}
						::testing::internal::UniversalPrint(*it, os);
					}
				}

				// Print both container information
				*os << std::endl << lhs_stl_container << std::endl << expected_;
			}

			return false;
		}

	private:
		const StlContainer expected_;
	};

	template <typename Container>
	::testing::PolymorphicMatcher<ft::ContainerEqMatcher<typename std::remove_const<Container>::type>> ContainerEq(const Container& rhs) {
		return ::testing::MakePolymorphicMatcher(ft::ContainerEqMatcher<Container>(rhs));
	}

	template<typename T, typename Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs) {
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}

	template<typename T, typename Alloc>
	bool operator==(const std::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}

}
