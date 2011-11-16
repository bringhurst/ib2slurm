#ifndef __IB2SLURM_H
#define __IB2SLURM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

#include <complib/cl_nodenamemap.h>
#include <infiniband/ibnetdisc.h>

void switch_iter_func(ibnd_node_t* node, void* iter_user_data);
void ca_iter_func(ibnd_node_t* node, void* iter_user_data);
void router_iter_func(ibnd_node_t* node, void* iter_user_data);

char* node_name(ibnd_node_t* node);

#endif /* __IB2SLURM_H */
