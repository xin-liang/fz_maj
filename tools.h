#ifndef MAJ_TOOLS_H
#define MAJ_TOOLS_H

#include "pointers.h"
#include "string.h"
#include <vector>
#include "defs.h"

namespace FZMAJ_NS {

class Tools : protected Pointers {
public:

	Tools(FZMAJ *maj);
	~Tools();

    int p2cp(int);   // p : 136,  cp : 34
    string cp2str(int,int);
    string p2str(int);
    Pai str2pai(char *, Bakyou *);
    void pai2c34(vector<Pai>, int[]);
    int count34(int[]);


};

}

#endif
