/**
 * BigNumber - a BigInt implementation in C++.
 * This file is licensed under the MIT license.
 * Do not remove this comment.
 * 2018 @ pr0crustes
 */
#ifndef BIGNUMBER_H
#define BIGNUMBER_H


#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <random>
#include <algorithm>
#include <iostream>
#include <stdexcept>


/**
  * Use an exclusive Debug Flag.
  * When defined, the lib will run slower,
  * but will performe multiple checks to make everything is fine.
  */
//#define BIG_NUMBER_DEBUG   // Use a exclusive debug flag


/**
 * @brief charToInt function that converts a char to the int it represents.
 * @param c the char to be parsed as int.
 * @return the int contained in c. E.g. '0' returns 0.
 * Throws an exception if the char is not a number.
 */
static int charToInt(char c) noexcept(false) {
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
			std::string message("[BigNumber] {Digit Parsing} ->  Char at string is not a valid int. Received: ");
			message.push_back(c);
			throw std::invalid_argument(message);
	}
}



namespace pr0crustes {

/**
 * @brief The BigNumber class represents a limitless number.
 * Can hold and operate values way larger than 2 to 64.
 */
class BigNumber {

	public:

		/*
		 * Constructors.
		 * BigNumber has 0 as default value.
		 * Can be instantiated with the value of a string or long long.
		 */
		BigNumber(std::string string) noexcept(false) {
			if (string.length() > 0) {
				if (string.at(0) == '-' || string.at(0) == '+') {
					this->m_positive = string.at(0) == '+';
					string = string.substr(1);  // remove the signal.
				}
				this->m_values.reserve(string.length());
				for (int i = string.size() - 1; i >= 0; i--) {    // from end to start, so that string 321 is represented as vector {1, 2, 3}.
					this->m_values.push_back(charToInt(string[i]));
				}
			} else {
				this->m_values.push_back(0);  // init with 0 by default.
			}
			this->removeLeftZeros();  // call removeLeftZeros, and not afterOperation since the object has not been completelly initialized.
		}

		BigNumber() : BigNumber("0") {}  // zero by default.

		BigNumber(long long value) : BigNumber(std::to_string(value)) {}  // just call the string constructor since its easier to parse.


		/**
		 * @brief fromBinary instantiates a BigNumber from a binary string representation.
		 * @param binary a binary like string. No checking is done to see if it is valid, any char other than 0 and 1 can lead to undefined behavior.
		 * @param isSigned if true, as default, the first bit will be interpreted as the signal, like any signed integers.
		 * @return a BigNumber with the value of the binary string.
		 */
		static BigNumber fromBinary(std::string binary, bool isSigned = true) noexcept(true) {
			BigNumber number(0);
			if (isSigned) {
				number.m_positive = binary.at(0) == '0';
				binary = binary.substr(1);
			}

			BigNumber powerTwo(1);
			for (int i = binary.length() - 1; i >= 0; i--) {
				if (binary.at(i) == '1') {
					number += powerTwo;
				}
				powerTwo *= 2;
			}
			return number;
		}


		/**
		 * @brief static method that generate random BigNumbers.
		 * THIS IS A PSEUDO-RANDOM FUNCTION. DO NOT RELY IN IT BEING COMPLETELY RANDOM.
		 * @param size the desired BigNumber size.
		 * @return a random BigNumber with the desired number of digits.
		 */
		static BigNumber randomBigNumber(int lenght) noexcept(false) {
			if (lenght <= 0) {
				throw std::invalid_argument("[BigNumber] {Random BigNumber} ->  RandomBigNumber size must be larger or equal to 1.");
			}

			std::stringstream ss;
			std::random_device rand_gen;

			while (ss.tellp() < lenght) {  // add random digits until its larger than the desired lenght.
				ss << rand_gen();
			}

			std::string randomDigits = ss.str().substr(0, lenght);  // cut the excess.
			return BigNumber(randomDigits);
		}


