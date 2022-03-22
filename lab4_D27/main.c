#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#include "queen_solver.h"

#define STRESS_TEST_BOARD_SIZE 10
#define DIV 1048576

int main() {
	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	Cell* ans = queen_task_solver(STRESS_TEST_BOARD_SIZE);
	for (unsigned i = 0; i < STRESS_TEST_BOARD_SIZE; i++)
		fprintf(stdout, "%u %u\n", ans[i].row, ans[i].colomn);

	QueryPerformanceCounter(&end);
	printf("Working time %f\n", (double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
	HINSTANCE hProcHandle = GetModuleHandle(NULL);
	PROCESS_MEMORY_COUNTERS_EX memory;
	GetProcessMemoryInfo(hProcHandle, &memory, sizeof(memory));

	printf("\nMemory usage: %u MB", memory.PrivateUsage / DIV);
	return 0;
}







