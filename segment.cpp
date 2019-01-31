#include "segment.h"
#include <string>
#include <iostream>

uint8_t Base[16] = {0,65,67,0,71,0,0,0,84,0,0,0,0,0,0,78};

AlignedSegment::AlignedSegment(bam1_t *b) {
  bb = b;
  core = b->core;
  flag = b->core.flag;
}

// AlignedSegment::~AlignedSegment() {
//   std::cout << "Bye" << std::endl;
// }

std::string AlignedSegment::query_sequence() {
  int length = core.l_qseq;
  uint8_t *seq = bam_get_seq(bb);
  std::string sequence(length, '\0');
  for (int i = 0; i < length; i++)
    sequence[i] = Base[bam_seqi(seq, i)];
  return sequence;
}

std::string AlignedSegment::query_quality() {
  int length = core.l_qseq;
  uint8_t *qual = bam_get_qual(bb);
  std::string quality(length, '\0');
  for (int i = 0; i < length; i++)
    quality[i] = qual[i] + 33;
  return quality;
}

#define BAM_FPROPER_PAIR   2
#define BAM_FUNMAP         4
#define BAM_FSECONDARY   256
#define BAM_FSUPPLEMENTARY 2048
bool AlignedSegment::is_proper_pair() {
  return (flag & BAM_FPROPER_PAIR) != 0;
}
bool AlignedSegment::is_unmapped() {
  return (flag & BAM_FUNMAP) != 0;
}
bool AlignedSegment::is_secondary() {
  return (flag & BAM_FSECONDARY) != 0;
}
bool AlignedSegment::is_supplementary() {
  return (flag & BAM_FSUPPLEMENTARY) != 0;
}

std::string AlignedSegment::map_coordinate() {
  if (core.isize >=0)
    return std::to_string(core.tid) + " " +
           std::to_string(core.pos + 1) + " " +
           std::to_string(core.mpos + 1);
  else
    return std::to_string(core.tid) + " " +
           std::to_string(core.mpos + 1) + "" +
           std::to_string(core.pos + 1);
}

std::string AlignedSegment::query_name() {
  return bam_get_qname(bb);
}
