#include "paili.h"
#include "tools.h"
#include "yaku.h"

#include "defs.h"
#include <vector>

using namespace FZMAJ_NS;

Paili::Paili(FZMAJ *maj) : Pointers(maj)

{
  yaku = new Yaku(maj);

}


Paili::~Paili() {}

void Paili::set_bakyou(Bakyou *b)
{
  bak = b;
}

void Paili::test()
{
  int i;
  int is_agari_kata;
  printf ("**************  paili   test  **************\n");
  printf ("tehai: ");
  for (i=0;i<bak->tehai.size();++i)
    printf(" %s ",tools->p2str(bak->tehai[i].idx).c_str());
  printf("\n");
  printf("dora : %d, hyoji =",bak->n_dora);
  for (i=0;i<bak->n_dora;++i)
    printf (" %s ",bak->dora[i].spai.c_str());
  printf("\n");
  if (bak->ura_check)
  {
    printf(" ura : %d, hyoji =",bak->n_dora);
    for (i=0;i<bak->n_dora;++i)
      printf (" %s ",bak->ura[i].spai.c_str());
    printf("\n");
  }
  else
  {
    printf(" ura : unavailabe\n");
  }
  is_agari_kata = test_agari_kata();
  printf("is_agari_kata : %d\n",is_agari_kata);
}

int Paili::test_agari_kata()
{
  tools->pai2c34(bak->tehai,bak->c34);
  int cnt = tools->count34(bak->c34);

  if (cnt%3!=2)
    return -1;

  int *c=bak->c34;
  int j=(1<<c[27])|(1<<c[28])|(1<<c[29])|(1<<c[30])|(1<<c[31])|(1<<c[32])|(1<<c[33]);
  if (j>=0x10) return 0;
  // Kokushi musou
  if (((j&3)==2) && (c[0]*c[8]*c[9]*c[17]*c[18]*c[26]*c[27]*c[28]*c[29]*c[30]*c[31]*c[32]*c[33]==2)) return 1;
  // 7 tui tsu
  if (!(j&10) && (
    (c[ 0]==2)+(c[ 1]==2)+(c[ 2]==2)+(c[ 3]==2)+(c[ 4]==2)+(c[ 5]==2)+(c[ 6]==2)+(c[ 7]==2)+(c[ 8]==2)+
    (c[ 9]==2)+(c[10]==2)+(c[11]==2)+(c[12]==2)+(c[13]==2)+(c[14]==2)+(c[15]==2)+(c[16]==2)+(c[17]==2)+
    (c[18]==2)+(c[19]==2)+(c[20]==2)+(c[21]==2)+(c[22]==2)+(c[23]==2)+(c[24]==2)+(c[25]==2)+(c[26]==2)+
    (c[27]==2)+(c[28]==2)+(c[29]==2)+(c[30]==2)+(c[31]==2)+(c[32]==2)+(c[33]==2))==7) return 1;
  if (j&2) return 0;
  int n00 = c[ 0]+c[ 3]+c[ 6], n01 = c[ 1]+c[ 4]+c[ 7], n02 = c[ 2]+c[ 5]+c[ 8];
  int n10 = c[ 9]+c[12]+c[15], n11 = c[10]+c[13]+c[16], n12 = c[11]+c[14]+c[17];
  int n20 = c[18]+c[21]+c[24], n21 = c[19]+c[22]+c[25], n22 = c[20]+c[23]+c[26];
  int n0 = (n00+n01+n02)%3;
  if (n0==1) return 0;
  int n1 = (n10+n11+n12)%3;
  if (n1==1) return 0;
  int n2 = (n20+n21+n22)%3;
  if (n2==1) return 0;
  if ((n0==2)+(n1==2)+(n2==2)+
    (c[27]==2)+(c[28]==2)+(c[29]==2)+(c[30]==2)+(c[31]==2)+(c[32]==2)+(c[33]==2)!=1) return 0;
  int nn0=(n00*1+n01*2)%3, m0=cc2m(c, 0);
  int nn1=(n10*1+n11*2)%3, m1=cc2m(c, 9);
  int nn2=(n20*1+n21*2)%3, m2=cc2m(c,18);
  if (j&4) return !(n0|nn0|n1|nn1|n2|nn2) && isMentsu(m0) && isMentsu(m1) && isMentsu(m2);
  if (n0==2) return !(n1|nn1|n2|nn2) && isMentsu(m1) && isMentsu(m2) && isAtamaMentsu(nn0,m0);
  if (n1==2) return !(n2|nn2|n0|nn0) && isMentsu(m2) && isMentsu(m0) && isAtamaMentsu(nn1,m1);
  if (n2==2) return !(n0|nn0|n1|nn1) && isMentsu(m0) && isMentsu(m1) && isAtamaMentsu(nn2,m2);
  return 0;
}

bool Paili::isMentsu(int m)
{
  int a=(m&7), b=0, c=0;
  if (a==1 || a==4) b=c=1; else if (a==2) b=c=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a<0) return false;b=c, c=0;if (a==1 || a==4) b+=1, c+=1; else if (a==2) b+=2, c+=2;
  m>>=3, a=(m&7)-b;if (a!=0 && a!=3) return false;
  m>>=3, a=(m&7)-c;
  return a==0 || a==3;
}

bool Paili::isAtamaMentsu(int nn, int m)
{
  if (nn==0){
    if ((m&(7<< 6))>=(2<< 6) && isMentsu(m-(2<< 6))) return true;
    if ((m&(7<<15))>=(2<<15) && isMentsu(m-(2<<15))) return true;
    if ((m&(7<<24))>=(2<<24) && isMentsu(m-(2<<24))) return true;
  }else if (nn==1){
    if ((m&(7<< 3))>=(2<< 3) && isMentsu(m-(2<< 3))) return true;
    if ((m&(7<<12))>=(2<<12) && isMentsu(m-(2<<12))) return true;
    if ((m&(7<<21))>=(2<<21) && isMentsu(m-(2<<21))) return true;
  }else if (nn==2){
    if ((m&(7<< 0))>=(2<< 0) && isMentsu(m-(2<< 0))) return true;
    if ((m&(7<< 9))>=(2<< 9) && isMentsu(m-(2<< 9))) return true;
    if ((m&(7<<18))>=(2<<18) && isMentsu(m-(2<<18))) return true;
  }
  return false;
}

int Paili::cc2m(int c[], int d)
{
  return (c[d+0]<< 0)|(c[d+1]<< 3)|(c[d+2]<< 6)|
         (c[d+3]<< 9)|(c[d+4]<<12)|(c[d+5]<<15)|
         (c[d+6]<<18)|(c[d+7]<<21)|(c[d+8]<<24);
}
