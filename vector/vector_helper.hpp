#pragma once

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

namespace {
	enum derived_force_exception {
		NO_EXCEPTION = 0,
		DEFAULT_CTOR_EXCEPTION = (1 << 0),
		INT_CTOR_EXCEPTION = (1 << 1),
		COPY_CTOR_EXCEPTION = (1 << 2),
		COPY_ASSIGN_EXCEPTION = (1 << 3),
		ALL_EXCEPTION = 255,
		THROW_ON_NBR = (1 << 9)
	};
}

// Used to force DerivedInt throw exception
extern int g_vector_force_exception = ::NO_EXCEPTION;

// Fixture for testing
namespace {
	// struct BaseDerivedInt {
	// 	int nbr;
	// 	int* leak;

	// 	BaseDerivedInt() : nbr(42), leak(0) { }
	// 	BaseDerivedInt(const int& n) : nbr(n), leak(new int(69)) { }
	// 	BaseDerivedInt(const int& n, int* l) : nbr(n), leak(l) { }
	// 	BaseDerivedInt(const BaseDerivedInt& copy) : nbr(copy.nbr), leak(0) { }
	// 	BaseDerivedInt& operator=(const BaseDerivedInt& other) {
	// 		this->nbr = other.nbr;
	// 		return *this;
	// 	}
	// 	virtual ~BaseDerivedInt() {
	// 		this->nbr++;
	// 		if (this->leak)
	// 			delete this->leak;
	// 		this->leak = NULL;
	// 	}
	// };

	// struct DerivedInt : public BaseDerivedInt {
	// 	DerivedInt() : BaseDerivedInt() { }
	// 	DerivedInt(const int& n) : BaseDerivedInt(n, NULL) { }
	// 	DerivedInt(const DerivedInt& copy) : BaseDerivedInt(copy.nbr, NULL) { }
	// 	DerivedInt& operator=(const DerivedInt& other) {
	// 		this->nbr = other.nbr;
	// 		return *this;
	// 	}
	// 	DerivedInt(const BaseDerivedInt* base) : BaseDerivedInt() {
	// 		if (base == NULL) return;
	// 		if (base->nbr < 0) throw "42";
	// 		this->nbr = base->nbr;
	// 		this->leak = new int(69);
	// 	}
	// 	~DerivedInt() {
	// 		this->nbr++;
	// 		if (this->leak)
	// 			delete this->leak;
	// 		this->leak = NULL;
	// 	}
	// };

	struct DerivedInt {
		static int to_throw;
		int nbr;
		int* leak;

		DerivedInt() : nbr(-1), leak(0) {
			if ((g_vector_force_exception & ::DEFAULT_CTOR_EXCEPTION) != 0) {
				if ((g_vector_force_exception & ::THROW_ON_NBR) != 0 && ::DerivedInt::to_throw >= 0) {
					throw "42";
				}
				else if ((g_vector_force_exception & ::THROW_ON_NBR) == 0) {
					throw "42";
				}
			}
			this->leak = new int(69);
			::DerivedInt::to_throw++;
		}
		DerivedInt(const int& val) : nbr(val), leak(0) {
			if ((g_vector_force_exception & ::INT_CTOR_EXCEPTION) != 0) {
				if ((g_vector_force_exception & ::THROW_ON_NBR) != 0 && ::DerivedInt::to_throw >= 0)
					throw "42";
				else if ((g_vector_force_exception & ::THROW_ON_NBR) == 0)
					throw "42";
			}
			this->leak = new int(69);
			::DerivedInt::to_throw++;
		}
		DerivedInt(const DerivedInt& copy) : nbr(copy.nbr), leak(0) {
			if ((g_vector_force_exception & ::COPY_CTOR_EXCEPTION) != 0) {
				if ((g_vector_force_exception & ::THROW_ON_NBR) != 0 && ::DerivedInt::to_throw >= 0)
					throw "42";
				else if ((g_vector_force_exception & ::THROW_ON_NBR) == 0)
					throw "42";
			}
			this->leak = new int(69);
			::DerivedInt::to_throw++;
		}
		DerivedInt& operator=(const DerivedInt& other) {
			if ((g_vector_force_exception & ::COPY_ASSIGN_EXCEPTION) != 0) {
				if ((g_vector_force_exception & ::THROW_ON_NBR) != 0 && ::DerivedInt::to_throw >= 0)
					throw "42";
				else if ((g_vector_force_exception & ::THROW_ON_NBR) == 0)
					throw "42";
			}
			::DerivedInt::to_throw++;
			if (&other == this) return *this;
			this->nbr = other.nbr;
			return *this;
		}
		virtual ~DerivedInt() {
			if (this->leak)
				delete this->leak;
			// This is to invalidate data at those memory in case user try to access them
			this->nbr++;
			this->leak = NULL;
		}
	};
	int DerivedInt::to_throw = 0;

