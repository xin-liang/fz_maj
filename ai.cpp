#include "ai.h"
#include "stdio.h"
#include "game.h"
#include "memory.h"

using namespace FZMAJ_NS;

AI::AI(FZMAJ *maj) : Pointers(maj)
{
  
}

AI::~AI() 
{
}

void AI::clear_act()
{
  act = 0;
  act_pai1 = -1;
  act_pai2 = -1;
}
