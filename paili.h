#ifndef MAJ_PAILI_H
#define MAJ_PAILI_H

#include "pointers.h"
#include "defs.h"

namespace FZMAJ_NS {

class Paili : protected Pointers {

public:

  Paili(class FZJAM *);
  ~Paili();

  Bakyou *bak;

};

}


#endif
