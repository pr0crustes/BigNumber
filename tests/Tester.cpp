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



	return TF_PRINT_RESULTS();
}
