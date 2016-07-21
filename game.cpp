#include "stdio.h"
#include "stdlib.h"
#include "game.h"
#include "input.h"
#include "ai.h"
#include "style_ai.h"
#include "error.h"
#include "memory.h"

using namespace std;
using namespace FZMAJ_NS;

Game::Game(FZMAJ *maj) : Pointers(maj) {
	for(int i=0;i<4;++i)
		ai[i] = NULL;

	ai_map = new std::map<std::string,AICreator>();


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

void Game::start(long seed)
{
  started = 1;
  fprintf(screen, "Game started with seed %d\n",seed);

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


