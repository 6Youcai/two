#include "segment.h"
#include <string>
#include <iostream>

uint8_t Base[16] = {0,65,67,0,71,0,0,0,84,0,0,0,0,0,0,78};

Segment::Segment(bam1_t *b) {
  core = b->core;
  length = core.l_qseq;
  seq = bam_get_seq(b);
  qual = bam_get_qual(b);
  flag = b->core.flag;
}

Segment::~Segment() {
  std::cout << "Bye" << std::endl;
}

//
std::string Segment::query_sequence() {
  std::string sequence(length, '\0');
  for (int i = 0; i < length; i++)
    sequence[i] = Base[bam_seqi(seq, i)];
    return sequence;
}

std::string Segment::query_quality() {
  std::string quality(length, '\0');
  for (int i = 0; i < length; i++)
    quality[i] = qual[i] + 33;
  return quality;
}

bool Segment::is_proper_pair() {
  return (flag & 2) != 0;
}
