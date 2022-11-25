#pragma once
#include "Layer.h"
#include <tuple>
#include <vector>

class NeuralNetwork {
public:
	NeuralNetwork() {

		for (int i = 1; i < m_NetworkShape.size(); i++) {
			int numInputs = m_NetworkShape[i - 1];
			int numNodes = m_NetworkShape[i];
			m_HiddenLayers.push_back(new Layer(numInputs, numNodes));
			m_HiddenLayers.at(i - 1)->RandomizeWeightsAndBiases();
		}

	}

	std::tuple<float*, size_t> Brain(float* inputs, size_t numInputs) {
		if (m_HiddenLayers.size() < 1) return std::tuple<float*, size_t>(0, 0);

		numInputs = m_NetworkShape[0];
		Layer* layer = nullptr;
		for (int i = 0; i < m_HiddenLayers.size(); i++) {
			 layer = m_HiddenLayers.at(i);
			if (i == 0) {
				layer->ForwardPass(inputs, numInputs);
				layer->ActivationReLU();
			}
			else {
				Layer* lastLayer = m_HiddenLayers.at(i - 1);
				layer->ForwardPass(lastLayer->nodes, lastLayer->m_NNodes);
				
				if(i != (m_HiddenLayers.size() - 1))
					layer->ActivationReLU();
			}

		}

		return std::tuple<float*, size_t>(layer->nodes, layer->m_NNodes);
	}

	std::vector<Layer*> m_HiddenLayers;
	std::vector<int> m_NetworkShape = {1, 4, 4, 1};
};