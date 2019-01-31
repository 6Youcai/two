#ifndef SEGMENT_H_
#define SEGMENT_H_
#include <string>
#include <htslib/sam.h>

class AlignedSegment {
private:
  bam1_t *bb;
  bam1_core_t core;
  uint16_t flag;

public:
  AlignedSegment(bam1_t *b);
  // ~AlignedSegment();
  std::string query_sequence();
  std::string query_quality();
  bool is_proper_pair();
  bool is_unmapped();
  bool is_secondary();
  bool is_supplementary();
  std::string map_coordinate();
  std::string query_name();
};

#endif
