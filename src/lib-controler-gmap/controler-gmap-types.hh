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
#ifndef CONTROLER_GMAP_TYPES_HH
#define CONTROLER_GMAP_TYPES_HH
//******************************************************************************
#include "controler-types.hh"
//******************************************************************************
namespace GMap3d
{
  //****************************************************************************
  //@name Objets prédéfinis, (sans la polyline)
  //@{
#define NB_PREDEFINED_OBJECTS (6)
  
  typedef int TObject;
  
  enum
  {
    FIRST_OBJECT_CONTROLER_GMAP = 0,
    
    OBJECT_POLYGON = FIRST_OBJECT_CONTROLER_GMAP,
    OBJECT_MESH,
    OBJECT_SPHERE,
    OBJECT_CYLINDER,
    OBJECT_PYRAMID,
    OBJECT_TORUS,

    LAST_OBJECT_CONTROLER_GMAP
  };
  //@}
  //****************************************************************************
  enum
  {
    FIRST_MODE_CONTROLER_GMAP = LAST_MODE_CONTROLER,
    
    MODE_CREATION_POLYLINE = FIRST_MODE_CONTROLER_GMAP,
    MODE_CREATION_POLYGON,
    MODE_CREATION_MESH,
    MODE_CREATION_SPHERE,
    MODE_CREATION_CYLINDER,
    MODE_CREATION_PYRAMID,
    MODE_CREATION_TORUS,

    MODE_TRANSLATION,
    MODE_ROTATION,
    MODE_SCALE,

    MODE_ROUNDING,
    
    LAST_MODE_CONTROLER_GMAP
  };
  //****************************************************************************
  enum
  {
    FIRST_MODE_OPERATION_CONTROLER_GMAP = LAST_MODE_OPERATION_CONTROLER,
   
    MODE_OPERATION_CREATION_POLYLINE = FIRST_MODE_OPERATION_CONTROLER_GMAP,
    MODE_OPERATION_CREATION_POLYGON,
    MODE_OPERATION_CREATION_MESH,
    MODE_OPERATION_CREATION_SPHERE,
    MODE_OPERATION_CREATION_CYLINDER,
    MODE_OPERATION_CREATION_PYRAMID,
    MODE_OPERATION_CREATION_TORUS,

    MODE_OPERATION_TRANSLATION,
    MODE_OPERATION_ROTATION,
    MODE_OPERATION_SCALE,

    MODE_OPERATION_ROUNDING,

    LAST_MODE_OPERATION_CONTROLER_GMAP
  };
  //****************************************************************************
  //@name Types de listes précompilées
  //@{
  enum
  {
    FIRST_PRECOMPILE_CONTROLER_GMAP = LAST_PRECOMPILE_CONTROLER,
    
    PRECOMPILE_DART = FIRST_PRECOMPILE_CONTROLER_GMAP,
    PRECOMPILE_FACE,
    PRECOMPILE_NORMAL_VECTOR,
    PRECOMPILE_OBJECT_TRANSFORMATION,
    PRECOMPILE_PREVIEW,
    PRECOMPILE_SEW,
#ifdef MODULE_SPAMOD
    PRECOMPILE_SPAMOD,
#endif // MODULE_SPAMOD
    PRECOMPILE_VERTEX,

    LAST_PRECOMPILE_CONTROLER_GMAP
  };
  //@}
  //****************************************************************************
  //@name Types de paramètres
  typedef int TParameter;

  enum
  {
    FIRST_PARAMETER_CONTROLER_GMAP = LAST_PARAMETER_CONTROLER,
    
    // Paramètres précompiles
    PARAMETER_DART = FIRST_PARAMETER_CONTROLER_GMAP,
    PARAMETER_FACE,
    PARAMETER_GRID,
    PARAMETER_NORMAL_VECTOR,
    PARAMETER_OBJECT_TRANSFORMATION,
    PARAMETER_PREVIEW,
    PARAMETER_SEW,
#ifdef MODULE_SPAMOD
    PARAMETER_SPAMOD,
#endif // MODULE_SPAMOD
    PARAMETER_VERTEX,

// Paramètres controleur
    PARAMETER_GMAP_VERTEX,
    PARAMETER_CREATION,
    PARAMETER_SELECTION,
    PARAMETER_OBJECT_POSITION,
    PARAMETER_POLYLINE_POSITION,
    PARAMETER_OBJECT_TRANSLATION,
    PARAMETER_OBJECT_ROTATION,
    PARAMETER_OBJECT_SCALE,
    PARAMETER_OBJECT_PONDERATION,
    PARAMETER_OPERATIONS,
    
    LAST_PARAMETER_CONTROLER_GMAP
  };
  //****************************************************************************
  //@name Types d'homothéties :
  typedef int TScaleType;

