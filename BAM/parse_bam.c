/* 
* Script to do something with records falling within a certain coordinate range
* The script needs a bam index for bam file you are parsing
*
* COMPILATION: 
* gcc -g -I/usr/local/include/htslib/ -D__STDC_LIMIT_MACROS -L /usr/local/lib/ parse_bam.c -o parse_bam -lz -lhts
*
* USAGE:
* parse_bam test.bam chr10:10000-110000
*/

#include "sam.h"
 
int main(int argc, char **argv) {
  hts_itr_t *iter=NULL;
	hts_idx_t *idx=NULL;
	samFile *in = NULL;
	bam1_t *b= NULL;
 
  bam_hdr_t *header = NULL;
  if(argc!=3) return -1;
  in = sam_open(argv[1], "r");
  if(in==NULL) return -1;
  if ((header = sam_hdr_read(in)) == 0) return -1;
	idx = sam_index_load(in,  argv[1]);
	if(idx==NULL) return -1;
	iter  = sam_itr_querys(idx, header, argv[2]); 
	if(iter==NULL) return -1;
	b = bam_init1();
	while ( sam_itr_next(in, iter, b) >= 0) 
	  {
	  fputs("DO STUFF\n",stdout); 
	  }
	hts_itr_destroy(iter);
	bam_destroy1(b);
	bam_hdr_destroy(header);
	sam_close(in);
   
  return 0;
}