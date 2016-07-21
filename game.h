#ifndef MAJ_GAME_H
#define MAJ_GAME_H

#include "pointers.h"
#include <vector>
#include <string>
#include <map>
#include "string.h"

//#define GAME_DEBUG

using namespace std;

namespace FZMAJ_NS {

class Game : protected Pointers {
public:


	Game(class FZMAJ *);
	~Game();

	void start(long);
	int started;

	class AI *ai[4];
	char *ai_style;
	typedef AI *(*AICreator)(FZMAJ *);
	void create_ai(const char*, int);
	std::map<std::string,AICreator> *ai_map;
	class AI *new_ai(const char *);
	void request(int,int);

    // for global games

    int is_aka[136];

protected: // AI BU NENG ZUO BI


    // for one set game

	int bafuu;
	int jifuu[4];
	int kyoku;
	int hajioya;
	int oya;
	int honba;
	int residue;
	int score[4];

    // for one kyoku

	int yama[136];

	int n_dora;
	int pai_ptr;
	int jun[4];
	int reach_jun[4];
	int dead_ptr;
	int pos_ptr;
	int furiten[4];
	int n_kan_tot;
    int is_renzoku;

	vector< vector<Pai> > river;
	vector< vector<int> > river_stat;
	vector<Pai> dora;
	vector<Pai> ura;

	int Ryukyoku;
	int nagaman[4];
	string agarilist[4];

    // for one junmoku

	int tsumo_hai;
	int sutehai;
	int cur_act;   //  tsumo, kiru, kakan
	int cur_pos;
	int dacya;

	int agari_flag;
	int naki_flag;

	long seed;

	template <typename T> static AI *ai_creator(FZMAJ *);

};

}

#endif
