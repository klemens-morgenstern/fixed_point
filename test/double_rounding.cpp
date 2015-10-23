//============================================================================
// Name        : prop_list.cpp
// Author      : Klemens Morgenstern
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#define CHECK(Cond) BOOST_CHECK(Cond); static_assert(Cond, #Cond);

#include <boost/test/minimal.hpp>

#include <mw/fixed_point/round_double.hpp>
#include <type_traits>



void test_float()
{
	using mw::fixed_point::round;
	using mw::fixed_point::trunc;
	using mw::fixed_point::ceil;
	using mw::fixed_point::floor;

	CHECK(round(1.4f) == 1.0f);
	CHECK(round(1.5f) == 2.0f);
	CHECK(round(1.9f) == 2.0f);
	CHECK(round(2.0f) == 2.0f);
	CHECK(round(2.1f) == 2.0f);

	CHECK(round(-5.1f) == -5.0f);
	CHECK(round(-5.0f) == -5.0f);
	CHECK(round(-5.5f) == -6.0f);
	CHECK(round(-5.6f) == -6.0f);

	CHECK(round(0.375f, 0.25f) == 0.5f);
	CHECK(round(0.4f,   0.25f) == 0.5f);
	CHECK(round(0.5f,   0.25f) == 0.5f);
	CHECK(round(0.6f,   0.25f) == 0.5f);

	CHECK(round(-0.375f, 0.25f) == -0.5f);
	CHECK(round(-0.4f,   0.25f) == -0.5f);
	CHECK(round(-0.5f,   0.25f) == -0.5f);
	CHECK(round(-0.6f,   0.25f) == -0.5f);



	CHECK(trunc(1.4f) == 1.0f);
	CHECK(trunc(1.5f) == 1.0f);
	CHECK(trunc(1.9f) == 1.0f);
	CHECK(trunc(2.0f) == 2.0f);
	CHECK(trunc(2.1f) == 2.0f);

	CHECK(trunc(-5.1f) == -5.0f);
	CHECK(trunc(-5.0f) == -5.0f);
	CHECK(trunc(-5.5f) == -5.0f);
	CHECK(trunc(-5.6f) == -5.0f);


	CHECK(trunc(0.375f, 0.25f) == 0.25f);
	CHECK(trunc(0.4f,   0.25f) == 0.25f);
	CHECK(trunc(0.5f,   0.25f) == 0.5f);
	CHECK(trunc(0.6f,   0.25f) == 0.5f);

	CHECK(trunc(-0.375f, 0.25f) == -0.25f);
	CHECK(trunc(-0.4f,   0.25f) == -0.25f);
	CHECK(trunc(-0.5f,   0.25f) == -0.5f);
	CHECK(trunc(-0.6f,   0.25f) == -0.5f);




	CHECK(ceil(1.4f) == 2.0f);
	CHECK(ceil(1.5f) == 2.0f);
	CHECK(ceil(1.9f) == 2.0f);
	CHECK(ceil(2.0f) == 2.0f);
	CHECK(ceil(2.1f) == 3.0f);

	CHECK(ceil(-5.1f) == -5.0f);
	CHECK(ceil(-5.0f) == -5.0f);
	CHECK(ceil(-5.5f) == -5.0f);
	CHECK(ceil(-5.6f) == -5.0f);


	CHECK(ceil(0.375f, 0.25f) == 0.5f);
	CHECK(ceil(0.4f,   0.25f) == 0.5f);
	CHECK(ceil(0.5f,   0.25f) == 0.5);
	CHECK(ceil(0.6f,   0.25f) == 0.75f);

	CHECK(ceil(-0.375f, 0.25f) == -0.25f);
	CHECK(ceil(-0.4f,   0.25f) == -0.25f);
	CHECK(ceil(-0.5f,   0.25f) == -0.5f);
	CHECK(ceil(-0.6f,   0.25f) == -0.5f);


	CHECK(floor(1.4f) == 1.0f);
	CHECK(floor(1.5f) == 1.0f);
	CHECK(floor(1.9f) == 1.0f);
	CHECK(floor(2.0f) == 2.0f);
	CHECK(floor(2.1f) == 2.0f);

	CHECK(floor(-5.1f) == -6.0f);
	CHECK(floor(-5.0f) == -5.0f);
	CHECK(floor(-5.5f) == -6.0f);
	CHECK(floor(-5.6f) == -6.0f);


	CHECK(floor(0.375f, 0.25f) == 0.25f);
	CHECK(floor(0.4f,   0.25f) == 0.25f);
	CHECK(floor(0.5f,   0.25f) == 0.5);
	CHECK(floor(0.6f,   0.25f) == 0.5f);

	CHECK(floor(-0.375f, 0.25f) == -0.5f);
	CHECK(floor(-0.4f,   0.25f) == -0.5f);
	CHECK(floor(-0.5f,   0.25f) == -0.5f);
	CHECK(floor(-0.6f,   0.25f) == -0.75f);

}



