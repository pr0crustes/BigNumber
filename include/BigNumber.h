#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

#include <iostream>
#include <stdexcept>


//#define BIG_NUMBER_DEBUG   // Use a exclusive debug flag


/**
 * @brief charToInt function that converts a char to the int it represents.
 * @param c the char to be parsed as int.
 * @return the int contained in c. E.g. '0' returns 0.
 * Throws an exception if the char is not a number.
 */
static int charToInt(char& c) {
	switch (c) {  // Since values are only 0-9, this is way faster than atoi.
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		default:
			std::string message("Char at string is not a valid int. Received: ");
			message.push_back(c);
			throw std::invalid_argument(message);
	}
}


/**
 * @brief The BigNumber class represents a limitless number.
 * Can hold values way larger than 2 to 64.
 */
class BigNumber {

	public:

		/*
		 * Constructors.
		 * BigNumber has 0 as default value.
		 * Can be instantiated with the value of a string or long long.
		 */
		BigNumber(std::string string) {
			if (string.length() > 0) {
				if (string.at(0) == '-' || string.at(0) == '+') {
					this->m_positive = string.at(0) == '+';
					string = string.substr(1);  // remove the signal.
				}
				for (int i = string.size() - 1; i >= 0; i--) {
					this->m_values.push_back(charToInt(string[i]));
				}
			} else {
				this->m_values.push_back(0);
			}
		}

		BigNumber () : BigNumber("0") {}  // zero by default.

		BigNumber(long long value) : BigNumber(std::to_string(value)) {}


		/*
		 * Copy constructor.
		 */
		/**
		 * @brief operator = copy constructor. Copy the vector and the sign.
		 * @param number
		 * @return
		 */
		BigNumber& operator=(const BigNumber& number) {
			this->m_values = number.m_values;
			this->m_positive = number.m_positive;
			return *this;
		}


		/*
		 * Unary operators.
		 */
		/**
		 * @brief operator + This does NOT return the absolute value.
		 * @return the BigNumber itself.
		 */
		BigNumber operator+() const {
			return *this;
		}


		/**
		 * @brief operator - the same as multiplying by -1.
		 * @return returns the bignumber with reverted signal.
		 */
		BigNumber operator-() const {
			BigNumber number = *this;
			if (number != BigNumber(0)) {
				number.m_positive = !number.m_positive;
			}
			return number;
		}


		/*
		 * Binary operators.
		 */
		/**
		 * @brief operator + plus operator. Add one BigNumber to this.
		 * @param number the number to be added.
		 * @return the sum of both BigNumbers.
		 */
		BigNumber operator+(const BigNumber& number) const {
			if (this->m_positive && !number.m_positive) {
				return *this - number.absoluteValue();
			} else if (!this->m_positive && number.m_positive) {
				return -(number - this->absoluteValue());
			}

			if (number == BigNumber(0)) {
				return *this;
			}
			if (*this == BigNumber(0)) {
				return number;
			}
			// At this point, both signs are equal.
			BigNumber result = *this;  // larger is not a pointer, since it will hold the result.

			for (int i = 0; i < number.m_values.size(); i++) {
				int digit = number.m_values[i];
				if (i < result.m_values.size()) {
					result.m_values[i] += digit;
				} else {  // no digit in this position, add to the end of vector.
					result.m_values.push_back(digit);
				}

#ifdef BIG_NUMBER_DEBUG
				if (result.m_values[i] > 19) {
					std::string message("Invalid value in m_value: ");
					message.push_back(result.m_values[i]);
					throw std::invalid_argument(message);
				}
#endif
				result.carryOver();
			}
			result.afterOperation();
			return result;
		}


