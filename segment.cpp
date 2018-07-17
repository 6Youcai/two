#include "segment.h"
#include <string>

uint8_t Base[16] = {0,65,67,0,71,0,0,0,84,0,0,0,0,0,0,78};

// 构造函数
Segment::Segment(bam1_t *b) {
  core = b->core;
  length = b->core.l_qseq;
  seq = bam_get_seq(b);
  qual = bam_get_qual(b);
}

// 析构函数
Segment::~Segment() {}

// 成员函数
std::string Segment::query_sequence() {
  std::string sequence(length, '\0');
  for (int i = 0; i < length; i++)
    sequence[i] = Base[bam_seqi(seq, i)];
    return sequence;
}
