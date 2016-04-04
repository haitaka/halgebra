#pragma once

#include <cmath>
#include <string>

#include "Utils.h"

#include <sstream>

namespace halg
{
class Function
{
public:
	virtual ~Function( ) {}

	virtual double Value( halg::VarVals args ) = 0;
	virtual operator std::string( ) = 0;
	virtual Function Derivative( std::string var ) = 0;
	virtual bool IsConst( ) = 0;
};

class Const : public Function
{
public:
	Const( double val )
		: m_val( val )
	{ }
	Const( Const const & src )
		: m_val( src.m_val )
	{ }
	~Const() override { }
	double Value( halg::VarVals ) override;
	operator std::string( ) override;
	Function Derivative( std::string ) override;
	bool IsConst( ) override;
private:
	double m_val;
};

class Var : public Function
{
public:
	Var( std::string name )
		: m_name( name )
	{ }
	Var( Var const & src )
		: m_name( src.m_name )
	{ }
	~Var() override { }
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	double m_name;
};

class Sum : public Function
{
public:
	Sum( Function const & left, Function const & right )
		: m_left( left )
		, m_right( right )
	{}
	Sum( Sum const & src )
		: m_left( src.m_left )
		, m_right( src.m_right )
	{}
	Sum( Function const & first, Function const & second,
		 Function const & third )
		: m_left( Sum( first, second ) )
		, m_right( third )
	{}
	~Sum( ) override {}
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	Function & m_left;
	Function & m_right;
};

class Diff : public Function
{
public:
	Diff( Function const & left, Function const & right )
		: m_left( left )
		, m_right( right )
	{}
	Diff( Diff const & src )
		: m_left( src.m_left )
		, m_right( src.m_right )
	{}
	Diff( Function const & first, Function const & second,
		  Function const & third )
		: m_left( Diff( first, second ) )
		, m_right( third )
	{}
	~Diff( ) override {}
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	Function & m_left;
	Function & m_right;
};

class Comp : public Function
{
public:
	Comp( Function const & left, Function const & right )
		: m_left( left )
		, m_right( right )
	{}
	Comp( Comp const & src )
		: m_left( src.m_left )
		, m_right( src.m_right )
	{}
	Comp( Function const & first, Function const & second,
		  Function const & third )
		: m_left( Comp( first, second ) )
		, m_right( third )
	{}
	~Comp( ) override {}
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	Function & m_left;
	Function & m_right;
};

class Div : public Function
{
public:
	Div( Function const & left, Function const & right )
		: m_left( left )
		, m_right( right )
	{}
	Div( Div const & src )
		: m_left( src.m_left )
		, m_right( src.m_right )
	{}
	Div( Function const & first, Function const & second,
		  Function const & third )
		: m_left( Div( first, second ) )
		, m_right( third )
	{}
	~Div( ) override {}
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	Function & m_left;
	Function & m_right;
};

class Pow : public Function
{
public:
	Pow( Function const & base, Function const & exp )
		: m_base( base )
		, m_exp( exp )
	{}
	Pow( Pow const & src )
		: m_base( src.m_base )
		, m_exp( src.m_exp )
	{}
	~Pow( ) override {}
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	Function & m_base;
	Function & m_exp;
};

class Log : public Function
{
public:
	Log( Function const & base )
		: m_base( base )
	{}
	Log( Log const & src )
		: m_base( src.m_base )
	{}
	~Log( ) override {}
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	Function & m_base;
};

class Sin : public Function
{
public:
	Sin( Function const & arg )
		: m_arg( arg )
	{}
	Sin( Sin const & src )
		: m_arg( src.m_arg )
	{}
	~Sin( ) override {}
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	Function & m_arg;
};

class Cos : public Function
{
public:
	Cos( Function const & arg )
		: m_arg( arg )
	{}
	Cos( Cos const & src )
		: m_arg( src.m_arg )
	{}
	~Cos( ) override {}
	double Value( halg::VarVals args ) override;
	operator std::string( ) override;
	Function Derivative( std::string var ) override;
	bool IsConst( ) override;
private:
	Function & m_arg;
};
}
