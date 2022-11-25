#pragma once
#include <functional>
#include <chrono>
#include <string>
#include <iostream>
#include <math.h>

long long BenchmarkFunctionUS(std::function<void()> fun, std::string benchmarkName) {
	auto before = std::chrono::high_resolution_clock::now();
	fun();
	auto after = std::chrono::high_resolution_clock::now();

	auto elapsed = after - before;
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	if (us > pow(10, 3)) {
		std::cout << benchmarkName << " took " << std::to_string((float)us / pow(10, 3)) << "us";

	}else
		std::cout << benchmarkName << " took " << std::to_string(us) << "us";
	return us;
}
