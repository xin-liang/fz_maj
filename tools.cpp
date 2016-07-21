#include "tools.h"
#include "stdlib.h"
#include "string.h"
#include "error.h"
#include "game.h"

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
