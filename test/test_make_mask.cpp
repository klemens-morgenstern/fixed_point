//============================================================================
// Name        : prop_list.cpp
// Author      : Klemens Morgenstern
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#define CHECK(Cond) BOOST_CHECK(Cond); static_assert(Cond, #Cond);

#include <cstdint>
#include <boost/test/minimal.hpp>

#include <mw/fixed_point/make_mask.hpp>
#include <type_traits>


void test_uint8()
{
	using mw::fixed_point::make_mask;
	CHECK(make_mask<std::uint8_t>(0) == 0b00000000u);
	CHECK(make_mask<std::uint8_t>(1) == 0b00000001u);
	CHECK(make_mask<std::uint8_t>(2) == 0b00000011u);
	CHECK(make_mask<std::uint8_t>(3) == 0b00000111u);
	CHECK(make_mask<std::uint8_t>(4) == 0b00001111u);
	CHECK(make_mask<std::uint8_t>(5) == 0b00011111u);
	CHECK(make_mask<std::uint8_t>(6) == 0b00111111u);
	CHECK(make_mask<std::uint8_t>(7) == 0b01111111u);
	CHECK(make_mask<std::uint8_t>(8) == 0b11111111u);


	CHECK(make_mask<std::uint8_t>(12) == 0b11111111u);

}

void test_int8()
{
	using mw::fixed_point::make_mask;
	CHECK(make_mask<std::int8_t>(0) == 0b00000000);
	CHECK(make_mask<std::int8_t>(1) == 0b00000001);
	CHECK(make_mask<std::int8_t>(2) == 0b00000011);
	CHECK(make_mask<std::int8_t>(3) == 0b00000111);
	CHECK(make_mask<std::int8_t>(4) == 0b00001111);
	CHECK(make_mask<std::int8_t>(5) == 0b00011111);
	CHECK(make_mask<std::int8_t>(6) == 0b00111111);
	CHECK(make_mask<std::int8_t>(7) == 0b01111111);
	CHECK(static_cast<std::uint8_t>(
			make_mask<std::int8_t>(8)) == 0b11111111);//because this results in a negative value -1

	CHECK(static_cast<std::uint8_t>(
			make_mask<std::int8_t>(80)) == 0b11111111);//because this results in a negative value -1
}

void test_uint16()
{
	using mw::fixed_point::make_mask;
	CHECK(make_mask<std::uint16_t>(0)  == 0b0000000000000000u);
	CHECK(make_mask<std::uint16_t>(1)  == 0b0000000000000001u);
	CHECK(make_mask<std::uint16_t>(2)  == 0b0000000000000011u);
	CHECK(make_mask<std::uint16_t>(3)  == 0b0000000000000111u);
	CHECK(make_mask<std::uint16_t>(4)  == 0b0000000000001111u);
	CHECK(make_mask<std::uint16_t>(5)  == 0b0000000000011111u);
	CHECK(make_mask<std::uint16_t>(6)  == 0b0000000000111111u);
	CHECK(make_mask<std::uint16_t>(7)  == 0b0000000001111111u);
	CHECK(make_mask<std::uint16_t>(8)  == 0b0000000011111111u);
	CHECK(make_mask<std::uint16_t>(9)  == 0b0000000111111111u);
	CHECK(make_mask<std::uint16_t>(10) == 0b0000001111111111u);
	CHECK(make_mask<std::uint16_t>(11) == 0b0000011111111111u);
	CHECK(make_mask<std::uint16_t>(12) == 0b0000111111111111u);
	CHECK(make_mask<std::uint16_t>(13) == 0b0001111111111111u);
	CHECK(make_mask<std::uint16_t>(14) == 0b0011111111111111u);
	CHECK(make_mask<std::uint16_t>(15) == 0b0111111111111111u);
	CHECK(make_mask<std::uint16_t>(16) == 0b1111111111111111u);

	CHECK(make_mask<std::uint16_t>(106) == 0b1111111111111111u);

}

void test_int16()
{
	using mw::fixed_point::make_mask;
	CHECK(make_mask<std::int16_t>(0)  == 0b0000000000000000);
	CHECK(make_mask<std::int16_t>(1)  == 0b0000000000000001);
	CHECK(make_mask<std::int16_t>(2)  == 0b0000000000000011);
	CHECK(make_mask<std::int16_t>(3)  == 0b0000000000000111);
	CHECK(make_mask<std::int16_t>(4)  == 0b0000000000001111);
	CHECK(make_mask<std::int16_t>(5)  == 0b0000000000011111);
	CHECK(make_mask<std::int16_t>(6)  == 0b0000000000111111);
	CHECK(make_mask<std::int16_t>(7)  == 0b0000000001111111);
	CHECK(make_mask<std::int16_t>(8)  == 0b0000000011111111);
	CHECK(make_mask<std::int16_t>(9)  == 0b0000000111111111);
	CHECK(make_mask<std::int16_t>(10) == 0b0000001111111111);
	CHECK(make_mask<std::int16_t>(11) == 0b0000011111111111);
	CHECK(make_mask<std::int16_t>(12) == 0b0000111111111111);
	CHECK(make_mask<std::int16_t>(13) == 0b0001111111111111);
	CHECK(make_mask<std::int16_t>(14) == 0b0011111111111111);
	CHECK(make_mask<std::int16_t>(15) == 0b0111111111111111);

	CHECK(static_cast<std::uint16_t>(
			make_mask<std::int16_t>(16)) == 0b1111111111111111);//because this results in a negative value -1
	CHECK(static_cast<std::uint16_t>(
			make_mask<std::int16_t>(126)) == 0b1111111111111111);//because this results in a negative value -1
}

