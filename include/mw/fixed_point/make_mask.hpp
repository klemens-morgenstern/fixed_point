/*
 * make_mask.hpp
 *
 *  Created on: 16.10.2015
 *      Author: Klemens
 */

#ifndef MW_FIXED_POINT_MAKE_MASK_HPP_
#define MW_FIXED_POINT_MAKE_MASK_HPP_

#include <mw/fixed_point/type_helper.hpp>

namespace mw
{
namespace fixed_point
{
namespace detail
{
template<typename T>
constexpr T make_mask_impl(T in, T cnt)
{
	return (cnt == in) ? 0 :
			(T(1) << cnt)
			| make_mask_impl<T>(in, cnt+1);
}
}

template<typename T>
constexpr T make_mask(T in)
{
	//limit in to be sizeof(t) * 8
	using Int = detail::to_unsigned_t<T> ;
	return detail::make_mask_impl<Int>(
			(static_cast<Int>(in) > (sizeof(T)<< 3)) ? //to large for type?
					(sizeof(T)<<3) // limit
					: static_cast<Int>(in), //pass in
					  0u);
}
}
}



#endif /* MW_FIXED_POINT_MAKE_MASK_HPP_ */
