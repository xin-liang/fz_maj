#include "tools.h"
#include "stdlib.h"
#include "string.h"
#include "error.h"
#include "game.h"
#include "defs.h"

using namespace FZMAJ_NS;

Tools::Tools(FZMAJ *maj) : Pointers(maj) {}

Tools::~Tools(){}

int Tools::p2cp(int p)
{
  return (int)p/4;
}

string Tools::p2str(int p)
{
  int cp;
  int aka;
  aka = game->is_aka[p];
  cp = p2cp(p);
  return cp2str(cp, aka);
}

string Tools::cp2str(int cp, int aka)
{
  string sth = "";
  char tp;
  if (cp>=9) {cp -= 9; tp = 'p';}
  else tp='m';
  if (cp>=9) {cp -= 9; tp = 's';}
  if (cp>=9) {cp -= 9; tp = 'z';}
  if (aka) sth += '0';
  else sth += ('1'+cp);
  sth += tp;
  return sth;
}

Pai Tools::str2pai(char *spai,Bakyou *b)
{
  Pai tmp_pai,last_pai;
  int i,j, e=-1, l, t, last, lastaka=0;
  int p_base,p;
  int h[3] = {0,0,0};
  int c[34];
  b->tehai.clear();
  for (i=0;i<34;++i)
    c[i]=0;
  l = strlen(spai);
  for(i=l-1;i>=0;i--) {
    if      (spai[i]=='m') e=0;
    else if (spai[i]=='p') e=1;
    else if (spai[i]=='s') e=2;
    else if (spai[i]=='z') e=3;
    else if (spai[i]>='0' && spai[i]<='9') {
      if (e==-1) error->all(FLERR,"Bad String");
      t=spai[i]-'0';
      if (t==0) {
        if (e>=3) error->all(FLERR, "BAD String");
        if (h[e]==0) {
          ++h[e];t=5;
          if (i==l-2)
            lastaka=1;
        }
        else error->all(FLERR, "Too many 0 in string");
      }
      if (t==5 && h[e]==0 && c[t*9+1]==3) error->all(FLERR,"no aka bug");
      t+=e*9-1;
      if (t>33) error->all(FLERR,"Illegal string");
      if (c[t]<4) ++c[t]; else error->all(FLERR,"too many same pai");
      if (i==l-2) last=t;
    }
  }
  last_pai.cpai = last;
  last_pai.aka = lastaka;
  last_pai.spai = cp2str(last,lastaka);
  last_pai.idx = last*4 + c[last] - 1;
  if (last%9==4)
    if (lastaka) last_pai.idx = last*4;
    else last_pai.idx = last_pai.idx - h[last/9] + 1;
  for (i=0;i<34;++i){
    p_base = i<<2;
    if (i%9==4 && h[i/9]==0) ++p_base;   // skip aka
    for (j=0;j<c[i];++j)
    {
      p = p_base + j;
      tmp_pai.idx = p;
      tmp_pai.cpai = i;
      tmp_pai.aka = game->is_aka[p];
      tmp_pai.spai = p2str(p);
      if (tmp_pai.idx!=last_pai.idx)
        b->tehai.push_back(tmp_pai);
    }
  }
  printf("here\n");
  b->cur_pai = last_pai;
  b->tehai.push_back(last_pai);
  return last_pai;
}

int Tools::count34(int c34[])
{
  int cnt = 0;
  for(int i=0;i<34;++i)
    cnt += c34[i];
  return cnt;
}

void Tools::pai2c34(vector<Pai> p, int c34[])
{
  for (int i=0;i<p.size();++i)
    ++c34[p[i].cpai];
}
