/*
 * evolution.cpp
 *
 *  Created on: Jun 11, 2013
 *      Author: magnanim
 */

#include <stdio.h>
#include <vector>
#include <iostream>
#include "generation.h"
#include "../../include/datastructures.h"
#include "measures.h"
#include "mlnetwork.h"
#include <math.h>

namespace mlnet {

void rename_node(MLNetworkSharedPtr mnet, NodeSharedPtr s_node, LayerSharedPtr c_layer){
	ActorSharedPtr new_actor = mnet->add_actor(s_node->actor->name+"mod");
	NodeSharedPtr new_node = mnet->add_node(new_actor, c_layer);
	for(NodeSharedPtr node: mnet->neighbors(s_node, INOUT)){
		mnet->add_edge(node, new_node);
	}

	mnet->erase(s_node);
}
NodeSharedPtr select_node(MLNetworkSharedPtr mnet, node_list &list, double goal, long layer_id){
	double d = INFINITY;
	NodeSharedPtr s_node = list.get_at_index(0);
	for(long i; i<list.size();i++){
		NodeSharedPtr node = list.get_at_index(i);
		if(node->layer->id == layer_id){
			double new_d = abs(degree(mnet, node->actor, node->layer, INOUT)-goal);
			if(new_d < d){
				s_node = node;
				d = new_d;
			}
		}
	}
	list.erase(s_node->id);
	return s_node;
}
void swap(MLNetworkSharedPtr mnet, ActorSharedPtr actor_1, ActorSharedPtr actor_2, LayerSharedPtr layer){
/*
	NodeSharedPtr node_1 = mnet->get_node(actor_1, layer);
	NodeSharedPtr node_2 = mnet->get_node(actor_2, layer);
	node_1->actor=actor_2;
	node_2->actor=actor_1;*/
	NodeSharedPtr node_2 = mnet->get_node(actor_2, layer);
	NodeSharedPtr node_1 = mnet->get_node(actor_1, layer);
	node_list neighbors_1 = mnet->neighbors(node_1, INOUT);
	node_list copy = neighbors_1;
	for(NodeSharedPtr node: mnet->neighbors(node_2, INOUT)){
		mnet->add_edge(node, node_1);
	}
	long copy_size = copy.size();
	for(long i = 0; i<copy_size; i++){
		NodeSharedPtr neighbor = copy.get_at_index(i);
		mnet->add_edge(neighbor, node_2);
	}


}
void adjust(MLNetworkSharedPtr mnet, double j_node, double j_edge){
	double s = ((1-j_edge)*100)/(1+j_edge);
	double sum = 0;
	double n_to_rename = ((1-j_node)*100)/(1+j_node);
	LayerSharedPtr c_layer = mnet->get_layer(1);
	int i = 0;
	double goal = 1;
	node_list list = mnet->get_nodes();
	while(i<n_to_rename){
		goal = (s-sum)/(n_to_rename-i);
		NodeSharedPtr s_node = select_node(mnet, list, goal, c_layer->id);
		sum += degree(mnet, s_node->actor, s_node->layer, INOUT);
		if(s_node->layer->id == c_layer->id){
			rename_node(mnet, s_node, c_layer);
			i++;
		}

	}
	/*for(NodeSharedPtr s_node : mnet->get_nodes()){

		if(s_node->layer->id == c_layer->id and i<30){
			std::cout<<s_node->id<<std::endl;
			std::cout<<s_node->layer->id<<std::endl;
			ActorSharedPtr new_actor = mnet->add_actor(s_node->actor->name+"mod");
			NodeSharedPtr new_node = mnet->add_node(new_actor, c_layer);
			for(NodeSharedPtr node: mnet->neighbors(s_node, INOUT)){
				mnet->add_edge(node, new_node);
				EdgeSharedPtr er_edge = mnet->get_edge(node, s_node);
				//bool erased = mnet->erase(er_edge);
			}
			i++;
		}
	}*/

}

void dissortative_swap(MLNetworkSharedPtr mnet){
	actor_list actor_list = mnet->get_actors();
	ActorSharedPtr actor_1 = actor_list.get_at_random();
	ActorSharedPtr actor_2 = actor_list.get_at_random();
	if (actor_1 != actor_2){
		LayerSharedPtr layer_1 = mnet->get_layer(1);
		LayerSharedPtr layer_2 = mnet->get_layer(2);
		double deg_actor1_layer1 = degree(mnet, actor_1, layer_1, INOUT);
		double deg_actor1_layer2 = degree(mnet, actor_1, layer_2, INOUT);
		double deg_actor2_layer1 = degree(mnet, actor_2, layer_1, INOUT);
		double deg_actor2_layer2 = degree(mnet, actor_2, layer_2, INOUT);
		if(fabs(deg_actor1_layer1-deg_actor1_layer2)<=fabs(deg_actor1_layer1-deg_actor2_layer2)
		   or fabs(deg_actor2_layer1-deg_actor2_layer2)<fabs(deg_actor2_layer1-deg_actor1_layer2)){
			std::cout<<"[!]  ("<<deg_actor1_layer2<<","<<deg_actor2_layer2<<")   >>";
			swap(mnet, actor_1, actor_2, layer_2);
			std::cout<<"("<<degree(mnet, actor_1, layer_2, INOUT)<<","<<degree(mnet, actor_2, layer_2, INOUT)<<")"<<std::endl;
		}
	}
}
void assortative_swap(MLNetworkSharedPtr mnet){

}
void adjust_assortativity(MLNetworkSharedPtr mnet, double assort, double max_iterations = 1000, double difference = 0.1) {
	LayerSharedPtr layer1 = mnet->get_layer(1);
	LayerSharedPtr layer2 = mnet->get_layer(2);
	double current_assort = pearson_degree(mnet, layer1, layer2, INOUT);
	for(int i =1; i<=max_iterations; i++){
		if(current_assort>assort+difference){
			dissortative_swap(mnet);
		}
		else if(current_assort<assort-difference){
			assortative_swap(mnet);
		}
	}
}

void benchmark_adjust_error(MLNetworkSharedPtr mlnet,
							const std::string filename,
							const std::string file_extension){
	std::ofstream Morison_File ("test/output/adjusting_error/"+filename
						   +"_Table."+file_extension);         //Opening file to print
	Morison_File << "jnode, jedge, error_jnode, error_jedge, assort" << std::endl; //Defining header

	for(double j_node=0.01; j_node<=0.91; j_node+=0.1){
		for(double j_edge=0.01; j_edge <=0.91; j_edge+=0.1){
			MLNetworkSharedPtr mnet = read_multilayer("test/data/ACModel_BA_copy.csv","mlnet 2",',');
			LayerSharedPtr layer1 = mnet->get_layer(1);
			LayerSharedPtr layer2 = mnet->get_layer(2);
			double assort = pearson_degree(mnet, layer1, layer2, INOUT);
			std::cout<<"---------START--------"<<std::endl;
			std::cout<<"assort: ";
			std::cout<<assort<<std::endl;
			adjust(mnet, j_node, j_edge);
			layer1 = mnet->get_layer(1);
			layer2 = mnet->get_layer(2);
			double jaccard_node_sim = jaccard_actor(mnet, layer1, layer2);
			double jaccard_sim = jaccard_edge(mnet, layer1, layer2);
			assort = pearson_degree(mnet, layer1, layer2, INOUT);

			std::cout<<"-----------------"<<std::endl;
			std::cout<<"[!] - "<<j_node<<"--"<<j_edge<<std::endl;
			std::cout<<"jedge: ";
			std::cout<<jaccard_sim<<std::endl;
			std::cout<<"jnode: ";
			std::cout<<jaccard_node_sim<<std::endl;
			std::cout<<"assort: ";
			std::cout<<assort<<std::endl;
			Morison_File<<j_node<<","<<j_edge<<","<<fabs(jaccard_node_sim-j_node)<<","<<fabs(jaccard_sim-j_edge)<<","<<assort<<std::endl;
		}
	}
	Morison_File.close();
}
void benchmark_dissortative_swap(MLNetworkSharedPtr mlnet,
									 const std::string filename,
									 const std::string file_extension){
		std::ofstream Morison_File ("test/output/adjusting_error/Dissortative_"+filename
									+"_Table."+file_extension);         //Opening file to print
		Morison_File << "assort, jnode, jedge, error_assort" << std::endl; //Defining header
	for(double max_iter = 10; max_iter<100; max_iter*=10){
		std::cout<<"============================="<<max_iter<<"============"<<std::endl;

		for(double assort = 0.01; assort<=0.91; assort+=0.1){
			MLNetworkSharedPtr mnet = read_multilayer("test/data/ACModel_BA_copy.csv","mlnet 2",',');
			adjust_assortativity(mnet, assort, max_iter);

			LayerSharedPtr layer1 = mnet->get_layer(1);
			LayerSharedPtr layer2 = mnet->get_layer(2);
			double jaccard_node_sim = jaccard_actor(mnet, layer1, layer2);
			double jaccard_sim = jaccard_edge(mnet, layer1, layer2);
			double current_assort = pearson_degree(mnet, layer1, layer2, INOUT);

			std::cout<<"-----------------"<<std::endl;
			std::cout<<"[!] - "<<assort<<std::endl;
			std::cout<<"jnode: ";
			std::cout<<jaccard_node_sim<<std::endl;
			std::cout<<"jedge: ";
			std::cout<<jaccard_sim<<std::endl;
			std::cout<<"assort: ";
			std::cout<<current_assort<<std::endl;
			Morison_File<<assort<<","<<jaccard_node_sim<<","<<jaccard_sim<<","<<fabs(current_assort-assort)<<std::endl;

		}
	}


	}
void evolve(MLNetworkSharedPtr mnet,
		long num_of_steps,
		long num_initial_actors,
		//std::vector<int> num_new_vertexes_per_step,
		std::vector<double> pr_no_event,
		std::vector<double> pr_internal_event,
		matrix<double> dependency,
		std::vector<EvolutionModel*> evolution_model) {

	/* init of support data structures
	std::vector<std::set<entity_id> > free_identities(mnet.getNumNetworks());
	std::set<entity_id> ids = mnet.getGlobalIdentities();

	//std::cout << "Init identities" << std::endl;
	for (int n=0; n<mnet.getNumNetworks(); n++) {
		std::set<entity_id> to_copy(ids.begin(),ids.end());
		free_identities[n] = to_copy;
	}
	*/

	// Creating num_initial_actors actors
	//std::cout << "INIT ACTORS" << std::endl;
	for (int i=0; i<num_initial_actors; i++)
		mnet->add_actor("A"+std::to_string(i));

	// Initialization
	for (int n=0; n<mnet->get_layers().size(); n++) {
		//std::cout << "INIT LAYER " << n << std::endl;
		evolution_model[n]->init_step(mnet,mnet->get_layers().get_at_index(n));
	}

	for (long i=0; i<num_of_steps; i++) {
		//std::cout << "step " << i << std::endl;
		for (int n=0; n<mnet->get_layers().size(); n++) {

			LayerSharedPtr target_layer = mnet->get_layers().get_at_index(n);
			/* Add new vertexes ???
			//std::cout << "Add vertexes to " << n << ": ";
			for (int new_v=0; new_v<num_new_vertexes_per_step[n]; new_v++) {
				if (free_identities[n].empty())
					break;
				entity_id gid = rand.getElement(free_identities[n]);
				free_identities[n].erase(gid);
				vertex_id vertex = mnet.getNetwork(n).addVertex();
				mnet.mapIdentity(gid,vertex,n);
				//std::cout << ".";
			}
			//std::cout << std::endl;
			*/

			if (test(pr_no_event[n])) {
				//std::cout << "no event" << std::endl;
				//std::cout << " No event " << target_layer->to_string() << std::endl;
				// DO NOTHING;
			}

			//std::set<vertex_id> vertexes = mnet.getNetwork(n).getVertexes();
			//for (vertex_id vertex: vertexes) {
			else if (test(pr_internal_event[n])) {
					/*
					//std::cout << "Iternal event for vertex " << vertex << std::endl;
					switch (strategy[n]) {
						case EVOLUTION_DEGREE:
							//std::cout << "Getting target vertex " << std::endl;
							vertex_id target = choice_degree(rand, mnet, n);
							if (target==-1) break;
							//std::cout << "Inserting edge to " << target << std::endl;
							if (!mnet.getNetwork(n).containsEdge(vertex,target))
								mnet.getNetwork(n).addEdge(vertex,target);
							break;
					}
					*/
				//std::cout << " Internal event " << target_layer->to_string() << std::endl;
				evolution_model[n]->evolution_step(mnet,target_layer);
			}
			else {
				// choose a layer from which to import an edge: first find the candidates:
				//std::set<network_id> candidates;
					int layer_index = test(dependency[n]);
					LayerSharedPtr layer = mnet->get_layers().get_at_index(layer_index);

					//std::cout << " External event " << target_layer->to_string() << " <- " << layer->to_string() << std::endl;

					// Choose an actor from that layer and replicate it to the target layer (if it does not already exist)
					NodeSharedPtr imported_node = mnet->get_nodes(layer).get_at_random();
					NodeSharedPtr new_node = mnet->get_node(imported_node->actor,target_layer);
					if (!new_node)
						new_node = mnet->add_node(imported_node->actor,target_layer);

					// finally we insert the actor's neighbors into the target layer, if the neighbors are also present there
					for (NodeSharedPtr neighbor: mnet->neighbors(imported_node,OUT)) {
						NodeSharedPtr local_neighbor = mnet->get_node(neighbor->actor,target_layer);
						if (local_neighbor) {
							if (!mnet->get_edge(new_node,local_neighbor)) {
								mnet->add_edge(new_node,local_neighbor);
							}
						}
					}
				}
		}
	}
}

/*
void evolve_edge_import(MultiplexNetwork &mnet,
		long num_of_steps,
		std::vector<double> pr_no_event,
		std::vector<double> pr_internal_event,
		std::vector<std::vector<double> > dependency,
		std::vector<EvolutionModel*> evolution_model) {

		Random rand;

		// check size
		for (int i=0; i<mnet.getNumNetworks(); i++) {
			evolution_model[i]->init_step(mnet, i);
		}

		for (long i=0; i<num_of_steps; i++) {
			//if (i%100==0) std::cout << "Step " << i << std::endl;
			for (int n=0; n<mnet.getNumNetworks(); n++) {
				//std::cout << "Network " << n << ": ";
				if (rand.test(pr_no_event[n])) {
					//std::cout << "no event" << std::endl;
					continue;
				}
				if (rand.test(pr_internal_event[n])) {
					//std::cout << "internal event" << std::endl;
					evolution_model[n]->evolution_step(mnet, n);
					continue;
				}
				else {
					// choose a network from which to import an edge: first find the candidates:
					std::set<network_id> candidates;
					for (int i=0; i<dependency[n].size(); i++) {
						if (rand.test(dependency[n][i]))
							candidates.insert(i);
					}
					// then pick uniformly at random one of the candidates
					network_id import = rand.getElement(candidates);
					//std::cout << "external event from " << import << std::endl;
					// finally we choose an edge uniformly at random from this network and we insert it into the target
					std::set<edge_id> edges = mnet.getNetwork(import).getEdges();
					edge_id edge_to_be_imported = rand.getElement(edges);
					entity_id id1 = mnet.getGlobalIdentity(edge_to_be_imported.v1, import);
					entity_id id2 = mnet.getGlobalIdentity(edge_to_be_imported.v2, import);
					// check if these identities are already present in the target network (if not, insert them)
					vertex_id vertex1, vertex2;
					if (!mnet.containsVertex(id1,n)) {
						if (mnet.getNetwork(n).isNamed())
							vertex1 = mnet.getNetwork(n).addVertex(mnet.getGlobalName(id1));
						else vertex1 = mnet.getNetwork(n).addVertex();
						mnet.mapIdentity(id1, vertex1, n);
					}
					else vertex1 = mnet.getVertexId(id1,n);
					if (!mnet.containsVertex(id2,n)) {
						if (mnet.getNetwork(n).isNamed())
							vertex2 = mnet.getNetwork(n).addVertex(mnet.getGlobalName(id2));
						else vertex2 = mnet.getNetwork(n).addVertex();
						mnet.mapIdentity(id2, vertex2, n);
					}
					else vertex2 = mnet.getVertexId(id2,n);
					if (!mnet.getNetwork(n).containsEdge(vertex1, vertex2))
						mnet.getNetwork(n).addEdge(vertex1, vertex2);
				}
			}
		}
}


void evolve_edge_copy(MultiplexNetwork &mnet,
		long num_of_steps,
		std::vector<double> pr_no_event,
		std::vector<double> pr_internal_event,
		std::vector<std::vector<double> > dependency,
		std::vector<EvolutionModel*> evolution_model) {

		Random rand;

		// check size
		for (int i=0; i<mnet.getNumNetworks(); i++) {
			evolution_model[i]->init_step(mnet, i);
		}

		for (long i=0; i<num_of_steps; i++) {
			//if (i%100==0) std::cout << "Step " << i << std::endl;
			for (int n=0; n<mnet.getNumNetworks(); n++) {
				//std::cout << "Network " << n << ": ";
				if (rand.test(pr_no_event[n])) {
					//std::cout << "no event" << std::endl;
					continue;
				}
				if (rand.test(pr_internal_event[n])) {
					//std::cout << "internal event " << n << std::endl;
					std::set<global_vertex_id> new_vertexes;
					std::set<global_edge_id> new_edges;
					evolution_model[n]->evolution_step(mnet, n, new_vertexes, new_edges);

					// The newly inserted vertexes and edges can be copied to other networks
					for (int i=0; i<dependency.size(); i++) {
						if (rand.test(dependency[i][n])) {
							//std::cout << dependency[i][n] << " copy to " << i << std::endl;
							/  * copy vertexes
							for (global_vertex_id gvid: new_vertexes) {
								global_identity gid = mnet.getGlobalIdentity(gvid.vid,gvid.network);
							if (!mnet.containsVertex(gid,i)) {
								vertex_id vertex;
								if (mnet.getNetwork(i).isNamed())
										vertex = mnet.getNetwork(i).addVertex(mnet.getGlobalName(gid));
								else
									vertex = mnet.getNetwork(i).addVertex();
								mnet.mapIdentity(gid, vertex, i);
							}
							}
							// copy edges
							for (global_edge_id geid: new_edges) {
								entity_id gid1 = mnet.getGlobalIdentity(geid.v1,geid.network);
								entity_id gid2 = mnet.getGlobalIdentity(geid.v2,geid.network);
								vertex_id lid1, lid2;
								if (!mnet.containsVertex(gid1,i)) { // not necessary
									if (mnet.getNetwork(i).isNamed())
										lid1 = mnet.getNetwork(i).addVertex(mnet.getGlobalName(gid1));
									else
										lid1 = mnet.getNetwork(i).addVertex();
									mnet.mapIdentity(gid1, lid1, i);
								}
								else lid1 = mnet.getVertexId(gid1,i);
								if (!mnet.containsVertex(gid2,i)) {
									if (mnet.getNetwork(i).isNamed())
										lid2 = mnet.getNetwork(i).addVertex(mnet.getGlobalName(gid2));
									else
										lid2 = mnet.getNetwork(i).addVertex();
									mnet.mapIdentity(gid2, lid2, i);
								}
								else lid2 = mnet.getVertexId(gid2,i);
								if (!mnet.getNetwork(i).containsEdge(lid1,lid2)) {
									mnet.getNetwork(i).addEdge(lid1,lid2);
									//std::cout << "E " << lid1 << " " << lid2 << std::endl;
								}
							}
						}
					}
				}
			}
		}
}

*/

}


