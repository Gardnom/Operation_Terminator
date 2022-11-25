#pragma once
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <time.h>

class Layer
{
public:
	int m_NNodes, m_NInputs;
	float* nodes;
	float* biases;
	float** weights;

	Layer(int nInputs, int nNodes) {
		m_NNodes = nNodes;
		m_NInputs = nInputs;
		nodes = new float[nNodes];
		biases = new float[nNodes];
		
		// Initialize weigths array
		weights = new float*[nInputs];
		for (int i = 0; i < nInputs; i++) {
			weights[i] = new float[nNodes];
		}
	}

	void RandomizeWeightsAndBiases() {
		srand(time(NULL));
		for (int i = 0; i < m_NNodes; i++) {
			float random = ((double)rand() / RAND_MAX);
			biases[i] = random;
		}
		for (int i = 0; i < m_NInputs; i++) {
			for (int k = 0; k < m_NNodes; k++)
			{
				float random = ((double)rand() / RAND_MAX);
				weights[i][k] = random;
			}
		}
	}

	void ForwardPass(float* inputs, size_t numInputs) {
		// Reset nodes
		memset(nodes, 0, m_NNodes);
		for (int i = 0; i < m_NNodes; i++){
			float y = biases[i];
			for (int k = 0; k < m_NInputs; k++) {
				y += weights[k][i] * inputs[k];
			}
			nodes[i] = y;
		}
	}

	void ActivationReLU() {

		for (int i = 0; i < m_NNodes; i++)
		{
			// Todo: Make this branchless
			if (nodes[i] < 0) {
				nodes[i] = 0;
			}
		}
	}

	const int NWeights() noexcept {
		return m_NInputs * m_NNodes;
	}
};

