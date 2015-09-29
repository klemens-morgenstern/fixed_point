/*
 * validator.h
 *
 *  Created on: 02.12.2013
 *      Author: klemens.morgenstern
 */

#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include <type_traits>
#include <limits>
#include <ostream>

namespace kdm
{

	template<typename ref, typename val>
	class validator;


	template<typename T>
	struct is_validator
	{
		constexpr static bool value = false;
		typedef std::false_type  type;
		typedef bool value_type;

		static constexpr type type_value{};
	};

	template<typename ref, typename val>
	struct is_validator<validator<ref, val>>
	{
		constexpr static bool value = true;
		typedef std::true_type  type;
		typedef bool value_type;

		static constexpr type type_value{};
	};
	///Class for the validation of a arithmetic class
	/** \tparam ref Reference class
	 *  \tparam val Class to validate
	 *
	 *  \attention classes must be convertible to one another
	 */
	template<typename ref, typename val>
	class validator
	{
		ref _ref;
		val _val;
		template<typename l, typename r>
		validator(l&& L, r && R) : _ref(std::forward<l>(L)), _val (std::forward<r>(R)) {};
	public:
		typedef ref ref_t;
		typedef val val_t;

		const ref get_ref() const {return _ref;};
		const val get_val() const {return _val;};

		validator() 				noexcept(std::is_nothrow_default_constructible<ref>::value && std::is_nothrow_constructible<val>::value) = default;
		validator(const validator&) noexcept(std::is_nothrow_copy_constructible<ref>::value && std::is_nothrow_copy_constructible<val>::value) = default;
		validator(validator&&) 		noexcept(std::is_nothrow_move_constructible<ref>::value && std::is_nothrow_move_constructible<val>::value) = default;

		validator& operator=(const validator&) 	noexcept(std::is_nothrow_copy_assignable<ref>::value && std::is_nothrow_copy_assignable<val>::value) = default;
		validator& operator=(validator&&) 		noexcept(std::is_nothrow_move_assignable<ref>::value && std::is_nothrow_move_assignable<val>::value) = default;

		template<typename ref2, typename val2>
		constexpr validator(const validator<ref2, val2>& rhs, std::true_type) : _ref(rhs.get_ref()), _val((val2)rhs.get_val()) {};

		template<typename T>
		constexpr validator(const T& Val, std::false_type)	: _ref(Val), _val(Val) {};


		template<typename T>
		constexpr validator(const T& Val) : validator(Val, typename is_validator<T>::type()) {};

		template<typename T>
		void assign(const T& Val, std::false_type)
		{
			_ref = Val;
			_val = Val;
		};

		template<typename T>
		void assign(const T& Val, std::true_type)
		{
			_ref = Val.get_ref();
			_val = (val)Val.get_val();
		};


		template<typename T>
		validator& operator=(const T& Val)
		{
			assign(Val, typename is_validator<T>::type());
			return *this;

		};


		constexpr ref error()
		{
			return (_ref - (ref)_val);
		}

		constexpr ref rel_error()
		{
			return _ref != 0 ? error()/_ref : error()/(ref)_val;
		}

		constexpr bool overflow()
		{
			return _ref > std::numeric_limits<val>::max().get_floating();
		}

		constexpr bool underflow()
		{
			return _ref < std::numeric_limits<val>::min().get_floating();
		}

		template<typename ret_r, typename ret_v, typename r_r, typename r_v>
		friend validator<ret_r, ret_v> operator+(const validator& lhs, const validator<r_r, r_v> & rhs);

		template<typename ret_r, typename ret_v, typename r_r, typename r_v>
		friend validator<ret_r, ret_v> operator-(const validator& lhs, const validator<r_r, r_v> & rhs);

		template<typename ret_r, typename ret_v, typename r_r, typename r_v>
		friend validator<ret_r, ret_v> operator*(const validator& lhs, const validator<r_r, r_v> & rhs);

		template<typename ret_r, typename ret_v, typename r_r, typename r_v>
		friend validator<ret_r, ret_v> operator/(const validator& lhs, const validator<r_r, r_v> & rhs);

		template< typename r_r, typename r_v>
		validator& operator+=(const validator<r_r, r_v> & rhs)
		{
			_ref += rhs._ref;
			_val += rhs._val;
		}

		template< typename r_r, typename r_v>
		validator& operator-=(const validator<r_r, r_v> & rhs)
		{
			_ref -= rhs._ref;
			_val -= rhs._val;
		}

		template< typename r_r, typename r_v>
		validator& operator*=(const validator<r_r, r_v> & rhs)
		{
			_ref *= rhs._ref;
			_val *= rhs._val;
		}

		template< typename r_r, typename r_v>
		validator& operator/=(const validator<r_r, r_v> & rhs)
		{
			_ref /= rhs._ref;
			_val /= rhs._val;
		}

		template<typename l, typename r>
		friend validator<l,r> make_validator(l && lhs, r&& rhs);

		template<typename ref2, typename val2>
		friend std::ostream &operator<<(std::ostream &, const validator<ref2,val2> &);


		template<typename ref__, typename val__>
		friend class validator;
	};


template<typename l, typename r>
inline validator<l,r> make_validator(l && lhs, r&& rhs)
{
	return validator<l,r>(std::forward<l>(lhs),std::forward<r>(rhs));
}


template<typename l_r, typename l_v, typename r_r, typename r_v>
auto operator+(const validator<l_r, l_v>& lhs, const validator<r_r, r_v> & rhs)
{
	return make_validator(lhs.get_ref()+lhs.get_ref(), lhs.get_val()+rhs.get_val());
}

template<typename l_r, typename l_v, typename r_r, typename r_v>
auto operator-(const validator<l_r, l_v>& lhs, const validator<r_r, r_v> & rhs)
{
	return make_validator(lhs.get_ref()-lhs.get_ref(), lhs.get_val()-rhs.get_val());
}

template<typename l_r, typename l_v, typename r_r, typename r_v>
auto operator*(const validator<l_r, l_v>& lhs, const validator<r_r, r_v> & rhs)
{
	return make_validator(lhs.get_ref()*lhs.get_ref(), lhs.get_val()*rhs.get_val());
}

template<typename l_r, typename l_v, typename r_r, typename r_v>
auto operator/(const validator<l_r, l_v>& lhs, const validator<r_r, r_v> & rhs)
{
	return make_validator(lhs.get_ref()/lhs.get_ref(), lhs.get_val()/rhs.get_val());
}

template<typename ref, typename val>
std::ostream &operator<<(std::ostream &ostr, const validator<ref, val> & val_ref)
{
	ostr << "Ref: " << val_ref.get_ref() << " Val: " << val_ref.get_val() << " Error: " << val_ref.rel_error()*100.0 << "% ";
	return ostr;
}

}
#endif /* VALIDATOR_H_ */
