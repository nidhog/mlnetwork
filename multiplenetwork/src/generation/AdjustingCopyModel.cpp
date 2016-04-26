/*
 * BAEvolutionModel.cpp
 *
 *  Created on: 13/ago/2013
 *      Author: matteo.magnani
 */

#include "generation.h"
#include "datastructures.h"
#include <set>
#include <iostream>
#include <string>

using namespace std;

namespace mlnet {


AdjustingCopyModel::~AdjustingCopyModel() {
}

void AdjustingCopyModel::set_params(int number_of_layers, int number_of_actors,
		std::string *single_layer_models,
		Target **interlayer_targets,
		Target *intralayer_targets){
	this->number_of_layers = number_of_layers;
	this->number_of_actors = number_of_actors;
	this->single_layer_models = single_layer_models;
	this->interlayer_targets = interlayer_targets;
	this->intralayer_targets = intralayer_targets;
}


}
