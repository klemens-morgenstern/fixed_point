/*
 * fp.h
 *
 *  Created on: 02.12.2013
 *      Author: klemens.morgenstern
 */

#ifndef FP_H_
#define FP_H_

#include "narrow.h"

namespace fixed_point
{
	/*template<	long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc, narrow fp_convs = narrow::imp_none,
				bool sign_change = false, narrow flt_convs = narrow::imp_only_not, narrow int_convs = narrow::delete_all>
	struct fp*/
template<	long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs,
				bool sign_change, narrow flt_convs, narrow int_convs>
	struct fp	: fp_int_conv<wl,fl, _sign_t, r_mode, fp_convs, sign_change, flt_convs, int_convs>
	{
		using fp_int_conv<wl,fl, _sign_t, r_mode, fp_convs, sign_change, flt_convs, int_convs>::fp_int_conv;
		using fp_int_conv<wl,fl, _sign_t, r_mode, fp_convs, sign_change, flt_convs, int_convs>::operator=;

		template<long wl2, long fl2, typename _sign_t2, rounding_mode r_mode2, narrow fp_convs2,
						bool sign_change2, narrow flt_convs2, narrow int_convs2>
		constexpr fp(const fp<wl2, fl2, _sign_t2, r_mode2, fp_convs2, sign_change2, flt_convs2,  int_convs2> &fp) : fp(fp.get_fp(fp())) {};

		fp() = default;
		fp(const fp &) = default;
		fp& operator= (const fp& ) = default;
	};
}


#endif /* FP_H_ */
