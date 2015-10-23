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


int test_main(int, char**)
{
	using mw::fixed_point::fp;
	CHECK(static_cast<double>(fp<4,2>(0b0101)) == 1.25);
	CHECK(static_cast<double>(fp<4,2>(0b1001)) == -1.75);
	CHECK(static_cast<double>(fp<4,2>(0b1111)) == -0.25);





	return 0;
}
