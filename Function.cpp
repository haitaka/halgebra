#include "Function.h"

// Const
double halg::Const::Value( halg::VarVals ) const
{
	return m_val;
}
halg::Const::operator std::string( ) const
{
	return std::to_string( m_val );
}
halg::Function * halg::Const::Derivative( std::string ) const
{
	return new halg::Const( 0 );
}
halg::Function * halg::Const::Copy( ) const
{
	return new Const( m_val );
}
bool halg::Const::IsConst( ) const
{
	return true;
}


// Var
double halg::Var::Value( halg::VarVals args ) const
{
	return args[ m_name ];
}
halg::Var::operator std::string( ) const
{
	return m_name;
}
halg::Function * halg::Var::Derivative( std::string var ) const
{
	if( var == m_name ) return new halg::Const( 1 );
	else                return new halg::Const( 0 );
}
halg::Function * halg::Var::Copy( ) const
{
	return new halg::Var( m_name );
}
bool halg::Var::IsConst( ) const
{
	return false;
}


// Neg
double halg::Neg::Value( halg::VarVals args ) const
{
	return -m_arg->Value( args );
}
halg::Neg::operator std::string( ) const
{
	return "-(" + std::string( *m_arg ) + ")";
}
halg::Function * halg::Neg::Derivative( std::string var ) const
{
	return new halg::Neg( m_arg->Derivative( var ) );
}
halg::Function * halg::Neg::Copy( ) const
{
	return new halg::Neg( m_arg );
}
bool halg::Neg::IsConst( ) const
{
	return m_arg->IsConst( );
}


// Sum
double halg::Sum::Value( halg::VarVals args ) const
{
	return ( m_left->Value( args ) +
			 m_right->Value( args ) );
}
halg::Sum::operator std::string( ) const
{
	return "(" +
		   std::string( *m_left ) +
		   ")+(" +
		   std::string( *m_right ) +
		   ")";
}
halg::Function * halg::Sum::Derivative( std::string var ) const
{
	return new halg::Sum( m_left->Derivative( var ),
						  m_right->Derivative( var ) );
}
halg::Function * halg::Sum::Copy( ) const
{
	return new halg::Sum( m_left, m_right );
}
bool halg::Sum::IsConst( ) const
{
	return ( m_left->IsConst( ) && m_right->IsConst( ) );
}


// Diff
double halg::Diff::Value( halg::VarVals args ) const
{
	return ( m_left->Value( args ) -
			 m_right->Value( args ) );
}
halg::Diff::operator std::string( ) const
{

	return "(" +
		   std::string( *m_left ) +
		   ")-(" +
		   std::string( *m_right ) +
		   ")";
}
halg::Function * halg::Diff::Derivative( std::string var ) const
{
	return new halg::Diff( m_left->Derivative( var ),
						   m_right->Derivative( var ) );
}
halg::Function * halg::Diff::Copy( ) const
{
	return new halg::Diff( m_left, m_right );
}
bool halg::Diff::IsConst( ) const
{
	return ( m_left->IsConst( ) && m_right->IsConst( ) );
}


// Comp
double halg::Comp::Value( halg::VarVals args ) const
{
	return ( m_left->Value( args ) *
			 m_right->Value( args ) );
}
halg::Comp::operator std::string( ) const
{

	return "(" +
		   std::string( *m_left ) +
		   ")*(" +
		   std::string( *m_right ) +
		   ")";
}
halg::Function * halg::Comp::Derivative( std::string var ) const
{
	return new halg::Sum(
				new halg::Comp(
					m_left->Derivative( var ),
					m_right->Copy( )
				),
				new halg::Comp(
					m_right->Derivative( var ),
					m_left->Copy( )
				)
			);
}
halg::Function * halg::Comp::Copy( ) const
{
	return new halg::Comp( m_left, m_right );
}
bool halg::Comp::IsConst( ) const
{
	return ( m_left->IsConst( ) && m_right->IsConst( ) );
}


