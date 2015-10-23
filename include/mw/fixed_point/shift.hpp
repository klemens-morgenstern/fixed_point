/*
 * shift.hpp
 *
 *  Created on: 22.10.2015
 *      Author: klemens.morgenstern
 */

#ifndef MW_FIXED_POINT_SHIFT_HPP_
#define MW_FIXED_POINT_SHIFT_HPP_


#include <type_traits>
#include <mw/fixed_point/fixed_point.hpp>


namespace mw {
namespace fixed_point {


template<unsigned I> std::integral_constant<unsigned, I> c;

template<long wl, long fl, typename _sign_t, rounding_mode rm, unsigned shift>
constexpr fp_t<wl, fl+shift, _sign_t, rm> operator<<(fp_t<wl, fl, _sign_t, rm> fp,  std::integral_constant<unsigned, shift>)
{
	return fp.value();
}

template<long wl, long fl, typename _sign_t, rounding_mode rm, unsigned shift>
constexpr fp_t<wl, fl-shift, _sign_t, rm> operator<<(fp_t<wl, fl, _sign_t, rm> fp,  std::integral_constant<unsigned, shift>)
{
	return fp.value();
}



}}



#endif /* SHIFT_HPP_ */