  enum
  {
    SCALE_POINT,
    SCALE_AXE,
    SCALE_PLANE
  };
  //****************************************************************************
  //@name Types de pondérations :
  typedef int TPonderationType;

  enum
  {
    PONDERATION_POINT,
    PONDERATION_AXE,
    PONDERATION_PLANE
  };
  //****************************************************************************
  //@name Types de lissage :
  typedef int TSmoothType;

  enum
  {
    HERMITE_SMOOTH,
    BEZIER_SMOOTH,
    OVERHAUSER_SMOOTH,
    SPLINE_SMOOTH,
    COONS_SMOOTH
  };

  //****************************************************************************
  enum
  {
    FIRST_OPERATION_CONTROLER_GMAP = LAST_OPERATION_CONTROLER,

    OPERATION_INVERT_LAST_OPERATION = FIRST_OPERATION_CONTROLER_GMAP,

    OPERATION_SELECT,

    OPERATION_CREATE,
    OPERATION_SEW,
    OPERATION_UNSEW,
    OPERATION_MERGE,
    OPERATION_MERGE_COLINEAR,
    OPERATION_MERGE_FACE_NODISCONNECTION,
    OPERATION_REMOVE_FACES_KEEP_BALLS,
    OPERATION_SHIFT_EDGES_INCIDENT_TO_VERTEX,
    OPERATION_REMOVE_DANGLING_EDGES,
    OPERATION_SIMPLIFY_2D_OBJECT,
    OPERATION_SIMPLIFY_3D_OBJECT,
    OPERATION_CONTRACT,
    OPERATION_DEL_FLAT_FACES,
    OPERATION_DEL_FLAT_VOLUMES,
    OPERATION_DELETE_DARTS,
    OPERATION_DUPLICATE_DARTS,
    OPERATION_DEL_NULL_EDGE,
    OPERATION_INSERT,
    OPERATION_STOP_UP,
    OPERATION_TRIANGULATE,
    OPERATION_QUADRANGULATE,
    OPERATION_EXTRUDE,
    OPERATION_THICKEN,
    OPERATION_MESH,
    OPERATION_SMOOTH,
    OPERATION_ROUND,
    OPERATION_TRIANGULATION,
    OPERATION_COREFINE,
    OPERATION_GEOLOGY,
    OPERATION_PLATE,
    OPERATION_DEFORM,
    OPERATION_MATERIALIZE,
    OPERATION_LOAD,
    OPERATION_SAVE,
    OPERATION_EXPORT,
    OPERATION_DUAL,
    OPERATION_EXTRACT_IMAGE,
    OPERATION_FIND_MOTIF_OFF,
    OPERATION_FIND_MOTIF_MOKA,

    LAST_OPERATION_CONTROLER_GMAP
  };
  //----------------------------------------------------------------------------
  enum
  {
    FIRST_SUB_OPERATION_CONTROLER_GMAP = LAST_SUB_OPERATION_CONTROLER,

    SUB_OPERATION_INVERT_LAST_ORIENTATION,
    SUB_OPERATION_INVERT_LAST_GEOMETRY,

    SUB_OPERATION_CREATE_POLYLINE,
    SUB_OPERATION_CREATE_POLYGON,
    SUB_OPERATION_CREATE_MESH,
    SUB_OPERATION_CREATE_CYLINDER,
    SUB_OPERATION_CREATE_PYRAMID,
    SUB_OPERATION_CREATE_SPHERE,
    SUB_OPERATION_CREATE_TORUS,

    SUB_OPERATION_INTUITIVE,
    SUB_OPERATION_INTUITIVE_TOPO,
    SUB_OPERATION_INTUITIVE_GEO,
    SUB_OPERATION_TOPO,
    SUB_OPERATION_GEO,

    SUB_OPERATION_INTUITIVE_BORDER,
    SUB_OPERATION_INTUITIVE_GEO_BORDER,
    SUB_OPERATION_INTUITIVE_TOPO_BORDER,
    SUB_OPERATION_BORDERS,
    SUB_OPERATION_GEO_BORDERS,
    SUB_OPERATION_TOPO_BORDERS,

    SUB_OPERATION_QUADRANGULATE_FACES,
    SUB_OPERATION_QUADRANGULATE_FACES_BASIC,

    SUB_OPERATION_EXTRUDE_BY_PATH,
    SUB_OPERATION_EXTRUDE_BY_NORMAL,
    SUB_OPERATION_EXTRUDE_BY_REVOLUTION,
    SUB_OPERATION_INTUITIVE_EXTRUDE_BY_NORMAL,

