//============================================================================
// Name        : FixedPoint.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "FixedPoint.h"
#include "Narrow.h"
#include "fp_limits.h"
//#include "fp_literals.h"
#include "fp.h"
#include <iostream>
#include <typeinfo>
#include <signal.h>
#include <stdexcept>
#include <array>

#include "validator.h"

using namespace std;
using namespace fixed_point;
using namespace kdm;

struct Ram_Poly_Struct
{

};

struct Tertullian
{

};

struct Polykarp
{
	using in_t 		= validator<double, fp_t<24,23>>;
	using mul_t   	= validator<double, fp_t<50,48>>;

	using mux_t  	= validator<double, fp_t<26,25>>;
	using add_out_t	= validator<double, fp_t<29,25>>;
	using add_t 	= validator<double, fp_t<28,25>>;
	
	using var_t  = const std::array<in_t,8>;


	in_t in;
	mul_t mul_out;

	mux_t mux1_in0;
	mux_t mux1_in1;

	mux_t regM_val;

	add_t add_in;

	add_t mux2_in0;
	add_t mux2_in1;
	add_t mux2_out;

	add_t regA_val;

	add_out_t add_out;


	in_t operator()(var_t & var, const in_t& cx, unsigned char n, bool sel_cx, bool sel_c0, bool en_ra)
	{
		///Output after RegA
		auto Q = regA_val;

		///between regM --> regA
		add_in = regA_val;

		add_out = add_in+regA_val;

		mux2_in0 = add_out;
		mux2_in1 = cx;

		mux2_out = sel_c0 ? mux2_in1 : mux2_in0;

		if (en_ra) regA_val = mux2_out;
		///befor register M
		in = var[n];

		mul_out = regM_val * in;

		mux1_in0 = mul_out;
		mux1_in1 = cx;

		regM_val = sel_cx ? mux1_in1 : mux1_in0;



		return Q;
	};
};


int main()
{

	auto sig_access = signal(SIGSEGV, +[](int signal) -> void 	{cerr << " invalid memory access (segmentation fault)  - " << signal; exit(0);});
	auto sig_term 	= signal(SIGTERM, +[](int signal) -> void 	{cerr << " 	termination request, sent to the program - " << signal; exit(0);});
	auto sig_int	= signal(SIGINT,  +[](int signal) -> void 	{cerr << " 	external interrupt, usually initiated by the user - " << signal; exit(0);});
	auto sig_ill	= signal(SIGILL,  +[](int signal) -> void 	{cerr << " 	invalid program image, such as invalid instruction - " << signal; exit(0);});
	auto sig_abrt	= signal(SIGABRT, +[](int signal) -> void 	{cerr << " 	abnormal termination condition, as is e.g. initiated by std::abort() - " << signal; exit(0);});
	auto sig_fpe	= signal(SIGFPE,  +[](int signal) -> void 	{cerr << " 	erroneous arithmetic operation such as divide by zero  - " << signal; exit(0);});

try {



	using namespace fixed_point;
	using namespace kdm;


	fp_t<44,20> fp1(7.554);
	fp_t<10,2> fp2(2.0);



	fp_t<14,4> val = fp1*fp2;


	auto x = fp1*fp2;
	auto y = fp1+fp2;

	auto z = fp1-fp2;
	auto a = fp1/fp2;

	return 0;
}
catch (exception &e)
{
	cerr << e.what();
}
}
