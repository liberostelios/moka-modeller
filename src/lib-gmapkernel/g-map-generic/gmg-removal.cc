/*
 * lib-gmapkernel : Un noyau de 3-G-cartes et des opérations.
 * Copyright (C) 2004, Moka Team, Université de Poitiers, Laboratoire SIC
 *               http://www.sic.sp2mi.univ-poitiers.fr/
 * Copyright (C) 2009, Guillaume Damiand, CNRS, LIRIS,
 *               guillaume.damiand@liris.cnrs.fr, http://liris.cnrs.fr/
 *
 * This file is part of lib-gmapkernel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//******************************************************************************
#include "g-map-generic.hh"
#include <deque>
#include <stack>
using namespace std;
using namespace GMap3d;
//******************************************************************************
// Suppression d'une i-cellules incidente à un brin donné.
//
// dim == 2: suppression de face
//           (pas de précondition)
// dim == 1: suppression d'arête
//           (précondition : arête de degré inférieur local égal à 2)
// dim == 0: suppression de sommet
//           (précondition : sommet de degré inférieur local égal à 2)
// 
//******************************************************************************
bool CGMapGeneric::canRemove(CDart * ADart, int ADim)
{
  assert(ADart!=NULL);
  assert(ADim>=0 && ADim<=2);

  return isLocalDegreeTwoSup(ADart, ADim);
}
//******************************************************************************
void CGMapGeneric::remove(CDart * ADart, int ADim, bool ADeleteDarts)
{
  assert(ADart!=NULL);
  assert(ADim>=0 && ADim<=2);
  assert(canRemove(ADart, ADim));

  int mark = getNewMark();
  markOrbit(ADart, ORBIT_CELL[ADim], mark);

  CDart* current = NULL;
  CDart* t2      = NULL;
  
  CCoverage * it = getStaticCoverage(ADart, ORBIT_CELL[ADim]);
  while ( it->cont() )
    {
      current = alpha((*it)++, ADim);
      if ( !isMarked(current, mark) )
	{
	  t2 = alpha(current, ADim);
	  while ( isMarked(t2, mark) )
	    {
	      t2 = alpha(alpha(t2, ADim+1), ADim);
	    }
	  
	  if ( t2 != alpha(current, ADim) )
	    {
	      unsew(current, ADim);
	      if (!isFree(t2, ADim)) unsew(t2, ADim);
	      if (current!=t2) sew(current, t2, ADim);
	    }
	}
    }

  if (ADeleteDarts)
    {
      for (it->reinit(); it->cont(); )
	delMapDart((*it)++);
    }
  else
    {
      unmarkOrbit(ADart, ORBIT_CELL[ADim], mark);
    }

  //  assert( isWholeMapUnmarked(mark) );
  
  freeMark(mark);
    
  delete it;
}
//******************************************************************************
int CGMapGeneric::removeMarkedCells( int AMarkNumber, int ADim,
				     bool ADeleteDarts )
{
  assert(ADim>=0 && ADim<=2);

  int nbRemove = markIncidentCells(ORBIT_CELL[ADim], AMarkNumber);

  CDynamicCoverageAll cov(this);
  for ( ; cov.cont(); ++cov )
    {
      if ( isMarked(*cov, AMarkNumber) )
	{
	  if ( !canRemove(*cov, ADim) )
	    {
	      unmarkOrbit( *cov, ORBIT_CELL[ADim], AMarkNumber );
	      --nbRemove;
	    }
	}
    }

  CDart* current = NULL;
  CDart* t2 = NULL;

  for ( cov.reinit(); cov.cont(); ++cov )
    {
      if (  !isMarked( *cov, AMarkNumber) &&
	    isMarked( alpha(*cov, ADim), AMarkNumber) )
	{
	  current = *cov;
	  t2 = alpha(current, ADim);
	   
	  while (isMarked(t2, AMarkNumber))
	    {
	      t2 = alpha(alpha(t2, ADim+1), ADim);
	    }

	  if ( t2 != alpha(current, ADim) )
	    {
	      unsew(current, ADim);
	      if ( !isFree(t2, ADim) ) unsew(t2, ADim);
	      if ( t2!=current ) sew(current, t2, ADim);
	    }
	}
    }
  
  if (ADeleteDarts)
    {
      for (cov.reinit(); cov.cont(); )
	{
	  if ( isMarked(*cov, AMarkNumber) )
	    delMapDart(cov++);
	  else
	    ++cov;
	}
    }
  
  return nbRemove;
}
//******************************************************************************
int CGMapGeneric::removeMarkedVerticesWithFictiveEdgeShifting(int AMarkNumber)
{
  int  nbRemove	   = 0;
  int  toDelete	   = getNewMark();
  int  fictiveEdge = getNewMark();
  int  treated     = getNewMark();
  CDart* aDart     = NULL;
  CDart* current   = NULL;
  
  // On propage les marques pour ne pas avoir de problèmes.
  markIncidentCells(ORBIT_VERTEX, AMarkNumber);

  // On commence par marques les arêtes fictives
  CDynamicCoverageAll cov(this);
  while ( cov.cont() )
    {
      current = cov++;

      if ( !isMarked(current, treated) )
	{
	  markOrbit( current, ORBIT_FACE, treated);
	  if ( !isFree2(current) &&
	       alpha1(current)!=alpha2(current) &&
	       alpha01(current)!=alpha02(current) &&
	       isSameOrbit(current, alpha2(current), ORBIT_FACE) )
	    {
	      assert( isFree3(current) );
	      markOrbit( current, ORBIT_EDGE, fictiveEdge);
	    }
	}
    }
  
  // On va supprimer les sommets en décallant les arêtes fictives.
  cov.reinit();
  while ( cov.cont() )
    {
      current = cov++;

      if ( isMarked(current, AMarkNumber) &&  !isMarked(current, toDelete) )
	{
	  if ( findVertexType(current, &aDart, fictiveEdge)==2 )
	    {
	      shiftAllFictiveEdgesAroundEdge
		/*shiftAllFictiveEdges*/( aDart, fictiveEdge );
	      assert ( canRemove(aDart, 0) );
	      {
		markOrbit( aDart, ORBIT_VERTEX, toDelete);
		remove( aDart, 0, false );
		++nbRemove;
	      }
	    }
	}
    }
  
  // On détruit les brins et enlève les marques.
  for ( cov.reinit(); cov.cont(); )
    {
      unsetMark(*cov, fictiveEdge);
      unsetMark(*cov, treated);
      
      if ( isMarked(*cov, toDelete) )
	delMapDart(cov++);
      else
	++cov;
    }

  freeMark(toDelete);
  freeMark(treated);
  freeMark(fictiveEdge);

  return nbRemove;
}
//******************************************************************************
int CGMapGeneric::
removeMarkedEdgesWithoutDisconnectionForSurface(int AMarkNumber)
{
  bool disconnect = false;
  int  toDelete	  = getNewMark();
  int  nbRemove	  = 0;
  CDart* current  = NULL;
  
  // On propage les marques pour ne pas avoir de problèmes.
  markIncidentCells(ORBIT_EDGE, AMarkNumber);

  std::stack<CDart*> FToTreat;
  
  CDynamicCoverageAll cov(this);
  while ( cov.cont() )
    {
      while ( ! FToTreat.empty() )
	{
	  current = FToTreat.top();
	  FToTreat.pop();
	  
	  if ( isMarked(current, AMarkNumber) && !isMarked(current, toDelete) )
	    {
	      if ( (alpha1(current) !=alpha2(current) ||   // Si c'est pas 
		    alpha01(current)!=alpha02(current)) && // une sphère.
		   alpha23(current)==alpha32(current) )
		{
		  if ( alpha12(current)==alpha21(current) )
		    FToTreat.push(alpha1(current));
		  
		  if (alpha012(current)==alpha021(current) )
		    FToTreat.push(alpha01(current));
		  
		  remove(current, 1, false);
		  markOrbit(current, ORBIT_EDGE, toDelete);
		  ++nbRemove;
		}
	    }
	}

      current = cov++;
      if ( isMarked(current, AMarkNumber) && !isMarked(current, toDelete) )
	{
	  if ( alpha23(current)==alpha32(current) )
	    {
	      // Test de deconnexion
	      disconnect = false;
	      // Le cas de la sphère
	      if ( alpha1(current)==alpha2(current) &&
		   alpha01(current)==alpha02(current) )
		{
		  disconnect = true;
		}
	      // Le cas d'une arête pendante
	      else if ( alpha1(current) ==alpha2(current) ||
			alpha01(current)==alpha02(current) )
		{
		  disconnect = false;
		}
	      // Le cas normal ou il faut tourner autour de la face
	      else
		{
		  for(CDynamicCoverage01 it(this,current);
		      it.cont() && !disconnect; ++it)
		    if (*it==alpha2(current)) disconnect = true;
		}
	      
	      if ( !disconnect )
		{
		  if ( alpha12(current)==alpha21(current) )
		    FToTreat.push(alpha1(current));
		  
		  if (alpha012(current)==alpha021(current) )
		    FToTreat.push(alpha01(current));
		  
		  remove(current, 1, false);
		  markOrbit(current, ORBIT_EDGE, toDelete);
		  ++nbRemove;
		}
	    }
	}
    }
  
  for ( cov.reinit(); cov.cont(); )
    {
      if ( isMarked(*cov, toDelete) )
	delMapDart(cov++);
      else
	++cov;
    }

  freeMark(toDelete);

  return nbRemove;
}
//******************************************************************************
int CGMapGeneric::removeMarkedEdgesWithoutDisconnection( int AMarkNumber )
{
  int  toDelete	   = getNewMark();
  int  treated	   = getNewMark();
  int  nbRemove	   = 0;
  CDart* current   = NULL;
  CDart* aDart     = NULL;
  
  // On propage les marques pour ne pas avoir de problèmes.
  markIncidentCells(ORBIT_EDGE, AMarkNumber);

  // We initialise one uf-tree for each face to detect efficiently if the degree of
  // an edge is 1 or 2.
  int index  = getNewDirectInfo();
  if ( index!=-1 ) initUnionFindTrees(index, ORBIT_FACE);
  else std::cout<<"Not enough directInfo to use union-find trees."<<std::endl;
	 
  CDynamicCoverageAll cov(this);

  // On commence par marquer les faces fictives et on en profite pour en
  // même temps supprimer les arêtes de degré deux.
  while ( cov.cont() )
    {
      current = cov++;

      // Si c'est une arête de degré deux et pas une sphère, on la supprime
      if ( isMarked(current, AMarkNumber) &&
	   !isMarked(current, toDelete) &&
	   ( (alpha1(current) !=alpha2(current) ||
	      alpha01(current)!=alpha02(current)) &&
	     alpha23(current)==alpha32(current) ) &&
	   (index!=-1?(findUnionFindTrees(current, index)!=
		       findUnionFindTrees(alpha2(current),index)):
	    (!isSameOrbit(current, alpha2(current), ORBIT_FACE))) )
	{
	  markOrbit(current, ORBIT_EDGE, toDelete);
	  remove(current, 1, false);
	  ++nbRemove;

	  if ( index!=-1 )
	    mergeUnionFindTrees(current, alpha2(current), index);
	}
      else
	if ( !isMarked(current, toDelete) && !isMarked(current, treated) )
	  // Ici on utilise la marque treated pour marquer les
	  // brins déjà traités.
	  {
	    markOrbit( current, ORBIT_FACE, treated);
	  }
    }  
  
  // On détruit les brins et enlève les marques.
  for ( cov.reinit(); cov.cont(); )
    {
      unsetMark(*cov, treated);
      
      if ( isMarked(*cov, toDelete) ) delMapDart(cov++);
      else ++cov;
    }

  freeMark(toDelete);
  freeMark(treated);

  if ( index!=-1 ) freeDirectInfo(index);
  
  return nbRemove;
}
//******************************************************************************
int CGMapGeneric::
removeMarkedEdgesWithoutDisconnectionWithFaceShifting( int AMarkNumber )
{
  int  toDelete	   = getNewMark();
  int  treated	   = getNewMark();
  int  nbRemove	   = 0;
  CDart* current   = NULL;
  CDart* aDart     = NULL;
  int fictiveFaces = getNewMark();
  int markFace     = getNewMark();
  int res;
  int nbDarts;
  bool existFictiveDart;
  bool generator;
  
  // On propage les marques pour ne pas avoir de problèmes.
  markIncidentCells(ORBIT_EDGE, AMarkNumber);

  CDynamicCoverageAll cov(this);

  // On commence par marquer les faces fictives et on en profite pour en
  // même temps supprimer les arêtes de degré deux.
  while ( cov.cont() )
    {
      current = cov++;

      // Si c'est une arête de degré deux et pas une sphère, on la supprime
      if ( isMarked(current, AMarkNumber) &&
	   !isMarked(current, toDelete) &&
	   ( (alpha1(current) !=alpha2(current) ||
	      alpha01(current)!=alpha02(current)) &&
	     alpha23(current)==alpha32(current) ) &&
	   !isSameOrbit(current, alpha2(current), ORBIT_FACE) )
	{
	  markOrbit(current, ORBIT_EDGE, toDelete);
	  remove(current, 1, false);
	  ++nbRemove;
	}
      else
	if ( !isMarked(current, toDelete) && !isMarked(current, treated) )
	  // Ici on utilise la marque toDelete pour marquer les
	  // brins déjà traités.
	  {
	    markOrbit( current, ORBIT_FACE, treated);
 	    if ( !isFree3(current) &&
 		 isSameOrbit(current, alpha3(current), ORBIT_VOLUME) )
 	      markOrbit( current, ORBIT_FACE, fictiveFaces);
	  }
    }
  
  // Maintenant on va traiter les arêtes
  cov.reinit();
  while ( cov.cont() )
    {
      current = cov++;
      
      if ( isMarked(current, AMarkNumber) && !isMarked(current, toDelete) )
	{
	  if ( (res=findEdgeType(current, &aDart, fictiveFaces))==2 &&
	       canShiftAllFictiveFaces(aDart, fictiveFaces) )
	    {
	      shiftAllFictiveFaces(aDart, fictiveFaces, toDelete);
	      markOrbit(aDart, ORBIT_EDGE, toDelete);
	      remove(aDart, 1, false);
	      ++nbRemove;
	      // break;
	    }
	  else if ( res==1 )
	    {
	      if ( isMarked(alpha2(aDart), fictiveFaces) )
		shiftOneFictiveFaceAlongDanglingEdge(aDart,
						     fictiveFaces,
						     toDelete);
	      markOrbit(aDart, ORBIT_EDGE, toDelete);
	      remove(aDart, 1, false);
	      ++nbRemove;
	    }
	}
    }
  
  // On va marquer les arêtes ayant un nombre impair de brins.
  negateMaskMark(treated);
  
  cov.reinit();
  while ( cov.cont() )
    {
      current = cov++;

      if ( !isMarked(current, toDelete) && !isMarked(current, treated) )
	{
	  existFictiveDart = false;
	  generator	   = true;
	  for (CDynamicCoverageEdge it(this,current); it.cont(); ++it)
	    {
	      if ( !isMarked(*it, treated) )
		{
		  setMark(*it, treated);
		  if ( isMarked(*it, fictiveFaces ) )
		    {
		      existFictiveDart = true;
		      nbDarts = 0;
		      
		      markOrbit(*it, ORBIT_FACE, markFace);	  
		      
		      for (CDynamicCoverageEdge it2(this,*it); it2.cont(); ++it2)
			{
			  if ( isMarked(*it2, markFace) )
			    {
			      setMark(*it2, treated);
			      ++nbDarts;
			    }
			}
		      
		      unmarkOrbit(*it, ORBIT_FACE, markFace);
		      
		      if ( (nbDarts/4)%2==1 ) // Si le nombre d'arête est pair
			// Alors l'arête est un générateur H1
			generator = false;
		    }
		}
	    }

	  if ( generator || !existFictiveDart )	  	      
	    markOrbit( current, ORBIT_EDGE, AMarkNumber);
	  else // sinon c'est le bord d'une face fictive
	    unmarkOrbit( current, ORBIT_EDGE, AMarkNumber);
	}
    }
  
  // On détruit les brins et enlève les marques.
  for ( cov.reinit(); cov.cont(); )
    {
      unsetMark(*cov, fictiveFaces);
      unsetMark(*cov, treated);
      unsetMark(*cov, markFace);
      
      if ( isMarked(*cov, toDelete) )
	delMapDart(cov++);
      else
	++cov;
    }

  freeMark(toDelete);
  freeMark(treated);
  freeMark(fictiveFaces);
  freeMark(markFace);
  
  {
    // temporaire pour tester la 0-suppression : TODO ajouter une
    // entrée dans le menu
    if ( nbRemove==0 )
      {
	treated=getNewMark();
	negateMaskMark(treated);
	nbRemove=removeMarkedVerticesWithFictiveEdgeShifting(treated);
	negateMaskMark(treated);
	freeMark(treated);	
      }
  }
  
  return nbRemove;
}
//******************************************************************************
int CGMapGeneric::removeMarkedFacesButKeepBalls(int AMarkNumber)
{
  int  toDelete	  = getNewMark();
  int  treated	  = getNewMark();
  int  toTreat2	  = getNewMark();
  int  nbRemove	  = 0;
  CDart* current  = NULL;
  std::stack<CDart*> FToTreat;
  bool dangling = false;

  // 1) On propage les marques pour ne pas avoir de problèmes.
  markIncidentCells(ORBIT_FACE, AMarkNumber);

  // 2) On fait la simplification de toute les faces en conservant des sphères
  //    mais on autorise les déconnections.
  CDynamicCoverageAll cov(this);
  while ( cov.cont() )
    {
      if ( ! FToTreat.empty() )
	{
	  current = FToTreat.top();
	  FToTreat.pop();
	}
      else
	{
	  current = cov++;
	}

      // On sauve la marque AMarkNumber dans toTreat2 pour la deuxième passe
      //      if ( isMarked(current, AMarkNumber) ) setMark( current, toTreat2 );

      // Est-ce que la face doit être supprimée ?
      if ( isMarked(current, AMarkNumber) && !isFree3(current) &&
	   !isMarked(current, toDelete) && !isMarked(current, treated) )
	{
	  // Ici on voudrait supprimer la face incidente à current.
	  // On doit vérifier si le volume reste une boule ou pas.
	  
	  // Pour ça on supprime les faces entre deux volumes distincts	  
	  // ou les faces pendantes (ATTENTION : def des faces pendantes ???)
	  
	  // Test sur la face pendante
	  dangling = false;
	  CDynamicCoverage01 itFace(this, current);
	  for ( ; itFace.cont(); ++itFace )
	    {
	      setMark( *itFace, treated );
	      setMark( alpha3(*itFace), treated );
	      
	      if ( alpha23(*itFace)==*itFace ) dangling = true;
	    }
	  
	  // Test si la face est entre deux volumes distincts
	  if ( dangling ||
	       !isSameOrbit(current, alpha3(current), ORBIT_VOLUME) )
	    {
	      // Il faut reconsidérer les faces adjacentes car elles sont
	      // susceptibles de pouvoir être supprimées.
	      for ( itFace.reinit(); itFace.cont(); ++itFace )
		{
		  if ( alpha23(*itFace)!=*itFace )
		    {
		      if ( isMarked(alpha2(*itFace), treated) )
			{
			  FToTreat.push(alpha2(*itFace));
			  unmarkOrbit(alpha2(*itFace), ORBIT_FACE, treated);
			}
		      if ( isMarked(alpha32(*itFace), treated) )
			{
			  FToTreat.push(alpha32(*itFace));
			  unmarkOrbit(alpha32(*itFace), ORBIT_FACE, treated);
			}
		    }

		  setMark( *itFace, toDelete );
		  setMark( alpha3(*itFace), toDelete );		  
		}

	      // La suppression proprement dite
	      remove(current, 2, false);
	      ++nbRemove;
	    }
	}
    }

  // 3) On démarque toutes les faces sauf les fictives
  for ( cov.reinit(); cov.cont(); )
    {
      current = cov++;

      unsetMark( current, treated );
      
      if ( isMarked(current, AMarkNumber) && !isMarked(current, toDelete) &&
	   !isFree3(current) )
	unmarkOrbit(current, ORBIT_FACE, AMarkNumber);
    }

  // 4) On supprime les faces qui ont été conservées pour garder les sphères
  //    (elles ont servit uniquement pour marquer les arêtes de degré > 2)
  /*
    for ( cov.reinit(); cov.cont(); )
    {
    if ( ! FToTreat.empty() )
    {
    current = FToTreat.top();
    FToTreat.pop();
    }
    else
    {
    current = cov++;
    }

    if ( isMarked(current, toTreat2) && !isFree3(current) &&
    !isMarked(current, toDelete) && !isMarked(current, treated) )
    {
    // Il faut reconsidérer les faces adjacentes car elles sont
    // susceptibles de pouvoir être supprimées.
    CDynamicCoverage01 itFace(this, current);
    for ( itFace.reinit(); itFace.cont(); ++itFace )
    {
    if ( alpha23(*itFace)!=*itFace )
    {
    if ( isMarked(alpha2(*itFace), treated) )
    {
    FToTreat.push(alpha2(*itFace));
    unmarkOrbit(alpha2(*itFace), ORBIT_FACE, treated);
    }
    if ( isMarked(alpha32(*itFace), treated) )
    {
    FToTreat.push(alpha32(*itFace));
    unmarkOrbit(alpha32(*itFace), ORBIT_FACE, treated);
    }
    }
    }
	  
    // La suppression proprement dite
    remove(current, 2, false);
    markOrbit(current,ORBIT_FACE,toDelete);
    ++nbRemove;
    }
    }
  */
  
  // 5) On supprime tout les brins
  for ( cov.reinit(); cov.cont(); )
    {
      current = cov++;

      unsetMark( current, treated );
      //      unsetMark( current, toTreat2 );
      
      if ( isMarked(current, toDelete) )
	delMapDart(current);
    }

  freeMark(toDelete);
  freeMark(treated);
  freeMark(toTreat2);

  return nbRemove;
}
//******************************************************************************
unsigned int CGMapGeneric::simplify2DObject()
{
  return 0;
}
//******************************************************************************
unsigned int CGMapGeneric::simplify3DObject(int AMark0, int AMark1, int AMark2)
{
  // Simplify a 3D map in its minimal form, without use shifting operations, and
  // by keeping each cell homeomorphic to a ball.
  // This method suppose that each cell is initially homeomorphic to a ball, and
  // that there is no dangling cell.
  // First we remove each degree two face, then each degree two edges, last each
  // degree two vertex.
  int  toDelete	  = getNewMark();
  int  treated	  = getNewMark();
  int  cell	  = getNewMark();
  CDart* current  = NULL;
  CDart* t1  = NULL;
  CDart* t2  = NULL;
  std::stack<CDart*> FToTreat;
  bool dangling = false;
  unsigned int nbRemove = 0;

  int toDelete0 = (AMark0==-1?toDelete:AMark0);
  int toDelete1 = (AMark1==-1?toDelete:AMark1);
  int toDelete2 = (AMark2==-1?toDelete:AMark2);
  
  int indexVol  = getNewDirectInfo();
  int indexFace = getNewDirectInfo();
  if ( indexVol!=-1 && indexFace!=-1 )
    initTwoUnionFindTrees(indexVol,ORBIT_VOLUME, indexFace,ORBIT_FACE);
  else
    {
      std::cout<<"Not enough directInfo to use union-find trees."<<std::endl;
      return 0;
    }

  // 1) We remove faces.
  CDynamicCoverageAll cov(this);
  while ( cov.cont() )
    {
      if ( ! FToTreat.empty() )
	{
	  current = FToTreat.top();
	  FToTreat.pop();
	  dangling = true;
	}
      else
	{
	  current = cov++;
	  dangling = false;
	}

      if ( !isMarked(current,toDelete) &&
	   (dangling || !isMarked(current, treated)) )
	{
	  if ( !isFree3(current) )
	    {
	      // We remove dangling faces and degree two faces.
	      if ( dangling ||
		   findUnionFindTrees(current, indexVol)!=
		   findUnionFindTrees(alpha3(current),indexVol) )
		{
		  // First we mark the current face.
		  CDynamicCoverage01 itFace(this, current);
		  for ( ; itFace.cont(); ++itFace )
		    {
		      setMark( *itFace, treated );
		      setMark( alpha3(*itFace), treated );
// 		      setMark( *itFace, cell );
// 		      setMark( alpha3(*itFace), cell );
		      setMark( *itFace, toDelete2 );
		      setMark(  alpha3(*itFace), toDelete2 );
		    }
		  
		  // Second, we push in the stack all the neighboors of the current
		  // face that become dangling after the removal.
		  // Moreover, we make the removal manually instead of calling
		  // remove(current, 2, false) for optimisation reasons.
		  for ( itFace.reinit(); itFace.cont(); ++itFace )
		    {
		      if ( alpha23(*itFace)==alpha32(*itFace) &&
			   !isMarked(alpha2(*itFace), toDelete2 /*cell*/) &&
			   !isFree3(alpha2(*itFace)) )
			   // && !isMarked(alpha2(*itFace),toDelete) )
			{
			  FToTreat.push(alpha2(*itFace));
			}
		  
		      // Now we update alpha2
		      t1 = alpha(*itFace, 2);
		      if ( !isMarked(t1, toDelete2) )
			{
			  t2 = *itFace;
			  while ( isMarked(t2, toDelete2) )
			    {
			      t2 = alpha32(t2);
			    }
			  
			  if ( t2 != alpha(t1, 2) )
			    {
			      unsew(t1, 2);
			      if (!isFree(t2, 2)) unsew(t2, 2);
			      if (t1!=t2) sew(t1, t2, 2);
			    }
			}
		    }
		  if ( !dangling )
		    mergeUnionFindTrees(current, alpha3(current), indexVol);
		}
	      else
		{
		  CDynamicCoverage01 itFace(this, current);
		  for ( ; itFace.cont(); ++itFace )
		    {
		      setMark( *itFace, treated );
		      setMark( alpha3(*itFace), treated );
		    }
		}
	    }
	  else
	    {
	      CDynamicCoverage01 itFace(this, current);
	      for ( ; itFace.cont(); ++itFace )
		{
		  setMark( *itFace, treated );
		}
	    }
	}
    }
  negateMaskMark(treated);
  
  // 2) We remove edges.
  cov.reinit();
  while ( cov.cont() )
    {
      if ( ! FToTreat.empty() )
	{
	  current = FToTreat.top();
	  FToTreat.pop();
	  dangling = true;
	}
      else
	{
	  current = cov++;
	  dangling = false;
	}

      if ( !isMarked(current, toDelete2) && !isMarked(current, toDelete1) &&
	   (dangling || !isMarked(current, treated)) )
	{
	  if ( !isFree2(current) )
	    {
	      // We remove dangling edges and degree two edges.
	      if ( (alpha1(current) !=alpha2(current) ||
		    alpha01(current)!=alpha02(current)) &&
		   alpha23(current)==alpha32(current) &&
		   ( dangling ||
		     findUnionFindTrees(current, indexFace)!=
		     findUnionFindTrees(alpha2(current),indexFace)) )
		{
		  // First we mark the current edge.
		  CDynamicCoverage02 itEdge(this, current);
		  for ( ; itEdge.cont(); ++itEdge )
		    {
		      setMark( *itEdge, treated );
		      setMark( alpha3(*itEdge), treated );
// 		      setMark( *itEdge, cell );
// 		      setMark( alpha3(*itEdge), cell );
		      setMark( *itEdge, toDelete1 );
		      setMark(  alpha3(*itEdge), toDelete1 );
		    }
	      
		  // Second, we push in the stack all the neighboors of the current
		  // edge that become dangling after the removal.
		  // Moreover, we make the removal manually instead of calling
		  // remove(current, 1, false) for optimisation reasons.
		  for ( itEdge.reinit(); itEdge.cont(); ++itEdge )
		    {
		      if ( alpha12(*itEdge)==alpha21(*itEdge) &&
			   !isMarked(alpha1(*itEdge), toDelete1) &&
			   !isFree2(alpha1(*itEdge)) )
			//&& !isMarked(alpha1(*itEdge),toDelete) )
			{
			  FToTreat.push(alpha1(*itEdge));
			}
		  
		      // Now we update alpha2
		      t1 = alpha(*itEdge, 1);
		      if ( !isMarked(t1, toDelete1) )
			{
			  t2 = *itEdge;
			  while ( isMarked(t2, toDelete1) )
			    {
			      t2 = alpha21(t2);
			    }
			  
			  if ( t2 != alpha(t1, 1) )
			    {
			      unsew(t1, 1);
			      if (!isFree(t2, 1)) unsew(t2, 1);
			      if (t1!=t2) sew(t1, t2, 1);
			    }
			}
		    }
		  
		  if ( !dangling )
		    mergeUnionFindTrees(current, alpha2(current), indexFace);
		}
	      else
		{
		  CDynamicCoverage02 itEdge(this, current);
		  for ( ; itEdge.cont(); ++itEdge )
		    {
		      setMark( *itEdge, treated );
		      setMark( alpha3(*itEdge), treated );
		    }
		}
	    }
	  else
	    {
	      CDynamicCoverage0 itEdge(this, current);
	      for ( ; itEdge.cont(); ++itEdge )
		{
		  setMark( *itEdge, treated );
		  setMark( alpha3(*itEdge), treated );
		}
	    }
	}
    }
  negateMaskMark(treated);

  // 3) We remove vertices. This is simpler since a vertex can not be dangling.
  cov.reinit();
  while ( cov.cont() )
    {
      current = cov++;

      if ( !isMarked(current,treated) && !isMarked(current, toDelete2)
	   && !isMarked(current, toDelete1) && !isMarked(current, toDelete0) )
      {
	bool deleteVertex = true;
	CStaticCoverage23 itVertex(this, current);
	for ( ; itVertex.cont(); ++itVertex )
	  {
	    setMark( *itVertex, treated );
	    setMark( alpha1(*itVertex), treated );

	    if ( isFree1(*itVertex)                     ||
		 alpha1 (*itVertex)==alpha2 (*itVertex) ||
		 alpha01(*itVertex)==alpha02(*itVertex) ||
		 alpha12(*itVertex)!=alpha21(*itVertex) )
	      deleteVertex = false;
	  }

	if ( deleteVertex )
	  {
	    // First we mark the current vertex.
	    for ( itVertex.reinit(); itVertex.cont(); ++itVertex )
	      {
		setMark( *itVertex, toDelete0 );
		setMark(  alpha1(*itVertex), toDelete0 );
	      }
	      
	    // Second, we make the removal manually instead of calling
	    // remove(current, 0, false) for optimisation reasons.
	    for ( itVertex.reinit(); itVertex.cont(); ++itVertex )
	      {
		t1 = alpha(*itVertex, 0);
		if ( !isMarked(t1, toDelete0) )
		  {
		    t2 = *itVertex;
		    while ( isMarked(t2, toDelete0) )
		      {
			t2 = alpha10(t2);
		      }
		    
		    if ( t2 != alpha(t1, 0) )
		      {
			unsew(t1, 0);
			if (!isFree(t2, 0)) unsew(t2, 0);
			if (t1!=t2) sew(t1, t2, 0);
		      }
		  }
	      }
	  }
      }
    }
  
  // 4) We remove all the darts marked toDelete
  for ( cov.reinit(); cov.cont(); )
    {
      current = cov++;

      //  assert(!isMarked(current,cell));

      unsetMark(current,treated);      
      if ( isMarked(current, toDelete) )
	{
	  delMapDart(current);
	}

      if ( isMarked(current, toDelete0) ||
	   isMarked(current, toDelete1) ||
	   isMarked(current, toDelete2) )
	++nbRemove;
    }
  
  freeMark(toDelete);
  freeMark(treated);
  freeMark(cell);

  freeDirectInfo(indexVol);
  freeDirectInfo(indexFace);

  return nbRemove;
}
//******************************************************************************
