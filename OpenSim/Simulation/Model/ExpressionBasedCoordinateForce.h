#ifndef OPENSIM_EXPRESSION_BASED_COORDINATE_FORCE_H_
#define OPENSIM_EXPRESSION_BASED_COORDINATE_FORCE_H_
/* -------------------------------------------------------------------------- *
 *                OpenSim:  ExpressionBasedCoordinateForce.h                  *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2017 Stanford University and the Authors                *
 * Author(s): Nabeel Allana                                                   *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */
// INCLUDE
#include "Force.h"
#include <lepton/ExpressionProgram.h>

namespace OpenSim {

class OSIMSIMULATION_API ExpressionBasedCoordinateForce : public Force
{
OpenSim_DECLARE_CONCRETE_OBJECT(ExpressionBasedCoordinateForce, Force);
public:
//==============================================================================
// PROPERTIES
//==============================================================================
    OpenSim_DECLARE_PROPERTY(coordinate, std::string,
        "Coordinate (name) to apply force to.");
    OpenSim_DECLARE_PROPERTY(expression, std::string,
        "Expression of the force magnitude as a function of the coordinate value (q)"
        "and its time derivative (qdot). Note, expression cannot have any whitespace"
        "separating characters");
//==============================================================================
// OUTPUTS
//==============================================================================
    OpenSim_DECLARE_OUTPUT(force_magnitude, double, getForceMagnitude,
            SimTK::Stage::Dynamics);
//==============================================================================
// PUBLIC METHODS
//==============================================================================
    /** Default constructor. **/
    ExpressionBasedCoordinateForce();
    /** Convenience constructor for API users.
    @param coordinate   name of the coordinate to apply the force to
    @param expression   the expression used to compute the force magnitude
    **/
    ExpressionBasedCoordinateForce(
                const std::string& coordinate, const std::string& expression);
//==============================================================================
// GET and SET parameters
//==============================================================================
    /**
    * Coordinate
    */
    void setCoordinateName(const std::string& coord)
    {   set_coordinate(coord); }
    const std::string& getCoordinateName() const {return get_coordinate();}

    /**
    * %Set the mathematical expression that defines the force magnitude of this
    * coordinate force in terms of the coordinate value (q) and its
    * time derivative (qdot). Expressions with C-mathematical operations
    * such as +,-,*,/ and common functions: exp, pow, sqrt, sin, cos, tan,
    * and so on are acceptable.
    * NOTE: a limitation is that the expression may not contain whitespace
    * @param expression    string containing the mathematical expression that
    *                      defines the coordinate force
    */
    void setExpression(const std::string& expression);


    /**
    * Get the computed Force magnitude determined by evaluating the
    * expression above. Note, computeForce must be evaluated first,
    * and this is done automatically if the system is realized to Dynamics
    * @param state    const state (reference) for the model
    * @return         const double ref to the force magnitude
    */
    const double& getForceMagnitude(const SimTK::State& state) const;


//==============================================================================
// COMPUTATION
//==============================================================================
    /** Compute the coordinate force based on the user-defined expression
        and apply it to the model */
    void computeForce(const SimTK::State& state,
                              SimTK::Vector_<SimTK::SpatialVec>& bodyForces,
                              SimTK::Vector& generalizedForces) const override;

    //--------------------------------------------------------------------------
    // COMPUTATIONS
    //--------------------------------------------------------------------------
    /** Force calculation operator. **/
    double calcExpressionForce( const SimTK::State& s) const;

//==============================================================================
// Reporting
//==============================================================================
    /**
     * Provide name(s) of the quantities (column labels) of the force value(s) to be reported
     */
    OpenSim::Array<std::string> getRecordLabels() const override;
    /**
    *  Provide the value(s) to be reported that correspond to the labels
    */
    OpenSim::Array<double> getRecordValues(const SimTK::State& state) const override;



protected:
//==============================================================================
// ModelComponent interface
//==============================================================================
    void extendConnectToModel(Model& model) override;
    void extendAddToSystem(SimTK::MultibodySystem& system) const override;


private:
    void setNull();
    void constructProperties();

    // parser programs for efficiently evaluating the expressions
    Lepton::ExpressionProgram _forceProg;

    // Corresponding generalized coordinate to which the force
    // is applied.
    SimTK::ReferencePtr<Coordinate> _coord;

    mutable CacheVariable<double> _forceMagnitudeCV;

}; //  class ExpressionBasedCoordinateForce

}; // namespace OpenSim

#endif // OPENSIM_EXPRESSION_BASED_COORDINATE_FORCE_H_
