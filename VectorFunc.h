#pragma once

#include "Function.h"
#include "Vector.h"

namespace halg
{
class VectorFunc : public Function , public Vector< Function * >
{
    Vector< double > Value( halg::VarVals const & args) const override
    {
        Vector< double > result( Size( ) );
        for( halg::uint id = 0; id < Size( ); ++id )
        {
            reuslt[ id ] = (*this)[ id ]->Value( args );
        }
        return result;
    }
    operator std::string( ) const override
    {
        return "TODO";
    }
    VectorFunc Derivative( std::string const & varName ) const override
    {
        Vector< double > result( Size( ) );
        for( halg::uint id = 0; id < Size( ); ++id )
        {
            reuslt[ id ] = (*this)[ id ]->Derivative( varName );
        }
        return result;
    }
    VectorFunc Copy( ) const override
    {
        Vector< double > result( Size( ) );
        for( halg::uint id = 0; id < Size( ); ++id )
        {
            reuslt[ id ] = (*this)[ id ]->Copy( );
        }
        return result;
    }
    bool IsConst( ) const override
    {
        for( halg::uint id = 0; id < Size( ); ++id )
        {
            if( !(*this)[ id ]->IsConst( ) ) return false;
        }
        return true;
    }
};
}