void test_double()
{

	using mw::fixed_point::round;
	using mw::fixed_point::trunc;
	using mw::fixed_point::ceil;
	using mw::fixed_point::floor;

	CHECK(round(3.0) == 3.);
	CHECK(round(3.2) == 3.);
	CHECK(round(3.5) == 4.);
	CHECK(round(3.6) == 4.);

	CHECK(round(-3.0) == -3.);
	CHECK(round(-3.2) == -3.);
	CHECK(round(-3.5) == -4.);
	CHECK(round(-3.6) == -4.);

	CHECK(round(2.1, 0.25) == 2.0);
	CHECK(round(3.2, 0.25) == 3.25);
	CHECK(round(3.5, 0.25) == 3.5);
	CHECK(round(3.6, 0.25) == 3.5);

	CHECK(round(-2.1, 0.25) == -2.0);
	CHECK(round(-3.2, 0.25) == -3.25);
	CHECK(round(-3.5, 0.25) == -3.5);
	CHECK(round(-3.6, 0.25) == -3.5);


	CHECK(trunc(3.0) == 3.);
	CHECK(trunc(3.2) == 3.);
	CHECK(trunc(3.5) == 3.);
	CHECK(trunc(3.6) == 3.);

	CHECK(trunc(-3.0) == -3.);
	CHECK(trunc(-3.2) == -3.);
	CHECK(trunc(-3.5) == -3.);
	CHECK(trunc(-3.6) == -3.);

	CHECK(trunc(2.1, 0.25) == 2.0);
	CHECK(trunc(3.2, 0.25) == 3.0);
	CHECK(trunc(3.5, 0.25) == 3.5);
	CHECK(trunc(3.6, 0.25) == 3.5);

	CHECK(trunc(-2.1, 0.25) == -2.0);
	CHECK(trunc(-3.2, 0.25) == -3.0);
	CHECK(trunc(-3.5, 0.25) == -3.5);
	CHECK(trunc(-3.6, 0.25) == -3.5);


	CHECK(ceil(3.0) == 3.);
	CHECK(ceil(3.2) == 4.);
	CHECK(ceil(3.5) == 4.);
	CHECK(ceil(3.6) == 4.);

	CHECK(ceil(-3.0) == -3.);
	CHECK(ceil(-3.2) == -3.);
	CHECK(ceil(-3.5) == -3.);
	CHECK(ceil(-3.6) == -3.);

	CHECK(ceil(2.1, 0.25) == 2.25);
	CHECK(ceil(3.2, 0.25) == 3.25);
	CHECK(ceil(3.5, 0.25) == 3.5);
	CHECK(ceil(3.6, 0.25) == 3.75);

	CHECK(ceil(-2.1, 0.25) == -2.0);
	CHECK(ceil(-3.2, 0.25) == -3.0);
	CHECK(ceil(-3.5, 0.25) == -3.5);
	CHECK(ceil(-3.6, 0.25) == -3.5);


	CHECK(floor(3.0) == 3.);
	CHECK(floor(3.2) == 3.);
	CHECK(floor(3.5) == 3.);
	CHECK(floor(3.6) == 3.);

	CHECK(floor(-3.0) == -3.);
	CHECK(floor(-3.2) == -4.);
	CHECK(floor(-3.5) == -4.);
	CHECK(floor(-3.6) == -4.);

	CHECK(floor(2.1, 0.25) == 2.0);
	CHECK(floor(3.2, 0.25) == 3.0);
	CHECK(floor(3.5, 0.25) == 3.5);
	CHECK(floor(3.6, 0.25) == 3.5);

	CHECK(floor(-2.1, 0.25) == -2.25);
	CHECK(floor(-3.2, 0.25) == -3.25);
	CHECK(floor(-3.5, 0.25) == -3.5);
	CHECK(floor(-3.6, 0.25) == -3.75);
}





