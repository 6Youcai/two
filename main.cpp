#include <iostream>
#include "segment.h"
#include <string> 

int main() {
  samFile *in = sam_open("/data2/Genomics/xuyw/ctDNA0426_backup/lane_4_TAAGGCGA.bam", "r");
  samFile *out = sam_open("out.cpp.bam", "wb");

  bam_hdr_t *header = sam_hdr_read(in);
  if (sam_hdr_write(out, header) < 0) {
    std::cerr << "Cannot write BAM file" << std::endl;
    return 0;
  }


  char **references = header->target_name;

  bam1_t *b = bam_init1();
  // input
  while(sam_read1(in, header, b) >= 0) {
    AlignedSegment read(b);
    if (read.is_unmapped() || read.is_secondary() || read.is_supplementary() || (!read.is_proper_pair())) {
        // output
        if (sam_write1(out, header, b) < 0 ) {
          std::cerr << "write failed" << std::endl;
          return 1;
        }
        continue;
    }
    std::cout << read.query_name() << "\t" << read.map_coordinate() << std::endl;

  }

  bam_hdr_destroy(header);
  bam_destroy1(b);
  sam_close(in);
  sam_close(out);
  return 0;
}
