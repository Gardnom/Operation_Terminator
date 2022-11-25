// Operation_Terminator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "NeuralNetwork.h";
#include "Matrix.h"
#include <iomanip>
#include "Timing.h"


int main()
{
	/*NeuralNetwork nn;
	float in[] = { 1 };
	nn.Brain(in, 1);
	while (true) {
		std::cout << "Give a number between 1-3 to the machine:";
		int x;
		std::cin >> x;
		float inputs[] = { x };
		auto[values, numValues] = nn.Brain(inputs, 1);
		printf("You get back: %.2f\n", values[0]);
		//printf("x: %d\n", x);

	}*/
	Matrix<float> mat(3, 3);
	
	
	for (int i = 0; i < mat.NumEntries(); i++) {
		mat.m_BackingArray[i] = i + 1;
	}
	auto mat2 = mat;
	try {
		//Matrix<float> mat2(3, 3);
		BenchmarkFunctionUS([&]() {

			auto mat3 = mat + mat2;

			std::cout << std::setprecision(2) << std::fixed;
			std::cout << mat;
			std::cout << "\n";

			std::cout << mat3 * 5;
		}, "Matrix addition");
	}
	catch (std::exception ex) {
		std::cout << ex.what();
	}



	std::cin.get();
}

