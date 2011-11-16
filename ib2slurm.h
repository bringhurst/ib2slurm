#ifndef __IB2SLURM_H
#define __IB2SLURM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

#include <complib/cl_nodenamemap.h>
#include <infiniband/ibnetdisc.h>

typedef struct ib2slurm_opts_t {
    nn_map_t* node_name_map;
    int lookup_flag;
    int compress_flag;
} ib2slurm_opts_t;

void switch_iter_func(ibnd_node_t* node, void* user_data);
char* node_name(ibnd_node_t* node, ib2slurm_opts_t* opts);

#endif /* __IB2SLURM_H */
