#include "function.h"

// Const
double halg::Const::Value( halg::VarVals )
{
	return m_val;
}
halg::Const::operator std::string( )
{
	std::ostringstream formatStr;
	formatStr << m_val;
	return formatStr.str();
}
halg::Function halg::Const::Derivative( std::string )
{
	return halg::Const( 0 );
}
bool halg::Const::IsConst( )
{
	return true;
}


// Var
double halg::Var::Value( halg::VarVals args )
{
	return args[ m_name ];
}
halg::Var::operator std::string( )
{
	std::ostringstream formatStr;
	formatStr << m_name;
	return formatStr.str();
}
halg::Function halg::Var::Derivative( std::string var )
{
	if( var == m_name ) return halg::Const( 1 );
	else                return halg::Const( 0 );
}
bool halg::Var::IsConst( )
{
	return false;
}


// Sum
double halg::Sum::Value( halg::VarVals args )
{
	return ( m_left.Value( args ) +
			 m_right.Value( args ) );
}
halg::Sum::operator std::string( )
{
	std::ostringstream formatStr;
	formatStr << m_left
			  << "+"
			  << m_right;
	return formatStr.str();
}
halg::Function halg::Sum::Derivative( std::string var )
{
	return halg::Sum( m_left.Derivative( var ),
					  m_right.Derivative( var ) );
}
bool halg::Sum::IsConst( )
{
	return ( m_left.IsConst( ) && m_right.IsConst( ) );
}


// Diff
double halg::Diff::Value( halg::VarVals args )
{
	return ( m_left.Value( args ) -
			 m_right.Value( args ) );
}
halg::Diff::operator std::string( )
{
	std::ostringstream formatStr;
	formatStr << m_left
			  << "-"
			  << m_right;
	return formatStr.str();
}
halg::Function halg::Diff::Derivative( std::string var )
{
	return halg::Diff( m_left.Derivative( var ),
					  m_right.Derivative( var ) );
}
bool halg::Diff::IsConst( )
{
	return ( m_left.IsConst( ) && m_right.IsConst( ) );
}
