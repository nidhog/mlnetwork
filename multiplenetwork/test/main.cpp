/*
 * This program runs all the unit tests defined for this library.
 */

#include "test.h"
#include <stdlib.h>

void test_begin(const std::string& name) {
	std::cout << "*************************************************" << std::endl;
	std::cout << "*************************************************" << std::endl;
	std::cout << "** TESTING: " << name << std::endl;
	std::cout << "*************************************************" << std::endl;
}

void test_end(const std::string& name) {
	std::cout << "*************************************************" << std::endl;
	std::cout << "** COMPLETED (" << name << ")" << std::endl;
	std::cout << "*************************************************" << std::endl;
	std::cout << std::endl;
}

int main(int argn, char* argv[]) {

	test_begin("All unit tests");
	try {
	//test_datastructures();
	//test_io();
	//test_measures();
	//test_transformations();
	//test_community();
	//test_dynamics();
	//test_evolution();
	//test_generation();
	//test_properties();
	test_double_layer();
	/*
	test_utils();
	test_datastructures();
	test_io();
	test_measures();
	/*
	test_transformations();
	test_community();
	test_dynamics();
	test_utils();
	test_randomwalks();
	test_evolution();
	test_modularity();
	*/
	}
	catch (std::exception& e) {
		std::cout << "[Error] UNIT TEST NOT PASSED: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	test_end("All unit tests");

	return EXIT_SUCCESS;
}


