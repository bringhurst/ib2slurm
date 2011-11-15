/*
 * An experiment to see if we can generate a slurm style topology.conf file
 * from ib network discovery.
 *
 * Jon Bringhurst <jonb@lanl.gov> - 2011-11-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <complib/cl_nodenamemap.h>
#include <infiniband/ibnetdisc.h>

void switch_iter_func(ibnd_node_t * node, void *iter_user_data)
{
    fprintf(stdout, "Found a switch!\n");
}

void ca_iter_func(ibnd_node_t * node, void *iter_user_data)
{
    fprintf(stdout, "Found a CA!\n");
}

void router_iter_func(ibnd_node_t * node, void *iter_user_data)
{
    fprintf(stdout, "Found a router!\n");
}

int main(int argc, char** argv)
{
    struct ibnd_config config = {0};
    ibnd_fabric_t *fabric = NULL;

    nn_map_t *node_name_map = NULL;
    char *node_name_map_file = NULL;

    char *ibd_ca = NULL;
    int ibd_ca_port = 0;

    int option_index = 0;
    int c;
    static struct option long_options[] = {
        {"node-name-map", 1, 0, 'm'},
        {NULL, 0, NULL, 0}
    };

    while((c = getopt_long(argc, argv, "m:", long_options, &option_index)) != -1) {
        switch(c) {
            case 'm':
                node_name_map_file = strdup(optarg);
                break;
        }
    }

    node_name_map = open_node_name_map(node_name_map_file);

    if ((fabric = ibnd_discover_fabric(ibd_ca, ibd_ca_port, NULL, &config)) == NULL) {
        fprintf(stderr, "IB discover failed.\n");
        exit(EXIT_FAILURE);
    }

    ibnd_iter_nodes_type(fabric, switch_iter_func, IB_NODE_SWITCH, NULL);
    ibnd_iter_nodes_type(fabric, ca_iter_func, IB_NODE_CA, NULL);
    ibnd_iter_nodes_type(fabric, router_iter_func, IB_NODE_ROUTER, NULL);

    ibnd_destroy_fabric(fabric);
    exit(EXIT_SUCCESS);
}

/* EOF */
