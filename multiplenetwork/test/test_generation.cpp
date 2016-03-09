
#include "test.h"
#include "mlnetwork.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <iostream>
#include <sstream>
#include <string>

using namespace mlnet;

void test_generation() {
	{
		test_begin("GENERATION");
	log("[generation Test R1] N1: larger independent, N2: smaller independent and with basic random graph generation model");
	// create multiplex network
	MLNetworkSharedPtr mnet = MLNetwork::create("synt1");
	LayerSharedPtr layer1 = mnet->add_layer("L1",true);
	LayerSharedPtr layer2 = mnet->add_layer("L2",true);
	// set generation parameters
	long num_of_steps = 100;
	long num_of_actors = 1000;
	std::vector<double> pr_no_event = {0.0,0.3};
	std::vector<double> pr_internal_event = {1.0,1.0};
	matrix<double> dependency = {{0, 1}, {1, 0}};
	BAEvolutionModel ba(3,2);
	UniformEvolutionModel ra(70);
	std::vector<EvolutionModel*> evolution_model = {&ba, &ra};
	evolve(mnet,num_of_steps,num_of_actors,pr_no_event,pr_internal_event,dependency,evolution_model);
	log(mnet->to_string());
	//log("Edge Jaccard similarity: " + to_string(jaccard_similarity(mnet,layer1,layer2)));
	log("Assortativity: " + to_string(assortativity(mnet,layer1,layer2,OUT)));
	}

	{
	log("[generation Test R2] N1: larger independent, N2: smaller dependent on N1, both with basic random graph generation model");
	MLNetworkSharedPtr mnet = MLNetwork::create("synt1");
	LayerSharedPtr layer1 = mnet->add_layer("L1",true);
	LayerSharedPtr layer2 = mnet->add_layer("L2",true);
	// set generation parameters
	long num_of_steps = 100;
	long num_of_actors = 1000;
	std::vector<double> pr_no_event = {0.0,0.3};
	std::vector<double> pr_internal_event = {1.0,0.5};
	matrix<double> dependency = {{0, 1}, {1, 0}};
	UniformEvolutionModel ra(30);
	std::vector<EvolutionModel*> evolution_model = {&ra, &ra};
	evolve(mnet,num_of_steps,num_of_actors,pr_no_event,pr_internal_event,dependency,evolution_model);
	log(mnet->to_string());
	//log("Edge Jaccard similarity: " + to_string(jaccard_similarity(mnet,layer1,layer2)));
	log("Assortativity: " + to_string(assortativity(mnet,layer1,layer2,OUT)));
	}
	test_end("GENERATION");

}

