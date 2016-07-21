#ifndef MAJ_TOOLS_H
#define MAJ_TOOLS_H

#include "pointers.h"
#include "string.h"

namespace FZMAJ_NS {

class Tools : protected Pointers {
public:

	Tools(FZMAJ *maj);
	~Tools();

    int p2cp(int);   // p : 136,  cp : 34
    string cp2str(int,int);
    string p2str(int);




};

}

#endif