void test_uint32()
{
	using mw::fixed_point::make_mask;
	CHECK(make_mask<std::uint32_t>(0)   == 0b00000000000000000000000000000000ul);
	CHECK(make_mask<std::uint32_t>(1)   == 0b00000000000000000000000000000001ul);
	CHECK(make_mask<std::uint32_t>(15)  == 0b00000000000000000111111111111111ul);
	CHECK(make_mask<std::uint32_t>(16)  == 0b00000000000000001111111111111111ul);
	CHECK(make_mask<std::uint32_t>(17)  == 0b00000000000000011111111111111111ul);

	CHECK(make_mask<std::uint32_t>(31)  == 0b01111111111111111111111111111111ul);
	CHECK(make_mask<std::uint32_t>(32)  == 0b11111111111111111111111111111111ul);


	CHECK(make_mask<std::uint32_t>(106) == 0b11111111111111111111111111111111ul);

}

void test_int32()
{
	using mw::fixed_point::make_mask;

	CHECK(make_mask<std::int32_t>(0)   == 0b00000000000000000000000000000000l);
	CHECK(make_mask<std::int32_t>(1)   == 0b00000000000000000000000000000001l);
	CHECK(make_mask<std::int32_t>(15)  == 0b00000000000000000111111111111111l);
	CHECK(make_mask<std::int32_t>(16)  == 0b00000000000000001111111111111111l);
	CHECK(make_mask<std::int32_t>(17)  == 0b00000000000000011111111111111111l);

	CHECK(make_mask<std::int32_t>(31)  == 0b01111111111111111111111111111111l);

	CHECK(static_cast<std::uint32_t>(
			make_mask<std::int32_t>(32)) == 0b11111111111111111111111111111111l);//because this results in a negative value -1
	CHECK(static_cast<std::uint32_t>(
			make_mask<std::int32_t>(126)) == 0b11111111111111111111111111111111l);//because this results in a negative value -1
}


void test_uint64()
{
	using mw::fixed_point::make_mask;
	CHECK(make_mask<std::uint64_t>(0)   == 0b0000000000000000000000000000000000000000000000000000000000000000ull);
	CHECK(make_mask<std::uint64_t>(1)   == 0b0000000000000000000000000000000000000000000000000000000000000001ull);
	CHECK(make_mask<std::uint64_t>(15)  == 0b0000000000000000000000000000000000000000000000000111111111111111ull);
	CHECK(make_mask<std::uint64_t>(16)  == 0b0000000000000000000000000000000000000000000000001111111111111111ull);
	CHECK(make_mask<std::uint64_t>(17)  == 0b0000000000000000000000000000000000000000000000011111111111111111ull);
	CHECK(make_mask<std::uint64_t>(31)  == 0b0000000000000000000000000000000001111111111111111111111111111111ull);
	CHECK(make_mask<std::uint64_t>(32)  == 0b0000000000000000000000000000000011111111111111111111111111111111ull);
	CHECK(make_mask<std::uint64_t>(63)  == 0b0111111111111111111111111111111111111111111111111111111111111111ull);

	CHECK(make_mask<std::uint64_t>(64)  == 0b1111111111111111111111111111111111111111111111111111111111111111ull);
	CHECK(make_mask<std::uint64_t>(106) == 0b1111111111111111111111111111111111111111111111111111111111111111ull);

}

void test_int64()
{
	using mw::fixed_point::make_mask;

	CHECK(make_mask<std::int64_t>(0)   == 0b0000000000000000000000000000000000000000000000000000000000000000ll);
	CHECK(make_mask<std::int64_t>(1)   == 0b0000000000000000000000000000000000000000000000000000000000000001ll);
	CHECK(make_mask<std::int64_t>(15)  == 0b0000000000000000000000000000000000000000000000000111111111111111ll);
	CHECK(make_mask<std::int64_t>(16)  == 0b0000000000000000000000000000000000000000000000001111111111111111ll);
	CHECK(make_mask<std::int64_t>(17)  == 0b0000000000000000000000000000000000000000000000011111111111111111ll);
	CHECK(make_mask<std::int64_t>(31)  == 0b0000000000000000000000000000000001111111111111111111111111111111ll);
	CHECK(make_mask<std::int64_t>(32)  == 0b0000000000000000000000000000000011111111111111111111111111111111ll);
	CHECK(make_mask<std::int64_t>(63)  == 0b0111111111111111111111111111111111111111111111111111111111111111ll);

	CHECK(static_cast<std::uint64_t>(
			make_mask<std::int64_t>(64)) == 0b1111111111111111111111111111111111111111111111111111111111111111ll);
	CHECK(static_cast<std::uint64_t>(
			make_mask<std::int64_t>(126)) == 0b1111111111111111111111111111111111111111111111111111111111111111ll);
}

int test_main(int, char**)
{
	test_int8();
	test_uint8();
	test_int16();
	test_uint16();
	test_int32();
	test_uint32();
	test_int64();
	test_uint64();
	return 0;
}