		/**
		 * @brief randomBigNumberInRange generate a random BigNumber in desired range, excluding higher.
		 * This method may be a little slow compared to the others, had'nt any better idea.
		 * Does not work with negative numbers.
		 * THIS IS A PSEUDO-RANDOM FUNCTION. DO NOT RELY IN IT BEING COMPLETELY RANDOM.
		 * @param lower the lower bound, inclusive.
		 * @param higher the upper bound, exclusive.
		 * @return a random BigNumber in range.
		 */
		static BigNumber randomBigNumberInRange(const BigNumber& low, const BigNumber& hight) noexcept(false) {
			if (low >= hight) {
				throw std::invalid_argument("[BigNumber] {Random BigNumber In Range} ->  Lower bound cannot be bigger or equal to higher bound.");
			}
			if (!low.isPositive() || !hight.isPositive()) {
				throw std::invalid_argument("[BigNumber] {Random BigNumber In Range} ->  Only works with positive BigNumbers.");
			}

			BigNumber diff = hight - low;

			BigNumber randomDiffRange = BigNumber::randomBigNumber(diff.lenght() + 1);  // + 1 makes sure the generated value is greater then diff.
			BigNumber modR = randomDiffRange % diff;

			BigNumber randomN = low + modR;

			return randomN;
		}


