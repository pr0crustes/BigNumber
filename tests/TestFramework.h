/**
 * Simple test framework made by me, pr0crustes.
 * This file is included in the MIT license.
 * Do not remove this comment.
 * @2018
 */
#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <iostream>
#include <sstream>
#include <chrono>


/**
 * If TF_PRINT_ONLY_FAIL is defined, only errors will be printed.
 * If TF_IGNORE_TESTS is defined, all tests are skipped.
 */

namespace _TF_IGNORE {  // Namespace for hidding stuff.
	int GLOBAL_ERROR_COUNT = 0;  // number of errors found.
	int GLOBAL_TEST_COUNT = 0;  // number of tests runned.
	std::stringstream GLOBAL_ASSERTIONS_SS;  // stringstream, where the messages will be apended.


	/**
	 * @brief addMessage adds a log message to GLOBAL_ASSERTIONS_SS.
	 * @param name the assertion name.
	 * @param file the assertion file name.
	 * @param line the assertion line number.
	 */
	void addMessage(std::string name, const char* file, int line) {
		_TF_IGNORE::GLOBAL_ASSERTIONS_SS << "\nAssertion \'" << name << "\' at file \'" << file << "\' at line \'" << line << "\' ->  ";
	}


	/**
	 * @brief validate checks if a == b, appendind to assertions if necessary.
	 * @param a the thing to be check.
	 * @param b the thing that a should be equal to.
	 * @param name the assertion name.
	 * @param file the assertion file name.
	 * @param line the assertion line number.
	 */
	template<typename T1, typename T2>
	void validate(T1 a, T2 b, std::string name, const char* file, int line) {
		_TF_IGNORE::GLOBAL_TEST_COUNT++;
		if (a == b) {
#ifndef TF_PRINT_ONLY_FAIL
			_TF_IGNORE::addMessage(name, file, line);
			_TF_IGNORE::GLOBAL_ASSERTIONS_SS << "Passed\n";
#endif
		} else {
			_TF_IGNORE::GLOBAL_ERROR_COUNT++;
			_TF_IGNORE::addMessage(name, file, line);
			_TF_IGNORE::GLOBAL_ASSERTIONS_SS << "Failed: Expected \'" << b << "\' received \'" << a << "\'\n";
		}
	}

}


/**
 * @brief TF_EXIT_CODE true if tests failed, 0 if passed.
 */
#define TF_EXIT_CODE() (_TF_IGNORE::GLOBAL_ERROR_COUNT > 0)


/**
 * @brief TF_PRINT_RESULT macro for printing the test result.
 */
#ifdef TF_IGNORE_TESTS
#define TF_PRINT_RESULT() {std::cout << "\n==> Ignored all tests." << std::endl;}
#else
#define TF_PRINT_RESULT() \
{ \
	std::cout << _TF_IGNORE::GLOBAL_ASSERTIONS_SS.str() << std::endl; \
	std::cout << "\n==> "; \
	if (_TF_IGNORE::GLOBAL_ERROR_COUNT > 0) { \
		std::cout << _TF_IGNORE::GLOBAL_ERROR_COUNT << " of " << _TF_IGNORE::GLOBAL_TEST_COUNT << " tests failed." << std::endl; \
	} else { \
		std::cout << "All of " << _TF_IGNORE::GLOBAL_TEST_COUNT << " tests passed." << std::endl; \
	} \
}
#endif


/**
 * @brief TF_ASSERT macro that does the assert.
 * This will call validate under the hood, passing FILE and LINE as arguments.
 * Since we want to know the file and line, this need to be a macro.
 * @param name the assertion name.
 * @param a the thing to be checked.
 * @param b the thing that a should be equal to.
 */
#ifdef TF_IGNORE_TESTS
#define TF_ASSERT(name, a, b)
#else
#define TF_ASSERT(name, a, b) _TF_IGNORE::validate(a, b, name, __FILE__, __LINE__)
#endif


/**
 * @brief Convenient macro for timing some code execution.
 * @param the block of code to be timed.
 */
#define TF_TIME_IT(code) \
{ \
	std::chrono::high_resolution_clock::time_point to = std::chrono::high_resolution_clock::now(); \
	{ code ; } \
	std::chrono::high_resolution_clock::time_point tf = std::chrono::high_resolution_clock::now(); \
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(tf - to).count(); \
	double asSeconds = duration / 1000000; \
	std::cout << "Execution of test at file \'" << __FILE__ "\' at line \'" << __LINE__ << "\' took: " << duration << " micro seconds, or " << asSeconds << " seconds." << std::endl; \
}


#endif // TESTFRAMEWORK_H
