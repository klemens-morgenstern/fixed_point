/*
 * Rounding.h
 *
 *  Created on: 16.10.2013
 *      Author: user
 */

#ifndef ROUNDING_H_
#define ROUNDING_H_

#include <mw/fixed_point/type_helper.hpp>
#include <cmath>
#include <type_traits>

namespace mw
{
namespace fixed_point
{

///
enum class rounding_mode
{
	trunc, ///<Computes nearest integer to arg. Number is rounded away from zero in halfway cases
	floor, ///<Computes nearest integer not greater than arg.
	ceil,  ///<Computes nearest integer not less than arg.
	round, ///<Computes nearest integer not greater in magnitude than arg.
};


template<typename T>
constexpr T mask(T fl, T mask_value = 0)
{
	return (mask_value < (1<<fl))
			? mask<T>(mask_value<<1 | 0b1)
			: mask_value;
}


//the part for float rounding
template<typename flt>
constexpr flt round_float(flt val, std::integral_constant<rounding_mode, rounding_mode::trunc>)
{return std::trunc(val);}

template<typename flt>
constexpr flt round_float(flt val, std::integral_constant<rounding_mode, rounding_mode::floor>)
{return std::floor(val);}

template<typename flt>
constexpr flt round_float(flt val, std::integral_constant<rounding_mode, rounding_mode::ceil> )
{return std::ceil(val);}

template<typename Flt>
constexpr Flt round_float(Flt val, std::integral_constant<rounding_mode, rounding_mode::round>)
{return std::round(val);}


#ifndef NO_BOOST

constexpr boost::multiprecision::float128 round_float(
		boost::multiprecision::float128 val,
		std::integral_constant<rounding_mode, rounding_mode::trunc>)
{
	return boost::multiprecision::trunc(val);
}

constexpr boost::multiprecision::float128 round_float(
		boost::multiprecision::float128 val,
		std::integral_constant<rounding_mode, rounding_mode::floor>)
{
	return boost::multiprecision::floor(val);
}

constexpr boost::multiprecision::float128 round_float(
		boost::multiprecision::float128 val,
		std::integral_constant<rounding_mode, rounding_mode::ceil> )
{
	return boost::multiprecision::ceil(val);
}

constexpr boost::multiprecision::float128 round_float(
		boost::multiprecision::float128 val,
		std::integral_constant<rounding_mode, rounding_mode::round>)
{
	return boost::multiprecision::round(val);
}

#endif



template<std::size_t Fl, rounding_mode Rounding_Mode, typename T>
constexpr T round_float(T val)
{
	return round_float(val * (1<<Fl), std::integral_constant<rounding_mode, Rounding_Mode>()) / (1<<Fl);
}



//the part with FP-rounding
template<typename I>
constexpr I round_fixed(I val, std::size_t fl, std::size_t fl_orig,  std::integral_constant<rounding_mode, rounding_mode::trunc>)

{
	return val>>(fl-fl_orig);//just truncate the thing
}

template<typename I>
constexpr I round_fixed(I val, std::size_t fl, std::size_t fl_orig,  std::integral_constant<rounding_mode, rounding_mode::floor>)

{
	return (val > 0)
			?
				(val>>(fl-fl_orig)) ///that is: val is positive or
			:
				(val>>(fl-fl_orig)) + (val&mask<I>(fl_orig-fl) != 0 ? 1 : 0);
}


template<typename I>
constexpr I round_fixed(I val, std::size_t fl, std::size_t fl_orig,  std::integral_constant<rounding_mode, rounding_mode::ceil>)
{
	return (val < 0)
			?
				(val>>(fl-fl_orig)) //negative value
			:
				(val>>(fl-fl_orig)) + (val&mask<I>(fl_orig-fl) != 0 ? 1 : 0);
}

template<typename I>
constexpr I round_fixed(I val, std::size_t fl, std::size_t fl_orig,  std::integral_constant<rounding_mode, rounding_mode::round>)
{
	return val>>(fl-fl_orig) + 	(val >>(fl_orig-fl-1) & 0b01);
}


template<std::size_t Fl, rounding_mode Rounding_Mode, typename T>
constexpr T round_fixed(T val, const std::size_t &fl_orig)
{

	return (fl_orig > Fl) ?
						round_fixed(val, Fl, fl_orig, std::integral_constant<rounding_mode, Rounding_Mode>())
						: (val << (Fl-fl_orig));

}





}}
#endif /* ROUNDING_H_ */
