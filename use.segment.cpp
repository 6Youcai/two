#include <iostream>
#include "segment.h"

using namespace std;

int main() {
  samFile *in = sam_open("/data2/Genomics/xuyw/ctDNA0426_backup/lane_1_AGGCAGAA.bam", "r");
  // samFile *out = sam_open("out.umi.bam", "wb");

  bam_hdr_t *header = sam_hdr_read(in);
  // if (sam_hdr_write(out, header) < 0)
  //   cerr << "Couldn't write header" << endl;

  bam1_t *b = bam_init1();
  while(sam_read1(in, header, b) >= 0) {
    Segment read(b);
    cout << read.query_sequence() << endl;

    b = bam_init1(); // start new RAM
  }

  bam_hdr_destroy(header);
  bam_destroy1(b);
  sam_close(in);
  // sam_close(out);
  return 0;
}
