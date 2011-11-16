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

typedef struct ib2slurm_list_t {
   char* str;
   struct ib2slurm_list_t* next;
} ib2slurm_list_t;

void switch_iter_func(ibnd_node_t* node, void* user_data);
void output_nodelist(char *tag, int type, ib2slurm_opts_t* opts, ibnd_node_t* node);
void print_without_compression(ib2slurm_list_t* list, char* tag);
void print_with_compression(ib2slurm_list_t* list, char* tag);
char* node_name(ibnd_node_t* node, ib2slurm_opts_t* opts);

#endif /* __IB2SLURM_H */
