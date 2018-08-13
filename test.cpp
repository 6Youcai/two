#include <iostream>
#include <htslib/sam.h>
#include <vector>
#include <map>

// g++ test.cpp -I /data/home/pengl/App/Lib/C/htslib/Install/include -L /data/home/pengl/App/Lib/C/htslib/Install/lib -lhts -o test

using namespace std;

/*
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
*/

bool is_proper_pair(const bam1_t *aln) {
  uint16_t flag = aln->core.flag;
    return (flag & 2) != 0;
}

void ShowBox(const vector<bam1_t> box) {
}

int main() {
  samFile *in = sam_open("/data2/Genomics/xuyw/ctDNA0426_backup/lane_1_AGGCAGAA.bam", "r");
  samFile *out = sam_open("out.umi.bam", "wb");

  bam_hdr_t *header = sam_hdr_read(in);
  if (sam_hdr_write(out, header) < 0)
    cerr << "Couldn't write header" << endl;

  bam1_t *aln = bam_init1();
  vector<bam1_t *> box;
  int32_t start = -1; // init, never occur in bamfile
  while(sam_read1(in, header, aln) >= 0) {
    int32_t tmp_start = aln->core.pos;
    if (tmp_start == start)
      box.push_back(aln);
    else {
      //vector<bam1_t *>::iterator it = box.begin();
      //while (it != box.end()) {
      //  cout << bam_get_qname(*it) << endl;
      //  it++;
      //}
      cout << box.size() << endl;
      box.clear();
      box.push_back(aln);
      start = tmp_start;
    }
    aln = bam_init1(); // start new RAM
  }

  bam_hdr_destroy(header);
  bam_destroy1(aln);
  sam_close(in);
  sam_close(out);
  return 0;
}

/*
if (sam_write1(out, header, aln) < 0)
*/
