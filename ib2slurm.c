/*
 * An experiment to see if we can generate a slurm style topology.conf file
 * from ib network discovery.
 *
 * Jon Bringhurst <jonb@lanl.gov> - 2011-11-15
 */

#include <stdio.h>                                                                                                         
#include <stdlib.h>                                                                                                        
#include <infiniband/ibnetdisc.h>                                                                                          
                                                                                                                           
int main(void)                                                                                                             
{                                                                                                                          
    struct ibnd_config config = {0};                                                                                       
    ibnd_fabric_t *fabric = NULL;                                                                                          
                                                                                                                           
    char *ibd_ca = NULL;                                                                                                   
    int ibd_ca_port = 0;                                                                                                   
                                                                                                                           
    if ((fabric = ibnd_discover_fabric(ibd_ca, ibd_ca_port, NULL, &config)) == NULL) {                                     
        fprintf(stderr, "IB discover failed.\n");                                                                          
        exit(EXIT_FAILURE);                                                                                                
    }                                                                                                                      
                                                                                                                           
    ibnd_chassis_t *ch = NULL;                                                                                             
    ibnd_node_t *node; 
    for (ch = fabric->chassis; ch; ch = ch->next) {                                                                        
        fprintf(stdout, "Found a chassis!\n");

        int i = 0;                                                                                  
        ibnd_node_t *node;
                                                                                                                           
        for (node = ch->nodes; node; node = node->next_chassis_node) {                                                     
            fprintf(stdout, "Found a node!\n");
            if (node->type == IB_NODE_SWITCH) {                                                                            
                fprintf(stdout, "Found a switch!\n");                                                                      
            }  
        }                                                                                                            
    }                                                                                                                      
                                                                                                                           
    ibnd_destroy_fabric(fabric);                                                                                           
    exit(EXIT_SUCCESS);
}

/* EOF */