		/**
		 * @brief operator - minus operator. Subtracts one BigNumber from this.
		 * @param number the BigNumber to be subtracted.
		 * @return the result of the subtraction
		 */
		BigNumber operator-(const BigNumber& number) const {
			if (this->m_positive && !number.m_positive) {
				return *this + number.absoluteValue();
			} else if (!this->m_positive && number.m_positive) {
				return -(number + this->absoluteValue());
			}

			if (number == BigNumber(0)) {
				return *this;
			}
			if (*this == BigNumber(0)) {
				return number;
			}

			// At this point, both signs are equal.
			// To subtract one number from other, it is important to know the larger and the smaller one,
			// since when subtracting 20 from 2 what you do is 20 - 2  and then reverse the signal.
			BigNumber result;  // result is not a pointer, since it will hold the result.
			const BigNumber* smaller;  // pointer to the smaller number. Read only.
			if (this->m_values.size() >= number.m_values.size()) {
				result = *this;
				smaller = &number;
			} else {
				result = number;
				smaller = this;
			}

			for (int i = 0; i < smaller->m_values.size(); i++) {
				int dif = result.m_values[i] - smaller->m_values[i];
				if (dif < 0) {
					for (int j = i + 1; j < result.m_values.size(); j++) {
						if (result.m_values[j] == 0) {
							result.m_values[j] = 9;
						} else {
							dif += 10;
							result.m_values[j]--;
							break;
						}
					}
				}

				result.m_values[i] = dif;
			}
			result.m_positive = *this >= number;  // If this is less than the number being subtracted, result will be negative.
			result.afterOperation();
			return result;
		}


		/**
		 * @brief operator * the multiplier operator.
		 * @param number the number to be multiplied by.
		 * @return the result of the multiplication.
		 */
		BigNumber operator*(const BigNumber& number) const {
			BigNumber product;
			for (int i = 0; i < this->m_values.size(); i++) {
				BigNumber partialProduct;
				for (int j = 0; j < this->m_values[i]; j++) {  // repeate `i` times.
					partialProduct += number.absoluteValue();
				}
				product += partialProduct.times10(i);
			}
			product.m_positive = this->m_positive == number.m_positive;
			product.afterOperation();
			return product;
		}


		/**
		 * @brief operator / divide one number by other.
		 * Keep in mind that the return is a BigNumber, so 10 / 4 is 2, not 2.5.
		 * If you want the reaminder of a division, see the `%` operator.
		 * @param number number to divide by.
		 * @return result of division.
		 */
		BigNumber operator/(const BigNumber& number) const {
			if (number == BigNumber(0)) {
				throw new std::invalid_argument("Division / Module by 0 is undefined.");
			}
			if (number > *this) {
				return BigNumber(0);
			}
			if (number == *this) {
				return BigNumber(1);
			}

			BigNumber absoluteThis = this->absoluteValue();
			BigNumber absoluteNumber = number.absoluteValue();

			BigNumber quotient;
			while (absoluteThis >= absoluteNumber) {
				quotient++;
				absoluteThis -= absoluteNumber;
			}
			quotient.m_positive = this->m_positive == number.m_positive;
			quotient.afterOperation();
			return quotient;
		}

		/**
		 * @brief operator % module operator. This function does not work with negative numbers.
		 * @param number the divisor number.
		 * @return the result of the module operator.
		 */
		BigNumber operator%(const BigNumber& number) const {
			if (!this->m_positive || !number.m_positive) {
				throw new std::invalid_argument("Operator % cannot be used with negative numbers. Perhaps you forgot to call `absoluteValue()`?");
			}
			// Use division to calculate module. Since the division is rounded, it works.
			BigNumber result = *this - (number * (*this / number));
			result.afterOperation();
			return result;
		}

		/*
		 * Assigment operators.
		 */
		BigNumber& operator+=(const BigNumber& number) {
			*this = *this + number;
			return *this;
		}


		BigNumber& operator-=(const BigNumber& number) {
			*this = *this - number;
			return *this;
		}


		BigNumber& operator*=(const BigNumber& number) {
			*this = *this * number;
			return *this;
		}


		BigNumber& operator/=(const BigNumber& number) {
			*this = *this / number;
			return *this;
		}


		BigNumber& operator%=(const BigNumber& number) {
			*this = *this % number;
			return *this;
		}

		/*
		 * Increment / Decrement operators.
		 */
		BigNumber& operator++() {
			*this += 1;
			return *this;
		}

		BigNumber& operator--() {
			*this -= 1;
			return *this;
		}

		BigNumber operator++(int) {
			BigNumber copy = *this;
			*this += 1;
			return copy;
		}

		BigNumber operator--(int) {
			BigNumber copy = *this;
			*this -= 1;
			return copy;
		}

