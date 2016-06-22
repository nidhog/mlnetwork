/*
 * modularity.cpp
 *
 * Created on: Feb 27, 2014
 * Author: matteomagnani
 * Version: 0.0.1
 */

#include "community.h"
#include "utils.h"
#include <iostream>

namespace mlnet {


community::community() :
	id(0) {}

community::community(long id, simple_set<CliqueSharedPtr> cliques, simple_set<LayerSharedPtr> layers) :
	id(id), cliques(cliques.begin(),cliques.end()), layers(layers.begin(),layers.end()) {}

std::set<ActorSharedPtr> community::actors() {
	std::set<ActorSharedPtr> actors;
	for (CliqueSharedPtr clique: cliques) {
		for (ActorSharedPtr actor: clique->actors)
			actors.insert(actor);
	}
	return actors;
}

std::string community::to_string() {
	std::string res = "C" + std::to_string(id) + ": ";
	simple_set<ActorSharedPtr> actors;
	for (CliqueSharedPtr clique: cliques) {
		for (ActorSharedPtr actor: clique->actors)
			actors.insert(actor);
	}
	for (ActorSharedPtr actor: actors)
		res += actor->name + " ";
	res += "( ";
	for (LayerSharedPtr layer: layers) {
		res += layer->name + " ";
	}
	res += ")";
	return res;
}

int community::size() const {
	simple_set<ActorSharedPtr> actors;
	for (CliqueSharedPtr clique: cliques) {
		for (ActorSharedPtr actor: clique->actors)
			actors.insert(actor);
	}
	return actors.size();
}

simple_set<CommunitySharedPtr> ml_cpm(MLNetworkSharedPtr mnet, int k, int m1, int m2) {
	simple_set<CliqueSharedPtr> C = find_max_cliques(mnet,k,m1);
	if (C.size()==0)
		return simple_set<CommunitySharedPtr>();

	std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> > adjacency = build_max_adjacency_graph(C,k,m2);

	return find_max_communities(mnet,adjacency,m2);
}




hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > get_mlneighbors(MLNetworkSharedPtr mnet, ActorSharedPtr actor) {

hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > result;
	for (NodeSharedPtr node: mnet->get_nodes(actor)) {
		for (NodeSharedPtr neigh: mnet->neighbors(node,INOUT)) {
			result[neigh->actor].insert(neigh->layer);
		}
	}
	return result;
}

simple_set<LayerSharedPtr> neighboring_layers(MLNetworkSharedPtr mnet, ActorSharedPtr actor1, ActorSharedPtr actor2) {
	simple_set<LayerSharedPtr> result;
	for (NodeSharedPtr node: mnet->get_nodes(actor1)) {
		NodeSharedPtr node2 = mnet->get_node(actor2,node->layer);
		if (!node2) continue;
		if (mnet->get_edge(node,node2)) {
			result.insert(node->layer);
		}
	}
	return result;
}

simple_set<CliqueSharedPtr> find_cliques(MLNetworkSharedPtr mnet, int k, int m) {
	simple_set<CliqueSharedPtr> C;
	simple_set<LayerSharedPtr> all_layers;
	for (LayerSharedPtr layer: mnet->get_layers()) {
		all_layers.insert(layer);
	}
	CliqueSharedPtr A(new clique());
	A->layers.insert(all_layers.begin(),all_layers.end());

	hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > B;
	for (ActorSharedPtr actor : mnet->get_actors()) {
		B[actor] = all_layers;
	}
	find_cliques(mnet,A,B,C,k,m);
	return C;
}

void find_cliques(MLNetworkSharedPtr mnet, CliqueSharedPtr A,
hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > B, simple_set<CliqueSharedPtr>& C, int k, int m) {
	if (A->actors.size()==k) {
		//A->id = C.size();
		C.insert(A);
		return;
	}
	for (auto n = B.begin(); n!=B.end(); ++n) {
		simple_set<ActorSharedPtr> P(A->actors.begin(),A->actors.end());
		P.insert(n->first);
		simple_set<LayerSharedPtr> S_P = s_intersection(A->layers,n->second);

hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > Q;
		auto n2 = n;
		for (++n2; n2!=B.end(); ++n2) {
			simple_set<LayerSharedPtr> common = s_intersection(n2->second,s_intersection(S_P,neighboring_layers(mnet,n->first,n2->first)));
			if (common.size()>=m) {
				Q[n2->first] = common;
			}
		}
		find_cliques(mnet,CliqueSharedPtr(new clique(P,S_P)),Q,C,k,m);
	}
}

simple_set<CliqueSharedPtr> find_max_cliques(MLNetworkSharedPtr mnet, int k, int m) {
	simple_set<LayerSharedPtr> layers;
	for (LayerSharedPtr layer: mnet->get_layers())
		layers.insert(layer);
	return find_max_cliques(mnet, layers, k, m);
}


simple_set<CliqueSharedPtr> find_max_cliques(MLNetworkSharedPtr mnet, simple_set<LayerSharedPtr> layers, int k, int m) {
	simple_set<CliqueSharedPtr> result;
	// A: empty clique
	CliqueSharedPtr A(new clique());
	A->layers.insert(layers.begin(), layers.end());
	// B: all actors
	hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > B;
	for (ActorSharedPtr actor : mnet->get_actors()) {
		B[actor] = layers;
	}
	// C: empty set of actors
	hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > C;
	find_max_cliques(mnet,A,B,C,result,k,m);
	return result;
}

void find_max_cliques(MLNetworkSharedPtr mnet, CliqueSharedPtr& A,
hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> >& B,
hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> >& C, simple_set<CliqueSharedPtr>& result, int k, int m) {
	/*
	for (int i=0; i<A->actors.size(); i++) std::cout << " - ";
	std::cout << "FMC(" << A->to_string() << ", { ";
	for (auto b = B.begin(); b!=B.end(); ++b) {
		std::cout << b->first->name << "( ";
		for (auto k: b->second) {
				std::cout << k->name << " ";
			}
		std::cout << ") ";
	}
	std::cout << "}, { ";
	for (auto b = C.begin(); b!=C.end(); ++b) {
		std::cout << b->first->name << "( ";
		for (auto k: b->second) {
			std::cout << k->name << " ";
		}
		std::cout << ") ";
	}
	std::cout << "})"<< std::endl;
	 */

	//hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > original_N(N.begin(),N.end());

	if (A->actors.size()+B.size()<k)
		return;

	if (A->layers.size()<m)
		return;

	if (A->actors.size()>=k) {
		int max_layers_C = 0;
		for (auto c: C) {
			if (c.second.size()>max_layers_C)
				max_layers_C = c.second.size();
		}
		int max_layers_B = 0;
		for (auto b: B) {
			if (b.second.size()>max_layers_B)
				max_layers_B = b.second.size();
		}
		if (max_layers_B<A->layers.size() && max_layers_C<A->layers.size()) {
			//A->id = result.size();
			result.insert(A);
			//for (int i=0; i<A->actors.size(); i++) std::cout << " - ";
			//std::cout << "RETURN " << A->to_string() << std::endl;
		}
	}


	simple_set<ActorSharedPtr> P(A->actors.begin(),A->actors.end());
	for (auto b = B.begin(); b!=B.end(); ++b) {
		// for all b in B
		P.insert(b->first);
		simple_set<LayerSharedPtr> S_P = s_intersection(A->layers,b->second);
		CliqueSharedPtr A_ext(new clique(P,S_P));


hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > B_ext;
		auto q = b;
		for (++q; q!=B.end(); ++q) {
			simple_set<LayerSharedPtr> common = s_intersection(q->second,neighboring_layers(mnet,b->first,q->first));
			if (common.size()>=m) {
				B_ext[q->first] = common;
			}
		}


hashtable<ActorSharedPtr,simple_set<LayerSharedPtr> > C_ext;
		for (auto c = C.begin(); c!=C.end(); ++c) {
			simple_set<LayerSharedPtr> common = s_intersection(c->second,neighboring_layers(mnet,b->first,c->first));
			if (common.size()>=m) {
				C_ext[c->first] = common;
			}
		}

		find_max_cliques(mnet,A_ext,B_ext,C_ext,result,k,m);
		C[b->first] = b->second;
		P.erase(b->first);
	}
}

std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> > build_max_adjacency_graph(const simple_set<CliqueSharedPtr>& C, int k, int m) {
	std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> > result;
	for (CliqueSharedPtr c1: C) {
		result[c1];
		for (CliqueSharedPtr c2: C) {
			if (c1<=c2)
				continue;
			int common_actors = s_intersection(c1->actors,c2->actors).size();
			int common_layers = s_intersection(c1->layers,c2->layers).size();
			if (common_actors>=k-1 && common_layers>=m) {
					result[c1].insert(c2);
					result[c2].insert(c1);
			}
		}
	}
	return result;
}

std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> > build_adjacency_graph(const simple_set<CliqueSharedPtr>& C, int m) {
	std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> > result;
	for (CliqueSharedPtr c1: C) {
		result[c1];
		for (CliqueSharedPtr c2: C) {
			if (c1==c2)
				continue;
			if (s_intersection(c1->actors,c2->actors).size()==c1->actors.size()-1) {
				if (s_intersection(c1->layers,c2->layers).size()>=m) {
					result[c1].insert(c2);
				}
			}
		}
	}
	return result;
}

simple_set<CommunitySharedPtr> find_communities(MLNetworkSharedPtr mnet, const std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> >& adjacency, int m) {
	simple_set<CommunitySharedPtr> C; // empty
	simple_set<CliqueSharedPtr> U; // empty
	for (auto clique : adjacency) {
		CommunitySharedPtr A(new community());
		A->cliques.insert(clique.first);
		A->layers = clique.first->layers;
		simple_set<CliqueSharedPtr> B;
		for (auto adj_clique: adjacency.at(clique.first)) {
			if (U.count(adj_clique)>0)
				B.insert(adj_clique);
		}
		find_communities(adjacency,A,B,U,C,m);
		U.insert(clique.first);
	}
	return C;
}

void find_communities(const std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> >& adjacency, CommunitySharedPtr A, const simple_set<CliqueSharedPtr>& B, simple_set<CliqueSharedPtr> U, simple_set<CommunitySharedPtr>& C, int m) {
	/* PRINT
	std::cout << "A: " << A->to_string() << std::endl;
	std::cout << "B: ";
	for (CliqueSharedPtr c: B)
		std::cout << c->id << " ";
	std::cout << std::endl;
	std::cout << "U: ";
	for (CliqueSharedPtr c: U)
		std::cout << c->id << " ";
	std::cout << std::endl;
	*/
	for (CliqueSharedPtr c : B) {
		//std::cout << "Extending with: " << c->id << std::endl;
		simple_set<CliqueSharedPtr> P(A->cliques.begin(),A->cliques.end());
		P.insert(c);
		//simple_set<CliqueSharedPtr> W(U.begin(),U.end());
		//W.insert(c);
		simple_set<LayerSharedPtr> S_P = s_intersection(A->layers,c->layers);
		simple_set<CliqueSharedPtr> Q;
		//auto c2 = c;
		bool part_of = false;
		for (CliqueSharedPtr c2 : B) {
			// c2 already in result
			if (A->cliques.count(c2)>0) {
				//std::cout << c2->id << " already in result" << std::endl;
				continue;
			}
			// | L(community) U L(c2) | >= m
			simple_set<LayerSharedPtr> common = s_intersection(S_P,c2->layers);
			if (common.size()>=m) {
				// c2 already used at this point
				if (U.count(c2)>0) {
					//std::cout << c2->id << " already used" << std::endl;
					part_of = true;
					continue;
				}
				Q.insert(c2);
				//std::cout << c2->id << " added"  << std::endl;
			}
		}
		for (CliqueSharedPtr c2: adjacency.at(c)) {
			// c2 already in result
			if (P.count(c2)>0) {
				//std::cout << c2->id << " already in result" << std::endl;
				continue;
			}
			if (Q.count(c2)>0)
				continue;
			// | L(community) U L(c2) | >= m
			simple_set<LayerSharedPtr> common = s_intersection(S_P,c2->layers);
			if (common.size()>=m) {
				// c2 already used at this point
				if (U.count(c2)>0) {
					//std::cout << c2->id << " already used" << std::endl;
					part_of = true;
					continue;
				}
				Q.insert(c2);
				//std::cout << c2->id << " added"  << std::endl;
			}
		}
		/*
		std::cout << "Q: ";
		for (CliqueSharedPtr c: Q)
			std::cout << c->id << " ";
		std::cout << std::endl;
		 */

		CommunitySharedPtr A_ext(new community(0,P,S_P));
		// if maximal, output -> no cliques to extend it and not including an already processed clique
		if (!part_of && Q.size()==0) {
			A_ext->id = C.size();
			C.insert(A_ext);
			//std::cout << "OUT: " << A_ext->to_string() << std::endl;
			return;
		}
		else if (Q.size()>0) {
			//std::cout << "recurse" << std::endl;
			find_communities(adjacency,A_ext,Q,U,C,m);
			U.insert(c);
		}
	}
}


simple_set<CommunitySharedPtr> find_max_communities(MLNetworkSharedPtr mnet, const std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> >& adjacency, int m) {
	// result: empty set of communities
	simple_set<CommunitySharedPtr> result;
	// A: empty community on all layers
	CommunitySharedPtr A(new community());
	simple_set<LayerSharedPtr> all_layers;
	for (LayerSharedPtr layer: mnet->get_layers()) {
		all_layers.insert(layer);
	}
	A->layers.insert(all_layers.begin(),all_layers.end());
	// C: cliques that have already been used (none so far)

hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > B;

hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > C;

hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > D;
	for (auto clique_pair : adjacency) {
		// std::cout << "processing "<< clique_pair.first->to_string() << std::endl;
		// B: cliques that can be used to extend the current community
		B[clique_pair.first].insert(clique_pair.first->layers.begin(),clique_pair.first->layers.end());
		find_max_communities(adjacency,A,B,C,D,result,m);
		B.erase(clique_pair.first);
		D[clique_pair.first].insert(clique_pair.first->layers.begin(),clique_pair.first->layers.end());
	}
	return result;
}

void find_max_communities2(const std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> >& adjacency, CommunitySharedPtr A,
hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > B,
hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > D,
hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > U, simple_set<CommunitySharedPtr>& C, int m) {
	/*std::cout << prefix << "FMComm(A: {";
	for (auto b: A->cliques) {
			std::cout << b->id;
			std::cout << " ";
		}
	std::cout << "}, B: {  ";
	for (auto b = B.begin(); b!=B.end(); ++b) {
		std::cout << b->first->id;
		std::cout << " ";
	}
	std::cout << "}, D: { ";
	for (auto b = D.begin(); b!=D.end(); ++b) {
		std::cout << b->first->id;
		std::cout << " ";
	}
	std::cout << "}, U: { ";
	for (auto b = U.begin(); b!=U.end(); ++b) {
		std::cout << b->first->id;
		std::cout << " ";
	}
	std::cout << "})"<< std::endl;*/

	// B_prime
	bool is_maximal = true;
	for (auto b: B) {
		// for all b in B
		//std::cout << "Extending with: " << b.first->to_string() << std::endl;
		simple_set<CliqueSharedPtr> P(A->cliques.begin(),A->cliques.end());
		P.insert(b.first);
		simple_set<LayerSharedPtr> S_P = s_intersection(A->layers,b.second);
		CommunitySharedPtr A_ext(new community(0,P,S_P));


hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > Q;
		if (adjacency.count(b.first)>0)
		for (auto q: adjacency.at(b.first)) {
			//std::cout << "   checking adj.: " << q->to_string() << std::endl;
			if (P.count(q)>0) continue;
			simple_set<LayerSharedPtr> common = s_intersection(q->layers,S_P);
			//std::cout << "   common size: " << common.size() << std::endl;
			if (common.size()>=m && U.count(q)==0) {
				Q[q] = common;
				//std::cout << "   added to B'" << std::endl;
				if (common.size()==S_P.size())
					is_maximal = false;
			}
		}
		for (auto q : B) {
			if (q.first==b.first) continue;
			if (P.count(q.first)>0) continue;
			simple_set<LayerSharedPtr> common = s_intersection(q.second,S_P);
			if (common.size()>=m && U.count(q.first)==0) {
				Q[q.first] = common;
				if (common.size()==S_P.size())
					is_maximal = false;
			}
		}


hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > D_ext;
		if (adjacency.count(b.first)>0)
		for (auto q: adjacency.at(b.first)) {
			if (P.count(q)>0) continue;
			simple_set<LayerSharedPtr> common = s_intersection(q->layers,S_P);
			if (common.size()>=m && U.count(q)>0) {
				D_ext[q] = common;
				if (common.size()==S_P.size())
					is_maximal = false;
			}
		}
		for (auto q: D) {
			if (q.first==b.first) continue;
			if (P.count(q.first)>0) continue;
			simple_set<LayerSharedPtr> common = s_intersection(q.second,S_P);
			if (common.size()>=m && U.count(q.first)>0) {
				D_ext[q.first] = common;
				if (common.size()==S_P.size())
					is_maximal = false;
			}
		}

		//if (is_maximal && A->layers.size()>=m) {
		if (is_maximal) {
			A_ext->id = C.size();
			C.insert(A_ext);
		}
		//if (!Q.empty())

hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > U_ext(U.begin(), U.end());
		find_max_communities2(adjacency,A_ext,Q,D_ext,U_ext,C,m);
		U[b.first] = b.second;
		//A_ext->cliques.erase(b->first);
	}
	/*for (auto n = original_N.begin(); n!=original_N.end(); ++n) {
		if (intersect(A->layers,n->second).size()==A->layers.size()) {
			is_maximal = false;
			continue;
		}
	}*/
}


void find_max_communities(const std::map<CliqueSharedPtr,simple_set<CliqueSharedPtr> >& adjacency, CommunitySharedPtr& A,
hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> >& B,
hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> >& C,
hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> >& D, simple_set<CommunitySharedPtr>& result, int m) {
	/*for (int i=0; i<A->cliques.size(); i++) std::cout << " - ";
	std::cout << "FMComm(A: {";
	for (auto b: A->cliques) {
			std::cout << b->id;
			std::cout << " ";
		}
	std::cout << "}, B: {  ";
	for (auto b = B.begin(); b!=B.end(); ++b) {
		std::cout << b->first->id << "( ";
		for (auto k: b->second) {
				std::cout << k->name << " ";
			}
		std::cout << ") ";
	}
	std::cout << "}, C: { ";
	for (auto b = C.begin(); b!=C.end(); ++b) {
		std::cout << b->first->id << "( ";
		for (auto k: b->second) {
			std::cout << k->name << " ";
		}
		std::cout << ") ";
	}
	std::cout << "})"<< std::endl;*/

	if (A->cliques.size()>0) {
		int max_layers_C = 0;
		for (auto c: C) {
			if (c.second.size()>max_layers_C)
				max_layers_C = c.second.size();
		}
		int max_layers_B = 0;
		for (auto b: B) {
			if (b.second.size()>max_layers_B)
				max_layers_B = b.second.size();
		}
		if (max_layers_B<A->layers.size() && max_layers_C<A->layers.size()) {
			A->id = result.size();
			result.insert(A);
			//for (int i=0; i<A->cliques.size(); i++) std::cout << " - ";
			//std::cout << "RETURN " << A->to_string() << std::endl;
		}
	}


	simple_set<CliqueSharedPtr> P(A->cliques.begin(),A->cliques.end());
	for (auto b = B.begin(); b!=B.end(); ++b) {
			// for all b in B
			P.insert(b->first);
			simple_set<LayerSharedPtr> S_P = s_intersection(A->layers,b->second);
			CommunitySharedPtr A_ext(new community(0,P,S_P));


hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > C_ext;
			for (auto c = C.begin(); c!=C.end(); ++c) {
				simple_set<LayerSharedPtr> common = s_intersection(c->second,S_P);
				if (common.size()>=m) {
					C_ext[c->first] = common;
				}
			}


hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > B_ext;
			for (auto q=B.begin(); q!=B.end(); ++q) {
				if (q->first==b->first)
					continue;
				simple_set<LayerSharedPtr> common = s_intersection(q->second,S_P);
				if (common.size()>=m) {
					if (D.count(q->first)==0)
						B_ext[q->first] = common;
					else
						C_ext[q->first] = common;
				}
			}

			for (auto j: adjacency.at(b->first)) {
				//std::cout << "   checking adj.: " << q->to_string() << std::endl;
				if (A_ext->cliques.count(j)>0)
					continue;
				simple_set<LayerSharedPtr> common = s_intersection(j->layers,S_P);
				//std::cout << "   common size: " << common.size() << std::endl;
				if (common.size()>=m) {
					if (D.count(j)==0)
						B_ext[j] = common;
					else
						C_ext[j] = common;
					//std::cout << "   added to B'" << std::endl;
				}
			}


hashtable<CliqueSharedPtr,simple_set<LayerSharedPtr> > D_ext;
			for (auto d = D.begin(); d!=D.end(); ++d) {
				simple_set<LayerSharedPtr> common = s_intersection(d->second,S_P);
				//if (common.size()>=m) {
					D_ext[d->first] = common;
				//}
			}

			find_max_communities(adjacency,A_ext,B_ext,C_ext,D_ext,result,m);
			D[b->first] = b->second;
			P.erase(b->first);
		}
}

/*

hashtable<NodeSharedPtr,long> label_propagation(const MLNetworkSharedPtr& mnet, double c) {

hashtable<NodeSharedPtr,long> membership;
	// initial assignment
	long i=0;
	for (NodeSharedPtr node: mnet->get_nodes()) {
		membership[node] = i++;
	}

hashtable<LayerSharedPtr,long> m_s;
	for (LayerSharedPtr s: mnet->get_layers()) {
		double m = mnet->get_edges(s,s).size();
		if (!mnet->is_directed(s,s))
			m *= 2;
		if (m == 0)
			m = 1; // no effect on the formula
		m_s[s] = m;
	}
	while (!stopping_condition(mnet,update_labels(mnet,membership,m_s,c,100))) {}
	return membership;
}

long update_labels(const MLNetworkSharedPtr& mnet,
hashtable<NodeSharedPtr,long>& membership,
hashtable<LayerSharedPtr,long> m_s, double c, long max_neighbors) {
	long num_updates = 0;
	for  (NodeSharedPtr node: mnet->get_nodes()) {
		if (mnet->neighbors(node,INOUT).size()==0)
			continue;

hashtable<long, double> labels;
		long k_node = mnet->neighbors(node,INOUT).size();
		for (NodeSharedPtr n: mnet->neighbors(node,INOUT)) {
			/ *
			int checked_neighbors = 0;
			for (NodeSharedPtr n2: mnet->neighbors(node,INOUT)) {
				if (max_neighbors<=checked_neighbors++)
					break;
				if (mnet->neighbors(n1,INOUT).get(n2->id))
					labels.inc(membership.at(n1));
			}
			* /
			long label = membership.at(n);
			long k_n = mnet->neighbors(n,INOUT).size();
			if (labels.count(label)==0)
				labels[label]=0;
			labels[label] += 1 - k_n*k_node/m_s.at(node->layer);
		}

		for (NodeSharedPtr n: mnet->get_nodes(node->actor)) {
			if (n==node) continue;
			long label = membership.at(n);
			if (labels.count(label)==0)
				labels[label]=0;
			labels[label] += c;
		}
		// find max label
		long new_label = 0;
		double max_val = 0;
		for (auto pair: labels) {
			if (max_val < pair.second) {
				max_val = pair.second;
				new_label = pair.first;
			}
		}
		if (membership[node] != new_label) {
			membership[node] = new_label;
			num_updates++;
		}
	}
	return num_updates;
}

bool stopping_condition(const MLNetworkSharedPtr& mnet, long info) {
	if (info<mnet->get_nodes().size()*.05) return true;
	else return false;
}
*/

}
