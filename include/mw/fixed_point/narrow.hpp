/*
 * Narrow.h
 *
 *  Created on: 25.10.2013
 *      Author: user
 */

#ifndef NARROW_H_
#define NARROW_H_

#include <cstdint>
#include <type_traits>
#include <limits>

#include "TypeHelper.h"
#include "FixedPoint.h"

namespace mw
{

namespace fixed_point
{


template<typename sign_l, typename sign_r, bool sign_change>
struct sign_narrow
{
	typedef std::true_type type;
	constexpr static bool value = true;
};

template<typename sign_l, bool sign_change>
struct sign_narrow<sign_l, signed, sign_change>
{
	typedef std::false_type type;
	constexpr static bool value = false;
};

template<typename sign_l, typename sign_r>
struct sign_narrow<sign_l, sign_r, true>
{
	typedef std::false_type type;
	constexpr static bool value = false;
};

template<	long wl_l, long fl_l, typename sign_l, rounding_mode mode_l,
			long wl_r, long fl_r, typename sign_r, rounding_mode mode_r,
			bool sign_change>
struct is_narrow
{
	typedef typename std::enable_if<
				(wl_l < wl_r) &&
				(fl_l < fl_r) &&
				sign_narrow<sign_l, sign_r, sign_change>::value,

				fp_t<wl_r, fl_r, sign_r, mode_r>
			>::type type;
};



template<	long wl_l, long fl_l, typename sign_l, rounding_mode mode_l,
			long wl_r, long fl_r, typename sign_r, rounding_mode mode_r,
			bool sign_change>
struct is_not_narrow
{
	typedef typename std::enable_if<
				!(wl_l < wl_r) ||
				!(fl_l < fl_r) ||
				!sign_narrow<sign_l, sign_r, sign_change>::value,
				fp_t<wl_r, fl_r, sign_r, mode_r>
		>::type type;
};

///FixedPoint gedöns

template<long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc,
			narrow fp_convs = narrow::imp_all, bool sign_change = false>
struct fp_fp_convs : fp_base_t<wl, fl, _sign_t, r_mode>
{
	using fp_base_t<wl, fl, _sign_t, r_mode>::fp_base_t;
	using fp_base_t<wl, fl, _sign_t, r_mode>::operator=;

};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, bool sign_change>
struct fp_fp_convs<wl, fl, _sign_t, r_mode, narrow::delete_all , sign_change> : fp_base_t<wl, fl, _sign_t, r_mode>
{

	using fp_base_t<wl, fl, _sign_t, r_mode>::fp_base_t;
	using fp_base_t<wl, fl, _sign_t, r_mode>::operator=;

	template<long wl_r, long fl_r, typename _sign_t_r, rounding_mode r_mode_r>
	operator fp_base_t<wl_r, fl_r, _sign_t, 	r_mode> () = delete;
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, bool sign_change>
struct fp_fp_convs<wl, fl, _sign_t, r_mode, narrow::imp_all , sign_change> : fp_base_t<wl, fl, _sign_t, r_mode>
{
	using fp_base_t<wl, fl, _sign_t, r_mode>::fp_base_t;
	using fp_base_t<wl, fl, _sign_t, r_mode>::operator=;


	template<long wl_r, long fl_r, typename _sign_t_r, rounding_mode r_mode_r>
	operator fp_t<wl_r, fl_r, _sign_t_r, 	r_mode_r> () const
	{
		return this->fp_base_t<wl,fl,_sign_t, r_mode>::
					get_fp(fp_t<wl_r, fl_r, _sign_t_r, r_mode_r>());
	};
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, bool sign_change>
struct fp_fp_convs<wl, fl, _sign_t, r_mode, narrow::delete_narrow , sign_change> : fp_base_t<wl, fl, _sign_t, r_mode>
{
	using fp_base_t<wl, fl, _sign_t, r_mode>::fp_base_t;
	using fp_base_t<wl, fl, _sign_t, r_mode>::operator=;


	template<long wl_r, long fl_r, typename _sign_t_r, rounding_mode r_mode_r>
	operator typename
	is_not_narrow<wl, fl, _sign_t, r_mode, wl_r, fl_r, _sign_t_r, r_mode_r, sign_change>::type () const
	{
		return this->fp_base_t<wl,fl,_sign_t, r_mode>::
					get_fp(fp_t<wl_r, fl_r, _sign_t_r, r_mode_r>());
	};
	template<long wl_r, long fl_r, typename _sign_t_r, rounding_mode r_mode_r>
	operator typename
	is_narrow<wl, fl, _sign_t, r_mode, wl_r, fl_r, _sign_t_r, r_mode_r, sign_change>::type () = delete;
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, bool sign_change>
struct fp_fp_convs<wl, fl, _sign_t, r_mode, narrow::imp_only_not , sign_change> : fp_base_t<wl, fl, _sign_t, r_mode>
{
	using fp_base_t<wl, fl, _sign_t, r_mode>::fp_base_t;
	using fp_base_t<wl, fl, _sign_t, r_mode>::operator=;


