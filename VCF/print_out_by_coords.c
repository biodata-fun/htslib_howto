/*
* Script to parse a certain file.vcf or file.vcf.gz file and print the records within a certain genomic interval to STDOUT
* 
* COMPILATION:
* gcc -std=c11 -g -I/usr/local/include/htslib/ -D__STDC_LIMIT_MACROS -L /usr/local/lib/ print_out_by_coords.c -o print_out_by_coords -lz -lhts
*
* USAGE:
* print_out_by_coords test.vcf.gz test.vcf.gz.csi 10 1000 1100
*/
#include <hts.h>
#include <vcf.h>
#include <tbx.h>


int main(int argc, char **argv)
{
    assert(argc == 6);
    const char *fn = argv[1], *fnidx = argv[2], *seq = argv[3];
    int start = atoi(argv[4]) - 1, end = atoi(argv[5]);

    tbx_t *idx=NULL;
    htsFile * fp=NULL;
    bcf_hdr_t *hdr=NULL;
    hts_itr_t *itr=NULL;
    bcf1_t *rec=NULL;
    kstring_t ksbuf = {0,0,0};

    fp = vcf_open(fn, "r");
    if (fp == NULL) {
        printf("error: failed to open file %s\n", fn);
        return EXIT_FAILURE;
    }

    idx = tbx_index_load2(fn, fnidx);
    if (idx == NULL) {
        printf("error: failed to open index file %s\n", fnidx);
        return EXIT_FAILURE;
    }
    
    hdr = bcf_hdr_read(fp);
    if (hdr == NULL) {
        printf("error: header error in %s\n", fn);
        return EXIT_FAILURE;
    }
    
    int tid = tbx_name2id(idx, seq);
    if (tid == -1) {
        printf("error: sequence %s not present in file %s\n", seq, fn);
        return EXIT_FAILURE;
    }
    
    itr = tbx_itr_queryi(idx, tid, start, end);
    if (itr == NULL) {
        printf("error: tbx_itr_queryi() returned NULL\n");
        return EXIT_FAILURE;
    }

    rec = bcf_init();
    if (NULL == rec) {
        printf("error: bcf_init() returned NULL\n");
        return EXIT_FAILURE;
    }

    while (tbx_itr_next(fp, idx, itr, &ksbuf) >= 0) {
        printf("%s\n", ksbuf.s); // print line
    }

    return 0;
}

