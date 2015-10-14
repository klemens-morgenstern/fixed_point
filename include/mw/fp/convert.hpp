/*
 * Convert.h
 *
 *  Created on: 16.10.2013
 *      Author: user
 */

#ifndef CONVERT_H_
#define CONVERT_H_

#include <cstdint>
#include "TypeHelper.h"

namespace fixed_point
{

/*template<typename int_type, typename = void>
struct converter_t
{
};


template<>
struct converter_t<uint64_t,uint64_t>
{
	typedef uint64_t type;
	uint64_t _value = 0;
	inline constexpr uint64_t to_uint64() const {return _value;}
	inline constexpr operator uint64_t () const {return _value;}
};


template<typename int_type>
struct converter_t<uint64_t, int_type>
{
	typedef int_type type;
	int_type _value = 0;
	inline constexpr uint64_t to_uint64() const {return _value;}
	inline constexpr operator uint64_t () const {return _value;}
};

template<typename int_type>
struct converter_t<uint32_t, int_type> : converter_t<uint64_t, int_type>
{
	inline constexpr uint32_t to_uint32() const {return _value;}
	inline constexpr operator uint32_t () const {return _value;}
};

template<typename int_type>
struct converter_t<uint16_t, int_type> : converter_t<uint32_t, int_type>
{
	inline constexpr uint16_t to_uint16() const {return _value;}
	inline constexpr operator uint16_t () const {return _value;}
};

template<typename int_type>
struct converter_t<uint8_t, int_type>  : converter_t<uint16_t, int_type>
{
	inline constexpr uint64_t to_uint8 () const {return _value;}
	inline constexpr operator uint8_t  () const {return _value;}
};

template<typename int_type>
struct converter_t<int_type,int_type> : converter_t<int_type, int_type>
{
};*/

template<typename T>
struct delete_int_narrowing
{};

template<>
struct delete_int_narrowing<uint8_t>
{
	inline constexpr operator uint8_t	() const = delete;
	inline constexpr uint8_t to_uint8	() const = delete;
};

template<>
struct delete_int_narrowing<int8_t>
{
	inline constexpr operator int8_t	() const = delete;
	inline constexpr uint8_t to_int8	() const = delete;
};

template<typename int_t, typename sign_t = signed, bool allow_narrowing_int = false, bool allow_narrowing_float = false>
struct convert_t {};

template<>
struct convert_t<uint32_t, signed, false, false>
{
	typedef uint32_t _type;
	uint32_t _value;
	inline constexpr operator uint64_t	() const {return _value;};
	inline constexpr uint64_t to_uint64	() const {return _value;};
	inline constexpr operator uint32_t	() const {return _value;};
	inline constexpr uint32_t to_uint32	() const {return _value;};

	inline constexpr operator uint16_t	() const = delete;
	inline constexpr uint16_t to_uint16	() const = delete;
	inline constexpr operator uint8_t	() const = delete;
	inline constexpr uint8_t to_uint8	() const = delete;
};



}


#endif /* CONVERT_H_ */
