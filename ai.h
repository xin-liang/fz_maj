#ifndef MAJ_AI_H
#define MAJ_AI_H

#include "pointers.h"
#include "defs.h"
#include <string>

namespace FZMAJ_NS {

class AI : protected Pointers {

public:

	int pos_me;
	char* style;

    AI(class FZMAJ *);
    virtual ~AI();

    virtual void compute() = 0;

    int act_pai1,act_pai2;
    int act;

    int *actlist;
    void clear_act();

};

}
#endif
