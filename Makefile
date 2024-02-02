#Makefile progetto ASD 2020
gestione_albero_bin_ric_rand: gestione_albero_bin_ric_rand.c gestione_albero_bin_ric_rand_test.c Makefile
	gcc -ansi -Wall -O gestione_albero_bin_ric_rand.c -o gestione_albero_bin_ric_rand
	gcc -ansi -Wall -O gestione_albero_bin_ric_rand_test.c -o gestione_albero_bin_ric_rand_test

pulisci_tutto:
	rm -f gestione_albero_bin_ric_rand 
	rm -f gestione_albero_bin_ric_rand_test 
