#ifndef ERROR_H_DEFINE_
#define ERROR_H_DEFINE_

#include <exception>
#include <string>

class TPluginException : public std::exception
{
public:
    TPluginException( const std::string _file,
                 int               _line,
                 const std::string _expression )
        : std::exception( _expression.c_str() ),
          file( _file ),
          line( _line ),
          expression( _expression )
    {
    }

    std::string file;
    int         line;
    std::string expression;
};

#define PluginAssert( x ) \
    if ( !( x ) )         \
    throw TPluginException( __FILE__, __LINE__, #x )

#define ErrCheck( err )           \
    if ( (int)err != A_Err_NONE ) \
    throw TPluginException( __FILE__, __LINE__, #err )

#endif
