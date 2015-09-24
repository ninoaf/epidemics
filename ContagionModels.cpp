/*
 * ContagionModels.cpp
 *
 *  Created on: Sep 24, 2015
 *      Authors: Nino Antulov-Fantulin & Mile Sikic
 */


/**
 * Function that simulate one epidemic spread untill temporal Threshold T
 */
void igraph_epidemic_classic_temporal(infected_structure * p_infected_parameters, double p, double q, igraph_vector_t * infected_nodes, int T_value) {

	igraph_vector_null(infected_nodes);
	igraph_dqueue_clear(p_infected_parameters->dq_infected_nodes);

    igraph_dqueue_push(p_infected_parameters->dq_infected_nodes, p_infected_parameters->start_node);
    VECTOR(*infected_nodes)[p_infected_parameters->start_node] = 1;
	int dis_time = 1;
	int delta_nodes_pop = igraph_dqueue_size(p_infected_parameters->dq_infected_nodes);

    while (igraph_dqueue_size(p_infected_parameters->dq_infected_nodes)) {
		if ( delta_nodes_pop == 0 ){
			dis_time++; // discrete epidemic time
			delta_nodes_pop = igraph_dqueue_size(p_infected_parameters->dq_infected_nodes);
		}

		if ( dis_time <= T_value){
			long int current_node;
			current_node = (long int) igraph_dqueue_pop(p_infected_parameters->dq_infected_nodes);
			delta_nodes_pop--;

			igraph_vector_t *neis;
			neis = igraph_adjlist_get(p_infected_parameters->al, current_node);
			igraph_real_t no_of_neigh;
			no_of_neigh = igraph_vector_size(neis);

			long int current_neigh;

			for (int i = 0; i < no_of_neigh; ++i) {
				current_neigh = (long int) VECTOR(*neis)[i];

				// check whether the node is susceptible
				if (VECTOR(*infected_nodes)[current_neigh] == 0) {
					if (my_random() <= p) {
						igraph_dqueue_push(p_infected_parameters->dq_infected_nodes, (igraph_real_t) current_neigh);
						VECTOR(*infected_nodes)[current_neigh] = 1; // infecting a neighbour
					}
				}
			}

			if (my_random() > q) { //node is not recovered
				igraph_dqueue_push(p_infected_parameters->dq_infected_nodes, current_node);
			}
		}else{
			break;
		}
    }
}
