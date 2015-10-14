/**
 * \file fp_t.h
 * Contains the classes \ref fp_t, which is not yet completed, since it has no calculation operators yet.
 *
 * \author Klemens D. Morgenstern
 *
 */

#ifndef fp_t_H_
#define fp_t_H_

#include <cmath>
#include <iostream>
#include <istream>
#include <type_traits>
#include "TypeHelper.h"
#include "Rounding.h"
#include "Convert.h"

namespace fixed_point {


enum class narrow
{
	delete_all,	//<delete all conversions exlicitly
	delete_narrow, ///<delete only the narrowing but implement the others
	imp_none,	  ///<implement none, which causes the compiler to use the int or float conversion. this one will produce a lot of nonsense
	imp_only_not, ///<implement only not narrowing conversions. also not recommended since this can also use several ways for conversions
	imp_all,	  ///<implement all conversions, even the narrowing ones. doesn't make much sense for the int types...
};

template<	long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc, narrow fp_convs = narrow::imp_all,
				bool sign_change = false, narrow flt_convs = narrow::imp_only_not, narrow int_convs = narrow::delete_all>
struct fp_t;

///Construct a Mask for getting the right value
inline constexpr unsigned long ConstructMask(unsigned long long i) {return (i>=1L) ? (ConstructMask(i-1)|(unsigned long)(1<<i)) : true;};


template<typename si1, typename si2>
struct sel_sign
{
	typedef signed type;
};
template<>
struct sel_sign<unsigned, unsigned>
{
	typedef unsigned type;
};


constexpr long bigger(long val1, long val2) {return val1>val2 ? val1 : val2;};


///Template for conversion of signed (two's complement) fixed-points. WordLength == full word length
/** This class allows you to store a fp_t value and convert them to double. For later use it will be
 * enhanced with mathematical operator, but since this application doesn't need them, they are not yet implemented.
 * If you cast this class to a double (can be don implicitly) you will automaticly get the converted value as floating point.
 * If you cast to long (also usigned, and implicit) you will get the digit. It works the other way round for the assignment or constructors.
 */
template<long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc>
struct fp_base_t
{
	typedef typename int_type<wl, _sign_t>::type type;
	typedef typename int_type<wl, _sign_t>::min_float_t min_float_t;
	typedef _sign_t sign_t;
	constexpr static bool is_signed = std::is_signed<sign_t>::value;
	constexpr static long word_length 	  = wl;
	constexpr static long fraction_length = fl;
	constexpr static rounding_mode round_mode = r_mode;
	constexpr static type mask = ConstructMask(wl);
	constexpr static type sign_pos = is_signed ? (1<<(wl-1)) : 0;

private:
	///The factor is the one in the fixed-point notation
	static constexpr min_float_t _factor = (1<<fl);
	///Value stored
    type _value;
    typedef fp_base_t<wl, fl, sign_t, r_mode> my_type;
public:
    constexpr static type max_i = std::is_signed<_sign_t>::value ? (ConstructMask(wl-2)) : mask;
	constexpr static type min_i = std::is_signed<_sign_t>::value ? (~ConstructMask(wl-2)) : 0;

	constexpr static fp_base_t max = fp_base_t(max_i);
	constexpr static fp_base_t min = fp_base_t(min_i);

	constexpr static min_float_t max_f = (min_float_t)max_i / (min_float_t)_factor;
	constexpr static min_float_t min_f = (min_float_t)min_i / (min_float_t)_factor;


    template<typename T = min_float_t>
    constexpr T get_floating(T = min_float_t()) const {return (T)_value / (T)_factor;}


    template<typename T = type>
    constexpr T get_integral(T = type()) const {return (T)_value;};



    template<typename FP = fp_base_t>
    constexpr FP get_fp(FP) const
    {
    	return FP(rounding_delegate<FP::fraction_length, FP::round_mode>::round_fp((typename FP::type)_value, fl));
    };


