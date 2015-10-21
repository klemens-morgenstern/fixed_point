/*
 * operations.hpp
 *
 *  Created on: 16.10.2015
 *      Author: Klemens
 */

#ifndef MW_FIXED_POINT_OPERATIONS_HPP_
#define MW_FIXED_POINT_OPERATIONS_HPP_

#include <mw/fixed_point/fixed_point.hpp>

namespace mw {
namespace fixed_point {
namespace detail {

template<typename Lhs, typename Rhs>
struct deduce_add_result {};

template<long wl_lhs, long fl_lhs, typename sign_lhs, rounding_mode r_mode_lhs,
		 long wl_rhs, long fl_rhs, typename sign_rhs, rounding_mode r_mode_rhs>
struct deduce_add_result<fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs> /*lhs*/,
						 fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs> /*rhs*/>
{
	typedef fp_t<(wl_lhs > wl_rhs ? wl_lhs : wl_rhs),
			(fl_lhs > fl_rhs ? fl_lhs : fl_rhs),
			std::conditional_t<(std::is_signed<sign_lhs>::value
			||std::is_signed<sign_rhs>::value), signed, unsigned>,
			r_mode_lhs != r_mode_rhs ? rounding_mode::round : r_mode_lhs>
			type;
};


template<typename Lhs, typename Rhs>
struct deduce_multiply_result {};

template<long wl_lhs, long fl_lhs, typename sign_lhs, rounding_mode r_mode_lhs,
		 long wl_rhs, long fl_rhs, typename sign_rhs, rounding_mode r_mode_rhs>
struct deduce_multiply_result<fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs> /*lhs*/,
						 	  fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs> /*rhs*/>
{
	typedef fp_t<wl_lhs + wl_rhs,
				 fl_lhs + fl_rhs,
			std::conditional_t<(std::is_signed<sign_lhs>::value
			|| std::is_signed<sign_rhs>::value), signed, unsigned>,
			r_mode_lhs != r_mode_rhs ? rounding_mode::round : r_mode_lhs>
			type;
};


template<typename Lhs, typename Rhs>
struct deduce_divide_result {};

template<long wl_lhs, long fl_lhs, typename sign_lhs, rounding_mode r_mode_lhs,
		 long wl_rhs, long fl_rhs, typename sign_rhs, rounding_mode r_mode_rhs>
struct deduce_divide_result<fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs> /*lhs*/,
						 	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs> /*rhs*/>
{
	typedef fp_t<wl_lhs + wl_rhs,
				 fl_lhs + (wl_rhs-fl_rhs), //hopefully that's right.
			std::conditional_t<(std::is_signed<sign_lhs>::value
			|| std::is_signed<sign_rhs>::value), signed, unsigned>,
			r_mode_lhs != r_mode_rhs ? rounding_mode::round : r_mode_lhs>
			type;
};



struct operations
{
	template<long wl_lhs, long fl_lhs, typename sign_lhs, rounding_mode r_mode_lhs,
			 long wl_rhs, long fl_rhs, typename sign_rhs, rounding_mode r_mode_rhs>
	constexpr auto add(fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs> lhs,
					   fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs> rhs) noexcept
		-> typename deduce_add_result<
					fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs>,
		   	   	   	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs>>::type
	{
		typedef typename deduce_add_result<
				fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs>,
	   	   	   	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs>>::type type;

		typedef typename type::int_type it;
		return type(static_cast<it>(lhs.value()) + static_cast<it>(rhs.value()));
	}

	template<long wl_lhs, long fl_lhs, typename sign_lhs, rounding_mode r_mode_lhs,
			 long wl_rhs, long fl_rhs, typename sign_rhs, rounding_mode r_mode_rhs>
	constexpr auto subtract(fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs> lhs,
					   	    fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs> rhs) noexcept
		-> typename deduce_add_result<
					fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs>,
		   	   	   	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs>>::type
	{
		typedef typename deduce_add_result<
				fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs>,
	   	   	   	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs>>::type type;

		typedef typename type::int_type it;
		return type(static_cast<it>(lhs.value()) - static_cast<it>(rhs.value()));
	}

	template<long wl_lhs, long fl_lhs, typename sign_lhs, rounding_mode r_mode_lhs,
			 long wl_rhs, long fl_rhs, typename sign_rhs, rounding_mode r_mode_rhs>
	constexpr auto multiply(fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs> lhs,
					   	    fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs> rhs) noexcept
		-> typename deduce_multiply_result<
					fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs>,
		   	   	   	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs>>::type
	{
		typedef typename deduce_multiply_result<
				fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs>,
	   	   	   	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs>>::type type;

		typedef typename type::int_type it;
		return type(static_cast<it>(lhs.value()) * static_cast<it>(rhs.value()));
	}

	template<long wl_lhs, long fl_lhs, typename sign_lhs, rounding_mode r_mode_lhs,
			 long wl_rhs, long fl_rhs, typename sign_rhs, rounding_mode r_mode_rhs>
	constexpr auto divide(fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs> lhs,
					   	    fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs> rhs) noexcept
		-> typename deduce_divide_result<
					fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs>,
		   	   	   	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs>>::type
	{
		typedef typename deduce_divide_result<
				fp_t<wl_lhs, fl_lhs, sign_lhs, r_mode_lhs>,
	   	   	   	fp_t<wl_rhs, fl_rhs, sign_rhs, r_mode_rhs>>::type type;
		//not yet implemented.
		typedef typename type::int_type it;
		return type(static_cast<it>(lhs.value()) * static_cast<it>(rhs.value()));
	}

};

}





}
}



#endif /* MW_FIXED_POINT_OPERATIONS_HPP_ */
