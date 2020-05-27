#pragma once

#include <memory>
#include <string>

class HeaderLog
{
	std::string header;

public:
	HeaderLog() {}
	HeaderLog( const char *str ) : header( str ) {}
	HeaderLog( const HeaderLog &other ) = delete;
	HeaderLog &operator=( const HeaderLog &other ) = delete;

	void trace( const char *str, bool newline = true );
	void warn( const char *str, bool newline = true );
	void info( const char *str, bool newline = true );
	void bad( const char *str, bool newline = true );
	void ok( const char *str, bool newline = true );
	void fatal( const char *str, bool newline = true );
	void set_header( const char *str );

private:
	void print( const char* color, const char *str, const char* end );
};

namespace Ramdan
{
	class Log
	{
	private:
		Log() {}
		static std::shared_ptr<HeaderLog> mCore;
		static std::shared_ptr<HeaderLog> mClient;

	public:
		Log( const Log &other ) = delete;
		Log operator=( const Log &other ) = delete;

		inline static std::shared_ptr<HeaderLog> &get_core() { return mCore; }
		inline static std::shared_ptr<HeaderLog> &get_client() { return mClient; }

		static void init() { init( "Core", "Client" ); }
		static void init( const char *core_header, const char *client_header )
		{
			if ( mCore == nullptr )
			{
				mCore = std::make_shared<HeaderLog>( core_header );
			}
			if ( mClient == nullptr )
			{
				mClient = std::make_shared<HeaderLog>( client_header );
			}
		}
		static void update_header( const char *core_header, const char *client_header )
		{
			if ( mCore && mClient != nullptr )
			{
				mCore->set_header( core_header );
				mClient->set_header( client_header );
			}
		}
	};
}

//core log macros
#ifdef  LOG_CORE
#define LOG_CORE_NOHEAD(...)          printf(__VA_ARGS__)
#define LOG_CORE_CLEAR(...)		      printf("\r                               \r");
#define LOG_CORE_TRACE(...)           Ramdan::Log::get_core()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)            Ramdan::Log::get_core()->info(__VA_ARGS__)
#define LOG_CORE_OK(...)              Ramdan::Log::get_core()->ok(__VA_ARGS__)
#define LOG_CORE_WARN(...)            Ramdan::Log::get_core()->warn(__VA_ARGS__)
#define LOG_CORE_BAD(...)             Ramdan::Log::get_core()->bad(__VA_ARGS__)
#define LOG_CORE_FATAL(...)           Ramdan::Log::get_core()->fatal(__VA_ARGS__)
#define LOG_CORE_TRACE_INLINE(...)    Ramdan::Log::get_core()->trace( __VA_ARGS__, false)
#define LOG_CORE_INFO_INLINE(...)     Ramdan::Log::get_core()->info(__VA_ARGS__, false)
#define LOG_CORE_OK_INLINE(...)       Ramdan::Log::get_core()->ok(__VA_ARGS__, false)
#define LOG_CORE_WARN_INLINE(...)     Ramdan::Log::get_core()->warn(__VA_ARGS__, false)
#define LOG_CORE_BAD_INLINE(...)      Ramdan::Log::get_core()->bad(__VA_ARGS__, false)
#define LOG_CORE_FATAL_INLINE(...)    Ramdan::Log::get_core()->fatal(__VA_ARGS__, false)
#define LOG_CORE_NEWLINE()			  std::cout << std::endl
#else
#define LOG_CORE_NOHEAD(...)   
#define LOG_CORE_CLEAR(...)
#define LOG_CORE_TRACE(...)        
#define LOG_CORE_INFO(...)         
#define LOG_CORE_OK(...)           
#define LOG_CORE_WARN(...)         
#define LOG_CORE_BAD(...)          
#define LOG_CORE_FATAL(...)        
#define LOG_CORE_TRACE_INLINE(...) 
#define LOG_CORE_INFO_INLINE(...)  
#define LOG_CORE_OK_INLINE(...)    
#define LOG_CORE_WARN_INLINE(...)  
#define LOG_CORE_BAD_INLINE(...)   
#define LOG_CORE_FATAL_INLINE(...) 
#define LOG_CORE_NEWLINE()
#endif
							
//client log macros
#define LOG_NOHEAD(...)               printf(__VA_ARGS__)
#define LOG_CLEAR(...)		          printf("\r                               \r");
#define LOG_TRACE(...)                Ramdan::Log::get_client()->trace( __VA_ARGS__)
#define LOG_INFO(...)                 Ramdan::Log::get_client()->info(__VA_ARGS__)
#define LOG_OK(...)                   Ramdan::Log::get_client()->ok(__VA_ARGS__)
#define LOG_WARN(...)                 Ramdan::Log::get_client()->warn(__VA_ARGS__)
#define LOG_BAD(...)                  Ramdan::Log::get_client()->bad(__VA_ARGS__)
#define LOG_FATAL(...)                Ramdan::Log::get_client()->fatal(__VA_ARGS__)
#define LOG_TRACE_INLINE(...)         Ramdan::Log::get_client()->trace( __VA_ARGS__, false)
#define LOG_INFO_INLINE(...)          Ramdan::Log::get_client()->info(__VA_ARGS__, false)
#define LOG_OK_INLINE(...)            Ramdan::Log::get_client()->ok(__VA_ARGS__, false)
#define LOG_WARN_INLINE(...)          Ramdan::Log::get_client()->warn(__VA_ARGS__, false)
#define LOG_BAD_INLINE(...)           Ramdan::Log::get_client()->bad(__VA_ARGS__, false)
#define LOG_FATAL_INLINE(...)         Ramdan::Log::get_client()->fatal(__VA_ARGS__, false)
#define LOG_NEWLINE()			      std::cout << std::endl

#ifdef LOG_CPU
#include "CPUMetrics.h"
#define LOG_CPU()					  Sleep( 250 ); s_CPUMetrics.GetCPULoad()
#define BENCH_CPU()					  Sleep( 250 ); s_CPUMetrics.BenchCPU()
#define GET_BENCH_RESULT(...)	      Sleep( 250 ); s_CPUMetrics.GetBenchCPU(__VA_ARGS__)
#define RESET_BENCH()				  Sleep( 250 ); s_CPUMetrics.ResetBench()
#else

#endif

#ifdef LOG_MEM
#include "AllocationMetrics.h"
#define LOG_MEM()					  PrintMemoryUsage()
#else
#define LOG_MEM()
#endif