    SUB_OPERATION_TRIANGULATION_SWAP_EDGE,
    SUB_OPERATION_TRIANGULATION_GEO_FACES,
    SUB_OPERATION_TRIANGULATION_TOPO_FACES,
    SUB_OPERATION_TRIANGULATION_MARK_NON_UNIFORM_FACES,
    SUB_OPERATION_TRIANGULATION_OPTIMIZE,
    SUB_OPERATION_TRIANGULATION_DELAUNAY,
    SUB_OPERATION_TRIANGULATION_OPTIMIZED_DELAUNAY,

    SUB_OPERATION_COREFINE2D_LINES,
    SUB_OPERATION_COREFINE2D_SWEEPING,
    SUB_OPERATION_COREFINE2D_PROPAGATION,
    SUB_OPERATION_COREFINE_BOOL_OPS2D,
    SUB_OPERATION_COREFINE3D,
    SUB_OPERATION_COREFINE3D_MARKED_FACES,
    SUB_OPERATION_COREFINE3D_MARKED_MESHES,
    SUB_OPERATION_COREFINE_BOOL_OPS3D,

    SUB_OPERATION_GEOLOGY_UNCERTAIN_ZONE,
    SUB_OPERATION_GEOLOGY_EXTEND,
    SUB_OPERATION_GEOLOGY_EXTEND_TO,
    SUB_OPERATION_GEOLOGY_SMOOTH,
    SUB_OPERATION_GEOLOGY_SIMPLIFY,
    SUB_OPERATION_GEOLOGY_RELAX,
    SUB_OPERATION_GEOLOGY_CENTER,
    SUB_OPERATION_GEOLOGY_PLATE_ON_FACES,
    SUB_OPERATION_GEOLOGY_PLATE_ON_EDGES,
    SUB_OPERATION_GEOLOGY_PLATE_ON_VERTICES,
    SUB_OPERATION_GEOLOGY_SELECT_VERTICES,
    SUB_OPERATION_GEOLOGY_SELECT_ALL_EDGES,
    SUB_OPERATION_GEOLOGY_SELECT_EDGES,
    SUB_OPERATION_GEOLOGY_SELECT_FACES,
    SUB_OPERATION_GEOLOGY_SELECT_BORDERS,
    SUB_OPERATION_GEOLOGY_IMPORT_GR2D,
    SUB_OPERATION_GEOLOGY_IMPORT_XYZ,
    SUB_OPERATION_GEOLOGY_IMPORT_TS,
    SUB_OPERATION_GEOLOGY_IMPORT_CLOUD,
    ///
    SUB_OPERATION_GEOLOGY_TRIANG_HOLES,
    SUB_OPERATION_GEOLOGY_HOLES_REFINEMENT,
    SUB_OPERATION_GEOLOGY_FILL_HOLES,
    SUB_OPERATION_GEOLOGY_FAILLE_DETECTION,
    SUB_OPERATION_GEOLOGY_EXTENSION_FAILLE,
    SUB_OPERATION_GEOLOGY_EXTRACT_FAILLE,
    SUB_OPERATION_GEOLOGY_MESH_SIMPLIFICATION,
    SUB_OPERATION_GEOLOGY_IMPORT_VRML,
    SUB_OPERATION_GEOLOGY_EXPORT_TS,
    ///
  
    SUB_OPERATION_TRANSLATE,
    SUB_OPERATION_ROTATE,
    SUB_OPERATION_SCALE,

    SUB_OPERATION_MATERIALIZE_BARYCENTER,
    SUB_OPERATION_MATERIALIZE_AXE,
    SUB_OPERATION_MATERIALIZE_PLANE,
    SUB_OPERATION_MATERIALIZE_NORMAL_VECTOR,
    SUB_OPERATION_MATERIALIZE_ORTHO_PLANE,
    SUB_OPERATION_MATERIALIZE_REFERENTIAL,

    SUB_OPERATION_SELECT_ORBIT,
    SUB_OPERATION_SET_SELECTION_LEVEL,
    SUB_OPERATION_SELECT_INCIDENTS,
    SUB_OPERATION_SELECT_INTERIOR,
    SUB_OPERATION_SELECT_INTERSECTION,
    SUB_OPERATION_REINIT_SELECTION,
    SUB_OPERATION_NEGATE_SELECTION,
    SUB_OPERATION_SWAP_SELECTIONS,
    SUB_OPERATION_EXTEND_SELECTION,
    SUB_OPERATION_SELECT_NON_PLANAR_FACES,
    SUB_OPERATION_MOVE_SELECTION,

    SUB_OPERATION_LOAD_MAP,
    SUB_OPERATION_ADD_MAP,

    LAST_SUB_OPERATION_CONTROLER_GMAP
  };
  //****************************************************************************
} // namespace GMap3d
//******************************************************************************
#endif // CONTROLER_TYPES_HH
//******************************************************************************
