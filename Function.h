#pragma once

#include <cmath>
#include <string>
#include <iostream>

#include "MiscMath.h"


namespace halg
{
class Function
{
public:
	virtual ~Function( ) { }

	virtual double Value( halg::VarVals args ) const = 0;
	virtual operator std::string( ) const = 0;
	virtual Function * Derivative( std::string var ) const = 0;
	virtual Function * Copy( ) const = 0;
	virtual bool IsConst( ) const = 0;
	friend std::ostream &
		operator << ( std::ostream & ioStream,
					  Function const * func )
	{
		ioStream << std::string( *func );
		return ioStream;
	}
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
	~Const( ) { }
	double Value( halg::VarVals ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string  const) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
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
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	std::string m_name;
};

class Neg : public Function
{
public:
	Neg( Function * arg )
		: m_arg( arg )
	{}
	Neg( Neg const & src )
		: m_arg( src.m_arg->Copy( ) )
	{}
	~Neg( ) override
	{
		delete m_arg;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_arg;
};

class Sum : public Function
{
public:
	Sum( Function * left, Function * right )
		: m_left( left )
		, m_right( right )
	{}
	Sum( Sum const & src )
		: m_left( src.m_left->Copy( ) )
		, m_right( src.m_right->Copy( ) )
	{}
	Sum( Function * first, Function * second,
		 Function * third )
		: m_left( new Sum( first, second ) )
		, m_right( third )
	{}
	~Sum( ) override
	{
		delete m_left;
		delete m_right;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_left;
	Function * m_right;
};

class Diff : public Function
{
public:
	Diff( Function * left, Function * right )
		: m_left( left )
		, m_right( right )
	{}
	Diff( Diff const & src )
		: m_left( src.m_left->Copy( ) )
		, m_right( src.m_right->Copy( ) )
	{}
	Diff( Function * first, Function * second,
		  Function * third )
		: m_left( new Diff( first, second ) )
		, m_right( third )
	{}
	~Diff( ) override
	{
		delete m_left;
		delete m_right;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_left;
	Function * m_right;
};

class Comp : public Function
{
public:
	Comp( Function * left, Function * right )
		: m_left( left )
		, m_right( right )
	{}
	Comp( Comp const & src )
		: m_left( src.m_left->Copy( ) )
		, m_right( src.m_right->Copy( ) )
	{}
	Comp( Function * first, Function * second,
		  Function * third )
		: m_left( new Comp( first, second ) )
		, m_right( third )
	{}
	~Comp( ) override
	{
		delete m_left;
		delete m_right;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_left;
	Function * m_right;
};

class Div : public Function
{
public:
	Div( Function * left, Function * right )
		: m_left( left )
		, m_right( right )
	{}
	Div( Div const & src )
		: m_left( src.m_left->Copy( ) )
		, m_right( src.m_right->Copy( ) )
	{}
	Div( Function * first, Function * second,
		 Function * third )
		: m_left( new Div( first, second ) )
		, m_right( third )
	{}
	~Div( ) override
	{
		delete m_left;
		delete m_right;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_left;
	Function * m_right;
};

class Pow : public Function
{
public:
	Pow( Function * base, Function * exp )
		: m_base( base )
		, m_exp( exp )
	{}
	Pow( Pow const & src )
		: m_base( src.m_base->Copy( ) )
		, m_exp( src.m_exp->Copy( ) )
	{}
	~Pow( ) override
	{
		delete m_base;
		delete m_exp;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_base;
	Function * m_exp;
};

class Log : public Function
{
public:
	Log( Function * arg )
		: m_arg( arg )
	{}
	Log( Log const & src )
		: m_arg( src.m_arg->Copy( ) )
	{}
	~Log( ) override
	{
		delete m_arg;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_arg;
};

class Sin : public Function
{
public:
	Sin( Function * arg )
		: m_arg( arg )
	{}
	Sin( Sin const & src )
		: m_arg( src.m_arg->Copy( ) )
	{}
	~Sin( ) override
	{
		delete m_arg;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_arg;
};

class Cos : public Function
{
public:
	Cos( Function * arg )
		: m_arg( arg )
	{}
	Cos( Cos const & src )
		: m_arg( src.m_arg->Copy( ) )
	{}
	~Cos( ) override
	{
		delete m_arg;
	}
	double Value( halg::VarVals args ) const override;
	operator std::string( ) const override;
	Function * Derivative( std::string var ) const override;
	Function * Copy( ) const override;
	bool IsConst( ) const override;
private:
	Function * m_arg;
};
}
