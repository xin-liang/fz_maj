#ifndef MAJ_DEFS_H
#define MAJ_DEFS_H

#define PI 3.1415926535897932384626

#define mio "mio hen cong ming de, bu yao qi fu mio."

#include <vector>
#include <string>

using namespace std;

struct Pai {
  string spai;
  int cpai; //34
  int idx; //136
  int aka; // 1 for aka, 0 for others
};

struct Naki {
  int naki_type; // 0: pon  1: chii  2: ankan  3: minkan  4: kakan
  int n_pai;  // 3 for chi and pon; 4 for kan
  Pai pais[4];
  int idx_naki_pai; //  which pai is naki pai
  int naki_from;  // naki from where, 0 for ankan
};

enum ACT {

  ACT_CANCEL = 0,
  ACT_TSUMOGIRI,
  ACT_TEKIRI,
  ACT_AGARI_TSUMO,
  ACT_AGARI_RON,
  ACT_KAKAN,
  ACT_CHII,
  ACT_PON,
  ACT_ANKAN,
  ACT_MINKAN,
  ACT_REACH,
  ACT_NAGASI_99,
  ACT_ADMIN_QUIT,
  NUM_ACT

};

struct Bakyou {

  int bafuu;
  int jifuu;
  int kyoku;
  int oya;
  int honba;
  int residue;
  int score[4];
  int juni[4];

  int n_dora;
  int pai_ptr;
  int dead_ptr;
  int jun[4];
  int reach_jun[4];
  int furiten;
  int n_kan_tot;

  vector<Pai> tehai;

  int n_tehai;
  int c34[34];

  vector< vector<Pai> > river;
  vector< vector<int> > river_stat;
  vector<Pai> dora;
  vector<Pai> ura;

  vector< vector<Naki> > naki;
  int n_naki[4];

  int ura_check;

  Pai cur_pai;
  int cur_pos;

};

struct Pattern {

  int c[34];
  int score;
  int score_oya;
  int score_ko;

  int fan, fan_nodora;
  int fu,fu_tmp;
  int yaku[46];

  int is_chiitoi;
  int is_kokushi;

  int is_yakuman;
  int yakuman_baisu;

};



#endif
