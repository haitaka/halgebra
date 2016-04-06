#include "TextTable.h"

std::string halg::TextTable::Row::sm_default = "";

void halg::TextTable::PrintRow(
		std::ostream & oStream,
		halg::TextTable::Row const & row,
		std::vector< halg::uint > const & widths
	) const
{
	oStream << " | ";
	for ( halg::uint i = 0; i < GetColsCount( ); ++i )
    {
		oStream << std::setw( widths[ i ] )
				<< row[ i ] << " | ";
    }
	oStream << std::endl;

	PrintSep( oStream, widths );
}

void halg::TextTable::PrintSep(
		std::ostream & oStream,
		std::vector< halg::uint > const & widths
	) const
{
	oStream << "-+-";
	for ( halg::uint i = 0; i < GetColsCount( ); ++i )
	{
		for ( halg::uint j = 0; j < widths[ i ]; ++j )
		{
			oStream << "-";
		}
		oStream << "-+-";
	}
	oStream << std::endl;
}

std::vector< halg::uint >
halg::TextTable::CountWidths( ) const
{
	halg::uint colsCount = GetColsCount( );
	std::vector< halg::uint > widths( colsCount, 0 );
	for( halg::uint colId = 0;
		 colId < colsCount;
		 ++colId )
	{
		if ( widths[ colId ] < m_header[ colId ].length( ) )
		{
			 widths[ colId ] = m_header[ colId ].length( );
		}
		for ( auto row: m_rows )
		{
			if ( widths[ colId ] < row[ colId ].length( ) )
				 widths[ colId ] = row[ colId ].length( );
		}
	}
	return widths;
}

halg::uint halg::TextTable::GetColsCount( ) const
{
	halg::uint count = m_header.Size( );
	for( auto row : m_rows )
	{
		count = halg::Max( count, row.Size( ) );
	}
	return count;
}
