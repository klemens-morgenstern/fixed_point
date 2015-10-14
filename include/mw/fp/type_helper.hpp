/*
 * TypHelper.h
 *
 *  Created on: 07.09.2013
 *      Author: user
 */

#ifndef MW_FP_TYPE_HELPER_H_
#define MW_FP_TYPE_HELPER_H_

#include <limits>
#include <cstdint>
#include <type_traits>

#ifndef NO_BOOST
#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#endif

namespace mw
{

namespace fixed_point
{


template<std::size_t Size>
struct float_type
{
	typedef float_type<Size+1> type;
};

template<>
struct float_type<std::numeric_limits<float>::digits * 8>
{
	typedef float type;
};

template<>
struct float_type<std::numeric_limits<double>::digits * 8>
{
	typedef float type;
};

template<>
struct float_type<std::numeric_limits<long double>::digits * 8>
{
	typedef float type;
};


#ifndef NO_BOOST
template<>
struct float_type<std::numeric_limits<boost::multiprecision::float128>::digits * 8>
{
	typedef float type;

};
#endif


template<std::size_t Size>
struct int_type
{

};

template<> struct int_type<8>
{
	typedef std::uint8_t unsigned_type;
	typedef std::int16_t signed_type;
};

template<> struct int_type<16>
{
	typedef std::uint16_t unsigned_type;
	typedef std::int32_t signed_type;
};

template<> struct int_type<32>
{
	typedef std::uint32_t unsigned_type;
	typedef std::int32_t signed_type;

};

template<> struct int_type<64>
{
	typedef std::uint64_t unsigned_type;
	typedef std::int64_t signed_type;
};


#ifndef NO_BOOST
template<> struct int_type<128>
{
	typedef boost::multiprecision::uint128_t unsigned_type;
	typedef boost::multiprecision:: int128_t signed_type;
};

template<> struct int_type<256>
{
	typedef boost::multiprecision::uint256_t unsigned_type;
	typedef boost::multiprecision:: int256_t signed_type;
};

template<> struct int_type<512>
{
	typedef boost::multiprecision::uint512_t unsigned_type;
	typedef boost::multiprecision:: int512_t  signed_type;
};

template<> struct int_type<1024>
{
	typedef boost::multiprecision::uint1024_t unsigned_type;
	typedef boost::multiprecision:: int1024_t signed_type;
};
#endif

///selector of the right integral type
template<size_t size, typename Sign = unsigned>
struct types
{
	typedef typename int_type<size>::unsigned_type 	unsigned_type;
	typedef typename int_type<size>::signed_type 	signed_type;
	typedef typename std::conditional<
						std::is_same<Sign, unsigned>::value,
						unsigned_type,
						signed_type>::type int_type;

	typedef typename float_type<size + (std::is_unsigned<Sign>::value ? 1 : 0)>::type	float_type;
};



}
}

#endif /* TYPHELPER_H_ */
