/*
 * Rounding.h
 *
 *  Created on: 16.10.2013
 *      Author: user
 */

#ifndef ROUNDING_H_
#define ROUNDING_H_

#include "TypeHelper.h"
#include <cmath>
#include <type_traits>


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


#define r_m rounding_mode
#define r_f now_round_the_stuff_baaaam
#define mask blaaablub

template<typename T>
constexpr T mask(T fl, T mask_value = 0) {return mask_value < (1<<fl) ? mask<T>(mask_value<<1 | 0b1) : mask_value;  }

//the part for float rounding
template<typename flt>
constexpr flt r_f(flt val, std::size_t fl, std::integral_constant<r_m, r_m::trunc>, std::true_type)
{return std::trunc(val*(1<<fl));}

template<typename flt>
constexpr flt r_f(flt val, std::size_t fl, std::integral_constant<r_m, r_m::floor>, std::true_type)
{return std::floor(val*(1<<fl));}

template<typename flt>
constexpr flt r_f(flt val, std::size_t fl, std::integral_constant<r_m, r_m::ceil>, std::true_type)
{return std::ceil(val*(1<<fl));}

template<typename flt>
constexpr flt r_f(flt val, std::size_t fl, std::integral_constant<r_m, r_m::round>, std::true_type)
{return std::round(val*(1<<fl));}

//the part with FP-rounding

//template<typename I, std::size_t wl, std::size_t fl>
//constexpr I r_f(I val, std::size_t fl_orig,
template<typename I>
constexpr I r_f(I val, std::size_t fl, std::size_t fl_orig,  std::integral_constant<r_m, r_m::trunc>, std::false_type)

{
	return val>>(fl-fl_orig);//just truncate the thing
}

template<typename I>
constexpr I r_f(I val, std::size_t fl, std::size_t fl_orig,  std::integral_constant<r_m, r_m::floor>, std::false_type)

{
	return (val > 0)
			?
				(val>>(fl-fl_orig)) ///that is: val is positive or
			:
				(val>>(fl-fl_orig)) + (val&mask<I>(fl_orig-fl) != 0 ? 1 : 0);
}


template<typename I>
constexpr I r_f(I val, std::size_t fl, std::size_t fl_orig,  std::integral_constant<r_m, r_m::ceil>, std::false_type)
{
	return (val < 0)
			?
				(val>>(fl-fl_orig)) //negative value
			:
				(val>>(fl-fl_orig)) + (val&mask<I>(fl_orig-fl) != 0 ? 1 : 0);
}

template<typename I>
constexpr I r_f(I val, std::size_t fl, std::size_t fl_orig,  std::integral_constant<r_m, r_m::round>, std::false_type)
{
	return val>>(fl-fl_orig) + 	(val >>(fl_orig-fl-1) & 0b01);
}


template<std::size_t fl, rounding_mode r_mode>
struct rounding_delegate
{
	template<typename T>
	constexpr static T round_flt(T val)
	{
		return r_f(val, fl, std::integral_constant<r_m, r_mode>(), std::true_type());
	}
	template<typename I>
	constexpr static I round_fp(I val, const std::size_t &fl_orig)
	{
		return (fl_orig > fl) ?
					r_f(val, fl, fl_orig, std::integral_constant<r_m, r_mode>(), std::false_type())
					:
					(val << (fl-fl_orig));
	}
};



#undef r_m
#undef r_f
#undef mask
}
#endif /* ROUNDING_H_ */
