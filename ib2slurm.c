#include "ib2slurm.h"

void switch_iter_func(ibnd_node_t* node, void* user_data)
{
    ibnd_port_t* port;
    int p = 0;
    ib2slurm_opts_t* opts = (ib2slurm_opts_t*)user_data;

    if(opts->lookup_flag) {
        char* switchname = node_name(node, opts);
        fprintf(stdout, "SwitchName=%s", switchname);
        free(switchname);
    } else {
        fprintf(stdout, "SwitchName=%" PRIx64, node->guid);
    }

    fprintf(stdout, " Switches=");
    for(p = 1; p <= node->numports; p++) {
        port = node->ports[p];

        if(port && port->remoteport) {
            if(port->remoteport->node->type == IB_NODE_SWITCH) {
                if(opts->lookup_flag) {
                    char* remoteswitch = node_name(port->remoteport->node, opts);
                    fprintf(stdout, "%s,", remoteswitch);
                    free(remoteswitch);
                } else {
                    fprintf(stdout, "%" PRIx64 ", ", port->remoteport->guid);
                }
            }
        }
    }

    fprintf(stdout, " Nodes=");
    for(p = 1; p <= node->numports; p++) {
        port = node->ports[p];

        if(port && port->remoteport) {
            if(port->remoteport->node->type == IB_NODE_CA) {
                char* remotenode = node_name(port->remoteport->node, opts);
                fprintf(stdout, "%s,", remotenode);
                free(remotenode);
            }
        }
    }

    fprintf(stdout, "\n");
}

char* node_name(ibnd_node_t* node, ib2slurm_opts_t* opts)
{
    char* buf = NULL;

    if(node == NULL) {
        fprintf(stderr, "Attempted to get a node name from an invalid node.");
        exit(EXIT_FAILURE);
    }

    buf = remap_node_name(opts->node_name_map, node->guid, node->nodedesc);

    return buf;
}

void output_header()
{
    fprintf(stdout, "# topology.conf\n"
            "# Switch Configuration\n#\n"
            "# Generated by ib2slurm <http://github.com/hpc/ib2slurm>\n#\n");
}

int main(int argc, char** argv)
{
    ibnd_fabric_t* fabric = NULL;
    struct ibnd_config config = {0};
    char* ibd_ca = NULL;
    int ibd_ca_port = 0;

    char* node_name_map_file = NULL;

    static ib2slurm_opts_t opts;
    int option_index = 0;
    int c;

    static struct option long_options[] = {
        {"node-name-map", required_argument, 0, 'm'},
        {"lookup-switch-name",  no_argument, &opts.lookup_flag,   's'},
        {"compress-node-names", no_argument, &opts.compress_flag, 'c'},
        {0, 0, 0, 0}
    };

    while((c = getopt_long(argc, argv, "m:", long_options, &option_index)) != -1) {
        switch(c) {
            case 'm':
                node_name_map_file = strdup(optarg);
                break;
        }
    }

    opts.node_name_map = open_node_name_map(node_name_map_file);

    if((fabric = ibnd_discover_fabric(ibd_ca, ibd_ca_port, NULL, &config)) == NULL) {
        fprintf(stderr, "IB discover failed.\n");
        exit(EXIT_FAILURE);
    }

    output_header();
    ibnd_iter_nodes_type(fabric, switch_iter_func, IB_NODE_SWITCH, &opts);

    ibnd_destroy_fabric(fabric);
    close_node_name_map(opts.node_name_map);

    exit(EXIT_SUCCESS);
}

/* EOF */
