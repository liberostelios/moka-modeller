#include "Matrice.hh"
#include <cstdlib>
#include <cstdio>

bool no(coord c)
{
  if(c.i==-1 && c.j==-1)
    {return true;}
  else
    {return false;}
}

Matrice::Matrice() : FSize(0)
{
  nb_lignes = 0;
  nb_colonnes = 0;
  mat = NULL;
}

unsigned long Matrice::size() const
{ return FSize; }

Matrice::Matrice(int nbli,int nbcol) : FSize(0)
{
  this->nb_lignes=nbli;
  this->nb_colonnes=nbcol;

  this->mat = new int*[nbli];
  FSize += sizeof(this->mat);
  
  for (int i = 0 ; i < nbli ; i++)
    {
      this->mat[i] = new int [nbcol] ;
      FSize += sizeof(this->mat[i]);
    }
  
  for(int i = 0 ; i < nbli ; i++)
    {
      for(int j = 0 ; j < nbcol ; j++)
	{
	  mat[i][j]=0;
	}
    }
}

Matrice::Matrice(const Matrice & source) : FSize(source.FSize)
{
  this->nb_lignes=source.nb_lignes;
  this->nb_colonnes=source.nb_colonnes;
  this->mat = new int*[source.nb_lignes];
  for (int i = 0 ; i < source.nb_lignes ; i++)
    {
      this->mat[i] = new int [source.nb_colonnes];
    }
  for (int i = 0 ; i < source.nb_lignes ; i++)
    {
      for (int j = 0 ; j < source.nb_colonnes ; j++)
	{
	  this->mat[i][j]=source.mat[i][j];
	}
    }
}

Matrice::~Matrice()
{
  for (int i = 0 ; i < nb_lignes ; i++)
    { delete []this->mat[i]; }
  
  delete []mat;
}

coord Matrice::verifyDiviseLigne(int pos)
{
  coord c;
  c.i=-1;
  c.j=-1;

  for(int i=pos;i<nb_colonnes;i++)
    {
      if(mat[pos][i]!=0 && mat[pos][i]%mat[pos][pos]!=0)
	{
	  c.i=pos;
	  c.j=i;
	}
    }

  return c;
}

coord Matrice::verifyDiviseColonne(int pos)
{
  coord c;
  c.i=-1;
  c.j=-1;

  for(int i=pos;i<nb_lignes;i++)
    {
      if(mat[i][pos]!=0 && mat[i][pos]%mat[pos][pos]!=0)
	{
	  c.i=i;
	  c.j=pos;
	}
    }

  return c;
}

coord Matrice::verifyOthers(int pos)
{
  coord c;
  c.i=-1;
  c.j=-1;
  
  for(int i=pos+1;i<nb_lignes;i++)
    {
      for(int j=pos+1;j<nb_colonnes;j++)
	{
	  if(mat[i][j]!=0 && mat[i][j]%mat[pos][pos]!=0)
	    {
	      c.i=i;
	      c.j=j;
	    }
	}
    }
  return c;
}

coord Matrice::getMinElemNonZero(int pos)
{
  coord c;
  int min=99999;
  c.i=-1;
  c.j=-1;

  for(int i=pos;i<nb_lignes;i++)
    {
      for(int j=pos;j<nb_colonnes;j++)
	{
	  if(abs(mat[i][j])<min && mat[i][j]!=0)
	    {
	      min=abs(mat[i][j]);
	      c.i=i;
	      c.j=j;
	    }
	}
    }
  return c;
}


Matrice *  Matrice::multGauche(Matrice * op2)
{
  int a=op2->nb_lignes;
  int b=op2->nb_colonnes;
  int c=nb_colonnes;
  
  Matrice *mattmp=new Matrice(a,c);
  
  for(int i=0;i<a;i++)
    {
      for(int j=0;j<c;j++)
	{
	  for(int k=0;k<b;k++)
	    {
	      mattmp->mat[i][j]+=op2->mat[i][k]*mat[k][j];
	    }
	}
    }
  return mattmp;
}

/*si les 2 matrices sont de meme dim
  alors le this devient la matrice M*/
void Matrice::setMatrice(Matrice * m)
{
  int a=nb_lignes;
  int b=nb_colonnes;
  
  for(int i=0;i<a;i++)
    {
      for(int j=0;j<b;j++)
	{
	  mat[i][j]=m->mat[i][j];
	}
    }
}

int Matrice::getVal(int i,int j)
{
  return this->mat[i][j];
}

int Matrice::getnbli()
{
  return this->nb_lignes;
}

int Matrice::getnbcol()
{
  return this->nb_colonnes;
}

void Matrice::setVal(int i,int j, int val)
{
  this->mat[i][j]=val;
}

void Matrice::inverseColonne(int i, int j)
{
  int tmp1;
  int tmp2;
  for(int n=0;n<nb_lignes;n++)
    {
      tmp1= mat[n][i];
      tmp2= mat[n][j];
      mat[n][i]=tmp2;
      mat[n][j]=tmp1;
    }
}

void Matrice::inverseLigne(int i, int j)
{
  int tmp1;
  int tmp2;
  for(int n=0;n<nb_colonnes;n++)
    {
      tmp1= mat[i][n];
      tmp2= mat[j][n];
      mat[i][n]=tmp2;
      mat[j][n]=tmp1;
    }
}

void Matrice::multiplyLigne(int i, int coeff)
{
  for(int n=0;n<nb_colonnes;n++)
    {
      mat[i][n]*=coeff;
    }
}

void Matrice::multiplyColonne(int i, int coeff)
{

  for(int n=0;n<nb_lignes;n++)
    {
      mat[n][i]*=coeff;
    }
}

void Matrice::addLigne(int i,int j, int coeff)
{
  for(int n=0;n<nb_colonnes;n++)
    {
      mat[i][n]+=coeff*mat[j][n];
    }
}

void Matrice::addColonne(int i,int j, int coeff)
{
  for(int n=0;n<nb_lignes;n++)
    {
      mat[n][i]+=coeff*mat[n][j];
    }
}

void Matrice::affiche()
{
  for (int i=0;i<nb_lignes;i++)
    {
      for(int j=0;j<nb_colonnes;j++)
	{
	  printf("%2d ",mat[i][j]);
	}
      std::cout << std::endl;
    }
}

int Matrice::nbCycle()
{
  int nb_z=0;
  for (int j=0;j<nb_colonnes;j++)
    {
      if(mat[0][j]==0)
	{
	  nb_z+=1;    
	}
      else
	{
	  break;
	}
    }
  return nb_z;
}

int Matrice::nbTorsion()
{
  int nb_z=this->nbCycle();
  int nb_t=0;
  for (int j=nb_z;j<nb_colonnes;j++)
    {
      if(mat[j-nb_z][j]>1)
	{
	  nb_t+=1;    
	}
      else
	{
	  break;
	}
    }
  return nb_t;
}

