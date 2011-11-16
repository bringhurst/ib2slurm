ib2slurm 0.1
============

A program that attempts to generate a slurm style topology.conf(5) file using
infiniband network discovery services.

Usage
-----

```ib2slurm --node-name-map <name_map>```

_name_map_ is the location of a node name map file formatted as described in the
ibnetdiscover(8) man page. The node name map entries must be compatible with
slurm's currently used node naming scheme.

If a node name map is not provided, ib2slurm will attempt to print the raw
infiniband guid values instead. If this happens, the topology file will not
be usable by slurm.
