#ifndef MATRICE_HH
#define MATRICE_HH

#include <iostream>

struct coord
{
  int i;
  int j;
};

bool no(coord c);

class Matrice
{

private :
  int nb_lignes;
  int nb_colonnes;
  int **mat;

public :
  Matrice();
  Matrice(int nbli,int nbcol); 
  Matrice(const Matrice & source);
  ~Matrice();
  
  int getVal(int i,int j);
  int getnbcol();
  int getnbli();
  coord getMinElemNonZero(int pos);
  void setVal(int i,int j,int val);
  void setMatrice(Matrice * m);
  void inverseColonne(int i, int j);
  void inverseLigne(int i,int j);
  void multiplyLigne(int i, int coeff);
  void multiplyColonne(int i,int coeff);
  Matrice * multGauche(Matrice * op2);
  coord verifyDiviseLigne(int pos);
  coord verifyDiviseColonne(int pos);
  coord verifyOthers(int pos);

  /*lignei = lignei + coeff*lignej;*/
  void addLigne(int i,int j, int coeff);
  
  void addColonne(int i,int j, int coeff);
  void affiche();
};

#endif
