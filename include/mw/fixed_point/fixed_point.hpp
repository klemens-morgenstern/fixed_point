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
struct operations;

}
///Template for conversion of signed (two's complement) fixed-points. WordLength == full word length
/** This class allows you to store a fp_t value and convert them to double. For later use it will be
 * enhanced with mathematical operator, but since this application doesn't need them, they are not yet implemented.
 * If you cast this class to a double (can be don implicitly) you will automaticly get the converted value as floating point.
 * If you cast to long (also usigned, and implicit) you will get the digit. It works the other way round for the assignment or constructors.
 */
template<long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc>
struct fp_t final
{
	static_assert(wl > 0, "Word lenght must be positive");
	typedef typename types<wl, _sign_t>::type int_type;
	typedef typename types<wl, _sign_t>::min_float_t float_type;
	typedef _sign_t sign_t;
	constexpr static bool is_signed = std::is_signed<sign_t>::value;
	constexpr static long word_length 	  = wl;
	constexpr static long fraction_length = fl;
	constexpr static rounding_mode round_mode = r_mode;
	constexpr static int_type mask = detail::construct_mask(wl);
	constexpr static int_type sign_bit = is_signed ? (1<<(wl-1)) : 0;

	///The factor is the one in the fixed-point notation
	static constexpr float_type factor = (1<<fl);
private:
	///Value stored
	int_type _value;
    typedef fp_t<wl, fl, sign_t, r_mode> type;
public:
    constexpr int_type   value() const {return _value;}
    constexpr bool is_negative() const {return _value & sign_bit;};
    constexpr static int_type max_i = std::is_signed<_sign_t>::value ? (detail::construct_mask(wl-1)) : mask;
	constexpr static int_type min_i = std::is_signed<_sign_t>::value ? (~detail::construct_mask(wl-1)) : 0;

	constexpr static fp_t max = fp_t(max_i);
	constexpr static fp_t min = fp_t(min_i);

	constexpr static float_type max_f = (float_type)max_i / (float_type)factor;
	constexpr static float_type min_f = (float_type)min_i / (float_type)factor;

	constexpr fp_t () noexcept = default;
	constexpr fp_t (const fp_t&) noexcept = default;
	constexpr fp_t (fp_t&&) noexcept = default;

	constexpr fp_t operator=(const fp_t&) noexcept = default;
	constexpr fp_t operator=(fp_t&&) noexcept = default;


/***********************************//* Constructor *//****************************************/
	///Construct from a floating point smaller then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsFloat = std::enable_if_t<std::is_floating_point<T>::value>,
			 typename NotNarrowing = std::enable_if_t<(sizeof(float_type)>=sizeof(T))>>
	constexpr fp_t(T flt) noexcept
			: _value(static_cast<int_type>(flt/factor) & mask) {}

	///Construct from a floating point larg then the needed one of this fixed point. Explicit, because it's mangling
	template<typename T,
			 typename IsFloat = std::enable_if_t<std::is_floating_point<T>::value>,
			 typename Narrowing = std::enable_if_t<(sizeof(float_type)>=sizeof(T))>,
			 typename = void> //because i cannot overload elsewise
	explicit constexpr fp_t(T flt) noexcept
		: _value(static_cast<int_type>(flt/factor) & mask) {}

	///Construct from a integral smaller then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsInt = std::enable_if_t<std::is_integral<T>::value>,
			 typename NotNarrowing = std::enable_if_t<(sizeof(float_type)>=sizeof(T))
			 && (is_signed ? std::is_signed<T>::value : true)>,
			 typename = void, typename = void>
	constexpr fp_t(T _int) noexcept
		: _value(_int & mask) {}

	///Construct from a integral lard then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsInt = std::enable_if_t<std::is_integral<T>::value>,
			 typename Narrowing = std::enable_if_t<sizeof(float_type)>=sizeof(T)
			 || (is_signed ? std::is_unsigned<T>::value : false)>,
			 typename = void,
			 typename = void,
			 typename = void>
	explicit constexpr fp_t(T _int) noexcept
		: _value(_int & mask) {}


