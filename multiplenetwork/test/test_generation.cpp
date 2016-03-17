
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
		log("[Generation Test R1] Testing average nearest actor centrality");
			std::cout << "Reading the multilayer network...";
			MLNetworkSharedPtr mnet = read_multilayer("test/io2.mpx","mlnet 2",',');
			std::cout << "Testing degree...";
			double measure = average_nearest_actor_centrality(mnet,"DEGREE",1,false);
			std::cout << "done!" << std::endl;
			test_end("GENERATION");

	}

