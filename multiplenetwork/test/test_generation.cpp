
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
		log("[Generation Test transp_London] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			MLNetworkSharedPtr mnet = read_multilayer("test/data/transp_London.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			double measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "transp_London.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Arabidopsis] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Arabidopsis.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Arabidopsis.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Arxiv] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Arxiv.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Arxiv.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test aucs] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/aucs.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "aucs.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Celegans] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Celegans.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Celegans.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Fao] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Fao.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Fao.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Noordin] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Noordin.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Noordin.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Padgett] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Padgett.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Padgett.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test transp_Airlines] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/transp_Airlines.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "transp_Airlines.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Kaptail] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			mnet = read_multilayer("test/data/Kaptail.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Kaptail.csv");
			std::cout << "Done!\n" << std::endl;
		log("[Generation Test Wiring] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...\n";
			 mnet = read_multilayer("test/data/Wiring.csv","mlnet 2",',');
			std::cout << "Testing degree...\n";
			measure = average_nearest_actor_centrality(mnet,"DEGREE",level,exact_level, "Wiring.csv");
			std::cout << "Done!\n" << std::endl;
			test_end("GENERATION");

	}

