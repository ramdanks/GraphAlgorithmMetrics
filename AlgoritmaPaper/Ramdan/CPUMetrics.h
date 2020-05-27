#pragma once
#include <Windows.h>

class CPUMetrics
{
    float CPU_Total_Load;
    unsigned int CPU_Total_Count;

private:
    static float CalculateCPULoad( unsigned long long idleTicks, unsigned long long totalTicks )
    {
        static unsigned long long _previousTotalTicks = 0;
        static unsigned long long _previousIdleTicks = 0;

        unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
        unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

        float ret = 1.0f - ( ( totalTicksSinceLastTime > 0 ) ? ( (float)idleTicksSinceLastTime ) / totalTicksSinceLastTime : 0 );

        _previousTotalTicks = totalTicks;
        _previousIdleTicks = idleTicks;
        return ret;
    }

    static unsigned long long FileTimeToInt64( const FILETIME &ft )
    {
        return ( ( ( unsigned long long )( ft.dwHighDateTime ) ) << 32 ) | ( ( unsigned long long )ft.dwLowDateTime );
    }

public:
    // Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
    // You'll need to call this at regular intervals, since it measures the load between
    // the previous call and the current one.  Returns -1.0 on error.
    float GetCPULoad()
    {
        FILETIME idleTime, kernelTime, userTime;
        return GetSystemTimes( &idleTime, &kernelTime, &userTime ) ? CalculateCPULoad( FileTimeToInt64( idleTime ), FileTimeToInt64( kernelTime ) + FileTimeToInt64( userTime ) ) : -1.0f;
    }

    void ResetBench()
    {
        CPU_Total_Load = 0.0f;
        CPU_Total_Count = 0;
    }

    void BenchCPU()
    {
        CPU_Total_Load += GetCPULoad();
        CPU_Total_Count++;
    }

    float GetBenchCPU( bool reset = false, bool print = true )
    {
        float BenchmarkResult = CPU_Total_Load / (float)CPU_Total_Count;
        if ( print )
            printf( "[CPU]:Usage[%.1f]%%\n", BenchmarkResult * 100.0f );
        if ( reset )
            ResetBench();
        return BenchmarkResult;
    }
};

CPUMetrics s_CPUMetrics;