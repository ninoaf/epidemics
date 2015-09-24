/*
 * ContagionModels.h
 *
 *  Created on: Sep 24, 2015
 *      Author: nino
 */

#ifndef CONTAGIONMODELS_H_
#define CONTAGIONMODELS_H_


void igraph_epidemic_classic_temporal(infected_structure * p_infected_parameters, double p, double q, igraph_vector_t * infected_nodes, int T_value);

#endif /* CONTAGIONMODELS_H_ */