		/*
		 * Relational operators
		 */
		bool operator<(const BigNumber& number) const {
			if (this->m_positive != number.m_positive) {  // oposite signs.
				return !this->m_positive;
			}
			if (this->m_values.size() != number.m_values.size()) {  // not the same lenght.
				return this->m_values.size() < number.m_values.size();
			}
			if (this->m_positive) {  // both positives.
				return this->asString() < number.asString();  // compare string representation.
			}
			return -(*this) > -number;  // both negatives.
		}


		bool operator>(const BigNumber& number) const {
			return *this >= number && !(*this == number);
		}


		bool operator<=(const BigNumber& number) const {
			return *this == number || *this < number;
		}


		bool operator>=(const BigNumber& number) const {
			return !(*this < number);
		}


		bool operator==(const BigNumber& number) const {
			return this->m_positive == number.m_positive && this->m_values == number.m_values;
		}


		bool operator!=(const BigNumber& number) const {
			return !(*this == number);
		}


		/*
		 * >> and << operators. Just for convenience.
		 */
		friend std::ostream& operator<<(std::ostream& stream, BigNumber const& number) {
			stream << number.asString();
			return stream;
		}


		friend std::istream& operator>>(std::istream& istream, BigNumber& number) {
			std::string in;
			istream >> in;
			number = BigNumber(in);
			return istream;
		}

		/**
		 * @brief asString methot that creates a string representation of a BigNumber.
		 * @return a string representing the BigNumber.
		 */
		std::string asString() const {
			std::stringstream ss;
			if (!this->m_positive) {
				ss << '-';
			}
			for (int i = this->m_values.size() - 1; i >= 0; i--) {  // reverse order, so that vector {1, 2, 3} prints 321 and not 123.
#ifdef BIG_NUMBER_DEBUG
				if (this->m_values[i] < 0 || this->m_values[i] > 9) {
					throw std::invalid_argument("m_values containing invalid value. Aborting...");
				}
#endif
				ss << this->m_values[i];
			}
			return ss.str();
		}

		/**
		 * @brief absoluteValue gets the absolute value of a BigNumber,
		 * @return a BigNumber copy, but positive, the absolute value.
		 */
		BigNumber absoluteValue() const {
			BigNumber temp = *this;
			temp.m_positive = true;
			return temp;
		}

		/**
		 * @brief times10 method that multiplies the number by 10, n times. Made to be fast.
		 * @param times how many times it shoud be multiplied by 10. Default is 1.
		 * @return the number times 10 n times.
		 */
		BigNumber times10(int times = 1) {
			BigNumber temp = *this;
			for (int i = 0; i < times; i++) {
				temp.m_values.insert(temp.m_values.begin(), 0);
			}
			temp.afterOperation();
			return temp;
		}


	private:

		bool m_positive = true;  // positive by default.
		std::vector<int> m_values;  // vector that will hold the digts. vector {1, 2, 3} means number 321.

		/**
		 * @brief removeLeftZeros removes all the zeroes to the left of a number,
		 * so 0008 becomes 8 and 000 becomes 0.
		 */
		void removeLeftZeros() {
			for (int i = this->m_values.size() - 1; i >= 1; i--) {  // until 1, not 0 so that 0 is represented as {0} and not {}
				if (this->m_values[i] == 0) {
					this->m_values.pop_back();
				} else {
					break;
				}
			}
		}

		/**
		 * @brief afterOperation just a method that updates internal stuff,
		 * should be called after most internal value update operations.
		 */
		void afterOperation() {
			this->removeLeftZeros();
			if (this->absoluteValue() == BigNumber(0)) {  // prevents -0.
				this->m_positive = true;
			}
		}


		/**
		 * @brief carryOver method that carry over digits in addition, making sure no number in m_vector is bigger than 9.
		 */
		void carryOver() {
			for (int i = 0; i < this->m_values.size(); i++) {
				if (this->m_values[i] > 9) {
					this->m_values[i] %= 10;
					if (i + 1 < this->m_values.size()) {
						this->m_values[i+1]++;
					} else {
						this->m_values.push_back(1);
					}
					this->carryOver();
					break;
				}
			}
		}

};


#endif // BIGNUMBER_H
