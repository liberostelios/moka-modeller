/*
 * Moka : Un modeleur de 3-G-cartes.
 * Copyright (C) 2004, Moka Team, Université de Poitiers, Laboratoire SIC
 *               http://www.sic.sp2mi.univ-poitiers.fr/
 * Copyright (C) 2009, Guillaume Damiand, CNRS, LIRIS,
 *               guillaume.damiand@liris.cnrs.fr, http://liris.cnrs.fr/
 *
 * This file is part of Moka
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DIALOG_TYPES_HH
#define DIALOG_TYPES_HH

// DialogWindow ---------------------
static const int NB_DIALOG_MODES = 19
#ifdef MODULE_EXTRACTION_IMAGE
+ 1
#endif // MODULE_EXTRACTION_IMAGE
;

//typedef enum
//{
//  None=-1,
//  Polyline, Polygon, MeshCreation, Cylinder, Pyramid, Sphere, Torus,
//  Help, Grid, Visu, Topo /* informations topologiques */,
//  Translate, Rotate, Scale,
//  Geo, Ponderation, Extrusion, Mesh, Rounding
//#ifdef MODULE_EXTRACTION_IMAGE
//  , Extract3d
//#endif // MODULE_EXTRACTION_IMAGE
//} DialogMode;

// DialogPonderation -----------------------------------------------------------
static const int NB_DISTANCE_TYPES = 3;

typedef enum { DistanceToVertex, DistanceToLine, DistanceToPlane } TDistanceType;

#endif
