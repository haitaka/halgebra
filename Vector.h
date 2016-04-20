#pragma once

#include "Matrix.h"
#include "Utils.h"

namespace halg
{
template< typename T >
class Vector : public halg::Matrix< T >
{
public:
	Vector( halg::uint size )
        : Matrix< T >( size, 1 )
	{}
	Vector( const Vector & src )
        : Matrix< T >( src )
	{}
    Vector( const Matrix< T > & srcMatrix )
        : Matrix< T >( srcMatrix.RowSize( ), 1 )
	{
		for( halg::uint id = 0; id < Size( ); ++id )
		{
            (*this)[id] = srcMatrix[id][0];
		}
	}
	halg::uint Size() const
	{
        return Matrix< T >::RowSize();
	}
	T & operator[] ( halg::uint id )
	{
        return Matrix< T >::Get( id, 0 );
    }
    T const & operator[] ( halg::uint id ) const
    {
        return Matrix< T >::Get( id, 0 );
    }
};

template< typename T >
T ScalProduct( Vector< T > const & left,
					Vector< T > const & right )
{
	if( left.Size( ) != right.Size( ) )
	{
		throw halg::SizeMismatch( );
	}

	T result;
    for( halg::uint id = 0; id < Matrix< T >::Size( ); ++id )
	{
		result += left[id] * right[id];
	}
	return result;
}
}
