#pragma once

#include "Function.h"
#include "Vector.h"

namespace halg
{
class VectorFunc : public Vector< Function * >
{
    VectorFunc( halg::uint size )
        : Vector( size )
    { }
    VectorFunc( const Vector< Function * > & src )
        : Vector( src )
    { }
    Vector< double > Value( halg::VarVals const & args) const
    {
        Vector< double > result( Size( ) );
        for( halg::uint id = 0; id < Size( ); ++id )
        {
            result[ id ] = (*this)[ id ]->Value( args );
        }
        return result;
    }
    operator std::string( ) const
    {
        return "TODO";
    }
    VectorFunc Derivative( std::string const & varName ) const
    {
        VectorFunc result( Size( ) );
        for( halg::uint id = 0; id < Size( ); ++id )
        {
            result[ id ] = (*this)[ id ]->Derivative( varName );
        }
        return result;
    }
    VectorFunc Copy( ) const
    {
        VectorFunc result( Size( ) );
        for( halg::uint id = 0; id < Size( ); ++id )
        {
            result[ id ] = (*this)[ id ]->Copy( );
        }
        return result;
    }
    bool IsConst( ) const
    {
        for( halg::uint id = 0; id < Size( ); ++id )
        {
            if( !(*this)[ id ]->IsConst( ) ) return false;
        }
        return true;
    }
};
}
