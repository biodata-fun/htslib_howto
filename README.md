# htslib_howto
Collection of C scripts for parsing VCF/BCF, BAM/CRAM or FASTQ files using the HTSLIB C library

This repo contains a set of small C scripts showing how to use the [htslib](https://github.com/samtools/htslib) C library for parsing VCF/BCF, BAM/CRAM and FASTQ files. The htslib library is, as fas as I know, the most efficient and fastest way of parsing these kind of files, but unfortunately it is difficult to find examples of how to use it. The simple scripts found in this repo try to address this and can be used as a starting point for more complex programs.


The repo is divided in three directories, `VCF` contains all the scripts dealing with files in the [VCF](https://samtools.github.io/hts-specs/VCFv4.2.pdf) format, whereas the `BAM` directory contains the scripts to work with files in the [BAM](https://samtools.github.io/hts-specs/SAMv1.pdf) format or any of its variants. Finally, the `FASTQ` directory contains scripts to parse files in the [FASTQ](https://en.wikipedia.org/wiki/FASTQ_format) format . The instructions on how to compile each of the scripts are contained in its comments.
