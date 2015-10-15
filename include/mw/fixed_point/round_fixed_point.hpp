/*
 * round_fp.hpp
 *
 *  Created on: 15.10.2015
 *      Author: klemens.morgenstern
 */

#ifndef ROUND_FP_HPP_
#define ROUND_FP_HPP_

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
 *
 */

template<long wl, long fl, typename sign, rounding_mode rm>
constexpr fp_t<wl, fl, sign, rm> round(fp_t<wl, fl, sign, rm> in)
{
	/*return in.negative() ?
			in.value()
			:
			;*/
}



}}




#endif /* ROUND_FP_HPP_ */
