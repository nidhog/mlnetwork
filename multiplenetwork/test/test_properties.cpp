
#include "test.h"
#include "io.h"
#include "mlnetwork.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace mlnet;

void test_properties() {
		test_begin("PROPERTIES");
		log(1);
/*MERGE TODO
		const std::string test_networks[] = {"test/data/transp_London.csv", "test/data/transp_Airlines.csv",	"test/data/Arxiv.csv"
				, "test/data/Padgett.csv", "test/data/multi_BA_BA.csv", "test/data/multi_ER_ER.csv"
				, "test/data/TwYtFf.csv", "test/data/Higgs.csv", "test/data/Arabidopsis.csv"};
		std::map<std::string, std::string> name_map = {};
				name_map["test/data/transp_London.csv"]= "transp_London";
				name_map["test/data/transp_Airlines.csv"]= "transp_Airlines";
				name_map["test/data/Arxiv.csv"]= "Arxiv";
				name_map["test/data/Padgett.csv"]= "Padgett";
				name_map["test/data/multi_BA_BA.csv"]= "multi_BA_BA";
				name_map["test/data/multi_ER_ER.csv"]= "multi_ER_ER";
				name_map["test/data/TwYtFf.csv"]= "TwYtFf";
				name_map["test/data/Higgs.csv"]= "Higgs";
				name_map["test/data/Arabidopsis.csv"]= "Arabidopsis";
		// exporting data for R
		for(std::string network_path : test_networks){
			std::cout<<"[!] Generating Single layers for Network : "<<network_path<< std::endl;
			std::cout<<"[...] Reading from the file... "<< std::endl;
			MLNetworkSharedPtr mnet = read_multilayer(network_path,"mlnet 2",',');
			int max_layers = 4;
			int cnt_layers = 0;
			for (LayerSharedPtr layer: mnet->get_layers()){
				std::cout<<"[...] Printing layer... "<< "ID : "<< layer->id<< "- NAME: " << layer->name <<std::endl;
				std::unordered_set<LayerSharedPtr> layers;
				layers.insert(layer);
				cnt_layers++;
				write_graphml(mnet, layers
						,network_path+"_R_"+std::to_string(layer->id)+"_"+layer->name+".csv"
						,true);
				if(cnt_layers>=max_layers){
					break;
				}
			}
		}

		for(std::string network_path : test_networks){
			std::cout<<"[!] Generating Properties for Network : "<<network_path<< std::endl;
			std::cout<<"[...] Reading from the file... "<< std::endl;
			MLNetworkSharedPtr mnet = read_multilayer(network_path,"mlnet 2",',');
			generate_intralayer_properties(mnet);
			generate_interlayer_properties(mnet, name_map[network_path]);
			generate_correlations_features(mnet);
		}/*
			/*std::cout << "Reading the multilayer network...\n";
			MLNetworkSharedPtr mnet = read_multilayer("test/data/transp_London.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			double measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "transp_London");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "transp_London");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "transp_London");
			std::cout << "Testing total jaccard similarity...\n";
					layer_list layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers;
					for(LayerSharedPtr layer : layers_l){
						layers.insert(layer);
					}
					double jaccard_sim = jaccard_similarity(mnet, layers);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					bool jaccard_mat = jaccard_similarity_matrix(mnet, layers, "transp_London");
					bool jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers, "transp_London");
					bool coverage_mat = coverage_matrix(mnet, layers, "transp_London");
					bool assortativity_mat = assortativity_matrix(mnet, layers, "transp_London");
					std::cout << "Testing jaccard similarity...\n";
					std::cout << "Done!\n" << std::endl;*/
			test_end("PROPERTIES");

	}

