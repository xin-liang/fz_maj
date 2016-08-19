#ifndef MAJ_GAME_H
#define MAJ_GAME_H

#include "pointers.h"
#include <vector>
#include <string>
#include <map>
#include "string.h"
#include "defs.h"

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

	long seed;

    int** actlist;
    Bakyou bak[4];

    // for one set game , init in initialize_game()

	int bafuu;
	int jifuu[4];
	int kyoku;
	int hajioya;
	int oya;
	int honba;
	int residue;
	int score[4];
    int juni[4];

    // for one kyoku , init in start_kyoku()

	int yama[136];

	int n_dora;
	int pai_ptr;
	int jun[4];
	int reach_jun[4];
	int dead_ptr;
	int pos_ptr;
	int furiten[4];
	int n_kan_tot;

    vector< vector<Pai> > tehai;
    int n_tehai[4];

    int c34[4][34];   // tehai 34

	vector< vector<Pai> > river;
	vector< vector<int> > river_stat;
	vector<Pai> dora;
	vector<Pai> ura;

    vector< vector<Naki> > naki;
    int n_naki[4];

    int ura_check;

	int ryukyoku;
	int nagaman[4];
	string agarilist[4];

    // for one junmoku, update in gameloop()

    Pai cur_pai;
	int cur_act;   //  tsumo, kiru, kakan
	int cur_pos;

    // inside functions

    void initialize_game();
    void clear_game();
    void clear_bakyou(Bakyou*);
    void set_bakyou(Bakyou*, int);
    void start_kyoku();
    void rand_perm(int, int[]);
    void pai2c(Pai*,int,int[]);

    void clear_naki(Naki*);
    void set_pai(Pai*, int); // from 136 to pai

    void update_juni();   // [0]=top,[1]=sec,[2]=tir,[3]=las

    void gameloop();

    void sort_tehai(int);

	template <typename T> static AI *ai_creator(FZMAJ *);

};

}

#endif
