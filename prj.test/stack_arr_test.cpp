#include <StackArr/StackArr.h>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("stack ctor") {
	StackArr test;
	TempComplex test_num(1, 1);

	test.push(test_num);
	test.push(test_num);
	test.push(test_num);
	test.push(test_num);

	

	CHECK_EQ(false, test.IsEmpty());
	/*CHECK_EQ(test_num, test.Top());*/

	/*test.pop();

	CHECK_EQ(true, test.IsEmpty());*/
}