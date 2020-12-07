/*
* Script to print contig name and contig size from the VCF
* COMPILATION:
* gcc -g -I/usr/local/include/htslib/ -D__STDC_LIMIT_MACROS -L /usr/local/lib/ print_contig_info.c  -o print_contig_info -lz -lhts
*
* USAGE:
* print_contig_info test.vcf.gz
*/

#include "vcf.h"
 
int main(int argc, char *argv[])
{
    htsFile *fp;
    bcf_hdr_t *hdr; // bcf_hdr_t is a struct
    bcf_idpair_t *ctg;
    int i;
    if (argc == 1) {
        fprintf(stderr, "Usage: print_contig_info <in.vcf>\n");
        return 1;
    }
    fp = vcf_open(argv[1], "r");
    hdr = vcf_hdr_read(fp); 
    ctg = hdr->id[BCF_DT_CTG]; 
    for (i = 0; i < hdr->n[BCF_DT_CTG]; ++i)
        printf("%s\t%lu\n", ctg[i].key, ctg[i].val->info[0]);
    bcf_hdr_destroy(hdr);
    vcf_close(fp);
    return 0;
}