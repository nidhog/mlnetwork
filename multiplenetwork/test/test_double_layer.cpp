
#include "test.h"
#include "mlnetwork.h"
#include "../include/mlnetwork.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <iostream>
#include <sstream>
#include <string>

using namespace mlnet;

void test_double_layer() {
	{
	log("[Double Layer Split Evolution] basic double layer split evolution model");
	// create multiplex network
	MLNetworkSharedPtr mnet = read_multilayer("test/data/ACModel_BA_copy.csv","mlnet 2",',');

	// BEGIN Getting Layers
	layer_list layers_l = mnet->get_layers();
	std::unordered_set<LayerSharedPtr> layers;
	for(LayerSharedPtr layer : layers_l){
		layers.insert(layer);
	}
	// END Getting Layers
/*
	std::cout<<"[.] NODE Jaccard :"<<std::endl;
	for(LayerSharedPtr layer1 : layers){

		for(LayerSharedPtr layer2 : layers){
			double jaccard_sim = jaccard_node_similarity(mnet, layer1, layer2);
			std::cout<<jaccard_sim<<" - ";

		}
		std::cout<<std::endl;
	}

	std::cout<<"[.] EDGE Jaccard :"<<std::endl;
	for(LayerSharedPtr layer1 : layers){

		for(LayerSharedPtr layer2 : layers){
			double jaccard_edge_sim = jaccard_similarity(mnet, layer1, layer2);
			std::cout<<jaccard_edge_sim<<" - ";

		}
		std::cout<<std::endl;
	}*/
		benchmark_adjust_error(mnet, "ACModel_BA_copy", "csv");
		//benchmark_dissortative_swap(mnet, "ACModel_BA_copy", "csv");
	}
}

