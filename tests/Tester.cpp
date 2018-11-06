#include "TestFramework.h"
#include "../include/BigNumber.h"


int main(int argc, char *argv[]) {

	TF_SET_ONLY_FAIL(true);

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


	TF_ASSERT("Comp > 1",
			  BigNumber(1000) > BigNumber(2),
			  true);

	TF_ASSERT("Comp > 2",
			  BigNumber(44) > BigNumber(43),
			  true);

	TF_ASSERT("Comp > 3",
			  BigNumber(88) > BigNumber(100),
			  false);


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


	TF_ASSERT("Comp >= 1",
			  BigNumber(666) >= BigNumber(666),
			  true);

	TF_ASSERT("Comp >= 2",
			  BigNumber(668) >= BigNumber(666),
			  true);

	TF_ASSERT("Comp >= 3",
			  BigNumber(660) >= BigNumber(663),
			  false);


	TF_ASSERT("Comp <= 1",
			  BigNumber(666) <= BigNumber(666),
			  true);

	TF_ASSERT("Comp <= 2",
			  BigNumber(633) <= BigNumber(660),
			  true);

	TF_ASSERT("Comp <= 3",
			  BigNumber(700) <= BigNumber(400),
			  false);


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
			  BigNumber(70) == BigNumber(70),
			  true);

	TF_ASSERT("Comp == 7",
			  BigNumber(3) == BigNumber(7),
			  false);

	TF_ASSERT("Comp == 8",
			  BigNumber(0) == BigNumber(22),
			  false);


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


	TF_ASSERT("AsString 1",
			  BigNumber(0).asString() == "0",
			  true);

	TF_ASSERT("AsString 2",
			  BigNumber(0).asString() == "-0",
			  false);

	TF_ASSERT("AsString 3",
			  BigNumber(-0).asString() == "0",
			  true);

	TF_ASSERT("AsString 4",
			  BigNumber(-50).asString() == "-50",
			  true);

	TF_ASSERT("AsString 5",
			  BigNumber(-12300).asString() == "-12300",
			  true);



	return TF_PRINT_RESULTS();
}
