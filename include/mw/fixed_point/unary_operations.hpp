/*
 * unary_operations.hpp
 *
 *  Created on: 22.10.2015
 *      Author: klemens.morgenstern
 */

#ifndef MW_FIXED_POINT_UNARY_OPERATIONS_HPP_
#define MW_FIXED_POINT_UNARY_OPERATIONS_HPP_

#include <mw/fixed_point/fixed_point.hpp>

namespace mw
{
namespace fixed_point
{

template<long wl, long fl, typename sign, rounding_mode r_mode>
constexpr fp_t<wl, fl, sign, r_mode> operator+(fp_t<wl, fl, sign, r_mode> fp) {return fp;}

template<long wl, long fl, rounding_mode r_mode>
constexpr fp_t<wl, fl, signed, r_mode> operator-(fp_t<wl, fl, signed, r_mode> fp)
{
	return -fp.value();
}

template<long wl, long fl, rounding_mode r_mode>
constexpr fp_t<wl+1, fl, signed, r_mode> operator-(fp_t<wl, fl, unsigned, r_mode> fp)
{
	typedef typename fp_t<wl+1, fl, signed, r_mode>::int_type int_type;
	return -static_cast<int_type>(fp.value());
}



}
}



#endif /* UNARY_OPERATIONS_HPP_ */
