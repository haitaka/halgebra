#pragma once

#include "Matrix.h"

namespace halg
{
template< typename T >
class Matrix;
template< typename T >
class MatrixRowBuff;

template< typename T >
class MatrixRow
{
public:
	MatrixRow( Matrix< T > & base, halg::uint id )
		: m_base( base )
		, m_id( id )
	{}
	/*MatrixRow( MatrixRowBuff< T > & rowBuff )
		: m_base( rowBuff.base )
		, m_id( rowBuff.id )
	{

	}*/

	virtual T & operator [] ( halg::uint colId )
	{
		return m_base.m_data[ m_id ][ colId ];
	}
	virtual T const & operator [] ( halg::uint colId ) const
	{
		return m_base.m_data[ m_id ][ colId ];
	}

	MatrixRowBuff< T > operator + ( MatrixRow const & right )
	{
		if( m_base.m_colSize != right.m_base.m_colSize )
		{
			throw halg::SizeMismatch( );
		}
		MatrixRowBuff< T > Sum( m_base, m_id );
		for( halg::uint colId = 0;
			 colId < m_base.m_colSize;
			 ++colId )
		{
			Sum[ colId ] = ( *this )[ colId ] +
						   right[ colId ];
		}
		return Sum;
	}
	MatrixRowBuff< T > operator - ( MatrixRow const & right )
	{
		if( m_base.m_colSize != right.m_base.m_colSize )
		{
			throw halg::SizeMismatch( );
		}
		MatrixRowBuff< T > Diff( m_base, m_id );
		for( halg::uint colId = 0;
			 colId < m_base.m_colSize;
			 ++colId )
		{
			Diff[ colId ] = ( *this )[ colId ] -
							right[ colId ];
		}
		return Diff;
	}
	MatrixRow & operator = ( MatrixRow const & value )
	{
		if( m_base.m_colSize != value.m_base.m_colSize )
		{
			throw halg::SizeMismatch( );
		}
		for( halg::uint colId = 0;
			 colId < m_base.m_colSize;
			 ++colId )
		{
			( *this )[ colId ] = value[ colId ];
		}
		return *this;
	}
	MatrixRow & operator += (  MatrixRow const & arg )
	{
		if( m_base.m_colSize != arg.m_base.m_colSize )
		{
			throw halg::SizeMismatch( );
		}
		for( halg::uint colId = 0;
			 colId < m_base.m_colSize;
			 ++colId )
		{
			( *this )[ colId ] += arg[ colId ];
		}
		return *this;
	}
	MatrixRow & operator -= (  MatrixRow const & arg )
	{
		if( m_base.m_colSize != arg.m_base.m_colSize )
		{
			throw halg::SizeMismatch( );
		}
		for( halg::uint colId = 0;
			 colId < m_base.m_colSize;
			 ++colId )
		{
			( *this )[ colId ] -= arg[ colId ];
		}
		return *this;
	}

	//Matrix_col operator* (const double & scal);
	//Matrix_col operator/ (const double & scal);
	//Matrix_col operator* (const double & scal);
	//Matrix_col operator/ (const double & scal);

private:
	Matrix< T > & m_base;
	halg::uint m_id;
};

template< typename T >
class MatrixRowBuff : public MatrixRow< T >
{
public:
	MatrixRowBuff( Matrix< T > & base, halg::uint id )
		: MatrixRow< T >( base, id )
		, m_buffer( new T [ base.ColSize() ] )
	{}
	~MatrixRowBuff( )
	{
		delete m_buffer;
	}

	T & operator [] ( halg::uint colId ) override
	{
		return m_buffer[ colId ];
	}
	T const & operator [] ( halg::uint colId ) const override
	{
		return m_buffer[ colId ];
	}
private:
	T * m_buffer;
};

template< typename T >
class MatrixColBuff;

template< typename T >
class MatrixCol
{
public:
	MatrixCol( Matrix< T > & base, halg::uint id )
		: m_base( base )
		, m_id( id )
	{}

	virtual T & operator [] ( halg::uint rowId )
	{
		return m_base.m_data[ m_id ][ rowId ];
	}
	virtual T const & operator [] ( halg::uint rowId ) const
	{
		return m_base.m_data[ m_id ][ rowId ];
	}

	MatrixColBuff< T > operator + ( MatrixCol const & right )
	{
		if( m_base.m_rowSize != right.m_base.m_rowSize )
		{
			throw halg::SizeMismatch( );
		}
		MatrixColBuff< T > Sum( m_base, m_id );
		for( halg::uint rowId = 0;
			 rowId < m_base.m_rowSize;
			 ++rowId )
		{
			Sum[ rowId ] = ( *this )[ rowId ] +
						   right[ rowId ];
		}
		return Sum;
	}
	MatrixColBuff< T > operator - ( MatrixCol const & right )
	{
		if( m_base.m_rowSize != right.m_base.m_rowSize )
		{
			throw halg::SizeMismatch( );
		}
		MatrixColBuff< T > Diff( m_base, m_id );
		for( halg::uint rowId = 0;
			 rowId < m_base.m_rowSize;
			 ++rowId )
		{
			Diff[ rowId ] = ( *this )[ rowId ] -
							right[ rowId ];
		}
		return Diff;
	}
	MatrixCol & operator = ( MatrixCol const & value )
	{
		if( m_base.m_rowSize != value.m_base.m_rowSize )
		{
			throw halg::SizeMismatch( );
		}
		for( halg::uint rowId = 0;
			 rowId < m_base.m_rowSize;
			 ++rowId )
		{
			( *this )[ rowId ] = value[ rowId ];
		}
		return *this;
	}
	MatrixCol & operator += (  MatrixCol const & arg )
	{
		if( m_base.m_rowSize != arg.m_base.m_rowSize )
		{
			throw halg::SizeMismatch( );
		}
		for( halg::uint rowId = 0;
			 rowId < m_base.m_rowSize;
			 ++rowId )
		{
			( *this )[ rowId ] += arg[ rowId ];
		}
		return *this;
	}
	MatrixCol & operator -= (  MatrixCol const & arg )
	{
		if( m_base.m_colSize != arg.m_base.m_colSize )
		{
			throw halg::SizeMismatch( );
		}
		for( halg::uint rowId = 0;
			 rowId < m_base.m_rowSize;
			 ++rowId )
		{
			( *this )[ rowId ] -= arg[ rowId ];
		}
		return *this;
	}

	//Matrix_col operator* (const double & scal);
	//Matrix_col operator/ (const double & scal);
	//Matrix_col operator* (const double & scal);
	//Matrix_col operator/ (const double & scal);

private:
	Matrix< T > & m_base;
	halg::uint m_id;
};

template< typename T >
class MatrixColBuff : public MatrixCol< T >
{
public:
	MatrixColBuff( Matrix< T > & base, halg::uint id )
		: MatrixRow< T >( base, id )
		, m_buffer( new T [ base.RowSize() ] )
	{}
	~MatrixColBuff( )
	{
		delete m_buffer;
	}

	T & operator [] ( halg::uint rowId ) override
	{
		return m_buffer[ rowId ];
	}
	T const & operator [] ( halg::uint rowId ) const override
	{
		return m_buffer[ rowId ];
	}
private:
	T * m_buffer;
};
}
