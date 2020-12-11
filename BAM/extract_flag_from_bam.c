/*
* Script that reads an alignment file in the .sam|.bam|.cram format and writes a BAM with the alignments 
* corresponding to the bitwise flag passed in the command line
*
* COMPILATION:
* gcc -g -I/usr/local/include/htslib/ -D__STDC_LIMIT_MACROS -L /usr/local/lib/ extract_flag_from_bam.c  -lhts -lz -o extract_flag_from_bam
*
* USAGE:
* extract_flag_from_bam input.[sam|bam|cram] output.bam 16\
*/

#include "sam.h"
#include "hts.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if(argc != 4){
        fprintf(stderr, "USAGE: read_bam input.[sam|bam|cram] output.bam 16\n");
        exit(1);
    }

    char * fn_in  = argv[1]; // input file name
    char * fn_out = argv[2]; // output file name
    int flag = atoi(argv[3]);

    // guess what type of file fn_in is: BAM, SAM, CRAM
    htsFile * h = hts_open(fn_in, "r");
    const htsFormat *fmt = hts_get_format(h);
    int hts_close(htsFile *fp);

    fprintf(stderr, "INFO: detected %s filetype\n", hts_format_file_extension(fmt));

    samFile *in = 0;
    bam_hdr_t *header = NULL;

    // open alignment file
    if((in = sam_open_format(fn_in, "r", fmt)) == 0){
        printf("FATAL: failed to open \"%s\" for reading\n", fn_in);
        return 1;
    }

    // read-in header
    if ((header = sam_hdr_read(in)) == 0) {
        fprintf(stderr, "FATAL: failed to read the header \"%s\" \n", fn_in);
        return 1;
    }

    // output file will be BAM
    samFile *output = sam_open(fn_out, "wb");

    // write header to ouput file
    sam_hdr_write(output, header);

    bam1_t * read1 = bam_init1();
    fprintf(stderr, "Reading: %s\n", fn_in);
    fprintf(stderr, "Flag: %i will be retrieved\n", flag);
    while(sam_read1(in, header, read1) >= 0){
        if(read1->core.flag & flag){
            sam_write1(output, header, read1);
        }
    }
    bam_destroy1(read1);
    bam_hdr_destroy(header);
    sam_close(output);
    return 0;
}