	bool operator==(const DerivedInt& lhs, const DerivedInt& rhs) {
		return lhs.nbr == rhs.nbr;
	}

	bool operator!=(const DerivedInt& lhs, const DerivedInt& rhs) {
		return lhs.nbr != rhs.nbr;
	}

	bool operator<(const DerivedInt& lhs, const DerivedInt& rhs) {
		return lhs.nbr < rhs.nbr;
	}

	bool operator<=(const DerivedInt& lhs, const DerivedInt& rhs) {
		return lhs.nbr <= rhs.nbr;
	}

	bool operator>(const DerivedInt& lhs, const DerivedInt& rhs) {
		return lhs.nbr > rhs.nbr;
	}

	bool operator>=(const DerivedInt& lhs, const DerivedInt& rhs) {
		return lhs.nbr >= rhs.nbr;
	}

	std::ostream& operator<<(std::ostream& os, const DerivedInt& i) {
		os << i.nbr;
		return os;
	}

	typedef ::testing::Types<int, DerivedInt> TestTypes;

	template<typename T>
	class VectorTest : public ::testing::Test {
	protected:
		void SetUp() override {
			g_vector_force_exception = ::NO_EXCEPTION;
			::DerivedInt::to_throw = 0;
		}

		ft::vector<T> ftvector;
		std::vector<T> stdvector;
	};

	template<typename Container>
	Container ConstructRandomVector(int size = TEST_SIZE) {
		Container v;
		for (int i = 0; i < size; ++i)
			v.push_back(std::rand() % size);
		return v;
	}

	template<typename T>
	class RandomizeVectorTest : public VectorTest<T> {
	protected:
		void SetUp() override {
			VectorTest<T>::SetUp();
			decltype(this->stdvector) tmp(ConstructRandomVector<std::vector<T>>());
			this->stdvector = std::vector<T>(tmp.begin(), tmp.end());
			this->ftvector = ft::vector<T>(tmp.begin(), tmp.end());
		}

		void TearDown() override {
			this->ftvector.clear();
			this->stdvector.clear();
		}
	};

	TYPED_TEST_SUITE(VectorTest, TestTypes);
	TYPED_TEST_SUITE(RandomizeVectorTest, TestTypes);
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
		explicit ContainerEqMatcher(const Container& expected) : expected_(View::Copy(expected)), expected_capacity_(expected.capacity()) {}

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

#ifdef TEST_EXACT
			if (lhs_stl_container == expected_
				&& lhs_stl_container.capacity() == expected_capacity_
				&& lhs_stl_container.max_size() == expected_.max_size())
#else
			if (lhs_stl_container == expected_)
#endif
				return true;

			std::ostream* const os = listener->stream();
			if (os != nullptr) {

#ifdef TEST_EXACT
				if (lhs_stl_container.capacity() != expected_capacity_)
					ADD_FAILURE() << "capacity isn't the same: ft::vector: " << lhs_stl_container.capacity()
								<< " and std::vector: " << expected_capacity_ << std::endl;

				if (lhs_stl_container.max_size() != expected_.max_size())
					ADD_FAILURE() << "max_size isn't the same: ft::vector: " << lhs_stl_container.max_size()
								<< " and std::vector: " << expected_.max_size() << std::endl;
#endif

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
				*os << std::endl << std::endl << lhs_stl_container << std::endl << expected_;
			}

			return false;
		}

	private:
		typedef typename StlContainer::size_type size_type;

		const StlContainer expected_;
		const size_type expected_capacity_;
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
