#include "defs.h"
#include "stdio.h"
#include "stdlib.h"
#include "game.h"
#include "input.h"
#include "ai.h"
#include "style_ai.h"
#include "error.h"
#include "memory.h"
#include "tools.h"
#include "paili.h"

#include <vector>
#include <functional>
#include <algorithm>


#define DEBUG_GAME 1

using namespace std;
using namespace FZMAJ_NS;

Game::Game(FZMAJ *maj) : Pointers(maj) {
	for(int i=0;i<4;++i)
		ai[i] = NULL;

	ai_map = new std::map<std::string,AICreator>();
    memory->create(actlist,4,NUM_ACT,"game:actlist");

    for(int i=0;i<136;++i)
      is_aka[i]=0;
    is_aka[16]=1;
    is_aka[52]=1;
    is_aka[88]=1;

    started = 0;

#define AI_CLASS
#define AIStyle(key,Class) \
  (*ai_map)[#key] = &ai_creator<Class>;
#include "style_ai.h"
#undef AIStyle
#undef AI_CLASS
}

Game::~Game(){
	delete ai_map;
	for (int i=0;i<4;++i)
		delete ai[i];
}

void Game::start(long s)
{
  seed = s;
  srand(seed);
  started = 1;
  fprintf(screen, "Game started with seed %d\n",seed);

  // check ai settings
  for(int i=0;i<4;++i)
    if (!ai[i]){
      create_ai("general",i);
    }

  // initialize the set of game

  initialize_game();

  fprintf(screen, "Start Kyoku test\n");

  start_kyoku();

}

void Game::initialize_game()
{
  bafuu = 27; //cp
  kyoku = 0;
  hajioya = rand()%4;
  oya  = hajioya;
  honba = 0;
  residue = 0;
  pai_ptr = 0;
  pos_ptr = hajioya;

  river.resize(4);
  river_stat.resize(4);
  naki.resize(4);
  tehai.resize(4);
  for(int i=0;i<4;++i)
    score[i] = 25000;

  update_juni();

}

void Game::update_juni()
{
  int top=0,sec=1,tir=2,las=3,swp;
  if(score[sec]>score[top]){swp=sec;sec=top;top=swp;}
  if(score[tir]>score[top]){swp=tir;tir=top;top=swp;}
  if(score[las]>score[top]){swp=las;las=top;top=swp;}
  if(score[tir]>score[sec]){swp=sec;sec=tir;tir=swp;}
  if(score[las]>score[sec]){swp=las;las=sec;sec=swp;}
  if(score[las]>score[tir]){swp=tir;tir=las;las=swp;}
  juni[0]=top;
  juni[1]=sec;
  juni[2]=tir;
  juni[3]=las;
}

void Game::start_kyoku()
{

  int i,j,k;
  int p,c0;
  Pai pai_tmp;

  clear_game();

  rand_perm(136,yama);

  // zhua pai

  for(i=0;i<3;++i)
    for(j=0;j<4;++j) {
      p = (j+oya)%4;
      for(k=0;k<4;++k) {
        c0 = yama[pai_ptr+k];
        set_pai(&pai_tmp,c0);
        tehai[p].push_back(pai_tmp);
      }
      pai_ptr += 4;
    }

  for(i=0;i<4;++i){
    p = (i+oya)%4;
    c0 = yama[pai_ptr+i];
    set_pai(&pai_tmp,c0);
    tehai[p].push_back(pai_tmp);
    n_tehai[p] = 13;
  }
  pai_ptr += 4;


  dead_ptr = 122;
  ura_check = 0;
  ryukyoku = 0;

  n_dora = 1;
  set_pai(&pai_tmp,yama[130]);
  dora.push_back(pai_tmp);
  set_pai(&pai_tmp,yama[131]);
  ura.push_back(pai_tmp);

  cur_pos = oya;
  set_pai(&cur_pai,yama[pai_ptr]);

  //test

  printf("dora hyoji = %s\n",dora[0].spai.c_str());
  printf("ura hyoji = %s\n",ura[0].spai.c_str());

  sort_tehai(0);
  tehai[0].push_back(cur_pai);

  debug_print_tehai(0);


  set_bakyou(0);

  paili->set_bakyou(&bak);
  paili->test();


}

void Game::debug_print_tehai(int pos)
{
#ifdef DEBUG_GAME
  printf("tehai %d: ",pos);
  for (int i=0;i<tehai[pos].size();++i)
    printf(" %s ",tools->p2str(tehai[pos][i].idx).c_str());
  printf("\n");
#endif
}

void Game::set_pai(Pai* pai, int c0)
{
  pai->idx = c0;
  pai->cpai = c0>>2;
  pai->aka = game->is_aka[c0];
  pai->spai = tools->p2str(c0);
}

void Game::pai2c(Pai* pai, int n_pai, int c[])
{
  int i;
  for(i=0;i<34;++i)
    c[i]=0;
  for(i=0;i<n_pai;++i)
    c[pai->cpai]++;
}

void Game::clear_bakyou(Bakyou* b)
{
  b->dora.clear();
  b->river.resize(4);
  b->river_stat.resize(4);
  b->naki.resize(4);
  b->ura.clear();
}

void Game::set_bakyou(int pos)
{
  Bakyou *b = &bak;
  clear_bakyou(b);
  int i,j,p;
  for(j=0;j<4;++j){
    p = (j-pos+4)%4;

    b->score[j] = score[p];
    b->juni[j] = juni[p];
    b->jun[j] = jun[p];
    b->reach_jun[j] = reach_jun[p];

    b->river[j] = river[p];
    b->river_stat[j] = river_stat[p];

    b->naki[j] = naki[p];
    b->n_naki[j] = n_naki[p];
  }
  b->bafuu = bafuu;
  b->jifuu = 27 + (4+pos-oya)%4;
  b->kyoku = kyoku;
  b->oya = oya;
  b->honba = honba;
  b->residue = residue;

  b->n_dora = n_dora;
  b->dora = dora;
  b->ura_check = ura_check;
  if (ura_check)
    b->ura = ura;
  b->pai_ptr = pai_ptr;
  b->dead_ptr = dead_ptr;
  b->furiten = furiten[pos];
  b->n_kan_tot = n_kan_tot;

  b->tehai = tehai[pos];
  b->n_tehai = n_tehai[pos];
  for(i=0;i<34;++i)
    b->c34[i] = c34[pos][i];

  b->cur_pai = cur_pai;
  b->cur_pos = cur_pos;
}

void Game::clear_game()
{
  int i,j;
  dora.clear();
  ura.clear();
  pai_ptr = 0;
  n_kan_tot = 0;
  for(i=0;i<4;++i){
    tehai[i].clear();
    river[i].clear();
    naki[i].clear();
    river_stat[i].clear();
    jun[i]=0;
    reach_jun[i]=-1;
    furiten[i]=0;
    nagaman[i]=0;
    n_naki[i]=0;
  }

}

void Game::clear_naki(Naki *nk){
  nk->naki_type = 0;
  nk->n_pai = 0;
  nk->idx_naki_pai = -1;
  nk->naki_from = 0;
}

void Game::rand_perm(int n, int perm[])
{
  int i,j,t;
  for(i=0;i<n;++i)
    perm[i]=i;
  for(i=0;i<n;++i){
    j = rand()%(n-i)+i;
    t = perm[j];
    perm[j] = perm[i];
    perm[i] = t;
  }
}

void Game::gameloop()
{
}

bool sort_by_p(const Pai& p1, const Pai& p2){return p1.idx < p2.idx;}

void Game::sort_tehai(int pos)
{
  sort(tehai[pos].begin(),tehai[pos].end(),sort_by_p);
}

void Game::create_ai(const char *style, int pos)
{
    if (pos>3) error->all(FLERR,"AI position should be 0~3");
	if (ai[pos]) delete ai[pos];
	ai[pos] = new_ai(style);
	ai[pos]->pos_me = pos;
	int n = strlen(style)+1;
	ai[pos]->style = new char[n];
	strcpy(ai[pos]->style, style);
}

AI *Game::new_ai(const char *style)
{
	if (!strcmp(style, "none")) return NULL;
	if (ai_map->find(style) != ai_map->end()) {
		AICreator ai_creator = (*ai_map)[style];
		return ai_creator(maj);
	}

	error->all(FLERR, "Invalid ai style");
	return NULL;
}

template <typename T>
AI *Game::ai_creator(FZMAJ *maj)
{
	return new T(maj);
}