    template<typename T>
    void _assign(const T & rhs, std::true_type is_int, std::false_type is_flt)
    {
    	_value = rhs & mask;
    }

    template<typename T>
    void _assign(const T & rhs, std::false_type is_int, std::true_type is_flt)
    {
    	_value = round(rhs*_factor);
    }


    template<typename T>
    fp_base_t& operator=(const T & rhs) {_assign(rhs,
    									typename std::is_integral<T>::type(),
    									typename std::is_floating_point<T>::type()); return *this;};



	///Construct from two longs
	constexpr fp_base_t(unsigned long Word, unsigned long Frac) : _value((Word<<fl | Frac)&mask) {};

	template<typename T>
	constexpr type sign_it(T value)
	{
		return (value > sign_pos) ? ((value & ~sign_pos) - sign_pos) : value;
	}

	///Construct from one long
	explicit constexpr fp_base_t(uint64_t Value) : _value(Value&mask) {};
	///Construct from one long
	explicit constexpr fp_base_t(uint32_t Value) : _value(Value&mask) {};
	///Construct from one long
	explicit constexpr fp_base_t(uint16_t Value) : _value(Value&mask) {};
	///Construct from one long
	explicit constexpr fp_base_t(uint8_t Value)  : _value(Value&mask) {};
	///Construct from one long
	explicit constexpr fp_base_t(int64_t Value)  : _value(Value) {};
	///Construct from one long
	explicit constexpr fp_base_t(int32_t Value)  : _value(Value) {};
	///Construct from one long
	explicit constexpr fp_base_t(int16_t Value)  : _value(Value) {}; //sign_it(Value&mask)
	///Construct from one long
	explicit constexpr fp_base_t(int8_t Value)   : _value(Value) {};



	///construct from underlying type
	//explicit constexpr fp_base_t(type Value) : _value(Value&mask) {};

	///Construct from double
	explicit constexpr fp_base_t(long double Value)	: _value(round(Value*_factor)) {};
	///Construct from double
	explicit constexpr fp_base_t(double Value)		: _value(round(Value*_factor)) {};
	///Construct from double
	explicit constexpr fp_base_t(float Value)		: _value(round(Value*_factor)) {};
	///Copy Constructor
	constexpr fp_base_t(const fp_base_t& rhs) : _value(rhs._value) {};

	///Construct empty value, will be 0
	explicit constexpr fp_base_t() : fp_base_t(0,0) {};

	template<long size_wl, long size_fl, typename __sign_t = signed, rounding_mode _r_mode = rounding_mode::trunc>
	constexpr operator fp_base_t<size_wl, size_fl, __sign_t, _r_mode>()
	{
		using fp_ret_t = fp_base_t<size_wl, size_fl, __sign_t, _r_mode>;
		return fp_ret_t(	(wl > size_wl) ? (_value<<(wl-size_wl)) : (_value>>(size_wl-wl)) );
	};

	constexpr operator double()
	{
		return (double)_value/(double)_factor;
	};

	constexpr fp_base_t operator>>(unsigned char shift)	{return fp_base_t(_value>>shift);}
	constexpr fp_base_t operator<<(unsigned char shift)	{return fp_base_t(_value<<shift);}

