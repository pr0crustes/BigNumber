//#define TF_IGNORE_TESTS
#define TF_PRINT_ONLY_FAIL

#include "TestFramework.h"

#include "../include/BigNumber.h"


using pr0crustes::BigNumber;


void constructor_test() {
	TF_ASSERT("Constructor 1",
			  BigNumber("100"),
			  BigNumber(100));

	TF_ASSERT("Constructor 2",
			  BigNumber(),
			  BigNumber(0));

	TF_ASSERT("Constructor 3",
			  BigNumber(),
			  BigNumber("0"));

	TF_ASSERT("Constructor 4",
			  BigNumber(),
			  BigNumber(""));
}


void sum_test() {
	TF_ASSERT("Sum 1",
			  BigNumber(10) + BigNumber(90),
			  BigNumber(100));

	TF_ASSERT("Sum 2",
			  BigNumber(22222) + BigNumber(33333),
			  BigNumber(55555));

	TF_ASSERT("Sum 3",
			  BigNumber(100) + BigNumber(-3),
			  BigNumber(97));

	TF_ASSERT("Sum 4",
			  BigNumber(0) + BigNumber(0),
			  BigNumber(0));

	TF_ASSERT("Sum 5",
			  BigNumber(0) + BigNumber(11),
			  BigNumber(11));

	TF_ASSERT("Sum 6",
			  BigNumber(33) + BigNumber(0),
			  BigNumber(33));

	TF_ASSERT("Sum 7",
			  BigNumber(2) + BigNumber(20),
			  BigNumber(22));

	TF_ASSERT("Sum 8",
			  BigNumber(20) + BigNumber(2),
			  BigNumber(22));

	TF_ASSERT("Sum 9",
			  BigNumber(19) + BigNumber(1),
			  BigNumber(20));

	TF_ASSERT("Sum 10",
			  BigNumber(19) + 1,
			  BigNumber(20));

	TF_ASSERT("Sum 11",
			  BigNumber(5) + 2,
			  BigNumber(7));

	TF_ASSERT("Sum 12",
			  BigNumber(1111111) + BigNumber(1999999),
			  BigNumber(3111110));
}


void subtraction_test() {
	TF_ASSERT("Sub 1",
			  BigNumber(100) - BigNumber(50),
			  BigNumber(50));

	TF_ASSERT("Sub 2",
			  BigNumber(10) - BigNumber(-10),
			  BigNumber(20));

	TF_ASSERT("Sub 3",
			  BigNumber(-10) - BigNumber(-10),
			  BigNumber(0));

	TF_ASSERT("Sub 4",
			  BigNumber(-10) - BigNumber(10),
			  BigNumber(-20));

	TF_ASSERT("Sub 5",
			  BigNumber(-10) - BigNumber(0),
			  BigNumber(-10));

	TF_ASSERT("Sub 6",
			  BigNumber(20) - BigNumber(2),
			  BigNumber(18));

	TF_ASSERT("Sub 7",
			  BigNumber(2) - BigNumber(20),
			  BigNumber(-18));

	TF_ASSERT("Sub 8",
			  BigNumber(1000) - BigNumber(10),
			  BigNumber(990));
}


void multiplication_test() {
	TF_ASSERT("Mult 1",
			  BigNumber(10) * BigNumber(10),
			  BigNumber(100));

	TF_ASSERT("Mult 2",
			  BigNumber(20) * BigNumber(30),
			  BigNumber(600));

	TF_ASSERT("Mult 3",
			  BigNumber(50) * BigNumber(-10),
			  BigNumber(-500));

	TF_ASSERT("Mult 4",
			  BigNumber(-30) * BigNumber(100),
			  BigNumber(-3000));

	TF_ASSERT("Mult 5",
			  BigNumber(-3000) * BigNumber(-2),
			  BigNumber(6000));

	TF_ASSERT("Mult 6",
			  BigNumber(-3111) * BigNumber(-2),
			  BigNumber(6222));

	TF_ASSERT("Mult 6",
			  BigNumber(37) * BigNumber(76),
			  BigNumber(2812));

	TF_ASSERT("Mult 7",
			  BigNumber("11111111111111111111111111111111") * BigNumber(3),
			  BigNumber("33333333333333333333333333333333"));

	TF_ASSERT("Mult 8",
			  BigNumber("11111111111111111111111111111111") * BigNumber(100000),
			  BigNumber("1111111111111111111111111111111100000"));
}


void division_test() {
	TF_ASSERT("Div 1",
			  BigNumber(1000) / BigNumber(10),
			  BigNumber(100));

	TF_ASSERT("Div 2",
			  BigNumber(1000) / BigNumber(1000),
			  BigNumber(1));

	TF_ASSERT("Div 3",
			  BigNumber(12) / BigNumber(10),
			  BigNumber(1));

	TF_ASSERT("Div 4",
			  BigNumber(20) / BigNumber(6),
			  BigNumber(3));

	TF_ASSERT("Div 5",
			  BigNumber(100) / BigNumber(1),
			  BigNumber(100));

	TF_ASSERT("Div 6",
			  BigNumber(300) / BigNumber(3),
			  BigNumber(100));

	TF_ASSERT("Div 7",
			  BigNumber(700) / BigNumber(5),
			  BigNumber(140));
}


