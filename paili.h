#ifndef MAJ_PAILI_H
#define MAJ_PAILI_H

#include "pointers.h"
#include "defs.h"

namespace FZMAJ_NS {

class Paili : protected Pointers {

public:

  Paili(class FZMAJ *);
  ~Paili();

  Bakyou *bak;

  void set_bakyou(Bakyou *b);

  void test();

  int test_agari_kata();

  void calc_syanten();
  int is_tenpai();

  int syanten_all;   // syanten_all = MIN(syanten_7, syanten_13, syanten_normal)
  int syanten_7;
  int syanten_13;
  int syanten_normal;

  class Yaku *yaku;

protected:

  bool isMentsu(int);
  bool isAtamaMentsu(int,int);
  int cc2m(int[],int);

  /* syanten

  int n_eval;
  int f_n4;
  int f_koritsu;
  int n_jidahai;
  int bakc[34];
  int c[34];
  int n_mentsu;
  int n_tatsu;
  int n_toitsu;

  void st_update_result();
  void st_scan_713();
  void st_scan_normal();
  void st_run();
  void st_remove_jihai();
  void st_i_anko(int);
  void st_d_anko(int);

*/

};

}


#endif
