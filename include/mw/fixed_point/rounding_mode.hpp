/*
 * rounding_mode.hpp
 *
 *  Created on: 16.10.2015
 *      Author: Klemens
 */

#ifndef MW_FIXED_POINT_ROUNDING_MODE_HPP_
#define MW_FIXED_POINT_ROUNDING_MODE_HPP_

namespace mw
{
namespace fixed_point
{

enum class rounding_mode
{
	trunc, ///<Computes nearest integer to arg. Number is rounded away from zero in halfway cases
	floor, ///<Computes nearest integer not greater than arg.
	ceil,  ///<Computes nearest integer not less than arg.
	round, ///<Computes nearest integer not greater in magnitude than arg.
};
}
}



#endif /* MW_FIXED_POINT_ROUNDING_MODE_HPP_ */
