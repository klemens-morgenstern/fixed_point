/**
 * \file fp_t.h
 * Contains the classes \ref fp_t, which is not yet completed, since it has no calculation operators yet.
 *
 * \author Klemens D. Morgenstern
 *
 */

#ifndef MW_FIXED_POINT_FIXED_POINT_H_
#define MW_FIXED_POINT_FIXED_POINT_H_

#include <cmath>
#include <iostream>
#include <istream>
#include <type_traits>
#include <mw/fixed_point/type_helper.hpp>
#include <mw/fixed_point/rounding.hpp>

namespace mw {

namespace fixed_point {

namespace detail
{
constexpr unsigned long construct_mask(std::size_t i) {return (i>=1L) ? (construct_mask(i-1)|static_cast<std::size_t>(1<<i)) : 0b1;};
}
///Template for conversion of signed (two's complement) fixed-points. WordLength == full word length
/** This class allows you to store a fp_t value and convert them to double. For later use it will be
 * enhanced with mathematical operator, but since this application doesn't need them, they are not yet implemented.
 * If you cast this class to a double (can be don implicitly) you will automaticly get the converted value as floating point.
 * If you cast to long (also usigned, and implicit) you will get the digit. It works the other way round for the assignment or constructors.
 */
template<long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc>
struct fp_t
{
	static_assert(wl > 0, "Word lenght must be positive");
	typedef typename types<wl, _sign_t>::type int_type;
	typedef typename types<wl, _sign_t>::min_float_t float_t;
	typedef _sign_t sign_t;
	constexpr static bool is_signed = std::is_signed<sign_t>::value;
	constexpr static long word_length 	  = wl;
	constexpr static long fraction_length = fl;
	constexpr static rounding_mode round_mode = r_mode;
	constexpr static int_type mask = detail::construct_mask(wl);
	constexpr static int_type sign_pos = is_signed ? (1<<(wl-1)) : 0;

	///The factor is the one in the fixed-point notation
	static constexpr float_t factor = (1<<fl);
private:
	///Value stored
	int_type _value;
    typedef fp_t<wl, fl, sign_t, r_mode> type;
public:
    int_type value() const {return _value;}
    constexpr static int_type max_i = std::is_signed<_sign_t>::value ? (detail::construct_mask(wl-1)) : mask;
	constexpr static int_type min_i = std::is_signed<_sign_t>::value ? (~detail::construct_mask(wl-1)) : 0;

	constexpr static fp_t max = fp_t(max_i);
	constexpr static fp_t min = fp_t(min_i);

	constexpr static float_t max_f = (float_t)max_i / (float_t)factor;
	constexpr static float_t min_f = (float_t)min_i / (float_t)factor;

	constexpr fp_t () noexcept = default;
	constexpr fp_t (const fp_t&) noexcept = default;
	constexpr fp_t (fp_t&&) noexcept = default;

	constexpr fp_t operator=(const fp_t&) noexcept = default;
	constexpr fp_t operator=(fp_t&&) noexcept = default;


/***********************************//* Constructor *//****************************************/
	///Construct from a floating point smaller then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsFloat = std::enable_if_t<std::is_floating_point<T>::value>,
			 typename Narrowing = std::enable_if_t<sizeof(float_t)>=T>>
	constexpr fp_t(T flt) noexcept
			: _value(static_cast<int_type>(flt/factor) & mask) {}

	///Construct from a floating point larg then the needed one of this fixed point. Explicit, because it's mangling
	template<typename T,
			 typename IsFloat = std::enable_if_t<std::is_floating_point<T>::value>,
			 typename Narrowing = std::enable_if_t<sizeof(float_t)>=T>,
			 typename = void> //because i cannot overload elsewise
	explicit constexpr fp_t(T flt) noexcept
		: _value(static_cast<int_type>(flt/factor) & mask) {}

	///Construct from a integral smaller then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsInt = std::enable_if_t<std::is_integral<T>::value>,
			 typename Narrowing = std::enable_if_t<sizeof(float_t)>=T>,
			 typename = void, typename = void>
	constexpr fp_t(T _int) noexcept
		: _value(_int & mask) {}

	///Construct from a integral lard then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsInt = std::enable_if_t<std::is_integral<T>::value>,
			 typename Narrowing = std::enable_if_t<sizeof(float_t)>=T>,
			 typename = void,
			 typename = void,
			 typename = void>
	explicit constexpr fp_t(T _int) noexcept
		: _value(_int & mask) {}


	template<long wl_in,
			 long fl_in,
			 typename _sign_t_in,
			 rounding_mode r_mode_in,
			 typename Narrowing = std::enable_if_t<
			 	 (fl_in >= fl) &&
				 (wl_in >= wl) &&
				 ((wl-fl) >= (wl_in-fl_in))>,
			 typename = void,
			 typename = void>
	constexpr fp_t(fp_t<wl_in, fl_in, _sign_t_in, r_mode_in> in) noexcept
		: _value(((fl > fl_in) ? in.value() << (fl-fl_in) : in.value()) & mask) { }

	template<long wl_in,
			 long fl_in,
			 typename _sign_t_in,
			 rounding_mode r_mode_in,
			 typename Narrowing = std::enable_if_t<
			 	 (fl_in < fl) ||
				 (wl_in < wl) ||
				 ((wl-fl) < (wl_in-fl_in))>,
			 typename = void,
			 typename = void,
			 typename = void>
	explicit constexpr fp_t(fp_t<wl_in, fl_in, _sign_t_in, r_mode_in> in) noexcept
		: _value(
				((fl > fl_in) ?
						in.value() << (fl - fl_in)
						: (fl < fl_in) ?
						in.value() >> (fl_in - fl)
						: in.value()
						) & mask) { }




};
}
}
#endif /* fp_t_H_ */