void module_test() {
	TF_ASSERT("Mod 1",
			  BigNumber(10) % BigNumber(3),
			  BigNumber(1));

	TF_ASSERT("Mod 2",
			  BigNumber(12) % BigNumber(3),
			  BigNumber(0));

	TF_ASSERT("Mod 3",
			  BigNumber(55) % BigNumber(10),
			  BigNumber(5));

	TF_ASSERT("Mod 4",
			  BigNumber(9) % BigNumber(10),
			  BigNumber(9));

	TF_ASSERT("Mod 5",
			  BigNumber(460) % BigNumber(360),
			  BigNumber(100));

	TF_ASSERT("Mod 6",
			  BigNumber(7655) % BigNumber(91),
			  BigNumber(11));
}


void times10_test() {
	TF_ASSERT("Times10 1",
			  BigNumber(31).times10(),
			  BigNumber(310));

	TF_ASSERT("Times10 2",
			  BigNumber(555).times10(2),
			  BigNumber(55500));

	TF_ASSERT("Times10 3",
			  BigNumber(789).times10(3),
			  BigNumber(789000));

	TF_ASSERT("Times10 4",
			  BigNumber(1000).times10(4),
			  BigNumber(10000000));
}


void divide10_test() {
	TF_ASSERT("Divide10 1",
			  BigNumber(56088).divide10(2),
			  BigNumber(560));
}


void greater_test() {
	TF_ASSERT("Comp > 1",
			  BigNumber(1000) > BigNumber(2),
			  true);

	TF_ASSERT("Comp > 2",
			  BigNumber(44) > BigNumber(43),
			  true);

	TF_ASSERT("Comp > 3",
			  BigNumber(88) > BigNumber(100),
			  false);
}


void less_test() {
	TF_ASSERT("Comp < 1",
			  BigNumber(1000) < BigNumber(1001),
			  true);

	TF_ASSERT("Comp < 2",
			  BigNumber(777) < BigNumber(800),
			  true);

	TF_ASSERT("Comp < 3",
			  BigNumber(7) < BigNumber(7),
			  false);

	TF_ASSERT("Comp < 4",
			  BigNumber(-7) < BigNumber(7),
			  true);

	TF_ASSERT("Comp < 5",
			  BigNumber(10) < BigNumber(100),
			  true);

	TF_ASSERT("Comp < 6",
			  BigNumber(-8) < BigNumber(-3),
			  true);
}


void greaterEqual_test() {
	TF_ASSERT("Comp >= 1",
			  BigNumber(666) >= BigNumber(666),
			  true);

	TF_ASSERT("Comp >= 2",
			  BigNumber(668) >= BigNumber(666),
			  true);

	TF_ASSERT("Comp >= 3",
			  BigNumber(660) >= BigNumber(663),
			  false);
}


void lessEqual_test() {
	TF_ASSERT("Comp <= 1",
			  BigNumber(666) <= BigNumber(666),
			  true);

	TF_ASSERT("Comp <= 2",
			  BigNumber(633) <= 660,
			  true);

	TF_ASSERT("Comp <= 3",
			  BigNumber(700) <= BigNumber(400),
			  false);
}


void equal_test() {
	TF_ASSERT("Comp == 1",
			  BigNumber(0) == BigNumber(0),
			  true);

	TF_ASSERT("Comp == 2",
			  BigNumber(0) == BigNumber(-0),
			  true);

	TF_ASSERT("Comp == 3",
			  BigNumber(-0) == BigNumber(-0),
			  true);

	TF_ASSERT("Comp == 4",
			  BigNumber(-1) == BigNumber(-1),
			  true);

	TF_ASSERT("Comp == 5",
			  BigNumber(70) == 70,
			  true);

	TF_ASSERT("Comp == 6",
			  BigNumber(3) == BigNumber(7),
			  false);

	TF_ASSERT("Comp == 7",
			  BigNumber(0) == 22,
			  false);
}


void notEqual_test() {
	TF_ASSERT("Comp != 1",
			  BigNumber(10) != BigNumber(0),
			  true);

	TF_ASSERT("Comp != 2",
			  BigNumber(22) != BigNumber(2),
			  true);

	TF_ASSERT("Comp != 3",
			  BigNumber(30) != BigNumber(3),
			  true);

	TF_ASSERT("Comp != 4",
			  BigNumber(10) != BigNumber(10),
			  false);

	TF_ASSERT("Comp != 5",
			  BigNumber(0) != BigNumber(0),
			  false);
}


void asString_test() {
	TF_ASSERT("AsString 1",
			  BigNumber(0).asString(),
			  std::string("0"));

	TF_ASSERT("AsString 2",
			  BigNumber(0).asString() == "-0",
			  false);

	TF_ASSERT("AsString 3",
			  BigNumber(-0).asString(),
			  std::string("0"));

	TF_ASSERT("AsString 4",
			  BigNumber(-50).asString(),
			  std::string("-50"));

	TF_ASSERT("AsString 5",
			  BigNumber(-12300).asString(),
			  std::string("-12300"));
}


