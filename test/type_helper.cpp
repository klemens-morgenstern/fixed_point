#include <boost/test/minimal.hpp>
#include <mw/fixed_point/type_helper.hpp>
#include <type_traits>


#define CHECK(Cond) BOOST_CHECK(Cond); static_assert(Cond, #Cond);

#define CHECK_TYPE(Width, Sign, IntType, Signed, Unsigned, FloatType, FloatOverflow) \
		{                                                                            \
		    using type = types<Width, Sign>;                                         \
		   	using t1 = std::is_same<typename type::unsigned_type, Unsigned>;         \
			using t2 = std::is_same<typename type::signed_type,   Signed>;           \
			using t3 = std::is_same<typename type::int_type, 	  IntType>;          \
			using t4 = std::is_same<typename type::float_type, 	  FloatType>;        \
                                                                                     \
		    CHECK(t1::value);                                                        \
		    CHECK(t2::value);                                                        \
		    CHECK(t3::value);                                                        \
		    CHECK(t4::value);                                                        \
		    CHECK(type::float_overflow == FloatOverflow)                             \
		}



int test_main(int , char* [])
{
	using mw::fixed_point::detail::types;
/*	using boost::multiprecision::float128;
	using boost::multiprecision::uint128_t;
	using boost::multiprecision:: int128_t;
	using boost::multiprecision::uint256_t;
	using boost::multiprecision:: int256_t;
	using boost::multiprecision::uint512_t;
	using boost::multiprecision:: int512_t;
	using boost::multiprecision::uint1024_t;
	using boost::multiprecision:: int1024_t;*/


	CHECK_TYPE(1 , signed,   std::int8_t, std::int8_t, std::uint8_t, float, false);
	CHECK_TYPE(7 , signed,   std::int8_t, std::int8_t, std::uint8_t, float, false);
	CHECK_TYPE(8 , signed,   std::int8_t, std::int8_t, std::uint8_t, float, false);
	CHECK_TYPE(9 , signed,   std::int16_t, std::int16_t, std::uint16_t, float, false);
	CHECK_TYPE(15, signed,   std::int16_t, std::int16_t, std::uint16_t, float, false);
	CHECK_TYPE(16, signed,   std::int16_t, std::int16_t, std::uint16_t, float, false);
	CHECK_TYPE(17, signed,   std::int32_t, std::int32_t, std::uint32_t, float, false);

	CHECK_TYPE(31, signed,   std::int32_t, std::int32_t, std::uint32_t, double, false);
	CHECK_TYPE(32, signed,   std::int32_t, std::int32_t, std::uint32_t, double, false);
	CHECK_TYPE(33, signed,   std::int64_t, std::int64_t, std::uint64_t, double, false);

	CHECK_TYPE(63, signed,   std::int64_t, std::int64_t, std::uint64_t, long double, false);
	CHECK_TYPE(64, signed,   std::int64_t, std::int64_t, std::uint64_t, long double, false);
/*	CHECK_TYPE(65, signed,   int128_t, int128_t, uint128_t, long double, false);

	CHECK_TYPE(127, signed,  int128_t, int128_t, uint128_t, long double, true);
	CHECK_TYPE(128, signed,  int128_t, int128_t, uint128_t, long double, true);
	CHECK_TYPE(129, signed,  int256_t, int256_t, uint256_t, long double, true);

	CHECK_TYPE(255, signed,  int256_t, int256_t, uint256_t, long double, true);
	CHECK_TYPE(256, signed,  int256_t, int256_t, uint256_t, long double, true);
	CHECK_TYPE(257, signed,  int512_t, int512_t, uint512_t, long double, true);

	CHECK_TYPE(511, signed,  int512_t, int512_t, uint512_t, long double, true);
	CHECK_TYPE(512, signed,  int512_t, int512_t, uint512_t, long double, true);
	CHECK_TYPE(513, signed,  int1024_t, int1024_t, uint1024_t, long double, true);

	CHECK_TYPE(1023, signed, int1024_t, int1024_t, uint1024_t, long double, true);
	CHECK_TYPE(1024, signed, int1024_t, int1024_t, uint1024_t, long double, true);*/





	CHECK_TYPE(1 , unsigned,   std::uint8_t, std::int8_t, std::uint8_t, float, false);
	CHECK_TYPE(7 , unsigned,   std::uint8_t, std::int8_t, std::uint8_t, float, false);
	CHECK_TYPE(8 , unsigned,   std::uint8_t, std::int8_t, std::uint8_t, float, false);
	CHECK_TYPE(9 , unsigned,   std::uint16_t, std::int16_t, std::uint16_t, float, false);
	CHECK_TYPE(15, unsigned,   std::uint16_t, std::int16_t, std::uint16_t, float, false);
	CHECK_TYPE(16, unsigned,   std::uint16_t, std::int16_t, std::uint16_t, float, false);
	CHECK_TYPE(17, unsigned,   std::uint32_t, std::int32_t, std::uint32_t, float, false);

	CHECK_TYPE(31, unsigned,   std::uint32_t, std::int32_t, std::uint32_t, double, false);
	CHECK_TYPE(32, unsigned,   std::uint32_t, std::int32_t, std::uint32_t, double, false);
	CHECK_TYPE(33, unsigned,   std::uint64_t, std::int64_t, std::uint64_t, double, false);

	CHECK_TYPE(63, unsigned,   std::uint64_t, std::int64_t, std::uint64_t, long double, false);
	CHECK_TYPE(64, unsigned,   std::uint64_t, std::int64_t, std::uint64_t, long double, false);
/*	CHECK_TYPE(65, unsigned,   uint128_t, int128_t, uint128_t, long double, false);

	CHECK_TYPE(127, unsigned,  uint128_t, int128_t, uint128_t, long double, true);
	CHECK_TYPE(128, unsigned,  uint128_t, int128_t, uint128_t, long double, true);
	CHECK_TYPE(129, unsigned,  uint256_t, int256_t, uint256_t, long double, true);

	CHECK_TYPE(255, unsigned,  uint256_t, int256_t, uint256_t, long double, true);
	CHECK_TYPE(256, unsigned,  uint256_t, int256_t, uint256_t, long double, true);
	CHECK_TYPE(257, unsigned,  uint512_t, int512_t, uint512_t, long double, true);

	CHECK_TYPE(511, unsigned,  uint512_t, int512_t, uint512_t, long double, true);
	CHECK_TYPE(512, unsigned,  uint512_t, int512_t, uint512_t, long double, true);
	CHECK_TYPE(513, unsigned,  uint1024_t, int1024_t, uint1024_t, long double, true);

	CHECK_TYPE(1023, unsigned, uint1024_t, int1024_t, uint1024_t, long double, true);
	CHECK_TYPE(1024, unsigned, uint1024_t, int1024_t, uint1024_t, long double, true);*/



	return 0;
}