		/*
		 * Copy constructor.
		 */
		/**
		 * @brief operator = copy constructor. Copy the vector and the sign.
		 * @param number
		 * @return
		 */
		BigNumber& operator=(const BigNumber& number) noexcept(true) {
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
		BigNumber operator+() const noexcept(true) {
			return *this;
		}


		/**
		 * @brief operator - the same as multiplying by -1.
		 * @return returns the bignumber with reverted signal.
		 */
		BigNumber operator-() const noexcept(true) {
			BigNumber number = *this;
			if (!number.isZero()) {
				number.m_positive = !number.isPositive();
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
		BigNumber operator+(const BigNumber& number) const noexcept(true) {
			if (this->isPositive() && !number.isPositive()) {
				return *this - number.absoluteValue();
			} else if (!this->isPositive() && number.isPositive()) {
				return -(number - this->absoluteValue());
			}

			if (number.isZero()) {
				return *this;
			}
			if (this->isZero()) {
				return number;
			}
			// At this point, both signs are equal.
			BigNumber result = *this;  // not a pointer, since it will hold the result.

			for (int i = 0; i < number.lenght(); i++) {  // the numbers will be iterated in normal order, units to hundreds.
				int digit = number.m_values[i];
				if (i < result.lenght()) {  // if there is a digit at the same position in the other number.
					result.m_values[i] += digit;  // sum to it.
				} else {
					result.m_values.push_back(digit);  // no digit in this position, add to the end of vector.
				}
			}
			result.doCarryOver();
			result.afterOperation();
			return result;
		}


		/**
		 * @brief operator - minus operator. Subtracts one BigNumber from this.
		 * @param number the BigNumber to be subtracted.
		 * @return the result of the subtraction
		 */
		BigNumber operator-(const BigNumber& number) const noexcept(true) {
			if (this->isPositive() && !number.isPositive()) {
				return *this + number.absoluteValue();
			} else if (!this->isPositive() && number.isPositive()) {
				return -(number + this->absoluteValue());
			}

			if (number.isZero()) {
				return *this;
			}
			if (this->isZero()) {
				return number;
			}

			// At this point, both signs are equal.
			// To subtract one number from other, it is important to know the larger and the smaller one,
			// since when subtracting 20 from 2 what you do is 20 - 2  and then reverse the signal.
			BigNumber result;  // result is not a pointer, since it will hold the result.
			const BigNumber* smaller;  // pointer to the smaller number. Read only.
			if (this->lenght() >= number.lenght()) {
				result = *this;
				smaller = &number;
			} else {
				result = number;
				smaller = this;
			}

			for (int i = 0; i < smaller->lenght(); i++) {   // iterate in normal order, units to hundreds.
				int dif = result.m_values[i] - smaller->m_values[i];
				if (dif < 0) {  // subtraction cannot be done without borrowing.
					// search for a number to borrow.
					for (int j = i + 1; j < result.lenght(); j++) {
						if (result.m_values[j] == 0) {  // replace 0's with 9 until finding a non-zero number.
							result.m_values[j] = 9;
						} else {  // subtract one from it and add 10 to the dif.
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
		 * Uses Karatsuba Algorithm, see https://en.wikipedia.org/wiki/Karatsuba_algorithm for info.
		 * @param number the number to be multiplied by.
		 * @return the result of the multiplication.
		 */
		BigNumber operator*(const BigNumber& number) const noexcept(true) {
			if (this->isZero() || number.isZero()) {
				return BigNumber(0);
			}
			if (this->isOne()) {
				return number;
			}
			if(number.isOne()) {
				return *this;
			}

			if (this->lenght() < 10 && number.lenght() < 10) {  // result can fit in a long long.
				return BigNumber(this->asLongLong() * number.asLongLong());
			}

			int maxLenght = std::max(this->lenght(), number.lenght());
			int splitPoint = maxLenght / 2;  // round down.

			// Apply the Karatsuba algorithm, you should read about it before reading this code.
			std::pair<BigNumber, BigNumber> splitThis = this->splitAt(splitPoint);
			std::pair<BigNumber, BigNumber> splitNumber = number.splitAt(splitPoint);

			BigNumber secondProduct = splitThis.second * splitNumber.second;
			BigNumber firstProduct = splitThis.first * splitNumber.first;
			BigNumber sumProduct = (splitThis.second + splitThis.first) * (splitNumber.second + splitNumber.first);

			BigNumber firstPadded = firstProduct.times10(splitPoint * 2);
			BigNumber deltaPadded = (sumProduct - firstProduct - secondProduct).times10(splitPoint);

			return firstPadded + deltaPadded + secondProduct;
		}


		/**
		 * @brief operator / divide one number by other.
		 * Keep in mind that the return is a BigNumber, so 10 / 4 is 2, not 2.5.
		 * If you want the reaminder of a division, see the `%` operator.
		 * @param number number to divide by.
		 * @return result of division.
		 * Throws in case of division by 0.
		 */
		BigNumber operator/(const BigNumber& number) const noexcept(false) {
			return this->divide(number).first;
		}


		/**
		 * @brief operator % module operator. This function does not work with negative numbers.
		 * @param number the divisor number.
		 * @return the result of the module operator.
		 * Throws in case of module by 0.
		 */
		BigNumber operator%(const BigNumber& number) const noexcept(false) {
			return this->divide(number).second;
		}


		/**
		 * @brief pow power method. Solves with Exponentiation by Squaring.
		 * Throws an exception in case of 0 to the power of 0 and in case of any number to a negative one.
		 * This function is slow with big numbers. If you want to apply a mod after, use modPow, since it is faster.
		 * See https://en.wikipedia.org/wiki/Exponentiation_by_squaring
		 * @param number the desired power.
		 * @return THIS to the power of NUMBER.
		 */
		BigNumber pow(BigNumber number) const noexcept(false) {
			if (this->isZero() && number.isZero()) {
				throw std::invalid_argument("[BigNumber] {Pow} ->  Zero to the power of Zero is undefined.");
			}
			if (!number.isPositive()) {
				throw std::invalid_argument("[BigNumber] {Pow} ->  Power cannot be negative.");
			}
			if (this->isZero()) {
				return BigNumber(0);
			}
			if (number.isZero()) {
				return BigNumber(1);
			}
			if (number.isOdd()) {
				return *this * (*this * *this).pow((number - 1) / 2);
			} else {
				return (*this * *this).pow(number / 2);
			}
		}


		/**
		 * @brief modPow fast way of doing apower operation followed by module.
		 * See https://en.wikipedia.org/wiki/Modular_exponentiation#Memory-efficient_method
		 * @param power the power wanted.
		 * @param mod the module wanted.
		 * @return this to the power power module mod.
		 */
		BigNumber modPow(const BigNumber& power, const BigNumber& mod) const noexcept(false) {
			if (mod.isZero()) {
				throw std::invalid_argument("[BigNumber] {Mod Pow} ->  Module by Zero is undefined.");
			}
			if (this->isZero() && power.isZero()) {
				throw std::invalid_argument("[BigNumber] {Mod Pow} ->  Zero to the power of Zero is undefined.");
			}
			if (!power.isPositive()) {
				throw std::invalid_argument("[BigNumber] {Mod Pow} ->  Power cannot be negative.");
			}
			if (this->isZero()) {
				return BigNumber(0);
			}
			BigNumber result(1);
			for (BigNumber i = 0; i < power; i++) {  // repeat power times.
				result = (*this * result) % mod;
			}
			return result;
		}


		/*
		 * Assigment operators.
		 */
		BigNumber& operator+=(const BigNumber& number) noexcept(true) {
			*this = *this + number;
			return *this;
		}


		BigNumber& operator-=(const BigNumber& number) noexcept(true) {
			*this = *this - number;
			return *this;
		}


		BigNumber& operator*=(const BigNumber& number) noexcept(true) {
			*this = *this * number;
			return *this;
		}


		BigNumber& operator/=(const BigNumber& number) noexcept(false) {
			*this = *this / number;
			return *this;
		}


		BigNumber& operator%=(const BigNumber& number) noexcept(false) {
			*this = *this % number;
			return *this;
		}


		/*
		 * Increment / Decrement operators.
		 */
		BigNumber& operator++() noexcept(true) {
			*this += 1;
			return *this;
		}


		BigNumber& operator--() noexcept(true) {
			*this -= 1;
			return *this;
		}


		BigNumber operator++(int) noexcept(true) {
			BigNumber copy = *this;
			*this += 1;
			return copy;
		}


		BigNumber operator--(int) noexcept(true) {
			BigNumber copy = *this;
			*this -= 1;
			return copy;
		}


		/*
		 * Relational operators
		 */
		bool operator<(const BigNumber& number) const noexcept(true) {
			if (this->m_positive != number.m_positive) {  // oposite signs.
				return !this->m_positive;
			}
			if (this->lenght() != number.lenght()) {  // not the same lenght.
				return this->lenght() < number.lenght();
			}
			// at this point, both are the same lenght.
			if (this->m_positive) {  // both positives.
				return this->asString() < number.asString();  // compare string representation.
			}
			return -(*this) > -number;  // both negatives.
		}


		bool operator>(const BigNumber& number) const noexcept(true) {
			return *this >= number && !(*this == number);
		}


		bool operator<=(const BigNumber& number) const noexcept(true) {
			return *this == number || *this < number;
		}


		bool operator>=(const BigNumber& number) const noexcept(true) {
			return !(*this < number);
		}


		bool operator==(const BigNumber& number) const noexcept(true) {
			return this->m_positive == number.m_positive && this->m_values == number.m_values;
		}


		bool operator!=(const BigNumber& number) const noexcept(true) {
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
		std::string asString() const noexcept(true) {
			std::stringstream ss;
			if (!this->isPositive()) {
				ss << '-';
			}
			for (int i = this->lenght() - 1; i >= 0; i--) {  // reverse order, so that vector {1, 2, 3} prints 321 and not 123.
#ifdef BIG_NUMBER_DEBUG
				if (this->m_values[i] < 0 || this->m_values[i] > 9) {
					std::cerr << "[BigNumber] {As String} ->  m_values containing invalid value: " << this->m_values[i] << ". Aborting..."<< std::endl;
					exit(1);
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
		BigNumber absoluteValue() const noexcept(true) {
			BigNumber temp = *this;
			temp.m_positive = true;
			return temp;
		}


		/**
		 * @brief times10 method that multiplies the number by 10, n times. Made to be fast.
		 * @param times how many times it shoud be multiplied by 10. Default is 1.
		 * @return the number times 10 n times.
		 */
		BigNumber times10(int times = 1) const noexcept(true) {
			BigNumber temp = *this;
			for (int i = 0; i < times; i++) {
				temp.m_values.insert(temp.m_values.begin(), 0);
			}
			temp.afterOperation();
			return temp;
		}


		/**
		 * @brief divide10 method that divides the number by 10, n times. Made to be fast.
		 * @param times how many times it shoud be divided by 10. Default is 1.
		 * @return the number divided by 10 n times.
		 */
		BigNumber divide10(int times = 1) const noexcept(true) {
			if (times >= this->lenght()) {
				return BigNumber(0);
			}
			BigNumber divided = *this;
			for (int i = 0; i < times; i++) {
				divided.m_values.erase(divided.m_values.begin());
			}
			return divided;
		}


		/**
		 * @brief asBinary returns a std::string representation of the BigNumber as binary.
		 * The lenght of the string will always be the smallest necessary to fit the representation, plus the signed bit.
		 * The representation is signed-like, so the first char is 1 if the number is negative, 0 if positive.
		 * @return a std::string representation of the BigNumber as binary.
		 */
		std::string asBinary() const noexcept(true) {
			std::stringstream ss;

			BigNumber copy = this->absoluteValue();

			while (copy > 0) {
				ss << (copy.isOdd() ? '1' : '0');
				copy /= 2;
			}

			ss << (this->isPositive() ? '0' : '1');  // Big for signed.

			std::string asString = ss.str();
			std::reverse(asString.begin(), asString.end());
			return asString;
		}


		/**
		 * @brief splitAt splits a BigNumber at a desired position.
		 * @param splitPos the position to be split at.
		 * Keep in mind that this position is from right to left, so spliting the number 123456 at pos 1 will result in 12345 and 6.
		 * If the param is not in range [0, this.lenght], it will be capped to it.
		 * @return a pair of the result BigNumbers.
		 */
		std::pair<BigNumber, BigNumber> splitAt(long long splitPos) const noexcept(true) {
			splitPos = std::min(std::max(splitPos, (long long) 0), (long long) this->lenght());  // cap values to [0, lengh]. I miss C++ 17 clamp.

			std::vector<int> firstHalf;
			firstHalf.reserve(splitPos);

			std::vector<int> secondHalf;
			secondHalf.reserve(this->lenght() - splitPos);

			for (size_t i = 0; i < this->lenght(); i++) {
				int digit = this->m_values[i];
				if (i > splitPos - 1) {
					firstHalf.push_back(digit);
				} else {
					secondHalf.push_back(digit);
				}
			}

			return std::make_pair(BigNumber(firstHalf), BigNumber(secondHalf));
		}


		/**
		 * @brief fitsInLongLong method that calculates if a number fits in a long long type.
		 * @return if number fits in long long type.
		 * Uses the lenght to calculate, since long long max is 9223372036854775807.
		 */
		bool fitsInLongLong() const noexcept(true) {
			return this->lenght() < 19;
		}


		/**
		 * @brief asLongLong returns a long long representation of this BigNumber object.
		 * Throws exeption of type std::out_of_range if the number does not fit.
		 * @return this BigNumber as a long long, if possible.
		 */
		long long asLongLong() const noexcept(false) {
#ifdef BIG_NUMBER_DEBUG
			if (!this->fitsInLongLong()) {
				std::cerr << "[BigNumber] {As Long Long} Invalid long long:" << *this << std::endl;
				exit(1);
			}
#endif
			return std::stoll(this->asString());
		}


		/**
		 * @brief lenght method to get the lenght of given number, counting the digits.
		 * @return the lenght of this BigNumber.
		 */
		size_t lenght() const noexcept(true) {
			return this->m_values.size();
		}


		/**
		 * @brief isOdd simple method to se if a BigNumber is odd or not.
		 * @return if the number is odd.
		 */
		bool isOdd() const noexcept(true) {
			return this->m_values[0] & 1;
		}


		/**
		 * @brief isEven just a negative of isOdd.
		 * @return if a number is even. Zero is considered even.
		 */
		bool isEven() const noexcept(true) {
			return !this->isOdd();
		}


		/**
		 * @brief isZero methot that tests if a number is zero, faster than Number == BigNumber(0).
		 * @return if the object is 0.
		 */
		bool isZero() const noexcept(true) {
			return this->lenght() == 1 && this->m_values[0] == 0;
		}


		/**
		 * @brief isOne method that tests if a number is one, faster than creating an object.
		 * @return is this object is 1.
		 */
		bool isOne() const noexcept(true) {
			return this->m_positive && this->lenght() == 1 && this->m_values[0] == 1;
		}


		/**
		 * @brief isPositive methot that returns if this number is positive or not.
		 * @return if this object has positive value or not.
		 */
		bool isPositive() const noexcept(true) {
			return this->m_positive;
		}


	private:

		bool m_positive = true;  // positive by default.
		std::vector<int> m_values;  // vector that will hold the digts. vector {1, 2, 3} means number 321.


		/**
		 * @brief removeLeftZeros removes all the zeroes to the left of a number,
		 * so 0008 becomes 8 and 000 becomes 0.
		 */
		void removeLeftZeros() noexcept(true) {
			for (int i = this->lenght() - 1; i >= 1; i--) {  // until 1, not 0 so that 0 is represented as {0} and not {}
				if (this->m_values[i] == 0) {
					this->m_values.pop_back();  // pops all zeroes to the left of the number.
				} else {
					break;
				}
			}
		}


		/**
		 * @brief doCarryOver utility method for addition, that does the carryover.
		 * @param start the point to start the parsing, used to recall the function recursively.
		 */
		void doCarryOver(int start = 0) noexcept(true) {
			for (int i = start; i < this->lenght(); i++) {
				if (this->m_values[i] > 9) {
					this->m_values[i] -= 10;
					if (i + 1 < this->lenght()) {
						this->m_values[i + 1]++;
					} else {
						this->m_values.push_back(1);
						return doCarryOver(i);
					}
				}
			}
		}


		/**
		 * @brief afterOperation just a method that updates internal stuff,
		 * should be called after most internal value update operations.
		 */
		void afterOperation() noexcept(true) {
			this->removeLeftZeros();
			if (this->isZero()) {  // prevents -0.
				this->m_positive = true;
			}
#ifdef BIG_NUMBER_DEBUG
			for (int i = 0; i < this->lenght(); i++) {
				if (this->m_values[i] < 0 || this->m_values[i] > 9) {
					std::cerr << "[BigNumber] {After Operation} Invalid value in vector: " << this->m_values[i] << std::endl;
					exit(1);
				}
			}
#endif
		}


		/**
		 * @brief divide method that contains the division logid.
		 * @param number to divide by.
		 * @return a pair, the first one is the division quocient, the second the division rest.
		 * The division rest is ALWAYS positive, since ISO14882:2011 says that the sign of the remainder is implementation-defined.
		 * Throws in case of division | module by 0.
		 */
		std::pair<BigNumber, BigNumber> divide(const BigNumber& number) const noexcept(false) {
			if (number.isZero()) {
				throw std::invalid_argument("[BigNumber] {Divide} ->  Division | Module by 0 is undefined.");
			}
			if (number.isOne()) {
				return std::make_pair(*this, BigNumber(0));
			}
			if (number == *this) {
				return std::make_pair(BigNumber(1), BigNumber(0));
			}
			if (number > *this) {
				return std::make_pair(BigNumber(0), *this);
			}
			// At this point, we can assume *this is larger than number.

			if (this->fitsInLongLong() && number.fitsInLongLong()) {  // this makes for huge optization.
				long long llThis = this->asLongLong();
				long long llNumber = number.asLongLong();
				return std::make_pair(BigNumber(llThis / llNumber), BigNumber(abs(llThis % llNumber)));
			}

			BigNumber rest = this->absoluteValue();  // this number will be modified.
			const BigNumber absoluteNumber = number.absoluteValue();

			BigNumber quotient;

			// Iterate lenghtDifference times, decreasing.
			int lenghDifference = rest.lenght() - absoluteNumber.lenght();
			while (lenghDifference-- >= 0) {
				// The number that it will try to subtract will be the absoluteNumber passed times 10 to the power of the current lenghDiff.
				// This will make for HUGE permorface, since instead of subtracting 2 from 200 100 times it will subtract 200 from 200 once.
				BigNumber toSubtract = absoluteNumber.times10(lenghDifference);
				while (rest >= toSubtract) {  // if we can subtract it.
					quotient += BigNumber(1).times10(lenghDifference);  // increase the quotient by the correct number.
					rest -= toSubtract;  // subtract the numbers.
				}
			}
			quotient.m_positive = this->m_positive == number.m_positive;  // Division signal rule.
			quotient.afterOperation();
			rest.afterOperation();
			return std::make_pair(quotient, rest);
		}


		/**
		 * @brief BigNumber this is a private constructor just to copy the vector.
		 * No checking is done to see if the vector is valid or not.
		 * An empty vector will result in the object being init with 0.
		 * @param vector the object m_values.
		 * @param reversed if true, the vector will be read in the reverse order.
		 */
		BigNumber(const std::vector<int> &vector, bool reversed=false) noexcept(true) {
			if (vector.size() > 0) {
#ifdef BIG_NUMBER_DEBUG
				for (int i = 0; i < vector.size(); i++) {
					if (vector[i] < 0 || vector[i] > 9) {
						std::cerr << "[BigNumber] {Vector Constructor} Invalid value in vector: " << vector[i] << std::endl;
						exit(1);
					}
				}
#endif

				this->m_values = vector;
				if (reversed) {
					std::reverse(this->m_values.begin(), this->m_values.end());
				}
			} else {
				this->m_values.push_back(0);
			}
			this->afterOperation();
		}

};

}  // Closing namespace pr0crustes.


#endif // BIGNUMBER_H
