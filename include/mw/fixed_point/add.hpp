/**
 * add.hpp
 *
 *  Created on: 22.10.2015
 *      Author: klemens.morgenstern
 */

#ifndef MW_FIXED_POINT_ADD_HPP_
#define MW_FIXED_POINT_ADD_HPP_

#include <mw/fixed_point/rounding_mode.hpp>
#include <mw/fixed_point/fixed_point.hpp>
#include <type_traits>

namespace mw
{
namespace fixed_point
{
namespace detail
{

template<typename L, typename R>
struct add_result {};

template<long Wl_l, long Fl_l, typename Sign_l, rounding_mode Rm_l,
		 long Wl_r, long Fl_r, typename Sign_r, rounding_mode Rm_r>
struct add_result<fp_t<Wl_r, Fl_r, Sign_r, Rm_r>,
				  fp_t<Wl_l, Fl_l, Sign_l, Rm_l>>
{
	constexpr static bool is_signed = std::is_signed<Sign_l>::value || is_signed<Sign_r>::value;
	constexpr static long int_l = ((is_signed && !std::is_signed<sign_l>::value) ? Wl_l + 1 : Wl_l) - Fl_l;
	constexpr static long int_r = ((is_signed && !std::is_signed<sign_r>::value) ? Wl_r + 1 : Wl_r) - Fl_r;
	constexpr static long int_res = (int_l > int_r ? int_l : int_r) + 1;

	constexpr static long fl_res = (Fl_l > Fl_r) ? Fl_l : Fl_r;

	constexpr static long wl_res = int_res + fl_res;

	using sign_res =  std::conditional_t<is_signed, signed, unsigned>;

	constexpr static rounding_mode rm_res = Rm_l == Rm_r ? Rm_l : rounding_mode::round;

	using type = fp_t<wl_res, fl_res, sign_res, rm_res>;

};



template<typename L, typename R>
using add_result_t = typename add_result<L, R>::type;


template<long Wl, long Fl, typename Sign, rounding_mode Rm>
constexpr fp_t<Wl, Fl, Sign, Rm> add(fp_t<Wl, Fl, Sign, Rm> lhs, fp_t<Wl, Fl, Sign, Rm> rhs)
{
	return lhs.value() + rhs.value() ;
}


}

template<long Wl_l, long Fl_l, typename Sign_l, rounding_mode Rm_l,
		 long Wl_r, long Fl_r, typename Sign_r, rounding_mode Rm_r>
constexpr auto operator+(fp_t<Wl_l, Fl_l, Sign_l, Rm_l> lhs, fp_t<Wl_r, Fl_r, Sign_r, Rm_r> rhs)
		-> add_result_t<fp_t<Wl_l, Fl_l, Sign_l, Rm_l>, fp_t<Wl_r, Fl_r, Sign_r, Rm_r>>
{
	using type = add_result_t<fp_t<Wl_l, Fl_l, Sign_l, Rm_l>, fp_t<Wl_r, Fl_r, Sign_r, Rm_r>>;

	return detail::add<
				type::wl_res,
				type::fl_res,
				typename type::sign_res,
				type::rm_res>
			(lhs, rhs);
}


}
}



#endif /* ADD_HPP_ */
