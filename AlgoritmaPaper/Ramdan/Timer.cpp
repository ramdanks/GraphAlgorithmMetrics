#include "Timer.h"
#include <iostream>
#include <direct.h>
#include <fstream>

namespace Ramdan
{
	Timer::Timer( std::string title, TimerPoint time, TimerOutput out )
		:
		mTitle(title),
		mTime(time),
		mOut(out)
	{
		Tic();
	}

	Timer::~Timer()
	{
		if ( mOut != NONE )
		{
			Toc();
			UpdateLogInfo();
			PrintLog();
		}
	}

	void Timer::Tic()
	{
		TimeLog = std::chrono::high_resolution_clock::now();
	}

	void Timer::Toc()
	{
		Duration = std::chrono::high_resolution_clock::now() - TimeLog;
	}

	void Timer::UpdateLogInfo()
	{
		mString.clear();
		TimerPoint TimePoint = mTime;
		if ( mTime == ADJUST )
		{
			if		( Duration.count() > 60 )				TimePoint = MIN;
			else if ( Duration.count() > 1 )				TimePoint = SEC;
			else if ( Duration.count() * 1000.0f > 1 )		TimePoint = MS;
			else if ( Duration.count() * 1000000.0f > 1 )	TimePoint = US;
		}
		switch ( TimePoint )
		{
		case MIN:
			mString = std::to_string( Duration.count() / MIN ) + " (min)"; break;
		case SEC:
			mString = std::to_string( Duration.count() * SEC ) + " (sec)"; break;
		case MS:
			mString = std::to_string( Duration.count() * MS ) + " (ms)"; break;
		case US:
			mString = std::to_string( Duration.count() * US ) + " (us)"; break;
		default:
			mString = std::to_string( Duration.count() * NS ) + " (ns)";  break;
		}	
	}

	std::string Timer::GetDurStr()
	{
		UpdateLogInfo();
		std::string DurString = mTitle + " Duration: " + mString;
		return DurString;
	}

	void Timer::PrintLog()
	{
		UpdateLogInfo();

		if ( mOut == CONSOLE )
		{
			std::cout << mTitle << " Duration: " << mString << std::endl;
		}
		else if ( mOut == WRITE )
		{
			if ( CreateFile() )
			{
				std::ofstream outfile( "Logdata/LogResult.txt", std::ios_base::app );
				if ( AlreadyHasTitle() )	outfile << mString << std::endl;
				else						outfile << "Logtime for : " << mTitle << std::endl << mString << std::endl;
				outfile.close();
			}
		}
	}

	float Timer::GetDur()
	{
		if ( mTime == MIN )		return Duration.count() / MIN;
		if ( mTime == SEC )		return Duration.count() * SEC;
		if ( mTime == MS )		return Duration.count() * MS;
		if ( mTime == US )		return Duration.count() * US;
		if ( mTime == NS )		return Duration.count() * NS;
		if ( mTime == ADJUST )	return Duration.count() * SEC;
	}

	bool Timer::CreateFile() const
	{
		std::ifstream file( "Logdata/LogResult.txt", std::ios_base::in );
		if ( !file.is_open() ) _mkdir( "Logdata" );
		file.close();
		return true;
	}

	bool Timer::AlreadyHasTitle() const
	{
		bool AlreadyHasTitle = false;
		std::string str; std::string title = "Logtime";
		std::ifstream file( "Logdata/LogResult.txt", std::ios_base::in ); // read file
		while ( getline( file, str ) )
		{
			if ( !AlreadyHasTitle )
				if ( str.substr( 14, str.length() - 14 ) == mTitle ) { AlreadyHasTitle = true; }

			if ( str.substr( 0, 7 ) == title )
				if ( str.substr( 14, str.length() - 14 ) != mTitle ) { AlreadyHasTitle = false; }
		}
		file.close();
		return AlreadyHasTitle;
	}
}
