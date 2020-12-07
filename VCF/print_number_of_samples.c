/*
* Script to print the number of samples in a VCF file
* COMPILATION:
* gcc -g -I/usr/local/include/htslib/ -D__STDC_LIMIT_MACROS -L /usr/local/lib/ print_number_of_samples.c  -o print_number_of_samples -lz -lhts
*
* USAGE:
* print_number_of_samples test.vcf.gz
*/

#include <stdio.h>  //puts and printf
#include "vcf.h"
 
int main(int argc, char **argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
 
    // counters
    int nseq = 0;
 
    htsFile * inf = bcf_open(argv[1], "r");
    if (inf == NULL) {
        return EXIT_FAILURE;
    }
 
    // read header
    bcf_hdr_t *hdr = bcf_hdr_read(inf);
    fprintf(stderr, "File %s contains %i samples\n", argv[1], bcf_hdr_nsamples(hdr));
 
    bcf_hdr_destroy(hdr);
    bcf_close(inf);
 
    return 0;
}