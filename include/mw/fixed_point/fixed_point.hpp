/**
 * \file fp.h
 * Contains the classes \ref fp, which is not yet completed, since it has no calculation operators yet.
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
#include <mw/fixed_point/make_mask.hpp>

namespace mw {

namespace fixed_point {

///Template for conversion of signed (two's complement) fixed-points. WordLength == full word length
/** This class allows you to store a fp value and convert them to double. For later use it will be
 * enhanced with mathematical operator, but since this application doesn't need them, they are not yet implemented.
 * If you cast this class to a double (can be don implicitly) you will automaticly get the converted value as floating point.
 * If you cast to long (also usigned, and implicit) you will get the digit. It works the other way round for the assignment or constructors.
 */
template<long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc>
struct fp final
{
	static_assert(wl > 0, "Word length must be positive");
	typedef typename detail::types<wl, _sign_t>::int_type 	  int_type;
	typedef typename detail::types<wl, _sign_t>::float_type float_type;
	typedef _sign_t sign_t;
	constexpr static bool is_signed = std::is_signed<sign_t>::value;
	constexpr static long word_length 	  = wl;
	constexpr static long fraction_length = fl;
	constexpr static rounding_mode round_mode = r_mode;
	constexpr static int_type mask = make_mask(wl);
	constexpr static int_type sign_bit = is_signed ? (1<<(wl-1)) : 0;

	///The factor is the one in the fixed-point notation
	static constexpr float_type factor = (1<<fl);
private:
	///Value stored
	int_type _value;
    typedef fp<wl, fl, sign_t, r_mode> type;
	constexpr static int_type adapt_int_impl(int_type it, std::true_type)
	{
		return (it & sign_bit) ?
				  static_cast<int_type>(~mask | it)
				: static_cast<int_type>( mask & it);
	}
	constexpr static int_type adapt_int_impl(int_type it, std::false_type)
	{
		return static_cast<int_type>(it & mask);
	}
public:

	template<typename in_type>
	constexpr static int_type adapt_int(in_type it)
	{
		return adapt_int_impl(it, std::integral_constant<bool, is_signed>());
	}

	template<typename Dbl> Dbl limit(Dbl value)
	{
		return (value > max_f) ? max_f : (value < min_f ? min_f : value);
	}

	constexpr static fp from_int(int_type it) { return it<<fl;}

    constexpr int_type   value() const {return _value;}
    constexpr bool is_negative() const {return _value & sign_bit;};
    constexpr static int_type max_i = std::is_signed<_sign_t>::value ? (make_mask(wl-1)) : mask;
	constexpr static int_type min_i = std::is_signed<_sign_t>::value ? (~make_mask(wl-1)) : 0;

	constexpr static fp max = fp(max_i);
	constexpr static fp min = fp(min_i);

	constexpr static float_type max_f = (float_type)max_i / (float_type)factor;
	constexpr static float_type min_f = (float_type)min_i / (float_type)factor;

	constexpr fp () noexcept = default;
	constexpr fp (const fp&) noexcept = default;
	constexpr fp (fp&&) noexcept = default;

	fp &operator=(const fp& rhs) noexcept {this->_value = rhs._value; return *this;}
	fp &operator=(fp&& rhs) 	 noexcept {this->_value = rhs._value; return *this;}


/***********************************//* Constructor *//****************************************/
	///Construct from a floating point smaller then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsFloat = std::enable_if_t<std::is_floating_point<T>::value>,
			 typename NotNarrowing = std::enable_if_t<(sizeof(float_type)>=sizeof(T))>>
	constexpr fp(T flt) noexcept
			: _value(static_cast<int_type>(limit(flt)/factor)) {}

	///Construct from a floating point larg then the needed one of this fixed point. Explicit, because it's mangling
	template<typename T,
			 typename IsFloat = std::enable_if_t<std::is_floating_point<T>::value>,
			 typename Narrowing = std::enable_if_t<(sizeof(float_type)<sizeof(T))>,
			 typename = void> //because i cannot overload elsewise
	explicit constexpr fp(T flt) noexcept
		: _value(static_cast<int_type>(limit(flt)/factor)) {}

	///Construct from a integral smaller then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsInt = std::enable_if_t<std::is_integral<T>::value>,
			 typename NotNarrowing = std::enable_if_t<(sizeof(int_type)>=sizeof(T))
			 && (is_signed ? std::is_signed<T>::value : true)>,
			 typename = void, typename = void>
	constexpr fp(T _int) noexcept
		: _value(adapt_int(_int)) {}

	///Construct from a integral larger then the needed one of this fixed point. Not explicit
	template<typename T,
			 typename IsInt = std::enable_if_t<std::is_integral<T>::value>,
			 typename Narrowing = std::enable_if_t<sizeof(int_type)<sizeof(T)
			 || (is_signed ? std::is_unsigned<T>::value : false)>,
			 typename = void,
			 typename = void,
			 typename = void>
	explicit constexpr fp(T _int) noexcept
		: _value(adapt_int(_int)) {}


	template<long wl_in,
			 long fl_in,
			 typename _sign_t_in,
			 rounding_mode r_mode_in,
			 typename NotNarrowing = std::enable_if_t<
			 	 (fl_in >= fl) &&
				 (wl_in >= wl) &&
				 ((wl-fl) >= (wl_in-fl_in)) &&
				 (is_signed ? std::is_signed<_sign_t_in>::value : true)>,
			 typename = void,
			 typename = void>
	constexpr fp(fp<wl_in, fl_in, _sign_t_in, r_mode_in> in) noexcept
		: _value(adapt_int((fl > fl_in) ?
							in.value() << (fl-fl_in) :
							in.value())) { }

	template<long wl_in,
			 long fl_in,
			 typename _sign_t_in,
			 rounding_mode r_mode_in,
			 typename Narrowing = std::enable_if_t<
			 	 (fl_in < fl) ||
				 (wl_in < wl) ||
				 ((wl-fl) < (wl_in-fl_in)) ||
				 (is_signed ? std::is_unsigned<_sign_t_in>::value : false)>,
			 typename = void,
			 typename = void,
			 typename = void>
	explicit constexpr fp(fp<wl_in, fl_in, _sign_t_in, r_mode_in> in) noexcept
		: _value(
				adapt_int((fl > fl_in) ?
						in.value() << (fl - fl_in)
						: (fl < fl_in) ?
						in.value() >> (fl_in - fl)
						: in.value()
						)) { }

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
			 typename NotNarrowing = std::enable_if_t<(sizeof(int_type)<=sizeof(T))
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
			 typename Narrowing = std::enable_if_t<(sizeof(int_type)>sizeof(T))
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
					 (is_signed ? std::is_signed<_sign_t_out>::value : true)>,
				 typename = void,
				 typename = void>
	constexpr operator fp<wl_out, fl_out, _sign_t_out, r_mode_out> () noexcept
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
				 (is_signed ? std::is_unsigned<_sign_t_out>::value : false)>,
			 typename = void,
			 typename = void,
			 typename = void>
	explicit constexpr operator fp<wl_out, fl_out, _sign_t_out, r_mode_out> () noexcept
	{
		typedef typename fp<wl_out, fl_out, _sign_t_out, r_mode_out> ::type ret_type;
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
#endif /* fp_H_ */
