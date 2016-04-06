#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "../Utils.h"

namespace halg
{
	class TextTable
    {
	public:
		struct Row
		{
		public:
			Row & operator << ( std::string const & str )
			{
				m_fields.push_back( str );
				return *this;
			}
			Row & operator << ( double num )
			{
				m_fields.push_back( std::to_string( num ) );
				return *this;
			}
			Row & operator << ( int num )
			{
				m_fields.push_back( std::to_string( num ) );
				return *this;
			}
			halg::uint Size( ) const {
				return m_fields.size( );
			}
			std::string const & operator [] ( halg::uint id ) const
			{
				if( id < m_fields.size( ) )
				{
					return m_fields[ id ];
				}
				return sm_default;
			}

		private:
			std::vector< std::string > m_fields;
			static std::string sm_default;
		};

		void SetHeader( halg::TextTable::Row const & header )
        {
			m_header = header;
        }
		void AddRow( halg::TextTable::Row const & row )
		{
			m_rows.push_back( row );
		}
		friend std::ostream & operator << (
				std::ostream & oStream,
				TextTable const & table
			)
		{
			std::vector< halg::uint > widths = table.CountWidths( );

			table.PrintSep( oStream, widths );
			table.PrintRow( oStream, table.m_header, widths );
			for ( auto row: table.m_rows )
			{
				table.PrintRow( oStream, row, widths );
			}
			return oStream;
		}
    private:
		void PrintRow(
				std::ostream & oStream,
				halg::TextTable::Row const & row,
				std::vector< halg::uint > const & widths
			) const;
		void PrintSep(
				std::ostream & output,
				std::vector< halg::uint > const & widths
			) const;
		std::vector< halg::uint > CountWidths( ) const;
		halg::uint GetColsCount( ) const;
    private:
		halg::TextTable::Row m_header;
		std::vector< halg::TextTable::Row > m_rows;
	};
}
