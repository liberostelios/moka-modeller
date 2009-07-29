/*
 * lib-controler-gmap : Le contrôleur de 3-G-cartes, surcouche de lib-controler.
 * Copyright (C) 2004, Moka Team, Université de Poitiers, Laboratoire SIC
 *               http://www.sic.sp2mi.univ-poitiers.fr/
 * Copyright (C) 2009, Guillaume Damiand, CNRS, LIRIS,
 *               guillaume.damiand@liris.cnrs.fr, http://liris.cnrs.fr/
 *
 * This file is part of lib-controler-gmap
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
#ifndef PARAMETER_GMAP_VERTEX_HH
#define PARAMETER_GMAP_VERTEX_HH
//******************************************************************************
#include "parameter.hh"
#include "g-map-vertex.hh"
//******************************************************************************
/** @author Guillaume Damiand, Frédéric Vidil
 */

/** La classe CParameterGMapVertex permet de savoir si le modèle à changé
 *  depuis la dernière mise à jour.
 *
 *  Cette classe contient simplement les accesseurs et modificateurs
 *  des différentes variables membres.
 */
//******************************************************************************
namespace GMap3d
{
  class CParameterGMapVertex : public CParameter
  {
  public:
    /// @name Constructeur et destructeur
    //@{

    /// Constructeur
    CParameterGMapVertex(CGMapVertex* AGMap, int ANbRef = 0);
    CParameterGMapVertex(const CParameterGMapVertex &);
    CParameter* copy() const;

    /// Destructeur
    virtual ~CParameterGMapVertex();

    //@}

    /// @name Sauvegarde et chargement des paramètres
    //@{

    /// Méthode permettant de sauver les valeurs des variables membres.
    virtual void save(std::ostream &);

    /// Méthode permettant de récupérer les valeurs des variables membres.
    virtual void load(std::istream &);

    /// Méthode pour réinitialiser avec nos valeurs par defaut.
    virtual void reinit();

    //@}

    /// @name Accesseurs et modificateurs des paramètres
    //@{

    ///@return la valeur de FMap.
    CGMapVertex* getMap() const;

    /// Pour changer la valeur de FMap.
    /// @param  AMap la nouvelle carte.
    void         setMap(CGMapVertex* AMap);
  
    ///@return la valeur de FChanged.
    bool getChanged() const;

    /// Met à vrai la variable FChanged et répercute aux précompiles concernés.
    void setChanged();

    /// Met à faux la variable FChanged sans repercution sur les précompiles.
    void unsetChanged();

    ///@return la valeur de FPartialChanged.
    bool getPartialChanged() const;

    /// Met à vrai la variable FPartialChanged.
    void setPartialChanged();

    /// Met à faux la variable FPartialChanged sans repercution sur les précompiles.
    void unsetPartialChanged();

    ///@return la valeur de FBlocked.
    bool getBlocked() const;

    /// Met à vrai la variable FBlocked sans répercution aux précompiles.
    void setBlocked();

    /// Met à faux la variable FBlocked et répercute aux précompiles concernés.
    void unsetBlocked();

    /// Accesseurs pour FMarkPartialChanged. Ce numéro contient la marque
    /// utilisée pour mettre à jour partiellement l'objet.
    /// Si FMarkPartialChanged=-1 => on met à jour toute la carte.
    int  getMarkPartialChanged() const;
    void setMarkPartialChanged(int AValue);
    
    /// Accesseurs à la méthode de calcul des sommets éclatés :
    void         setBurstMethod(TBurstMethod AMethod);
    TBurstMethod getBurstMethod() const;

    //@}

    /// Identificateur du type de paramètre.
    virtual int getType() const;

  private:
    /// La carte.
    CGMapVertex* FMap;

    /// Booléen pour indiquer si le modèle à changé depuis la dernière mise à jour.
    bool FChanged;

    /// Booléen pour indiquer si le modèle à partiellement changé depuis
    /// la dernière mise à jour. Dans ce cas on utilise le numéro de marque
    /// qui contient la marque utilisée pour savoir quoi mettre à jour.
    bool FPartialChanged;
    int  FMarkPartialChanged;

    /// Booléen permettant de bloquer le recalcul de l'affichage éclatée.
    int  FBlocked;
  };
  
} // namespace GMap3d
//******************************************************************************
#endif // PARAMETER_GMAP_VERTEX_HH
//******************************************************************************
