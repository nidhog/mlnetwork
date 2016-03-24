
#include "test.h"
#include "mlnetwork.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <iostream>
#include <sstream>
#include <string>
#include "test.h"

using namespace mlnet;

void test_generation() {
		test_begin("GENERATION");
		bool exact_level = false;
		int level = 1;
		/*log("[Generation Test Higgs] Testing average nearest actor centrality");
		std::cout << "Reading the multilayer network...\n";
		MLNetworkSharedPtr mnet = read_multilayer("test/data/higgs-activity_time.csv","mlnet 2",',');
		std::cout << "Testing degree...\n";
		double measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "higgs");
		log("[Generation Test Higgs 2] Testing average nearest actor centrality");
			std::cout << "Testing 3 level degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",3,exact_level, "higgs");
			std::cout << "Done!\n" << std::endl;*/
		log("[Generation Test transp_London] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
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
					std::cout << "Done!\n" << std::endl;

			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Arabidopsis] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Arabidopsis.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Arabidopsis");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "Arabidopsis");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "Arabidopsis");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers2;
					for(LayerSharedPtr layer : layers_l){
						layers2.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers2);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers2, "Arabidopsis");
					jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers2, "Arabidopsis");
					coverage_mat = coverage_matrix(mnet, layers2, "Arabidopsis");
					assortativity_mat = assortativity_matrix(mnet, layers2, "Arabidopsis");
					std::cout << "Testing jaccard similarity...\n";
					std::cout << "Done!\n" << std::endl;
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Arxiv] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Arxiv.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Arxiv");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "Arxiv");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "Arxiv");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers3;
					for(LayerSharedPtr layer : layers_l){
						layers3.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers3);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers3, "Arxiv");
						jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers3, "Arxiv");
						coverage_mat = coverage_matrix(mnet, layers3, "Arxiv");
						assortativity_mat = assortativity_matrix(mnet, layers3, "Arxiv");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test aucs] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/aucs.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "aucs");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "aucs");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "aucs");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers4;
					for(LayerSharedPtr layer : layers_l){
						layers4.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers4);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers4, "aucs");
						jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers4, "aucs");
						coverage_mat = coverage_matrix(mnet, layers4, "aucs");
						assortativity_mat = assortativity_matrix(mnet, layers4, "aucs");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Celegans] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Celegans.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Celegans");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "Celegans");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "Celegans");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers5;
					for(LayerSharedPtr layer : layers_l){
						layers5.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers5);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers5, "Celegans");
						jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers5, "Celegans");
						coverage_mat = coverage_matrix(mnet, layers5, "Celegans");
						assortativity_mat = assortativity_matrix(mnet, layers5, "Celegans");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Fao] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Fao.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Fao");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "Fao");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "Fao");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers6;
					for(LayerSharedPtr layer : layers_l){
						layers6.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers6);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers6, "Fao");
						jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers6, "Fao");
						coverage_mat = coverage_matrix(mnet, layers6, "Fao");
						assortativity_mat = assortativity_matrix(mnet, layers6, "Fao");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Noordin] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Noordin.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Noordin");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "Noordin");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "Noordin");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers7;
					for(LayerSharedPtr layer : layers_l){
						layers7.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers7);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers7, "Noordin");
						jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers7, "Noordin");
						coverage_mat = coverage_matrix(mnet, layers7, "Noordin");
						assortativity_mat = assortativity_matrix(mnet, layers7, "Noordin");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Padgett] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Padgett.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Padgett");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "Padgett");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "Padgett");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers8;
					for(LayerSharedPtr layer : layers_l){
						layers8.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers8);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers8, "Padgett");
						jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers8, "Padgett");
						coverage_mat = coverage_matrix(mnet, layers8, "Padgett");
						assortativity_mat = assortativity_matrix(mnet, layers8, "Padgett");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test transp_Airlines] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/transp_Airlines.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "transp_Airlines");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "transp_Airlines");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "transp_Airlines");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers9;
					for(LayerSharedPtr layer : layers_l){
						layers9.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers9);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers9, "transp_Airlines");
						jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers9, "transp_Airlines");
						coverage_mat = coverage_matrix(mnet, layers9, "transp_Airlines");
						assortativity_mat = assortativity_matrix(mnet, layers9, "transp_Airlines");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Kaptail] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			mnet = read_multilayer("test/data/Kaptail.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Kaptail");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "Kaptail");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "Kaptail");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers10;
					for(LayerSharedPtr layer : layers_l){
						layers10.insert(layer);
					}
					 jaccard_sim = jaccard_similarity(mnet, layers10);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					 jaccard_mat = jaccard_similarity_matrix(mnet, layers10, "Kaptail");
						jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers10, "Kaptail");
						coverage_mat = coverage_matrix(mnet, layers10, "Kaptail");
						assortativity_mat = assortativity_matrix(mnet, layers10, "Kaptail");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Wiring] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Wiring.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Wiring");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+1,exact_level, "Wiring");
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level+2,exact_level, "Wiring");
			std::cout << "Testing total jaccard similarity...\n";
					  layers_l = mnet->get_layers();
					std::unordered_set<LayerSharedPtr> layers11;
					for(LayerSharedPtr layer : layers_l){
						layers11.insert(layer);
					}
					jaccard_sim = jaccard_similarity(mnet, layers11);
					std::cout<<jaccard_sim<<std::endl;
					std::cout << "Testing jaccard similarity matrix...\n";
					jaccard_mat = jaccard_similarity_matrix(mnet, layers11, "Wiring");
					jaccard_triangle_mat = jaccard_triangle_similarity_matrix(mnet, layers11, "Wiring");
					coverage_mat = coverage_matrix(mnet, layers11, "Wiring");
					assortativity_mat = assortativity_matrix(mnet, layers11, "Wiring");
					std::cout << "Testing jaccard similarity...\n";
			std::cout << "Done!\n" << std::endl;
			test_end("GENERATION");

	}

