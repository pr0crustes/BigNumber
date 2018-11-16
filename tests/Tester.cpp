#include "TestFramework.h"

#include "../include/BigNumber.h"


int main(int argc, char *argv[]) {

	using pr0crustes::BigNumber;

//	TF::setIgnoreAllTests(true);

//	TF::setOnlyFail(true);

//	TF_ASSERT("Constructor 1",
//			  BigNumber("100"),
//			  BigNumber(100));

//	TF_ASSERT("Constructor 2",
//			  BigNumber(),
//			  BigNumber(0));

//	TF_ASSERT("Constructor 3",
//			  BigNumber(),
//			  BigNumber("0"));

//	TF_ASSERT("Constructor 4",
//			  BigNumber(),
//			  BigNumber(""));


//	TF_ASSERT("Sum 1",
//			  BigNumber(10) + BigNumber(90),
//			  BigNumber(100));

//	TF_ASSERT("Sum 2",
//			  BigNumber(22222) + BigNumber(33333),
//			  BigNumber(55555));

//	TF_ASSERT("Sum 3",
//			  BigNumber(100) + BigNumber(-3),
//			  BigNumber(97));

//	TF_ASSERT("Sum 4",
//			  BigNumber(0) + BigNumber(0),
//			  BigNumber(0));

//	TF_ASSERT("Sum 5",
//			  BigNumber(0) + BigNumber(11),
//			  BigNumber(11));

//	TF_ASSERT("Sum 6",
//			  BigNumber(33) + BigNumber(0),
//			  BigNumber(33));

//	TF_ASSERT("Sum 7",
//			  BigNumber(2) + BigNumber(20),
//			  BigNumber(22));

//	TF_ASSERT("Sum 8",
//			  BigNumber(20) + BigNumber(2),
//			  BigNumber(22));

//	TF_ASSERT("Sum 9",
//			  BigNumber(19) + BigNumber(1),
//			  BigNumber(20));

//	TF_ASSERT("Sum 10",
//			  BigNumber(19) + 1,
//			  BigNumber(20));

//	TF_ASSERT("Sum 11",
//			  BigNumber(5) + 2,
//			  BigNumber(7));

//	TF_ASSERT("Sum 12",
//			  BigNumber(1111111) + BigNumber(1999999),
//			  BigNumber(3111110));


//	TF_ASSERT("Sub 1",
//			  BigNumber(100) - BigNumber(50),
//			  BigNumber(50));

//	TF_ASSERT("Sub 2",
//			  BigNumber(10) - BigNumber(-10),
//			  BigNumber(20));

//	TF_ASSERT("Sub 3",
//			  BigNumber(-10) - BigNumber(-10),
//			  BigNumber(0));

//	TF_ASSERT("Sub 4",
//			  BigNumber(-10) - BigNumber(10),
//			  BigNumber(-20));

//	TF_ASSERT("Sub 5",
//			  BigNumber(-10) - BigNumber(0),
//			  BigNumber(-10));

//	TF_ASSERT("Sub 6",
//			  BigNumber(20) - BigNumber(2),
//			  BigNumber(18));

//	TF_ASSERT("Sub 7",
//			  BigNumber(2) - BigNumber(20),
//			  BigNumber(-18));

//	TF_ASSERT("Sub 8",
//			  BigNumber(1000) - BigNumber(10),
//			  BigNumber(990));


//	TF_ASSERT("Mult 1",
//			  BigNumber(10) * BigNumber(10),
//			  BigNumber(100));

//	TF_ASSERT("Mult 2",
//			  BigNumber(20) * BigNumber(30),
//			  BigNumber(600));

//	TF_ASSERT("Mult 3",
//			  BigNumber(50) * BigNumber(-10),
//			  BigNumber(-500));

//	TF_ASSERT("Mult 4",
//			  BigNumber(-30) * BigNumber(100),
//			  BigNumber(-3000));

//	TF_ASSERT("Mult 5",
//			  BigNumber(-3000) * BigNumber(-2),
//			  BigNumber(6000));

//	TF_ASSERT("Mult 6",
//			  BigNumber(-3111) * BigNumber(-2),
//			  BigNumber(6222));

//	TF_ASSERT("Mult 6",
//			  BigNumber(37) * BigNumber(76),
//			  BigNumber(2812));


//	TF_ASSERT("Div 1",
//			  BigNumber(1000) / BigNumber(10),
//			  BigNumber(100));

//	TF_ASSERT("Div 2",
//			  BigNumber(1000) / BigNumber(1000),
//			  BigNumber(1));

//	TF_ASSERT("Div 3",
//			  BigNumber(12) / BigNumber(10),
//			  BigNumber(1));

//	TF_ASSERT("Div 4",
//			  BigNumber(20) / BigNumber(6),
//			  BigNumber(3));

//	TF_ASSERT("Div 5",
//			  BigNumber(100) / BigNumber(1),
//			  BigNumber(100));

//	TF_ASSERT("Div 6",
//			  BigNumber(300) / BigNumber(3),
//			  BigNumber(100));

//	TF_ASSERT("Div 7",
//			  BigNumber(700) / BigNumber(5),
//			  BigNumber(140));


//	TF_ASSERT("Mod 1",
//			  BigNumber(10) % BigNumber(3),
//			  BigNumber(1));

//	TF_ASSERT("Mod 2",
//			  BigNumber(12) % BigNumber(3),
//			  BigNumber(0));

//	TF_ASSERT("Mod 3",
//			  BigNumber(55) % BigNumber(10),
//			  BigNumber(5));

//	TF_ASSERT("Mod 4",
//			  BigNumber(9) % BigNumber(10),
//			  BigNumber(9));

//	TF_ASSERT("Mod 5",
//			  BigNumber(460) % BigNumber(360),
//			  BigNumber(100));

//	TF_ASSERT("Mod 6",
//			  BigNumber(7655) % BigNumber(91),
//			  BigNumber(11));


//	TF_ASSERT("Times10 1",
//			  BigNumber(31).times10(),
//			  BigNumber(310));

//	TF_ASSERT("Times10 2",
//			  BigNumber(555).times10(2),
//			  BigNumber(55500));

//	TF_ASSERT("Times10 3",
//			  BigNumber(789).times10(3),
//			  BigNumber(789000));

//	TF_ASSERT("Times10 4",
//			  BigNumber(1000).times10(4),
//			  BigNumber(10000000));


//	TF_ASSERT("Comp > 1",
//			  BigNumber(1000) > BigNumber(2),
//			  true);

//	TF_ASSERT("Comp > 2",
//			  BigNumber(44) > BigNumber(43),
//			  true);

//	TF_ASSERT("Comp > 3",
//			  BigNumber(88) > BigNumber(100),
//			  false);


//	TF_ASSERT("Comp < 1",
//			  BigNumber(1000) < BigNumber(1001),
//			  true);

//	TF_ASSERT("Comp < 2",
//			  BigNumber(777) < BigNumber(800),
//			  true);

//	TF_ASSERT("Comp < 3",
//			  BigNumber(7) < BigNumber(7),
//			  false);

//	TF_ASSERT("Comp < 4",
//			  BigNumber(-7) < BigNumber(7),
//			  true);

//	TF_ASSERT("Comp < 5",
//			  BigNumber(10) < BigNumber(100),
//			  true);

//	TF_ASSERT("Comp < 6",
//			  BigNumber(-8) < BigNumber(-3),
//			  true);


//	TF_ASSERT("Comp >= 1",
//			  BigNumber(666) >= BigNumber(666),
//			  true);

//	TF_ASSERT("Comp >= 2",
//			  BigNumber(668) >= BigNumber(666),
//			  true);

//	TF_ASSERT("Comp >= 3",
//			  BigNumber(660) >= BigNumber(663),
//			  false);


//	TF_ASSERT("Comp <= 1",
//			  BigNumber(666) <= BigNumber(666),
//			  true);

//	TF_ASSERT("Comp <= 2",
//			  BigNumber(633) <= BigNumber(660),
//			  true);

//	TF_ASSERT("Comp <= 3",
//			  BigNumber(700) <= BigNumber(400),
//			  false);


//	TF_ASSERT("Comp == 1",
//			  BigNumber(0) == BigNumber(0),
//			  true);

//	TF_ASSERT("Comp == 2",
//			  BigNumber(0) == BigNumber(-0),
//			  true);

//	TF_ASSERT("Comp == 3",
//			  BigNumber(-0) == BigNumber(-0),
//			  true);

//	TF_ASSERT("Comp == 4",
//			  BigNumber(-1) == BigNumber(-1),
//			  true);

//	TF_ASSERT("Comp == 5",
//			  BigNumber(70) == BigNumber(70),
//			  true);

//	TF_ASSERT("Comp == 7",
//			  BigNumber(3) == BigNumber(7),
//			  false);

//	TF_ASSERT("Comp == 8",
//			  BigNumber(0) == BigNumber(22),
//			  false);


//	TF_ASSERT("Comp != 1",
//			  BigNumber(10) != BigNumber(0),
//			  true);

//	TF_ASSERT("Comp != 2",
//			  BigNumber(22) != BigNumber(2),
//			  true);

//	TF_ASSERT("Comp != 3",
//			  BigNumber(30) != BigNumber(3),
//			  true);

//	TF_ASSERT("Comp != 4",
//			  BigNumber(10) != BigNumber(10),
//			  false);

//	TF_ASSERT("Comp != 5",
//			  BigNumber(0) != BigNumber(0),
//			  false);


//	TF_ASSERT("AsString 1",
//			  BigNumber(0).asString() == "0",
//			  true);

//	TF_ASSERT("AsString 2",
//			  BigNumber(0).asString() == "-0",
//			  false);

//	TF_ASSERT("AsString 3",
//			  BigNumber(-0).asString() == "0",
//			  true);

//	TF_ASSERT("AsString 4",
//			  BigNumber(-50).asString() == "-50",
//			  true);

//	TF_ASSERT("AsString 5",
//			  BigNumber(-12300).asString() == "-12300",
//			  true);


//	TF_ASSERT("FitsInLongLong 1",
//			  BigNumber("-123456789").fitsInLongLong(),
//			  true);

//	TF_ASSERT("FitsInLongLong 2",
//			  BigNumber("922337203685477580").fitsInLongLong(),
//			  true);

//	TF_ASSERT("FitsInLongLong 3",
//			  BigNumber("9223372036854775807").fitsInLongLong(),
//			  false);

//	TF_ASSERT("FitsInLongLong 4",
//			  BigNumber("922337203685477580799").fitsInLongLong(),
//			  false);


//	TF_ASSERT("AsLongLong 1",
//			  BigNumber(123456789).asLongLong(),
//			  (long long) 123456789);

//	TF_ASSERT("AsLongLong 2",
//			  BigNumber("-123456789").asLongLong(),
//			  (long long) -123456789);


//	TF_ASSERT("Lenght 1",
//			  BigNumber("-123456789").lenght(),
//			  (long long) 9);

//	TF_ASSERT("Lenght 2",
//			  BigNumber("00001").lenght(),
//			  (long long) 1);


//	TF_ASSERT("Odd 1",
//			  BigNumber("00001").isOdd(),
//			  true);

//	TF_ASSERT("Odd 2",
//			  BigNumber("20").isOdd(),
//			  false);


//	TF_ASSERT("isZero 1",
//			  BigNumber("0").isZero(),
//			  true);

//	TF_ASSERT("isZero 2",
//			  BigNumber("10").isZero(),
//			  false);


//	TF_ASSERT("isOne 1",
//			  BigNumber("1").isOne(),
//			  true);

//	TF_ASSERT("isOne 2",
//			  BigNumber("10").isOne(),
//			  false);

//	TF_ASSERT("isOne 3",
//			  BigNumber("-1").isOne(),
//			  false);


//	TF_ASSERT("Pow 1",
//			  BigNumber(2).pow(BigNumber(2)),
//			  BigNumber(4));

//	TF_ASSERT("Pow 2",
//			  BigNumber(10).pow(BigNumber(10)),
//			  BigNumber(10000000000));

//	TF_ASSERT("Pow 3",
//			  BigNumber(7).pow(BigNumber(0)),
//			  BigNumber(1));

//	TF_ASSERT("Pow 4",
//			  BigNumber(0).pow(BigNumber(2)),
//			  BigNumber(0));

//	TF_ASSERT("Pow 5",
//			  BigNumber(-5).pow(BigNumber(2)),
//			  BigNumber(25));

//	TF_ASSERT("Pow 6",
//			  BigNumber(-5).pow(BigNumber(3)),
//			  BigNumber(-125));


//	TF_ASSERT("ModPow 1",
//			  BigNumber(5).modPow(10, 3),
//			  BigNumber(1));

//	TF_ASSERT("ModPow 2",
//			  BigNumber(522).modPow(7, 22),
//			  BigNumber(14));


//	TF_ASSERT("Random 1",
//			  BigNumber::randomBigNumber(100).lenght(),
//			  (long long) 100);

//	TF_ASSERT("Random 2",
//			  BigNumber::randomBigNumber(1024).lenght(),
//			  (long long) 1024);


//	TF_ASSERT("Random in Range 1",
//			  BigNumber::randomBigNumberInRange(10, 100) >= 10,
//			  true);

//	TF_ASSERT("Random in Range 2",
//			  BigNumber::randomBigNumberInRange(100, 1000) < 1000,
//			  true);

//	TF_TIME_IT({
	BigNumber a = BigNumber("-100");
	std::string b = a.asBinary();
	std::cout << a << "  |  " << b << std::endl;
//	});



	return TF::printResult();
}
