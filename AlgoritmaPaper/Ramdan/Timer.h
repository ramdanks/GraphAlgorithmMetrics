/*======================================*/
// Author	: Ramadhan Kalih Sewu		//
// About	: Logging (Timer)			//
/*======================================*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#pragma message("Benchmark")

#include <chrono>
#include <string>

enum TimerPoint { 
					MIN		= 60,
					SEC		= 1,
					MS		= 1000,
					US		= 1000000,
					NS		= 1000000000,
					ADJUST
				};

enum TimerOutput { CONSOLE, WRITE, NONE };

namespace Ramdan
{
	class Timer
	{
	public:
		Timer( std::string title = "Log", TimerPoint time = ADJUST, TimerOutput out = CONSOLE );
		~Timer();

	public:
		void Tic();
		void Toc();
		std::string GetDurStr();
		float GetDur();

	private:
		void UpdateLogInfo();		
		void PrintLog();

		bool CreateFile() const;
		bool AlreadyHasTitle() const;

	private:
		std::chrono::time_point<std::chrono::steady_clock> TimeLog;
		std::chrono::duration<float> Duration;

		TimerPoint mTime;
		TimerOutput mOut;

		std::string mTitle;
		std::string mString;
	};
}