//============================================================================
// Name        : basic_fp.cpp
// Author      : Klemens Morgenstern
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#define CHECK(Cond) BOOST_CHECK(Cond); static_assert(Cond, #Cond);

#include <boost/test/minimal.hpp>

#include <mw/fixed_point/fixed_point.hpp>
#include <type_traits>
#include <iostream>

int test_main(int, char**)
{
	using mw::fixed_point::fp;
	//alright, test a view adaptations of ints, though i am putting them into chars.
	CHECK(static_cast<double>(fp<4,2>(0b0101)) == 1.25);
	CHECK(static_cast<double>(fp<4,2>(0b1001)) == -1.75);
	CHECK(static_cast<double>(fp<4,2>(0b1111)) == -0.25);
	CHECK(static_cast<double>(fp<4,2>(0b0100)) ==  1.0);
	CHECK(static_cast<double>(fp<4,2>(0b1000)) == -2.0);

	CHECK(static_cast<double>(fp<5,2>(232.2)) == 3.75);
	CHECK(static_cast<double>(fp<5,2>(-232.)) == -4.00);


	return 0;
}