void fitsInLongLong_test() {
	TF_ASSERT("FitsInLongLong 1",
			  BigNumber("-123456789").fitsInLongLong(),
			  true);

	TF_ASSERT("FitsInLongLong 2",
			  BigNumber("922337203685477580").fitsInLongLong(),
			  true);

	TF_ASSERT("FitsInLongLong 3",
			  BigNumber("9223372036854775807").fitsInLongLong(),
			  false);

	TF_ASSERT("FitsInLongLong 4",
			  BigNumber("922337203685477580799").fitsInLongLong(),
			  false);
}


void asLongLong_test() {
	TF_ASSERT("AsLongLong 1",
			  BigNumber(123456789).asLongLong(),
			  123456789);

	TF_ASSERT("AsLongLong 2",
			  BigNumber("-123456789").asLongLong(),
			  -123456789);
}


void length_test() {
	TF_ASSERT("Lenght 1",
			  BigNumber("-123456789").lenght(),
			  9);

	TF_ASSERT("Lenght 2",
			  BigNumber("00001").lenght(),
			  1);
}


void isOdd_test() {
	TF_ASSERT("Odd 1",
			  BigNumber("00001").isOdd(),
			  true);

	TF_ASSERT("Odd 2",
			  BigNumber("20").isOdd(),
			  false);
}


void isZero_test() {
	TF_ASSERT("isZero 1",
			  BigNumber("0").isZero(),
			  true);

	TF_ASSERT("isZero 2",
			  BigNumber("10").isZero(),
			  false);
}


void isOne_test() {
	TF_ASSERT("isOne 1",
			  BigNumber("1").isOne(),
			  true);

	TF_ASSERT("isOne 2",
			  BigNumber("10").isOne(),
			  false);

	TF_ASSERT("isOne 3",
			  BigNumber("-1").isOne(),
			  false);
}


void power_test() {
	TF_ASSERT("Pow 1",
			  BigNumber(2).pow(BigNumber(2)),
			  BigNumber(4));

	TF_ASSERT("Pow 2",
			  BigNumber(10).pow(BigNumber(10)),
			  BigNumber(10000000000));

	TF_ASSERT("Pow 3",
			  BigNumber(7).pow(BigNumber(0)),
			  BigNumber(1));

	TF_ASSERT("Pow 4",
			  BigNumber(0).pow(BigNumber(2)),
			  BigNumber(0));

	TF_ASSERT("Pow 5",
			  BigNumber(-5).pow(BigNumber(2)),
			  BigNumber(25));

	TF_ASSERT("Pow 6",
			  BigNumber(-5).pow(BigNumber(3)),
			  BigNumber(-125));
}


void modularPower_test() {
	TF_ASSERT("ModPow 1",
			  BigNumber(5).modPow(10, 3),
			  BigNumber(1));

	TF_ASSERT("ModPow 2",
			  BigNumber(522).modPow(7, 22),
			  BigNumber(14));
}


void random_test() {
	TF_ASSERT("Random 1",
			  BigNumber::randomBigNumber(100).lenght(),
			  100);

	TF_ASSERT("Random 2",
			  BigNumber::randomBigNumber(1024).lenght(),
			  1024);
}


void randomInRange_test() {
	TF_ASSERT("Random in Range 1",
			  BigNumber::randomBigNumberInRange(10, 100) >= 10,
			  true);

	TF_ASSERT("Random in Range 2",
			  BigNumber::randomBigNumberInRange(100, 1000) < 1000,
			  true);
}


void asBinary_test() {
	TF_ASSERT("AsBinary 1",
			  BigNumber("234567898765432123456789").asBinary(),
			  std::string("0110001101010111111001110000110100011010010101101001010110110100111110100010101"));

	TF_ASSERT("AsBinary 2",
			  BigNumber(77).asBinary(),
			  std::string("01001101"));
}


void fromBinary_test() {
	TF_ASSERT("FromBinary 1",
			  BigNumber::fromBinary(BigNumber(154).asBinary()),
			  BigNumber(154));
}


void splitAt_test() {
	TF_ASSERT("SplitAt 1",
			  BigNumber("12323123129392841823845913213124133").splitAt(10).second,
			  BigNumber("3213124133"));
}



int main(int argc, char *argv[]) {

	constructor_test();
	sum_test();
	subtraction_test();
	multiplication_test();
	division_test();
	module_test();
	times10_test();
	divide10_test();
	greater_test();
	less_test();
	greaterEqual_test();
	lessEqual_test();
	equal_test();
	notEqual_test();
	asString_test();
	fitsInLongLong_test();
	asLongLong_test();
	length_test();
	isOdd_test();
	isZero_test();
	isOne_test();
	power_test();
	modularPower_test();
	random_test();
	randomInRange_test();
	asBinary_test();
	fromBinary_test();
	splitAt_test();



	TF_PRINT_RESULT();
	return TF_EXIT_CODE();
}