	template<long wl_r, long fl_r, typename _sign_t_r, rounding_mode r_mode_r>
	operator typename
	is_not_narrow<wl, fl, _sign_t, r_mode, wl_r, fl_r, _sign_t_r, r_mode_r, sign_change>::type () const
	{
		return this->fp_base_t<wl,fl,_sign_t, r_mode>::
					get_fp(fp_t<wl_r, fl_r, _sign_t_r, r_mode_r>());
	};
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs = narrow::imp_none, bool sign_change = false, narrow flt_convs = narrow::imp_none, typename inc = void>
struct fp_flt_conv : fp_fp_convs<wl, fl, _sign_t, r_mode>
{
	using fp_fp_convs<wl, fl, _sign_t, r_mode>::fp_fp_convs;
	using fp_fp_convs<wl, fl, _sign_t, r_mode>::operator=;
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::delete_all, void> : fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>
{
	using fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>::fp_fp_convs;
	using fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>::operator=;

	operator float 	() const = delete;
	operator double () const = delete;
	operator long double () const = delete;
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_all, void> : fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>
{
	operator float 	() const {return this->fp_fp_convs<wl, fl, _sign_t, r_mode>::get_floating(float());};
	operator double () const {return this->fp_fp_convs<wl, fl, _sign_t, r_mode>::get_floating(double());};
	typedef long double ld;
	operator ld () {return this->fp_fp_convs<wl, fl, _sign_t, r_mode>::get_floating(ld());};

	using fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>::fp_fp_convs;
	using fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>::operator=;
};


template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct 	fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::delete_narrow, void> :
		fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<float>::digits) ? narrow::delete_narrow : narrow::imp_only_not, double>
{
	using fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<float>::digits) ? narrow::delete_narrow : narrow::imp_only_not, double>::fp_flt_conv;
	using fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<float>::digits) ? narrow::delete_narrow : narrow::imp_only_not, double>::operator=;
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct 	fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::delete_narrow, float> :
		fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<double>::digits) ? narrow::delete_narrow : narrow::imp_only_not, double>
{
	using fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<double>::digits) ? narrow::delete_narrow : narrow::imp_only_not, double>::fp_flt_conv;
	using fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<double>::digits) ? narrow::delete_narrow : narrow::imp_only_not, double>::operator=;


	operator typename std::enable_if< (wl<=std::numeric_limits<float>::digits),	float>::type () = delete;
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct 	fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::delete_narrow, double> :
		fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<long double>::digits) ? narrow::delete_narrow : narrow::imp_only_not, long double>
{
	using fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<long double>::digits) ? narrow::delete_narrow : narrow::imp_only_not, long double>::fp_flt_convs;
	using fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change,
			(wl<=std::numeric_limits<long double>::digits) ? narrow::delete_narrow : narrow::imp_only_not, long double>::operator=;

	operator typename std::enable_if< (wl<=std::numeric_limits<double>::digits),	double>::type () = delete;
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct 	fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::delete_narrow, long double> : fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>
{
	using fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>::fp_fp_convs;
	using fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>::fp_fp_convs::operator=;

	operator typename std::enable_if< (wl<=std::numeric_limits<long double>::digits), long double>::type () = delete;
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct 	fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, float> :
		fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, double>
{
	using fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, double>::fp_flt_conv;
	using fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, double>::operator=;

	operator typename std::enable_if< (wl>=std::numeric_limits<float>::digits),	float>::type ()
	{
		return this->fp_fp_convs<wl, fl, _sign_t, r_mode>::get_floating(float());
	}
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct 	fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, double> :
		fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, long double>
{
	using fp_flt_conv<wl,fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, long double>::fp_flt_conv;
	using fp_flt_conv<wl,fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, long double>::operator=;


	operator typename std::enable_if< (wl>=std::numeric_limits<double>::digits),	double>::type ()
				{return this->fp_fp_convs<wl, fl, _sign_t, r_mode>::get_floating(double());};
};

template<long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs, bool sign_change>
struct 	fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, narrow::imp_only_not, long double> : fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>
{
	using fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>::fp_fp_convs;
	using fp_fp_convs<wl, fl, _sign_t, r_mode, fp_convs, sign_change>::operator=;


	operator typename std::enable_if< (wl<=std::numeric_limits<long double>::digits), long double>::type ()
	{
		using ld = long double;
		return this->fp_fp_convs<wl, fl, _sign_t, r_mode>::get_floating(ld());
	};
};

template<	long wl, long fl, typename _sign_t, rounding_mode r_mode, narrow fp_convs = narrow::imp_none,
			bool sign_change = false, narrow flt_convs = narrow::imp_only_not, narrow int_convs = narrow::delete_all>
struct fp_int_conv : fp_flt_conv<wl, fl, _sign_t, r_mode, fp_convs, sign_change, flt_convs>
{
	using fp_flt_conv<wl,fl, _sign_t, r_mode, fp_convs, sign_change, flt_convs>::fp_flt_conv;
	using fp_flt_conv<wl,fl, _sign_t, r_mode, fp_convs, sign_change, flt_convs>::operator=;

	template<typename T>
	operator typename std::enable_if<std::is_integral<T>::value,T>::type () = delete;

};


}
}
#endif /* NARROW_H_ */
