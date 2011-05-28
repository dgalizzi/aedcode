/*
 *  catch_capture.hpp
 *  Catch
 *
 *  Created by Phil on 18/10/2010.
 *  Copyright 2010 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#ifndef TWOBLUECUBES_CATCH_CAPTURE_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_CAPTURE_HPP_INCLUDED

#include "catch_resultinfo.hpp"
#include "catch_result_type.h"
#include "catch_interfaces_capture.h"
#include "catch_debugger.hpp"
#include "catch_evaluate.hpp"
#include "catch_hub.h"
#include "catch_common.h"
#include <sstream>

namespace Catch
{
namespace Detail
{
    // The following code, contributed by Sam Partington, allows us to choose an implementation
    // of toString() depending on whether a << overload is available
    
    struct NonStreamable
    {
        // allow construction from anything...
        template<typename Anything> 
        NonStreamable(Anything)
        {}
    };
    
    // a local operator<<  which may be called if there isn't a better one elsewhere...
    inline NonStreamable operator << ( std::ostream&, const NonStreamable& ns )
    {
        return ns;
    }

    template<typename T>
    struct IsStreamable
    {
        static NoType Deduce( const NonStreamable& );
        static YesType Deduce( std::ostream& );

        enum
        {
            value = sizeof( Deduce( Synth<std::ostream&>() << Synth<const T&>() ) ) 
                        == sizeof( YesType )
        };
    };
    
    // << is available, so use it with ostringstream to make the string
    template<typename T, bool streamable>
    struct StringMaker
    {
        ///////////////////////////////////////////////////////////////////////
        static std::string apply
        (
            const T& value
        )
        {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
    };
      
    // << not available - use a default string
    template<typename T>
    struct StringMaker<T, false>
    {
        ///////////////////////////////////////////////////////////////////////
        static std::string apply
        (
            const T&
        )
        {
            return "{?}";
        }
    };

}// end namespace Detail

///////////////////////////////////////////////////////////////////////////////
template<typename T>
std::string toString
(
    const T& value
)
{
    return Detail::StringMaker<T, Detail::IsStreamable<T>::value>::apply( value );
}
    
// Shortcut overloads

///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    const std::string& value
)
{
    return "\"" + value + "\"";
}

///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    const std::wstring& value
)
{
    std::ostringstream oss;
    oss << "\"";
    for(size_t i = 0; i < value.size(); ++i )
        oss << static_cast<char>( value[i] <= 0xff ? value[i] : '?');
    oss << "\"";
    return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    const char* const value
)
{
    return value ? Catch::toString( std::string( value ) ) : std::string( "{null string}" );
}   

///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    char* const value
)
{
    return Catch::toString( static_cast<const char* const>( value ) );
}        

///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    int value
)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    unsigned int value
)
{
    std::ostringstream oss;
    if( value > 8192 )
        oss << "0x" << std::hex << value;
    else
        oss << value;
    return oss.str();
}
    
///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    unsigned long value
)
{
    std::ostringstream oss;
    if( value > 8192 )
        oss << "0x" << std::hex << value;
    else
        oss << value;
    return oss.str();
}
    
///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    const double value 
)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}    

///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    bool value
)
{
    return value ? "true" : "false";
}

///////////////////////////////////////////////////////////////////////////////
inline std::string toString
(
    void* p
)
{
    if( !p )
        return INTERNAL_CATCH_STRINGIFY( NULL );
    std::ostringstream oss;
    oss << p;
    return oss.str();
}
    
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline std::string toString
(
    T* p
)
{
    return Catch::toString( static_cast<void*>( p ) );
}
    
///////////////////////////////////////////////////////////////////////////////
template<typename T>
inline std::string toString
(
    const T* p
)
{
    return Catch::toString( static_cast<void*>( const_cast<T*>( p ) ) );
}
    
struct TestFailureException
{
};
struct DummyExceptionType_DontUse
{
};
struct STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison;
    
class MutableResultInfo : public ResultInfo
{
public:
    
    ///////////////////////////////////////////////////////////////////////////
    MutableResultInfo
    ()
    {}
    
    ///////////////////////////////////////////////////////////////////////////
    MutableResultInfo
    (
        const char* expr, 
        bool isNot, 
        const char* filename, 
        std::size_t line, 
        const char* macroName,
        const char* message = ""
    )
    : ResultInfo( expr, ResultWas::Unknown, isNot, filename, line, macroName, message )
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    void setResultType
    (
        ResultWas::OfType result
    )
    {
        // Flip bool results if isNot is set
        if( m_isNot && result == ResultWas::Ok )
            m_result = ResultWas::ExpressionFailed;
        else if( m_isNot && result == ResultWas::ExpressionFailed )
            m_result = ResultWas::Ok;
        else
            m_result = result;        
    }

    ///////////////////////////////////////////////////////////////////////////
    void setMessage
    (
        const std::string& message
    )
    {
        m_message = message;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    void setFileAndLine
    (
        const std::string& filename,
        std::size_t line
    )
    {
        m_filename = filename;
        m_line = line;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator ||
    (
        const RhsT&
    );

    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator &&
    (
        const RhsT&
    );
    
private:
    friend class ResultBuilder;
    template<typename T> friend class Expression;

    template<typename T> friend class PtrExpression;

    ///////////////////////////////////////////////////////////////////////////
    MutableResultInfo& captureBoolExpression
    (
        bool result
    )
    {
        m_lhs = Catch::toString( result );
        m_op = m_isNot ? "!" : "";
        setResultType( result ? ResultWas::Ok : ResultWas::ExpressionFailed );
        return *this;
    }    

    ///////////////////////////////////////////////////////////////////////////
    template<Internal::Operator Op, typename T1, typename T2>    
    MutableResultInfo& captureExpression
    (
        const T1& lhs, 
        const T2& rhs
    )
    {
        setResultType( Internal::compare<Op>( lhs, rhs ) ? ResultWas::Ok : ResultWas::ExpressionFailed );
        m_lhs = Catch::toString( lhs );
        m_rhs = Catch::toString( rhs );
        m_op = Internal::OperatorTraits<Op>::getName();
        return *this;
    }
    
};

template<typename T>
class Expression
{
	void operator = ( const Expression& );

public:
    ///////////////////////////////////////////////////////////////////////////
    Expression
    (
        MutableResultInfo& result, 
        const T& lhs 
    )
    :   m_result( result ),
        m_lhs( lhs )
    {
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    MutableResultInfo& operator == 
    (
        const RhsT& rhs
    )
    {
        return m_result.captureExpression<Internal::IsEqualTo>( m_lhs, rhs );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    MutableResultInfo& operator != 
    (
        const RhsT& rhs
    )
    {
        return m_result.captureExpression<Internal::IsNotEqualTo>( m_lhs, rhs );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    MutableResultInfo& operator <
    (
        const RhsT& rhs
    )
    {
        return m_result.captureExpression<Internal::IsLessThan>( m_lhs, rhs );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    MutableResultInfo& operator >
    (
        const RhsT& rhs
    )
    {
        return m_result.captureExpression<Internal::IsGreaterThan>( m_lhs, rhs );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    MutableResultInfo& operator <= 
    (
        const RhsT& rhs
    )
    {
        return m_result.captureExpression<Internal::IsLessThanOrEqualTo>( m_lhs, rhs );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    MutableResultInfo& operator >= 
    (
        const RhsT& rhs
    )
    {
        return m_result.captureExpression<Internal::IsGreaterThanOrEqualTo>( m_lhs, rhs );
    }

    ///////////////////////////////////////////////////////////////////////////
    operator MutableResultInfo&
    ()
    {
        return m_result.captureBoolExpression( m_lhs );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator +
    (
        const RhsT&
    );
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator -
    (
        const RhsT&
    );

private:
    MutableResultInfo& m_result;
    const T& m_lhs;
};
    
template<typename LhsT> 
class PtrExpression
{
public:

    ///////////////////////////////////////////////////////////////////////////
    PtrExpression
    (
        MutableResultInfo& result, 
        const LhsT* lhs 
    )
    :   m_result( &result ),
        m_lhs( lhs )
    {}
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    MutableResultInfo& operator == 
    (
        const RhsT* rhs
    )
    {
        return m_result->captureExpression<Internal::IsEqualTo>( m_lhs, rhs );
    }

    ///////////////////////////////////////////////////////////////////////////
    // This catches NULL
    MutableResultInfo& operator == 
    (
        LhsT* rhs
    )
    {
        return m_result->captureExpression<Internal::IsEqualTo>( m_lhs, rhs );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename RhsT>
    MutableResultInfo& operator != 
    (
        const RhsT* rhs
    )
    {
        return m_result->captureExpression<Internal::IsNotEqualTo>( m_lhs, rhs );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    // This catches NULL
    MutableResultInfo& operator != 
    (
        LhsT* rhs
    )
    {
        return m_result->captureExpression<Internal::IsNotEqualTo>( m_lhs, rhs );
    }

    ///////////////////////////////////////////////////////////////////////////
    operator MutableResultInfo&
    ()
    {
        return m_result->captureBoolExpression( m_lhs );
    }
    
    
private:
    MutableResultInfo* m_result;
    const LhsT* m_lhs;
};
    
class ResultBuilder
{
public:

    ///////////////////////////////////////////////////////////////////////////
    ResultBuilder
    (
        const char* filename, 
        std::size_t line, 
        const char* macroName,
        const char* expr = "",
        bool isNot = false
    )
    : m_result( expr, isNot, filename, line, macroName )
    {}
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename T>
    Expression<T> operator->*
    (
        const T & operand
    )
    {
        Expression<T> expr( m_result, operand );
        
        return expr;
    }

    ///////////////////////////////////////////////////////////////////////////
    template<typename T>
    PtrExpression<T> operator->*
    (
        const T* operand
    )
    {
        PtrExpression<T> expr( m_result, operand );
        
        return expr;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename T>
    PtrExpression<T> operator->*
    (
        T* operand
    )
    {
        PtrExpression<T> expr( m_result, operand );
        
        return expr;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template<typename T>
    ResultBuilder& operator <<
    (
        const T & value
    )
    {
        m_messageStream << Catch::toString( value );        
        return *this;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    ResultBuilder& setResultType
    (
        ResultWas::OfType resultType
    )
    {
        m_result.setResultType( resultType );
        return *this;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    operator MutableResultInfo&
    ()
    {
        m_result.setMessage( m_messageStream.str() );
        return m_result;
    }
    
private:
    MutableResultInfo m_result;
    std::ostringstream m_messageStream;
    
};

class ScopedInfo
{
public:
    ///////////////////////////////////////////////////////////////////////////
    ScopedInfo
    ()
    {
        Hub::getResultCapture().pushScopedInfo( this );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    ~ScopedInfo
    ()
    {
        Hub::getResultCapture().popScopedInfo( this );
    }
    
    ///////////////////////////////////////////////////////////////////////////
    ScopedInfo& operator << 
    (
        const char* str
    )
    {
        m_oss << str;
        return *this; 
    }
    
    ///////////////////////////////////////////////////////////////////////////
    std::string getInfo
    ()
    const
    {
        return m_oss.str();
    }
    
private:
    std::ostringstream m_oss;
};
        
///////////////////////////////////////////////////////////////////////////////
// This is just here to avoid compiler warnings with macro constants
inline bool isTrue
(
    bool value
)
{
    return value;
}
    
} // end namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_ACCEPT_EXPR( expr, stopOnFailure ) \
    if( Catch::ResultAction::Value action = Catch::Hub::getResultCapture().acceptExpression( expr )  ) \
    { \
        if( action == Catch::ResultAction::DebugFailed ) BreakIntoDebugger(); \
        if( Catch::isTrue( stopOnFailure ) ) throw Catch::TestFailureException(); \
    }

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TEST( expr, isNot, stopOnFailure, macroName ) \
    INTERNAL_CATCH_ACCEPT_EXPR( ( Catch::ResultBuilder( __FILE__, __LINE__, macroName, #expr, isNot )->*expr ), stopOnFailure ); \
    if( Catch::isTrue( false ) ){ bool dummyResult = ( expr ); Catch::isTrue( dummyResult ); }

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_NO_THROW( expr, stopOnFailure, macroName ) \
    try \
    { \
        expr; \
        INTERNAL_CATCH_ACCEPT_EXPR( Catch::ResultBuilder( __FILE__, __LINE__, macroName, #expr ).setResultType( Catch::ResultWas::Ok ), stopOnFailure ); \
    } \
    catch( std::exception& ex ) \
    { \
        INTERNAL_CATCH_ACCEPT_EXPR( ( Catch::ResultBuilder( __FILE__, __LINE__, macroName, #expr ) << ex.what() ).setResultType( Catch::ResultWas::ThrewException ), stopOnFailure ); \
    } \
    catch( ... ) \
    { \
        INTERNAL_CATCH_ACCEPT_EXPR( ( Catch::ResultBuilder( __FILE__, __LINE__, macroName, #expr ) << Catch::Hub::getExceptionTranslatorRegistry().translateActiveException() ).setResultType( Catch::ResultWas::ThrewException ), stopOnFailure ); \
    }

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS( expr, exceptionType, stopOnFailure, macroName ) \
    try \
    { \
        expr; \
        INTERNAL_CATCH_ACCEPT_EXPR( Catch::ResultBuilder( __FILE__, __LINE__, macroName, #expr ).setResultType( Catch::ResultWas::DidntThrowException ), stopOnFailure ); \
    } \
    catch( Catch::TestFailureException& ) \
    { \
        throw; \
    } \
    catch( exceptionType ) \
    { \
        INTERNAL_CATCH_ACCEPT_EXPR( Catch::ResultBuilder( __FILE__, __LINE__, macroName, #expr ).setResultType( Catch::ResultWas::Ok ), stopOnFailure ); \
    }

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_AS( expr, exceptionType, stopOnFailure, macroName ) \
    INTERNAL_CATCH_THROWS( expr, exceptionType, stopOnFailure, macroName ) \
    catch( ... ) \
    { \
        INTERNAL_CATCH_ACCEPT_EXPR( ( Catch::ResultBuilder( __FILE__, __LINE__, macroName, #expr ) << Catch::Hub::getExceptionTranslatorRegistry().translateActiveException() ).setResultType( Catch::ResultWas::ThrewException ), stopOnFailure ); \
    }

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_MSG( reason, resultType, stopOnFailure, macroName ) \
    Catch::Hub::getResultCapture().acceptExpression( ( Catch::ResultBuilder( __FILE__, __LINE__, macroName ) << reason ).setResultType( resultType ) );

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_SCOPED_INFO( log ) \
    Catch::ScopedInfo INTERNAL_CATCH_UNIQUE_NAME( info ); \
    INTERNAL_CATCH_UNIQUE_NAME( info ) << log

#endif // TWOBLUECUBES_CATCH_CAPTURE_HPP_INCLUDED