void test_long_double()
{

	using mw::fixed_point::round;
	using mw::fixed_point::trunc;
	using mw::fixed_point::ceil;
	using mw::fixed_point::floor;

	CHECK(round(3.0L) == 3.L);
	CHECK(round(3.2L) == 3.L);
	CHECK(round(3.5L) == 4.L);
	CHECK(round(3.6L) == 4.L);

	CHECK(round(-3.0L) == -3.L);
	CHECK(round(-3.2L) == -3.L);
	CHECK(round(-3.5L) == -4.L);
	CHECK(round(-3.6L) == -4.L);

	CHECK(round(2.1L, 0.25L) == 2.0);
	CHECK(round(3.2L, 0.25L) == 3.25);
	CHECK(round(3.5L, 0.25L) == 3.5);
	CHECK(round(3.6L, 0.25L) == 3.5);

	CHECK(round(-2.1L, 0.25L) == -2.0);
	CHECK(round(-3.2L, 0.25L) == -3.25);
	CHECK(round(-3.5L, 0.25L) == -3.5);
	CHECK(round(-3.6L, 0.25L) == -3.5);


	CHECK(trunc(3.0L) == 3.L);
	CHECK(trunc(3.2L) == 3.L);
	CHECK(trunc(3.5L) == 3.L);
	CHECK(trunc(3.6L) == 3.L);

	CHECK(trunc(-3.0L) == -3.L);
	CHECK(trunc(-3.2L) == -3.L);
	CHECK(trunc(-3.5L) == -3.L);
	CHECK(trunc(-3.6L) == -3.L);

	CHECK(trunc(2.1L, 0.25L) == 2.0L);
	CHECK(trunc(3.2L, 0.25L) == 3.0L);
	CHECK(trunc(3.5L, 0.25L) == 3.5L);
	CHECK(trunc(3.6L, 0.25L) == 3.5L);

	CHECK(trunc(-2.1L, 0.25L) == -2.0L);
	CHECK(trunc(-3.2L, 0.25L) == -3.0L);
	CHECK(trunc(-3.5L, 0.25L) == -3.5L);
	CHECK(trunc(-3.6L, 0.25L) == -3.5L);


	CHECK(ceil(3.0L) == 3.L);
	CHECK(ceil(3.2L) == 4.L);
	CHECK(ceil(3.5L) == 4.L);
	CHECK(ceil(3.6L) == 4.L);

	CHECK(ceil(-3.0L) == -3.L);
	CHECK(ceil(-3.2L) == -3.L);
	CHECK(ceil(-3.5L) == -3.L);
	CHECK(ceil(-3.6L) == -3.L);

	CHECK(ceil(2.1L, 0.25L) == 2.25L);
	CHECK(ceil(3.2L, 0.25L) == 3.25L);
	CHECK(ceil(3.5L, 0.25L) == 3.5L);
	CHECK(ceil(3.6L, 0.25L) == 3.75L);

	CHECK(ceil(-2.1L, 0.25L) == -2.0L);
	CHECK(ceil(-3.2L, 0.25L) == -3.0L);
	CHECK(ceil(-3.5L, 0.25L) == -3.5L);
	CHECK(ceil(-3.6L, 0.25L) == -3.5L);


	CHECK(floor(3.0L) == 3.L);
	CHECK(floor(3.2L) == 3.L);
	CHECK(floor(3.5L) == 3.L);
	CHECK(floor(3.6L) == 3.L);

	CHECK(floor(-3.0L) == -3.L);
	CHECK(floor(-3.2L) == -4.L);
	CHECK(floor(-3.5L) == -4.L);
	CHECK(floor(-3.6L) == -4.L);

	CHECK(floor(2.1L, 0.25L) == 2.0L);
	CHECK(floor(3.2L, 0.25L) == 3.0L);
	CHECK(floor(3.5L, 0.25L) == 3.5L);
	CHECK(floor(3.6L, 0.25L) == 3.5L);

	CHECK(floor(-2.1L, 0.25L) == -2.25L);
	CHECK(floor(-3.2L, 0.25L) == -3.25L);
	CHECK(floor(-3.5L, 0.25L) == -3.5L);
	CHECK(floor(-3.6L, 0.25L) == -3.75L);
}


int test_main(int, char**)
{
	test_float();
	test_double();
	test_long_double();
	return 0;
}
