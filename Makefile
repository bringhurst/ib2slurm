all:
	cc -Wextra -Wall -g -o ib2slurm ib2slurm.c -I/usr/include/infiniband -libnetdisc

clean:
	rm -f ib2slurm core.*
