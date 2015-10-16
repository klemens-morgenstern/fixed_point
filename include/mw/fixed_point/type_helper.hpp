/*
 * TypHelper.h
 *
 *  Created on: 07.09.2013
 *      Author: user
 */

#ifndef MW_FIXED_POINT_TYPE_HELPER_H_
#define MW_FIXED_POINT_TYPE_HELPER_H_

#include <limits>
#include <cstdint>
#include <type_traits>

#ifndef NO_BOOST
#include <boost/iterator/iterator_traits.hpp> //for some reason travis does not compile
#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#endif

namespace mw
{
namespace fixed_point
{

#ifndef NO_BOOST
using boost::multiprecision::float128;
using boost::multiprecision::uint128_t;
using boost::multiprecision:: int128_t;
using boost::multiprecision::uint256_t;
using boost::multiprecision:: int256_t;
using boost::multiprecision::uint512_t;
using boost::multiprecision:: int512_t;
using boost::multiprecision::uint1024_t;
using boost::multiprecision:: int1024_t;
#endif

namespace detail
{

template<std::size_t Size>
struct float_type
{
	typedef typename float_type<Size+1>::type type;
};

template<>
struct float_type<std::numeric_limits<float>::digits>
{
	typedef float type;
};

template<>
struct float_type<std::numeric_limits<double>::digits>
{
	typedef double type;
};

template<>
struct float_type<std::numeric_limits<long double>::digits>
{
	typedef long double type;
};


#ifndef NO_BOOST
template<>
struct float_type<std::numeric_limits<boost::multiprecision::float128>::digits>
{
	typedef boost::multiprecision::float128 type;

};

typedef boost::multiprecision::float128 float_type_max;

#else

typedef long double float_type_max;

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


typedef boost::multiprecision::uint1024_t unsigned_type_max;
typedef boost::multiprecision:: int1024_t   signed_type_max;


#else

typedef std::uint64_t unsigned_type_max;
typedef std:: int64_t   signed_type_max;


#endif

///selector of the right integral type
template<size_t size, typename Sign = unsigned>
struct types
{
	static_assert(size <= std::numeric_limits<unsigned_type_max>::digits, "Requested size is too large");

	typedef typename int_type<size>::unsigned_type 	unsigned_type;
	typedef typename int_type<size>::signed_type 	signed_type;
	typedef typename std::conditional<
						std::is_same<Sign, unsigned>::value,
						unsigned_type,
						signed_type>::type int_type;

	typedef typename float_type<size + (std::is_unsigned<Sign>::value ? 1 : 0)>::type	float_type;
	typedef std::integral_constant<bool, (std::numeric_limits<float_type_max>::digits > size)> float_overflow;
};

template<typename T> struct to_signed {};
template<typename T> struct to_unsigned {};


template<> struct to_signed<std::uint8_t>  { typedef std::int8_t  type; };
template<> struct to_signed<std:: int8_t>  { typedef std::int8_t  type; };
template<> struct to_signed<std::uint16_t> { typedef std::int16_t type; };
template<> struct to_signed<std:: int16_t> { typedef std::int16_t type; };
template<> struct to_signed<std::uint32_t> { typedef std::int32_t type; };
template<> struct to_signed<std:: int32_t> { typedef std::int32_t type; };
template<> struct to_signed<std::uint64_t> { typedef std::int64_t type; };
template<> struct to_signed<std:: int64_t> { typedef std::int64_t type; };

template<> struct to_unsigned<std::uint8_t>  { typedef std::uint8_t  type; };
template<> struct to_unsigned<std:: int8_t>  { typedef std::uint8_t  type; };
template<> struct to_unsigned<std::uint16_t> { typedef std::uint16_t type; };
template<> struct to_unsigned<std:: int16_t> { typedef std::uint16_t type; };
template<> struct to_unsigned<std::uint32_t> { typedef std::uint32_t type; };
template<> struct to_unsigned<std:: int32_t> { typedef std::uint32_t type; };
template<> struct to_unsigned<std::uint64_t> { typedef std::uint64_t type; };
template<> struct to_unsigned<std:: int64_t> { typedef std::uint64_t type; };

#ifndef NO_BOOST
template<> struct to_signed<uint128_t>  { typedef int128_t  type; };
template<> struct to_signed< int128_t>  { typedef int128_t  type; };
template<> struct to_signed<uint256_t>  { typedef int256_t  type; };
template<> struct to_signed< int256_t>  { typedef int256_t  type; };
template<> struct to_signed<uint512_t>  { typedef int512_t  type; };
template<> struct to_signed< int512_t>  { typedef int512_t  type; };
template<> struct to_signed<uint1024_t> { typedef int1024_t type; };
template<> struct to_signed< int1024_t> { typedef int1024_t type; };

template<> struct to_unsigned<uint128_t>  { typedef uint128_t  type; };
template<> struct to_unsigned< int128_t>  { typedef uint128_t  type; };
template<> struct to_unsigned<uint256_t>  { typedef uint256_t  type; };
template<> struct to_unsigned< int256_t>  { typedef uint256_t  type; };
template<> struct to_unsigned<uint512_t>  { typedef uint512_t  type; };
template<> struct to_unsigned< int512_t>  { typedef uint512_t  type; };
template<> struct to_unsigned<uint1024_t> { typedef uint1024_t type; };
template<> struct to_unsigned< int1024_t> { typedef uint1024_t type; };
#endif


template<typename T> using to_signed_t 	 = typename to_signed<T>::  type;
template<typename T> using to_unsigned_t = typename to_unsigned<T>::type;


}
}
}

#endif /* TYPHELPER_H_ */
