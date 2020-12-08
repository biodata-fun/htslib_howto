/* 
* Script to print some features for each of the alignment records
*
* COMPILATION: 
* gcc -g -I/usr/local/include/htslib/ -D__STDC_LIMIT_MACROS -L /usr/local/lib/ get_aln_feats.c  -lhts -lz -lgcov -lpthread -o get_aln_feats
*
* USAGE:
* get_aln_feats test.bam
*/

#include <stdio.h>
#include "sam.h"
  
int usage() {
    fprintf(stderr, "Usage: get_aln_feats test.bam\n");
    return 1;
}
 
int main(int argc, char* argv[]) {
    if(argc == 2) {
        samFile *fp_in = hts_open(argv[1],"r"); //open bam file
        bam_hdr_t *bamHdr = sam_hdr_read(fp_in); //read header
    	bam1_t *aln = bam_init1(); //initialize an alignment
 
        while(sam_read1(fp_in,bamHdr,aln) > 0){
		
    		  int32_t pos = aln->core.pos +1; //left most position of alignment in zero based coordianate (+1)
              char *chr = bamHdr->target_name[aln->core.tid] ; //contig name (chromosome)
		      uint32_t len = aln->core.l_qseq; //length of the read.
		
		      uint8_t *q = bam_get_seq(aln); //quality string
		      uint32_t q2 = aln->core.qual ; //mapping quality
		
		      char *qseq = (char *)malloc(len);
 
		      for(int i=0; i< len ; i++){
			      qseq[i] = seq_nt16_str[bam_seqi(q,i)]; //gets nucleotide id and converts them into IUPAC id.
		      }
		
		      printf("%s\t%d\t%d\t%s\t%s\t%d\n",chr,pos,len,qseq,q,q2);
        }
        bam_destroy1(aln);
        sam_close(fp_in);
    } else {
        return usage();
    }
 
    return 0;
}
