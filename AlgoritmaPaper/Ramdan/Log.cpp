#include "Log.h"
#include <stdio.h>

#ifndef COLOR_LOG
#define COLOR_LOG

#define RST   "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#endif

namespace Ramdan
{
	std::shared_ptr<HeaderLog> Log::mCore;
	std::shared_ptr<HeaderLog> Log::mClient;
}

void HeaderLog::trace( const char *str, bool newline )
{
	newline ? print( KWHT, str, "\n" ) : print( KWHT, str, "" );
}

void HeaderLog::warn( const char *str, bool newline )
{
	newline ? print( KYEL, str, "\n" ) : print( KYEL, str, "" );
}

void HeaderLog::info( const char *str, bool newline )
{
	newline ? print( KCYN, str, "\n" ) : print( KCYN, str, "" );
}

void HeaderLog::bad( const char *str, bool newline )
{
	newline ? print( KRED, str, "\n" ) : print( KRED, str, "" );
}

void HeaderLog::ok( const char *str, bool newline )
{
	newline ? print( KGRN, str, "\n" ) : print( KGRN, str, "" );
}

void HeaderLog::fatal( const char *str, bool newline )
{
	newline ? print( KMAG, str, "\n" ) : print( KMAG, str, "" );
}

void HeaderLog::set_header( const char *str )
{
	if ( !this->header.empty() )	this->header.clear();
	this->header = str;
}

void HeaderLog::print( const char *color, const char *str, const char *end )
{
	printf( "[%s]:%s%s%s%s", this->header.c_str(), color, str, end, RST );
}