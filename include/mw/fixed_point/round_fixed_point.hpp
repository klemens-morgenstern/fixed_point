/*
 * round_fp.hpp
 *
 *  Created on: 15.10.2015
 *      Author: klemens.morgenstern
 */

#ifndef MW_FIXED_POINT_ROUND_FIXED_POINT_HPP_
#define MW_FIXED_POINT_ROUND_FIXED_POINT_HPP_

#include <mw/fixed_point/rounding_mode.hpp>
#include <mw/fixed_point/make_mask.hpp>
#include <mw/fixed_point/type_helper.hpp>

namespace mw
{
namespace fixed_point
{


template<long wl, long fl, typename _sign_t, rounding_mode r_mode>
struct fp_t;


namespace detail
{


}

/** Ok, so here's how it works:
 *
 *  ### Positive number, wl=5, fl=3
 *
 *  01000 = 1.0 (8)
 *  00100 = 0.5 (4)
 *
 *  round the positive version:
 *  fl_bits = fraction bits
 *  @code
 *  if (fraction_bits & 0b100)
 *  {
 *  	value |= 0b111;
 *  	value++;
 *  }
 *  else
 *  {
 *  	value &= ~0b111;
 *  }
 *  @endcode
 *
 *  negative versino is a bit more tricky.
 *  if (fraction_bits > 0b100)
 *  {
 *  	value |= 0b111;
 *  	value++;
 *  }
 *  else
 *  {
 *  	value &= ~0b111;
 *  }
 *
 *  @tparam fl_to The fraction it should be rounded to.
 */

template<long wl, long fl, typename sign, rounding_mode rm, long fl_to = fl>
constexpr fp_t<wl, fl, sign, rm> round(fp_t<wl, fl, sign, rm> in)
{
	typedef typename fp_t<wl, fl_to, sign, rm>::int_type type;
	constexpr static type  first_frac = (1<<(fl_to-1));
	constexpr static type frac_mask = make_mask<type>(fl_to);

	return in.negative() ?
			(in.value() & frac_mask) >= first_frac ?
					(in.value() | frac_mask) + 1
					: (in.value() & ~frac_mask)
			:
			((in.value() & first_frac) ?
					(in.value() | frac_mask) +1
				:	(in.value() & ~frac_mask))
			;
}

template<long wl, long fl, typename sign, rounding_mode rm, long fl_to = fl>
constexpr fp_t<wl, fl, sign, rm> trunc(fp_t<wl, fl, sign, rm> in)
{
	typedef typename fp_t<wl, fl_to, sign, rm>::int_type type;
	constexpr static type frac_mask = make_mask<type>(fl_to);
	return in.negative() ?
			((in.value() & frac_mask) ?
					(in.value() | frac_mask) + 1
					: in.value())
			:
			(in.value() & frac_mask) ?
					(in.value() & ~frac_mask) + 1
					: in.value()
			;
}

template<long wl, long fl, typename sign, rounding_mode rm, long fl_to = fl>
constexpr fp_t<wl, fl, sign, rm> ceil(fp_t<wl, fl, sign, rm> in)
{
	typedef typename fp_t<wl, fl_to, sign, rm>::int_type type;
	constexpr static type frac_mask = make_mask<type>(fl_to);
	return 	((in.value() & frac_mask) ?
			  (in.value() | frac_mask) + 1
			: in.value())
			;
}

template<long wl, long fl, typename sign, rounding_mode rm, long fl_to = fl>
constexpr fp_t<wl, fl, sign, rm> floor(fp_t<wl, fl, sign, rm> in)
{
	typedef typename fp_t<wl, fl_to, sign, rm>::int_type type;
	constexpr static type frac_mask = make_mask<type>(fl_to);
	return 	((in.value() & frac_mask) ?
			  in.value() & ~frac_mask
			: in.value())
			;
}

}}




#endif /* ROUND_FP_HPP_ */
