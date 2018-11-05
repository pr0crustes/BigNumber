/**
 * Simple test framework made by me, pr0crustes.
 */
#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <iostream>
#include <sstream>


namespace _TF_IGNORE {  // Namespace for hidding globals.
	bool TF_PRINT_ONLY_FAIL = false;
	int TF_GLOBAL_ERROR_COUNT = 0;
	int TF_GLOBAL_TEST_COUNT = 0;
	std::stringstream TF_GLOBAL_ASSERTIONS_SS;
}


int TF_PRINT_RESULTS() {
	std::cout << _TF_IGNORE::TF_GLOBAL_ASSERTIONS_SS.str() << std::endl;
	if (_TF_IGNORE::TF_GLOBAL_ERROR_COUNT > 0) {
		std::cout << "\n==> " << _TF_IGNORE::TF_GLOBAL_ERROR_COUNT << " of " << _TF_IGNORE::TF_GLOBAL_TEST_COUNT << " tests failed.\n";
		return 1;
	} else {
		std::cout << "\n==> All of " << _TF_IGNORE::TF_GLOBAL_TEST_COUNT << " tests passed.\n";
		return 0;
	}
}


void TF_SET_ONLY_FAIL(bool b) {
	_TF_IGNORE::TF_PRINT_ONLY_FAIL = b;
}


#define _TF_IGNORE_ASSERT_MESSAGE(name) _TF_IGNORE::TF_GLOBAL_ASSERTIONS_SS << "\nAssertion \'" << name << "\' at file \'" << __FILE__ "\' at line \'" << __LINE__ << "\' ->  "

#define TF_ASSERT(name, a, b) \
{ \
	_TF_IGNORE::TF_GLOBAL_TEST_COUNT++; \
	auto ra = a; \
	auto rb = b; \
	if (ra == rb) { \
		if (!_TF_IGNORE::TF_PRINT_ONLY_FAIL) { \
			_TF_IGNORE_ASSERT_MESSAGE(name); \
			_TF_IGNORE::TF_GLOBAL_ASSERTIONS_SS << "Passed\n"; \
		} \
	} else { \
		_TF_IGNORE_ASSERT_MESSAGE(name); \
		_TF_IGNORE::TF_GLOBAL_ERROR_COUNT++; \
		_TF_IGNORE::TF_GLOBAL_ASSERTIONS_SS << "Failed: Expected \'" << rb << "\' received \'" << ra << "\'\n"; \
	} \
}

#endif // TESTFRAMEWORK_H
