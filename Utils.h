#pragma once

#include <cstdint>
#include <exception>

namespace halg
{
	typedef std::size_t uint;

	template< typename T >
	T & Max( T & val1, T & val2 )
	{
		if( val1 > val2 )
			return val1;
		else
			return val2;
	}

	class SizeMismatch : public std::exception
	{
	public:
		SizeMismatch() noexcept {}
		SizeMismatch(
				SizeMismatch const & source ) noexcept
		{
			*this = source;
		}
		SizeMismatch & operator = (
				SizeMismatch const & ) noexcept
		{
			return *this;
		}
		virtual const char* what() const noexcept
		{
			return "Performing operations such as addition "
				   "on Matrices of different size.";
		}
	};
	class ColRowBaseMismatch : public std::exception
	{
	public:
		ColRowBaseMismatch() noexcept {}
		ColRowBaseMismatch(
				ColRowBaseMismatch const & source ) noexcept
		{
			*this = source;
		}
		ColRowBaseMismatch & operator = (
				ColRowBaseMismatch const & ) noexcept
		{
			return *this;
		}
		virtual const char* what() const noexcept
		{
			return "Performing operations on "
				   "MatrixCols or MatrixRows "
				   "of different Matrices";
		}
	};
}