	constexpr fp_base_t& operator>>=(unsigned char shift)	{_value >> shift; return *this;}
	constexpr fp_base_t& operator<<=(unsigned char shift)	{_value << shift; return *this;}

	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1, long wl2, long fl2, typename sign_t2, rounding_mode r_mode2> //long wl1, long fl1, typename sign_t, rounding_mode r_mode,
	constexpr friend fp_t<wl1+wl2, fl1+fl2, typename sel_sign<sign_t1, sign_t2>::type, r_mode1> operator* (const fp_base_t<wl1, fl1, sign_t1, r_mode1>&, const fp_base_t<wl2, fl2, sign_t2, r_mode2>&);

	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1, long wl2, long fl2, typename sign_t2, rounding_mode r_mode2> //long wl1, long fl1, typename sign_t, rounding_mode r_mode,
	constexpr friend fp_t<wl1+wl2, fl1+fl2, typename sel_sign<sign_t1, sign_t2>::type, r_mode1> operator/ (const fp_base_t<wl1, fl1, sign_t1, r_mode1>&, const fp_base_t<wl2, fl2, sign_t2, r_mode2>&);


	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1, long wl2, long fl2, typename sign_t2, rounding_mode r_mode2> //long wl1, long fl1, typename sign_t, rounding_mode r_mode,
	friend constexpr fp_t<bigger(wl1,wl2), bigger(fl1,fl2), typename sel_sign<sign_t1, sign_t2>::type, r_mode1> operator+ (const fp_base_t<wl1, fl1, sign_t1, r_mode1>&, const fp_base_t<wl2, fl2, sign_t2, r_mode2>&);

	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1, long wl2, long fl2, typename sign_t2, rounding_mode r_mode2> //long wl1, long fl1, typename sign_t, rounding_mode r_mode,
	friend constexpr fp_t<bigger(wl1,wl2), bigger(fl1,fl2), typename sel_sign<sign_t1, sign_t2>::type, r_mode1> operator- (const fp_base_t<wl1, fl1, sign_t1, r_mode1>&, const fp_base_t<wl2, fl2, sign_t2, r_mode2>&);

	constexpr fp_base_t operator<<=(int shift) {_value<<=shift; return *this;}
	constexpr fp_base_t operator>>=(int shift) {_value>>=shift; return *this;}

	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1>
	 fp_base_t &operator+=(fp_base_t<wl1, fl1, sign_t1, r_mode1> fp)
	{
		using int_t = typename fp_base_t<wl1, fl1, sign_t1, r_mode1>::type;
		_value += fp.get_fp(*this).get_integral();

		return *this;
	}
	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1>
	fp_base_t &operator-=(fp_base_t<wl1, fl1, sign_t1, r_mode1> fp)
	{
		using int_t = typename fp_base_t<wl1, fl1, sign_t1, r_mode1>::type;
		_value += fp.get_fp(*this).get_integral();


		return *this;
	}

	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1>
	fp_base_t &operator*=(fp_base_t<wl1, fl1, sign_t1, r_mode1> fp)
	{
		using int_t = typename int_type<wl+wl1, sign_t>::type;
		_value = ((int_t)fp._value * (int_t)_value)>>fl1; //if int_t == this::type it is assumed for the compiler to optimize it.
		return *this;
	}

	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1>
	fp_base_t &operator/=(fp_base_t<wl1, fl1, sign_t1, r_mode1> fp)
	{
		using int_t = typename int_type<wl+wl1, sign_t>::type;
		_value = (((int_t)_value)<<fl1) / (int_t)fp._value; //if int_t == this::type it is assumed for the compiler to optimize it.
		return *this;
	}

