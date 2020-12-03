/* 
* Script to count number of SNPs in a VCF file
* COMPILATION: 
* gcc -g -I/usr/local/include/htslib/ -D__STDC_LIMIT_MACROS -L /usr/local/lib/ get_number_of_snps.c -o get_number_of_snps -lz -lhts
*
* USAGE:
* get_number_of_snps test.vcf.gz
*/
#include <stdio.h>
#include "vcf.h"
#include "vcfutils.h"
 
int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    // counters
    int n    = 0;  // total number of records in file
    int nsnp = 0;  // number of SNP records in file
    int nindel = 0; // number of INDEL records in file
        
    htsFile * inf = bcf_open(argv[1], "r");
    if (inf == NULL) {
        return EXIT_FAILURE;
    }
        
    // read header
    bcf_hdr_t *hdr = bcf_hdr_read(inf);
 
    // struc for storing each record
    bcf1_t *rec = bcf_init();
    if (rec == NULL) {
        return EXIT_FAILURE;
    }
 
    while (bcf_read(inf, hdr, rec) == 0) {
        n++;
        if (bcf_is_snp(rec)) {
            nsnp++;
        } else {
            continue;
        }
    }
    fprintf(stderr, "Number of SNPs: %i\n", nsnp);
 
    bcf_hdr_destroy(hdr);
    bcf_close(inf);
    bcf_destroy(rec);
    return EXIT_SUCCESS;
}