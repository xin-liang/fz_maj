#include "check.h"
#include "input.h"
#include "error.h"
#include "memory.h"
#include "tools.h"
#include "paili.h"
#include "game.h"

using namespace FZMAJ_NS;

Check::Check(FZMAJ *maj) : Pointers(maj) {}

void Check::command(int narg, char **arg)
{
  Pai last_pai;

  set_empty_bakyou();
  printf("%s\n",arg[0]);

  last_pai = tools->str2pai(arg[0],&bak);
  paili->set_bakyou(&bak);
  paili->test();

}

void Check::set_empty_bakyou()
{

  Bakyou *b = &bak;
  game->clear_bakyou(b);
  int i,j,p;
  for(j=0;j<4;++j){
    b->score[j] = 25000;
    b->juni[j] = j;
    b->jun[j] = 0;
    b->reach_jun[j] = -1;

    b->river[j].clear();
    b->river_stat[j].clear();

    b->naki[j].clear();
    b->n_naki[j]=0;
  }
  b->bafuu = 27;
  b->jifuu = 28;
  b->kyoku = 0;
  b->oya = 0;
  b->honba = 0;
  b->residue = 0;
  b->n_dora = 0;
  b->ura_check = 0;
  b->dora.clear();
  b->ura.clear();
  b->pai_ptr = 1;
  b->dead_ptr = 122;
  b->furiten = 0;
  b->n_kan_tot = 0;

  b->tehai.clear();
  for(i=0;i<34;++i)
    b->c34[i]=0;
  b->cur_pos = 0;
  b->cur_pai.idx = -1;

}