	template<long wl_in,
			 long fl_in,
			 typename _sign_t_in,
			 rounding_mode r_mode_in,
			 typename NotNarrowing = std::enable_if_t<
			 	 (fl_in >= fl) &&
				 (wl_in >= wl) &&
				 ((wl-fl) >= (wl_in-fl_in)) &&
				 && (is_signed ? std::is_signed<_sign_t_in>::value : true)>,
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
				 ((wl-fl) < (wl_in-fl_in)) ||
				 && (is_signed ? std::is_unsigned<_sign_t_in>::value : false)>,
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

/***********************************//* Cast-Operator *//****************************************/
	///Cast to a same of larger float type
	template<typename T,
			 typename IsFloat = std::enable_if_t<std::is_floating_point<T>::value>,
			 typename NotNarrowing = std::enable_if_t<sizeof(float_type)<=sizeof(T)>>
	constexpr operator T() noexcept
	{
		return static_cast<T>(_value) / factor;
	}

	///Cast to a same of smaller float type
	template<typename T,
			 typename IsFloat = std::enable_if_t<std::is_floating_point<T>::value>,
			 typename Narrowing = std::enable_if_t<(sizeof(float_type)>sizeof(T))>,
			 typename = void>
	constexpr explicit operator T() noexcept
	{
		return static_cast<T>(_value) / factor;
	}

	///Cast to a same of larger int type
	template<typename T,
			 typename IsInt = std::enable_if_t<std::is_integral<T>::value>,
			 typename NotNarrowing = std::enable_if_t<(sizeof(float_type)<=sizeof(T))
			 	 	 	 	 && (is_signed ? std::is_signed<T>::value : true ) >,
			 typename = void,
			 typename = void>
	constexpr operator T() noexcept
	{
		return static_cast<T>(_value);
	}

	///Cast to a same of smaller int type
	template<typename T,
			 typename IsInt = std::enable_if_t<std::is_integral<T>::value>,
			 typename Narrowing = std::enable_if_t<(sizeof(float_type)>sizeof(T))
			 	 	 	 	 || (is_signed ? std::is_unsigned<T>::value : false)>,
			 typename = void,
			 typename = void,
			 typename = void>
	constexpr explicit operator T() noexcept
	{
		return static_cast<T>(_value);
	}

	//cast to larger fixed_point type
	template<long wl_out,
				 long fl_out,
				 typename _sign_t_out,
				 rounding_mode r_mode_out,
				 typename NotNarrowing = std::enable_if_t<
				 	 (fl_out <= fl) &&
					 (wl_out <= wl) &&
					 ((wl-fl) <= (wl_out-fl_out)) &&
					 && (is_signed ? std::is_signed<_sign_t_out>::value : true)>,
				 typename = void,
				 typename = void>
	constexpr operator fp_t<wl_out, fl_out, _sign_t_out, r_mode_out> () noexcept
	{
		return fl_out > fl ?
				_value << (fl_out - fl)
				: _value
				;
	}
	//cast to smaller fixed_point type.
	template<long wl_out,
			 long fl_out,
			 typename _sign_t_out,
			 rounding_mode r_mode_out,
			 typename Narrowing = std::enable_if_t<
				 (fl_out > fl) ||
				 (wl_out > wl) ||
				 ((wl-fl) > (wl_out-fl_out)) ||
				 && (is_signed ? std::is_unsigned<_sign_t_out>::value : false)>,
			 typename = void,
			 typename = void,
			 typename = void>
	explicit constexpr operator fp_t<wl_out, fl_out, _sign_t_out, r_mode_out> () noexcept
	{
		typedef typename fp_t<wl_out, fl_out, _sign_t_out, r_mode_out> ::type ret_type;
		return fl_out > fl ?
					fl_out < fl ?
					static_cast<ret_type>(_value) >> (fl-fl_out)
					: static_cast<ret_type>(_value)
				: 	static_cast<ret_type>(_value) << (fl_out - fl) ;
	}


	friend class operations;
};
}
}
#endif /* fp_t_H_ */
