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
	CHECK(static_cast<double>(fp<4,2>(0b0000)) ==  0.0);
	CHECK(static_cast<double>(fp<4,2>(0b0100)) ==  1.0);
	CHECK(static_cast<double>(fp<4,2>(0b1000)) == -2.0);

	CHECK(static_cast<double>(fp<5,2>(232.2)) == 3.75);
	CHECK(static_cast<double>(fp<5,2>(-232.)) == -4.00);


	CHECK(static_cast<double>(fp<1,3, signed  >(1)) == -0.125); //ok, that seems to work.
	CHECK(static_cast<double>(fp<1,3, unsigned>(1)) ==  0.125);


	CHECK(static_cast<double>(fp<1,-4, unsigned>(1)) ==  16);
	CHECK(static_cast<double>(fp<1,-4,   signed>(1)) == -16);


	CHECK(static_cast<double>(fp<8,4>(0b11111111)) == -0.0625);
	CHECK(static_cast<double>(fp<8,4>(0b01111111)) ==
			   (0.0	+ 4.0  + 2.0	+ 1.0 +
				0.5 + 0.25 + 0.125 	+ 0.0625));


	CHECK(static_cast<double>(fp<8,4, unsigned>(0b11111111)) ==
			   (8.0	+ 4.0  + 2.0	+ 1.0 +
				0.5 + 0.25 + 0.125 	+ 0.0625));


	return 0;
}
