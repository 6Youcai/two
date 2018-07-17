#ifndef SEGMENT_H_
#define SEGMENT_H_
#include <string>
#include <htslib/sam.h>

class Segment {
private:
  bam1_core_t core;
  int length;
  uint8_t *seq;
  uint8_t *qual;
public:
  Segment(bam1_t *b);
  ~Segment();
  std::string query_sequence();
};

#endif
