/*
 * Literals.h
 *
 *  Created on: 29.11.2013
 *      Author: klemens.morgenstern
 */


#ifndef LITERALS_H_
#define LITERALS_H_

#include "Narrow.h"
#include "fp.h"

namespace fixed_point
{

#define generate_literal_int(wl, fl) constexpr inline fp_t<wl,fl> operator"" _fp_##wl##_##fl (unsigned long long val) 	{return fp_t<wl,fl>(val);}
#define generate_literal_flt(wl, fl) constexpr inline fp_t<wl,fl> operator"" _fp_##wl##_##fl (long double val) 			{return fp_t<wl,fl>(val);}
#define generate_literal(wl,fl) \
		generate_literal_flt(wl,fl) \
		generate_literal_int(wl,fl)

#include "gen_help"

#undef generate_literal
#undef generate_literal_int
#undef generate_literal_flt

};

#endif /* LITERALS_H_ */
