/*
 * TypHelper.h
 *
 *  Created on: 07.09.2013
 *      Author: user
 */

#ifndef TYPHELPER_H_
#define TYPHELPER_H_

#include <limits>
#include <cstdint>
#include <type_traits>

namespace fixed_point
{

template<size_t size,  bool to_small = true, typename inc_t = void>
struct float_type
{
	typedef float_type<size, to_small, inc_t> type;
};

template<size_t size>
struct float_type<size, true, void>
{typedef typename float_type<size, std::numeric_limits<float>::digits >= size , float>::type type;};

template<size_t size>
struct float_type<size, true, float>
{
	typedef typename float_type<size, std::numeric_limits<double>::digits >= size , double>::type type;
};

template<size_t size>
struct float_type<size, true, double>
{
	using type = long double;  //there is nothing greater...
};


template<size_t size>
struct float_type<size, false, float>
{typedef float type;};

template<size_t size>
struct float_type<size, false, double>
{typedef double type;}; //there is nothing greater...



///selector of the right integral type
template<size_t size, typename sign_t = signed, bool to_big = false> struct int_type
{
	typedef typename int_type<size+1, sign_t, (size>64)>::type 	 type;
	typedef typename int_type<size+1, sign_t, (size>64)>::bigger_than_64 bigger_than_64;
	typedef typename int_type<size+1, sign_t, (size>64)>::signed_type signed_type;

	typedef typename float_type<size + (std::is_unsigned<sign_t>::value ? 1 : 0)>::type	min_float_t;
};

template<size_t size, typename sign_t>
struct int_type<size, sign_t, true>
{

};

template<> struct int_type<7,  unsigned, false>
{
	typedef uint8_t type;
	typedef std::false_type bigger_than_64;
	typedef int8_t signed_type;

	typedef typename float_type<7 + 1>::type	min_float_t;

};

template<> struct int_type<8,  unsigned, false>
{
	typedef uint8_t type;
	typedef std::false_type bigger_than_64;
	typedef int16_t signed_type;

	typedef typename float_type<8 + 1>::type	min_float_t;
};

template<> struct int_type<15, unsigned, false>
{
	typedef uint16_t type;
	typedef std::false_type bigger_than_64;
	typedef int16_t signed_type;

	typedef typename float_type<15 + 1>::type	min_float_t;
};

template<> struct int_type<16, unsigned, false>
{
	typedef uint16_t type;
	typedef std::false_type bigger_than_64;
	typedef int32_t signed_type;

	typedef typename float_type<16 + 1>::type	min_float_t;
};

template<> struct int_type<31, unsigned, false>
{
	typedef uint32_t type;
	typedef std::false_type bigger_than_64;
	typedef int32_t signed_type;

	typedef typename float_type<31 + 1>::type	min_float_t;

};
template<> struct int_type<32, unsigned, false>
{
	typedef uint32_t type;
	typedef std::false_type bigger_than_64;
	typedef int64_t signed_type;

	typedef typename float_type<32 + 1>::type	min_float_t;

};

template<> struct int_type<63, unsigned, false>
{
	typedef int64_t type;
	typedef std::false_type bigger_than_64;
	typedef int64_t signed_type;

	typedef typename float_type<63 + 1>::type	min_float_t;
};

template<> struct int_type<64, unsigned, false>
{
	typedef int64_t type;
	typedef std::false_type bigger_than_64;
	typedef void signed_type;

	typedef typename float_type<64 + 1>::type	min_float_t;
};

template<> struct int_type<8,  signed, false>
{
	typedef int8_t type;
	typedef std::false_type bigger_than_64;
	typedef int8_t signed_type;

	typedef typename float_type<8>::type	min_float_t;
};

template<> struct int_type<16, signed, false>
{
	typedef int16_t type;
	typedef std::false_type bigger_than_64;
	typedef int16_t signed_type;

	typedef typename float_type<16>::type	min_float_t;

};

template<> struct int_type<32, signed, false>
{
	typedef int32_t type;
	typedef std::false_type bigger_than_64;
	typedef int32_t signed_type;

	typedef typename float_type<32>::type	min_float_t;

};


template<> struct int_type<64, signed, false>
{
	typedef int64_t type;
	typedef std::false_type bigger_than_64;
	typedef int64_t signed_type;

	typedef typename float_type<64>::type	min_float_t;


};

}


#endif /* TYPHELPER_H_ */
