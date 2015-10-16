/*
 * is_fixed_point.hpp
 *
 *  Created on: 16.10.2015
 *      Author: Klemens
 */

#ifndef MW_FIXED_POINT_IS_FIXED_POINT_HPP_
#define MW_FIXED_POINT_IS_FIXED_POINT_HPP_

#include <type_traits>

namespace mw
{
namespace fixed_point
{
template<long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc>
struct fp_t;

template<typename T>
struct is_fixed_point : std::false_type {};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode>
struct is_fixed_point<fp_t<wl, fl, _sign_t, r_mode>> : std::true_type {};

}

using fixed_point::is_fixed_point;

}



#endif /* MW_FIXED_POINT_IS_FIXED_POINT_HPP_ */
