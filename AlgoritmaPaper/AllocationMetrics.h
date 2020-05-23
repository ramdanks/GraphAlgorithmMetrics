#pragma once
#include <iostream>
#define LOG_MEM() PrintMemoryUsage()

struct AllocationMetrics
{
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentMemoryUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void *operator new( size_t size )
{
	s_AllocationMetrics.TotalAllocated += size;
	return malloc( size );
}

void operator delete( void *ptr, size_t size )
{
	s_AllocationMetrics.TotalFreed += size;
	free( ptr );
}

void PrintMemoryUsage()
{
	std::cout << "[Memory]:" << s_AllocationMetrics.CurrentMemoryUsage() << " (Bytes)" << std::endl;
}