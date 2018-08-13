#include <iostream>
#include <htslib/sam.h>
#include <vector>
#include <map>

// g++ main.cpp -I /data/home/pengl/App/Lib/C/htslib/Install/include -L /data/home/pengl/App/Lib/C/htslib/Install/lib -lhts
// https://github.com/samtools/htslib/blob/develop/htslib/sam.h

using namespace std;

// "=ACMGRSVTWYHKDBN"
uint8_t Base[16] = {0,65,67,0,71,0,0,0,84,0,0,0,0,0,0,78};

string get_sequence(const bam1_t *aln) {
  int length = aln->core.l_qseq;
  uint8_t *seq = bam_get_seq(aln);
  string sequence(length, '\0');
  for (int i = 0; i < length; i++)
    sequence[i] = Base[bam_seqi(seq, i)];
  return sequence;
}

string get_quality(const bam1_t *aln) {
  int length = aln->core.l_qseq;
  uint8_t *qual = bam_get_qual(aln);
  string quality(length, '\0');
  for (int i = 0; i < length; i++)
    quality[i] = qual[i] + 33;
  return quality;
}

bool is_proper_pair(const bam1_t *aln) {
  uint16_t flag = aln->core.flag;
    return (flag & 2) != 0;
}

int main() {
  samFile *in;
  in = sam_open("/data2/Genomics/xuyw/ctDNA0426_backup/lane_1_AGGCAGAA.bam", "r");

  bam_hdr_t *header = sam_hdr_read(in);
  bam1_t *aln = bam_init1();
  
  // map<string, bam1_t*> dict;
  long good = 0, all = 0;

  while(sam_read1(in, header, aln) >= 0) {
    int32_t start = aln->core.pos;
    // string name = bam_get_qname(aln);
    // string seq = get_sequence(aln);
    // string qual = get_quality(aln);
    // string umi = seq.substr(0, 9);

    if (is_proper_pair(aln))
      good++;
    all++;
  }
  cout << "proper_pair: " << good << endl;
  cout << "all reads:" << all << endl;
  return 0;
}