// Div
double halg::Div::Value( halg::VarVals args ) const
{
	return ( m_left->Value( args ) /
			 m_right->Value( args ) );
}
halg::Div::operator std::string( ) const
{

	return "(" +
		   std::string( *m_left ) +
		   ")/(" +
		   std::string( *m_right ) +
		   ")";
}
halg::Function * halg::Div::Derivative( std::string var ) const
{
	return new halg::Div(
				new halg::Diff(
					new halg::Comp(
						m_left->Derivative( var ),
						m_right->Copy( )
					),
					new halg::Comp(
						m_right->Derivative( var ),
						m_left->Copy( )
					)
				),
				new halg::Comp(
					m_right->Copy( ),
					m_right->Copy( )
				)
			);
}
halg::Function * halg::Div::Copy( ) const
{
	return new halg::Div( m_left, m_right );
}
bool halg::Div::IsConst( ) const
{
	return ( m_left->IsConst( ) && m_right->IsConst( ) );
}


// Pow
double halg::Pow::Value( halg::VarVals args ) const
{
	return pow( m_base->Value( args ),
				m_exp->Value( args ) );
}
halg::Pow::operator std::string( ) const
{

	return "(" +
		   std::string( *m_base ) +
		   ")^(" +
		   std::string( *m_exp ) +
		   ")";
}
halg::Function * halg::Pow::Derivative( std::string var ) const
{
	Function * pow_part;
	Function * exp_part;

	if ( m_base->IsConst( ) )
	{
		pow_part = new halg::Const( 0 );
	}
	else
	{
		pow_part = new halg::Comp(
						new halg::Comp(
							m_exp->Copy( ),
							new halg::Pow(
								m_base->Copy( ),
								new halg::Diff(
								   m_exp->Copy( ),
								   new halg::Const( 1 )
								)
							)
						),
						m_base->Derivative( var )
					);
	}
	if ( m_exp->IsConst( ) )
	{
		exp_part = new halg::Const( 0 );
	}
	else
	{
		exp_part = new halg::Comp(
						new halg::Comp(
							new halg::Log(
							   m_base->Copy( )
							),
							new halg::Pow(
							   m_base->Copy( ),
							   m_exp->Copy( )
							)
						),
						m_exp->Derivative( var )
					);
	}
	return new Sum( pow_part, exp_part );
}
halg::Function * halg::Pow::Copy( ) const
{
	return new halg::Pow( m_base, m_exp );
}
bool halg::Pow::IsConst( ) const
{
	return ( m_base->IsConst( ) && m_exp->IsConst( ) );
}


// Log
double halg::Log::Value( halg::VarVals args ) const
{
	return log( m_arg->Value( args ) );
}
halg::Log::operator std::string( ) const
{
	return "log(" + std::string( *m_arg ) + ")";
}
halg::Function * halg::Log::Derivative( std::string var ) const
{
	return new Div(
				m_arg->Derivative( var ),
				m_arg->Copy( )
			 );
}
halg::Function * halg::Log::Copy( ) const
{
	return new halg::Log( m_arg );
}
bool halg::Log::IsConst( ) const
{
	return m_arg->IsConst( );
}


// Sin
double halg::Sin::Value( halg::VarVals args ) const
{
	return sin( m_arg->Value( args ) );
}
halg::Sin::operator std::string( ) const
{
	return "sin(" + std::string( *m_arg ) + ")";
}
halg::Function * halg::Sin::Derivative( std::string var ) const
{
	return new Comp(
				new halg::Cos( m_arg->Copy( ) ),
				m_arg->Derivative( var )
			 );
}
halg::Function * halg::Sin::Copy( ) const
{
	return new halg::Sin( m_arg );
}
bool halg::Sin::IsConst( ) const
{
	return m_arg->IsConst( );
}


// Cos
double halg::Cos::Value( halg::VarVals args ) const
{
	return cos( m_arg->Value( args ) );
}
halg::Cos::operator std::string( ) const
{
	return "cos(" + std::string( *m_arg ) + ")";
}
halg::Function * halg::Cos::Derivative( std::string var ) const
{
	return new halg::Neg(
				new halg::Comp(
					new halg::Sin( m_arg->Copy( ) ),
					m_arg->Derivative( var )
				)
			);
}
halg::Function * halg::Cos::Copy( ) const
{
	return new halg::Cos( m_arg );
}
bool halg::Cos::IsConst( ) const
{
	return m_arg->IsConst( );
}
