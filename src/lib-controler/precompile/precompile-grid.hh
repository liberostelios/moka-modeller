/*
 * lib-controler : Un contrôleur générique de scène 3D.
 * Copyright (C) 2004, Moka Team, Université de Poitiers, Laboratoire SIC
 *               http://www.sic.sp2mi.univ-poitiers.fr/
 * Copyright (C) 2009, Guillaume Damiand, CNRS, LIRIS,
 *               guillaume.damiand@liris.cnrs.fr, http://liris.cnrs.fr/
 *
 * This file is part of lib-controler
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
#ifndef PRECOMPILE_GRID_HH
#define PRECOMPILE_GRID_HH
//******************************************************************************
/** @author Guillaume Damiand, Frédéric Vidil
 */
//******************************************************************************
#include "precompile.hh"
#include "parameter-grid.hh"
//******************************************************************************

  /** La classe CPrecompileGrid permet l'affichage de la grille.
   */
  class CPrecompileGrid : public CPrecompile
  {
  public:
    //@name Constructeurs et destructeur.
    //@{
    /** Constructeur
     *
     * @param AParameterGrid les paramètres de dessin de la grille
     *
     */
    CPrecompileGrid(CParameterGrid*);
    CPrecompileGrid(const CPrecompileGrid &);
    CPrecompile* copy() const;

    /** Destructeur
     */
    virtual ~CPrecompileGrid();
    //@}

    void        setParameter(CParameter* AParameter);
    CParameter* getParameter() const;
  
    /** getType
     *
     *  Cette méthode retourne le type du precompile.
     */
    virtual TPrecompile getType() const;

    /** setGrid
     *
     *  Modifie le paramètre PARAMETER_GRID associé au précompile.
     */
    void setGrid(CParameterGrid* AGrid);

  protected:

    /** drawModel
     *
     *  Cette méthode affiche la / les grille(s).
     */
    virtual void drawModel();


  private:
    /// Les différents paramètres
    CParameterGrid* FParameterGrid;
  };

//******************************************************************************
#endif // PRECOMPILE_GRID_HH
//******************************************************************************
