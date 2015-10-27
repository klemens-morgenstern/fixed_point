/**
 * @file   rouncing.hpp
 * @date   14.10.2015
 * @author Klemens
 *
 * Published under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0.html)
 */

#ifndef MW_FIXED_POINT_ROUND_DOUBLE_HPP_
#define MW_FIXED_POINT_ROUND_DOUBLE_HPP_

#include <mw/fixed_point/type_helper.hpp>

namespace mw
{
namespace fixed_point
{
namespace detail
{

template<typename T> struct select_int {};

template<> struct select_int<float> 	  {typedef int 			type;};
template<> struct select_int<double> 	  {typedef long 		type;};
template<> struct select_int<long double> {typedef long long 	type;};

#ifdef MW_FIXED_POINT_EXPERIMENTAL_BOOST_MULTIPRECISION
template<> struct select_int<float128> {typedef int128_t type;};
#endif



template<typename T>
using select_int_t = typename select_int<T>::type;

template<typename Flt>
constexpr Flt round_impl(Flt round_base, Flt factor, select_int_t<Flt> times)
{

	return 	(factor > 0) ?
			(((factor - static_cast<Flt>(times)) >= 0.5) ?
			static_cast<Flt>(times+1) * round_base
			: static_cast<Flt>(times) * round_base)
			  :
			(((factor - static_cast<Flt>(times)) <= -0.5) ?
			   static_cast<Flt>(times-1)  * round_base
			:  static_cast<Flt>(times)    * round_base)
			  ;
}
template<typename Flt>
constexpr Flt round_impl(Flt round_base, Flt factor)
{
	using Int = select_int_t<Flt>;
	return round_impl(round_base, factor, static_cast<Int>(factor));
}

template<typename Flt>
constexpr Flt round_impl(Flt value, select_int_t<Flt> i_value)
{

	return static_cast<Flt>((value > 0) ?
			(((value - static_cast<Flt>(i_value)) >= 0.5) ?
			   i_value + 1
			:  i_value)
			  :
			(((value - static_cast<Flt>(i_value)) <= -0.5) ?
			   i_value - 1
			:  i_value)
			  );
}

template<typename Flt>
constexpr Flt trunc_impl(Flt frac, select_int_t<Flt> i_fac)
{
	return i_fac * frac;
}
template<typename Flt>
constexpr Flt trunc_impl(Flt frac, Flt fac)
{
	using Int = select_int_t<Flt>;
	return trunc_impl(frac, static_cast<Int>(fac));
};


template<typename Flt>
constexpr Flt ceil_impl(Flt ceil_base, Flt factor, select_int_t<Flt> times)
{
	return 	(factor != static_cast<Flt>(times))  ?
			((factor > 0) ?
				static_cast<Flt>(times+1) * ceil_base
			: ( static_cast<Flt>(times)   * ceil_base))
			  : static_cast<Flt>(times)*ceil_base;
			  ;
}

template<typename Flt>
constexpr Flt ceil_impl(Flt ceil_base, Flt factor)
{
	using Int = select_int_t<Flt>;
	return ceil_impl(ceil_base, factor, static_cast<Int>(factor));
}

// simple impl
template<typename Flt>
constexpr Flt ceil_impl(Flt value, select_int_t<Flt> i_value)
{

	return (value != static_cast<Flt>(i_value)) ?
			((value > 0) ?
			 i_value+1
			 : i_value) : i_value;
}


template<typename Flt>
constexpr Flt floor_impl(Flt floor_base, Flt factor, select_int_t<Flt> times)
{

	return 	(factor != static_cast<Flt>(times)) ?
			((factor > 0) ?
			static_cast<Flt>(times) * floor_base
			: static_cast<Flt>(times-1) * floor_base)
			  : static_cast<Flt>(times)*floor_base;
			  ;
}
template<typename Flt>
constexpr Flt floor_impl(Flt floor_base, Flt factor)
{
	using Int = select_int_t<Flt>;
	return floor_impl(floor_base, factor, static_cast<Int>(factor));
}

// simple impl
template<typename Flt>
constexpr Flt floor_impl(Flt value, select_int_t<Flt> i_value)
{

	return (value != i_value) ?
			((value > 0) ?
			 i_value
			 : i_value-1) : i_value;
}
}


constexpr float round(float value, float frac) 		{	return detail::round_impl(frac, value/frac);}
constexpr float round(float value)					{	return detail::round_impl(value, static_cast<int>(value)); }

constexpr double round(double value, double frac) 	{	return detail::round_impl(frac, value/frac);}
constexpr double round(double value)				{	return detail::round_impl(value, static_cast<long>(value)); }

constexpr long double round(long double value, long double frac) {	return detail::round_impl(frac, value/frac);}
constexpr long double round(long double value)					{	return detail::round_impl(value, static_cast<long long>(value)); }




constexpr float trunc(float value, float frac) 		{	return detail::trunc_impl(frac, value/frac);}
constexpr float trunc(float value)					{	return static_cast<int>(value); }

constexpr double trunc(double value, double frac) 	{	return detail::trunc_impl(frac, value/frac);}
constexpr double trunc(double value)				{	return static_cast<long>(value); }

constexpr long double trunc(long double value, long double frac) {	return detail::trunc_impl(frac, value/frac);}
constexpr long double trunc(long double value)					{	return static_cast<long long>(value); }




constexpr float ceil(float value, float frac) 		{	return detail::ceil_impl(frac, value/frac);}
constexpr float ceil(float value)					{	return detail::ceil_impl(value, static_cast<int>(value)); }

constexpr double ceil(double value, double frac) 	{	return detail::ceil_impl(frac, value/frac);}
constexpr double ceil(double value)					{	return detail::ceil_impl(value, static_cast<long>(value)); }

constexpr long double ceil(long double value, long double frac)  {	return detail::ceil_impl(frac, value/frac);}
constexpr long double ceil(long double value)					{	return detail::ceil_impl(value, static_cast<long long>(value)); }


constexpr float floor(float value, float frac) 	{	return detail::floor_impl(frac, value/frac);}
constexpr float floor(float value)					{	return detail::floor_impl(value, static_cast<int>(value)); }

constexpr double floor(double value, double frac) 	{	return detail::floor_impl(frac, value/frac);}
constexpr double floor(double value)				{	return detail::floor_impl(value, static_cast<long>(value)); }

constexpr long double floor(long double value, long double frac) {	return detail::floor_impl(frac, value/frac);}
constexpr long double floor(long double value)					{	return detail::floor_impl(value, static_cast<long long>(value)); }



}
}


#endif /* ROUNDING_HPP_ */