	///That one is unclean, but hey...
	template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1>
	friend struct fp_base_t;


};



template<long wl, long fl, typename sign_t = signed, rounding_mode r_mode, long wl2, long fl2, typename sign_t2, rounding_mode r_mode2> //long wl1, long fl1, typename sign_t, rounding_mode r_mode,
constexpr fp_t<wl+wl2, fl+fl2, typename sel_sign<sign_t, sign_t2>::type, r_mode> operator* (const fp_base_t<wl, fl, sign_t, r_mode>& lhs, const fp_base_t<wl2, fl2, sign_t2, r_mode2>& rhs)
{
	using fp_type = fp_t<wl+wl2, fl+fl2, typename sel_sign<sign_t, sign_t2>::type, r_mode>;
	using int_t = typename fp_type::type;
	return fp_type(((int_t)lhs._value)*((int_t)rhs._value));
}

template<long wl, long fl, typename sign_t = signed, rounding_mode r_mode, long wl2, long fl2, typename sign_t2, rounding_mode r_mode2> //long wl1, long fl1, typename sign_t, rounding_mode r_mode,
constexpr fp_t<wl+wl2, fl+fl2, typename sel_sign<sign_t, sign_t2>::type, r_mode> operator/ (const fp_base_t<wl, fl, sign_t, r_mode>& lhs, const fp_base_t<wl2, fl2, sign_t2, r_mode2>& rhs)
{
	using fp_type = fp_t<wl+wl2, fl+fl2, typename sel_sign<sign_t, sign_t2>::type, r_mode>;
	using int_t1 = typename fp_base_t<wl+wl2+wl2, fl+fl2+fl2, typename sel_sign<sign_t, sign_t2>::type, r_mode>::type;
	return fp_type(((int_t1)lhs._value << (fl2+fl2))/((int_t1)rhs._value));

}

template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1, long wl2, long fl2, typename sign_t2, rounding_mode r_mode2> //long wl1, long fl1, typename sign_t, rounding_mode r_mode,
constexpr fp_t<bigger(wl1,wl2), bigger(fl1,fl2), typename sel_sign<sign_t1, sign_t2>::type, r_mode1> operator+ (const fp_base_t<wl1, fl1, sign_t1, r_mode1>& lhs, const fp_base_t<wl2, fl2, sign_t2, r_mode2>& rhs)
{
	using fp_type = fp_t<bigger(wl1,wl2), bigger(fl1,fl2) , typename sel_sign<sign_t1, sign_t2>::type, r_mode1>;
	using int_t1 = typename fp_base_t<wl1, fl1, sign_t1, r_mode1>::type;
	using int_t2 = typename fp_base_t<wl2, fl2, sign_t2, r_mode2>::type;
	using int_t = typename fp_type::type;

	return fp_type( ((typename fp_type::type)lhs._value<< (fp_type::fraction_length - fl1))
				+ 	((typename fp_type::type)rhs._value<< (fp_type::fraction_length - fl2)));

}

template<long wl1, long fl1, typename sign_t1, rounding_mode r_mode1, long wl2, long fl2, typename sign_t2, rounding_mode r_mode2> //long wl1, long fl1, typename sign_t, rounding_mode r_mode,
constexpr fp_t<bigger(wl1,wl2), bigger(fl1,fl2), typename sel_sign<sign_t1, sign_t2>::type, r_mode1> operator- (const fp_base_t<wl1, fl1, sign_t1, r_mode1>& lhs, const fp_base_t<wl2, fl2, sign_t2, r_mode2>& rhs)
{
	//static constexpr long wl = bigger(wl1,wl2);
	//static constexpr long fl = bigger(fl1,fl2); //bigger(fl1,fl2)
	using fp_type = fp_t<bigger(wl1,wl2), bigger(fl1,fl2) , typename sel_sign<sign_t1, sign_t2>::type, r_mode1>;
	using int_t1 = typename fp_base_t<wl1, fl1, sign_t1, r_mode1>::type;
	using int_t2 = typename fp_base_t<wl2, fl2, sign_t2, r_mode2>::type;
	using int_t = typename fp_type::type;

	return fp_type(((int_t)lhs._value<< (fp_type::fraction_length - fl1))
			-	   ((int_t)rhs._value<< (fp_type::fraction_length - fl2)));



}


template<long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc>
inline std::ostream &operator<<(std::ostream& ostr, const fp_base_t<wl,fl,_sign_t, r_mode>& fp)
{
	ostr << fp.get_floating();
	return ostr;
}

template<long wl, long fl, typename _sign_t = signed, rounding_mode r_mode = rounding_mode::trunc>
inline std::istream &operator>>(std::istream& istr, fp_base_t<wl,fl,_sign_t, r_mode>& fp)
{
	typename decltype(fp)::min_float_t flt;
	istr >> flt;
	fp = flt;
	return istr;
}

}
#endif /* fp_t_H_ */
