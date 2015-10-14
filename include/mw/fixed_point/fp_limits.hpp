/*
 * fp_limits.h
 *
 *  Created on: 02.12.2013
 *      Author: klemens.morgenstern
 */

#ifndef FP_LIMITS_H_
#define FP_LIMITS_H_

#include <mw/fixed_point/fixed_point.hpp>
#include <limits>

namespace std
{

template<long wl, long fl, typename _sign_t, mw::fixed_point::rounding_mode r_mode, fixed_point::narrow fp_convs,
				bool sign_change, fixed_point::narrow flt_convs, fixed_point::narrow int_convs>
struct numeric_limits<fixed_point::fp_t<wl, fl, _sign_t, r_mode, fp_convs, sign_change, flt_convs, int_convs>>
{
	using _fp = fixed_point::fp_t<wl, fl, _sign_t, r_mode, fp_convs, sign_change, flt_convs, int_convs>;
	static constexpr bool is_specialized = true;

    static constexpr _fp min() noexcept { return _fp(_fp::min_i); }
    static constexpr _fp max() noexcept { return _fp(_fp::max_i); }



      static constexpr _fp lowest() noexcept { return min(); }


      static constexpr int digits = wl;
      static constexpr int digits10 = wl * log10(2);
      static constexpr int max_digits10 = 0;
      static constexpr bool is_signed = is_signed<_sign_t>::value;
      static constexpr bool is_integer 	 = false;
      static constexpr bool is_exact	 = false;
      static constexpr int radix = 2;

      static constexpr _fp epsilon() noexcept
    	{return 0;}

      static constexpr _fp round_error() noexcept
      {
    	  return (r_mode == fixed_point::rounding_mode::round) ? 0.5 : 1.0;
      }

      static constexpr int min_exponent = fl;
      static constexpr int min_exponent10 = fl*log10(2);
      static constexpr int max_exponent = fl;
      static constexpr int max_exponent10 = fl*log10(2);

      static constexpr bool has_infinity = false;
      static constexpr bool has_quiet_NaN = false;
      static constexpr bool has_signaling_NaN = false;
      static constexpr float_denorm_style has_denorm = denorm_absent;
      static constexpr bool has_denorm_loss = false;

      static constexpr _fp infinity() noexcept { return _fp(); }

      static constexpr _fp quiet_NaN() noexcept { return _fp(); }

      static constexpr _fp signaling_NaN() noexcept { return _fp(); }

      static constexpr char
      denorm_min() noexcept { return static_cast<char>(0); }

      static constexpr bool is_iec559 = false;
      static constexpr bool is_bounded = true;
      static constexpr bool is_modulo = false;

      static constexpr bool traps = true;
      static constexpr bool tinyness_before = false;
      static constexpr float_round_style round_style = (r_mode == fixed_point::rounding_mode::trunc) ? round_toward_zero
    		  	  	  	  	  	  	  	  	  	  	: (r_mode == fixed_point::rounding_mode::floor)  ? round_toward_neg_infinity
    		  	  	  	  	  	  	  	  	  	  	: (r_mode == fixed_point::rounding_mode::ceil)   ? round_toward_infinity
    		  	  	  	  	  	  	  	  	  	  	: (r_mode == fixed_point::rounding_mode::round)  ? round_to_nearest : round_indeterminate;

};

}



#endif /* FP_LIMITS_H_ */
