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


namespace _TF_IGNORE {  // Namespace for hidding stuff.
	bool PRINT_ONLY_FAIL = false;  // If true, only erros should print.
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
	template<typename T>
	void validate(T a, T b, std::string name, const char* file, int line) {
		_TF_IGNORE::GLOBAL_TEST_COUNT++;
		if (a == b) {
			if (!_TF_IGNORE::PRINT_ONLY_FAIL) {
				_TF_IGNORE::addMessage(name, file, line);
				_TF_IGNORE::GLOBAL_ASSERTIONS_SS << "Passed\n";
			}
		} else {
			_TF_IGNORE::GLOBAL_ERROR_COUNT++;
			_TF_IGNORE::addMessage(name, file, line);
			_TF_IGNORE::GLOBAL_ASSERTIONS_SS << "Failed: Expected \'" << a << "\' received \'" << b << "\'\n";
		}
	}

}


namespace TF {  // TF = TestFramework

	/**
	 * @brief setOnlyFail sets if should only print errors.
	 * @param value a bool, if set to true, only errors will be printed.
	 */
	void setOnlyFail(bool value) {
		_TF_IGNORE::PRINT_ONLY_FAIL = value;
	}

	/**
	 * @brief printResult function that does the printing of the results.
	 * @return 0 if all tests passed, 1 otherwise.
	 */
	int printResult() {
		std::cout << _TF_IGNORE::GLOBAL_ASSERTIONS_SS.str() << std::endl;
		if (_TF_IGNORE::GLOBAL_ERROR_COUNT > 0) {
			std::cout << "\n==> " << _TF_IGNORE::GLOBAL_ERROR_COUNT << " of " << _TF_IGNORE::GLOBAL_TEST_COUNT << " tests failed.\n";
			return 1;
		} else {
			std::cout << "\n==> All of " << _TF_IGNORE::GLOBAL_TEST_COUNT << " tests passed.\n";
			return 0;
		}
	}

}


/**
 * @brief TF_ASSERT macro that does the assert.
 * This will call validate under the hood, passing FILE and LINE as arguments.
 * Since we want to know the file and line, this need to be a macro.
 * @param name the assertion name.
 * @param a the thing to be checked.
 * @param b the thing that a should be equal to.
 */
#define TF_ASSERT(name, a, b) _TF_IGNORE::validate(a, b, name, __FILE__, __LINE__)


#endif // TESTFRAMEWORK_H
