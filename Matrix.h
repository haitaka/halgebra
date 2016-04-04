#pragma once

#include <string>

#include "Utils.h"
#include "MatrixColRow.h"

namespace halg
{
template< typename T >
class Matrix
{
	friend class MatrixRow< T >;
	friend class MatrixCol< T >;
public:
	Matrix( halg::uint size )
		: m_rowSize( size )
		, m_colSize( size )
	{
		Init( );
	}
	Matrix( halg::uint rowSize, halg::uint colSize )
		: m_rowSize( rowSize )
		, m_colSize( colSize )
	{
		Init( );
	}
	Matrix( Matrix const & src )
		: m_rowSize( src.rowSize )
		, m_colSize( src.colSize )
		, m_data( nullptr )
	{
		*this = src;
	}
	~Matrix( )
	{
		Del( );
	}

	// RowSize is count of rows in matrix !
	halg::uint RowSize( ) const
	{
		return m_rowSize;
	}
	halg::uint ColSize( ) const
	{
		return m_colSize;
	}

	T & Get( halg::uint i, halg::uint j )
	{
		return m_data[i][j];
	}
	T const & Get( halg::uint i, halg::uint j ) const
	{
		return m_data[i][j];
	}

	MatrixRow< T > operator [] ( halg::uint id )
	{
		return GetRow( id );
	}
	MatrixRow< T > const
	operator [] ( halg::uint id ) const
	{
		return GetRow( id );
	}

	MatrixRow< T > GetRow( halg::uint rowId )
	{
		return MatrixRow< T >( *this, rowId );
	}
	MatrixCol< T > GetCol( halg::uint colId )
	{
		return MatrixCol< T >( *this, colId );
	}
	MatrixRow< T > const GetRow( halg::uint rowId ) const
	{
		return MatrixRow< T >( *this, rowId );
	}
	MatrixCol< T > const GetCol( halg::uint colId ) const
	{
		return MatrixCol< T >( *this, colId );
	}

	Matrix operator + ( Matrix const & right );
	Matrix operator - ( Matrix const & right );
	Matrix operator * ( Matrix const & right );

	Matrix & operator = ( Matrix const & value )
	{
		if ( m_data != value.m_data )
		{
			Del( );
			m_rowSize = value.m_rowSize;
			m_colSize = value.m_colSize;
			Init( );
			for( halg::uint i = 0; i < m_rowSize; ++i )
			{
				for( halg::uint j = 0; j < m_colSize; ++j )
				{
					m_data[i][j] = value.m_data[i][j];
				}
			}
		}
		return *this;
	}
	Matrix & operator += ( Matrix const & arg )
	{
		*this = *this + arg;
		return *this;
	}
	Matrix & operator -= ( Matrix const & arg )
	{
		*this = *this - arg;
		return *this;
	}
	Matrix & operator *= ( Matrix const & arg )
	{
		*this = *this * arg;
		return *this;
	}

	//Matrix operator * ( const double & scal );
	//Matrix operator / ( const double & scal );
	//Matrix & operator *= ( const double & arg );
	//Matrix & operator /= ( const double & arg );

	Matrix Transpose( ) const
	{
		Matrix Trans( m_colSize, m_rowSize );

		for( halg::uint i = 0; i < m_rowSize; ++i )
		{
			for( halg::uint j = 0; j < m_colSize; ++j )
			{
				Trans.m_data[j][i] = m_data[i][j];
			}
		}
		return Trans;
	}
	void SwapRows( halg::uint row1, halg::uint row2 )
	{
		if ( row1 == row2 ) return;

		T * tmp = m_data[row1];
		m_data[row1] = m_data[row2];
		m_data[row2] = tmp;
	}

	void SwapCols( halg::uint col1, halg::uint col2 )
	{
		if ( col1 == col2 ) return;

		T tmp;
		for( halg::uint i = 0; i < m_rowSize; ++i )
		{
			tmp = m_data[i][col1];
			m_data[i][col1] = m_data[i][col2];
			m_data[i][col2] = tmp;
		}
	}

private:
	void Init( )
	{
		m_rowColBuff =
			new T [ halg::Max( m_rowSize, m_colSize ) ];
		m_data = new T * [ m_rowSize ];
		for( halg::uint i = 0; i < m_rowSize; ++i )
		{
			m_data[i] = new T [ m_colSize ];
		}
	}
	void Del( )
	{
		for( halg::uint i = 0; i < m_rowSize; ++i )
		{
			delete m_data[i];
		}
		delete m_data;
		delete m_rowColBuff;
	}
private:
	T ** m_data;
	halg::uint m_rowSize;// RowSize is count of rows in matrix !
	halg::uint m_colSize;

	T * m_rowColBuff;
};


template< typename T >
Matrix< T > Matrix< T >::operator + ( Matrix const & right )
{
	if (m_rowSize != right.m_rowSize ||
		m_colSize != right.m_colSize)
	{
		throw halg::SizeMismatch( );
	}

	Matrix Sum( m_rowSize, m_colSize );
	for( halg::uint i = 0; i < m_rowSize; ++i )
	{
		for( halg::uint j = 0; j < m_colSize; ++j )
		{
			Sum.m_data[i][j] = m_data[i][j] +
							   right.m_data[i][j];
		}
	}
	return Sum;
}
template< typename T >
Matrix< T > Matrix< T >::operator - ( Matrix const & right )
{
	if (m_rowSize != right.m_rowSize ||
		m_colSize != right.m_colSize)
	{
		throw halg::SizeMismatch( );
	}

	Matrix Diff( m_rowSize, m_colSize );
	for( halg::uint i = 0; i < m_rowSize; ++i )
	{
		for( halg::uint j = 0; j < m_colSize; ++j )
		{
			Diff.m_data[i][j] = m_data[i][j] -
							   right.m_data[i][j];
		}
	}
	return Diff;
}
template< typename T >
Matrix< T > Matrix< T >::operator * ( Matrix const & right )
{
	if (m_rowSize != right.m_rowSize ||
		m_colSize != right.m_colSize)
	{
		throw halg::SizeMismatch( );
	}

	Matrix Comp( m_rowSize, m_colSize );
	for( halg::uint i = 0; i < m_rowSize; ++i )
	{
		for( halg::uint j = 0; j < m_colSize; ++j )
		{
			Comp.m_data[i][j] = m_data[i][j] *
							   right.m_data[i][j];
		}
	}
	return Comp;
}
}
