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
#ifndef PARAMETER_GRID_HH
#define PARAMETER_GRID_HH
//******************************************************************************
#include "parameter.hh"
//******************************************************************************
/** @author Guillaume Damiand, Frédéric Vidil
 */

/** La classe CParameterGrid regroupe les paramètres nécessaires au dessin de la grille
 *
 *  Cette classe contient simplement les accesseurs et modificateurs
 *  des différentes variables membres.
 */

  class CParameterGrid : public CParameter
  {
  public:
    /** @name Constructeur et destructeur
     */

    //@{

    /** Constructeur
     */
    CParameterGrid(int ANbRef = 0);
    CParameterGrid(const CParameterGrid &);
    CParameter * copy() const;

    /** Destructeur
     */
    virtual ~CParameterGrid();

    //@}

    /** @name Sauvegarde et chargement des paramètres
     */

    //@{

    /** save
     *
     *  Méthode permettant de sauver les valeurs des variables membres.
     */
    virtual void save(std::ostream&);

    /** load
     *
     *  Méthode permettant de récupérer les valeurs des variables membres.
     */
    virtual void load(std::istream&);

    /** reinit
     *
     *    Reinitialise le paramètre.
     */
    virtual void reinit();

    //@}

    /** @name Accesseurs pour la taille des lignes
     */

    //@{
    int  getLWGrid() const;
    void setLWGrid(int);
    //@}

    /** @name Accesseurs pour différentes mesures
     */

    //@{
    int   getLGGrid() const; // nombre de subdivision de la grille
    void  setLGGrid(int);
    //@}

    /** @name Accesseurs pour les couleurs
     */

    //@{
    float         getCLGrid(int AIndice) const;
    const float * getCLGrid() const;
    void          setCLGrid(int AIndice, float AValue);
    void          setCLGrid(float AValue0, float AValue1, float AValue2);
    void          setCLGrid(float const ATab[3]);
    //@}

    /** @name Accesseurs pour des flags
     *   Chaque variable à trois méthodes :
     *       bool getXXX() const; pour récupérer la valeur du flag
     *       void setXXX(bool);   pour fixer la valeur
     *       void invXXX();       pour inverser sa valeur
     */

    //@{
    bool getDisplayGridXY() const; /// affichage de la grille XY
    void setDisplayGridXY(bool);
    void invDisplayGridXY();

    bool getDisplayGridYZ() const; /// affichage de la grille YZ
    void setDisplayGridYZ(bool);
    void invDisplayGridYZ();

    bool getDisplayGridXZ() const; /// affichage de la grille XZ
    void setDisplayGridXZ(bool);
    void invDisplayGridXZ();

    bool getDisplayPositiveGridX() const; /// grille seulement pour X > 0
    void setDisplayPositiveGridX(bool);
    void invDisplayPositiveGridX();

    bool getDisplayPositiveGridY() const; /// grille seulement pour Y > 0
    void setDisplayPositiveGridY(bool);
    void invDisplayPositiveGridY();

    bool getDisplayPositiveGridZ() const; /// grille seulement pour Z > 0
    void setDisplayPositiveGridZ(bool);
    void invDisplayPositiveGridZ();
    //@}

    /// Identificateur du type de paramètre.
    virtual int getType() const;

    /// Fonctions amies pour lire et écrire dans un flux.
    friend std::ostream& operator << (std::ostream&, const CParameterGrid &);
    friend std::istream& operator >> (std::istream&, CParameterGrid &);

  private:
    /// Largeur des lignes pour la grille
    int FLWGrid;

    /// Nombre de subdivision de la grille
    int   FLGGrid;

    /// Couleur de la grille
    float FCLGrid[3];

    /// Les flags pour afficher seulement la grille
    bool FDisplayGridXY;        ///             en XY
    bool FDisplayGridYZ;        ///             en YZ
    bool FDisplayGridXZ;        ///             en XZ
    bool FDisplayPositiveGridX; /// uniquement les valeurs positives en X
    bool FDisplayPositiveGridY; /// uniquement les valeurs positives en Y
    bool FDisplayPositiveGridZ; /// uniquement les valeurs positives en Z
  };

//******************************************************************************
#endif // PARAMETER_GRID_HH
//******************************************************************************
