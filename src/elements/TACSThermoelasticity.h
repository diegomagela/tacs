/*
  This file is part of TACS: The Toolkit for the Analysis of Composite
  Structures, a parallel finite-element code for structural and
  multidisciplinary design optimization.

  Copyright (C) 2014 Georgia Tech Research Corporation

  TACS is licensed under the Apache License, Version 2.0 (the
  "License"); you may not use this software except in compliance with
  the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0
*/

#ifndef TACS_THERMOELASTICITY_H
#define TACS_THERMOELASTICITY_H

#include "TACSElementModel.h"
#include "TACSLinearElasticity.h"
#include "TACSPlaneStressConstitutive.h"

class TACSLinearThermoelasticity2D : public TACSElementModel {
 public:
  TACSLinearThermoelasticity2D( TACSPlaneStressConstitutive *_con,
                                ElementStrainType strain_type );
  ~TACSLinearThermoelasticity2D();

  int getSpatialDim();
  int getVarsPerNode();

  /**
    Retrieve the global design variable numbers associated with this element
  */
  int getDesignVarNums( int elemIndex, int dvLen, int dvNums[] );

  /**
    Set the element design variables from the design vector
  */
  void setDesignVars( int elemIndex, int dvLen, const TacsScalar dvs[] );

  /**
    Get the element design variables values
  */
  void getDesignVars( int elemIndex, int dvLen, TacsScalar dvs[] );

  /**
    Get the lower and upper bounds for the design variable values
  */
  void getDesignVarRange( int elemIndex, int dvLen,
                          TacsScalar lb[], TacsScalar ub[] );

  /**
    Evaluate the coefficients of the weak form integrand
  */
  void evalWeakIntegrand( int elemIndex, const double time, int n,
                          const double pt[], const TacsScalar X[],
                          const TacsScalar Ut[], const TacsScalar Ux[],
                          TacsScalar DUt[], TacsScalar DUx[] );

  /**
    Evaluate the derivatives of the weak form coefficients
  */
  void evalWeakJacobian( int elemIndex, const double time, int n,
                         const double pt[], const TacsScalar X[],
                         const TacsScalar Ut[], const TacsScalar Ux[],
                         TacsScalar DUt[], TacsScalar DUx[],
                         int *Jac_nnz, const int *_Jac_pairs[],
                         TacsScalar Jac[] );

  /**
     Add the derivative of the product of the adjoint and residual to
     the design vector
  */
  void addWeakAdjProduct( int elemIndex, const double time, int n,
                          const double pt[], const TacsScalar X[],
                          const TacsScalar Ut[], const TacsScalar Ux[],
                          const TacsScalar Psi[], const TacsScalar Psix[],
                          TacsScalar scale, int dvLen, TacsScalar dfdx[] );

  /**
     Evaluate a point-wise quantity of interest at a quadrature point
  */
  int evalPointQuantity( int elemIndex, const int quantityType,
                         const double time, int n, const double pt[],
                         const TacsScalar X[], const TacsScalar Xd[],
                         const TacsScalar Ut[], const TacsScalar Ux[],
                         TacsScalar *quantity );

  /**
     Add the derivative of the quantity w.r.t. the design variables
  */
  void addPointQuantityDVSens( int elemIndex, const int quantityType,
                               const double time, TacsScalar scale,
                               int n, const double pt[],
                               const TacsScalar X[], const TacsScalar Xd[],
                               const TacsScalar Ut[], const TacsScalar Ux[],
                               const TacsScalar dfdq[],
                               int dvLen, TacsScalar dfdx[] );

  /**
     Evaluate the derivatives of the point-wise quantity of interest
     with respect to X, Ut and Ux.
  */
  void evalPointQuantitySens( int elemIndex, const int quantityType,
                              const double time, int n, const double pt[],
                              const TacsScalar X[], const TacsScalar Xd[],
                              const TacsScalar Ut[], const TacsScalar Ux[],
                              const TacsScalar dfdq[],
                              TacsScalar dfdX[], TacsScalar dfdXd[],
                              TacsScalar dfdUt[], TacsScalar dfdUx[] );

  /**
    Get the output for a single node in the mesh
  */
  void getOutputData( int elemIndex, const double time,
                      ElementType etype, int write_flag,
                      const double pt[], const TacsScalar X[],
                      const TacsScalar Ut[], const TacsScalar Ux[],
                      int ld_data, TacsScalar *data );

 private:
  ElementStrainType strain_type;
  TACSPlaneStressConstitutive *stiff;

  // Constant member data
  static const int linear_Jac_pairs[54];
};

#endif // TACS_THERMOELASTICITY_H
