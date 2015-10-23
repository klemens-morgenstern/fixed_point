/*
 * to_string.hpp
 *
 *  Created on: 22.10.2015
 *      Author: klemens.morgenstern
 */

#ifndef MW_FIXED_POINT_TO_STRING_HPP_
#define MW_FIXED_POINT_TO_STRING_HPP_


#include <string>
#include <ostream>
#include <boost/format.hpp>
#include <mw/fixed_point/fixed_point.hpp>

namespace mw
{
namespace fixed_point
{



template<long wl, long fl,  rounding_mode rm>
std::string to_string(fp_t<wl, fl, signed, rm> fp)
{
	return boost::format("%1i%fp.s.%2i%.%3i%") % fp.value() % wl % fl;
}

template<long wl, long fl, rounding_mode rm>
std::wstring to_wstring(fp_t<wl, fl, signed, rm> fp)
{
	return boost::wformat(L"%1i%fp.s.%2i%.%3i%") % fp.value() % wl % fl;
}



template<long wl, long fl,  rounding_mode rm>
std::string to_string(fp_t<wl, fl, unsigned, rm> fp)
{
	return boost::format("%1i%fp.u.%2i%.%3i%") % fp.value() % wl % fl;
}

template<long wl, long fl, rounding_mode rm>
std::wstring to_wstring(fp_t<wl, fl, unsigned, rm> fp)
{
	return boost::wformat(L"%1i%fp.u.%2i%.%3i%") % fp.value() % wl % fl;
}



template<long wl, long fl, rounding_mode rm>
std::ostream& operator<<(std::ostream& ostr, fp_t<wl, fp, signed, rm> fp)
{
	ostr << fp.value() << "fp.s." << wl << "." << fl;
	return ostr;
}


template<long wl, long fl, rounding_mode rm>
std::owstream& operator<<(std::owstream& ostr, fp_t<wl, fp, signed, rm> fp)
{
	ostr << fp.value() << L"fp.s." << wl << "." << fl;
	return ostr;
}


template<long wl, long fl, rounding_mode rm>
std::ostream& operator<<(std::ostream& ostr, fp_t<wl, fp, unsigned, rm> fp)
{
	ostr << fp.value() << "fp.u." << wl << "." << fl;
	return ostr;
}


template<long wl, long fl, rounding_mode rm>
std::owstream& operator<<(std::owstream& ostr, fp_t<wl, fp, unsigned, rm> fp)
{
	ostr << fp.value() << L"fp.u." << wl << "." << fl;
	return ostr;
}


}

using fixed_point:: to_string;
using fixed_point::to_wstring;

}




#endif /* TO_STRING_HPP_ */
