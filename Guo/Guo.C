/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
    Copyright (C) 2017-2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "Guo.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(Guo, 0);
    addToRunTimeSelectionTable
    (
        viscosityModel,
        Guo,
        dictionary
    );
}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

// This "Protected Member Functions" is used to calculate the kinematic viscosity,
// which is used in the "Constructors".

Foam::tmp<Foam::volScalarField>
Foam::viscosityModels::Guo::calcNu() const
{  
    // Info << "strainRate: " << strainRate() << endl;
    return 
    (
        tau0OverRho_/max
        (
            strainRate(),
            // dimensionedScalar("VSMALL", dimless/dimTime, VSMALL)
            dimensionedScalar("VSMALL", dimless/dimTime, 1e-6)
        )
        *
        pow
        (
            (scalar(1.0) + alpha_*strainRate()),
            beta_
        )
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::Guo::Guo
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    viscosityModel(name, viscosityProperties, U, phi),
    GuoCoeffs_
    (
        viscosityProperties.optionalSubDict(typeName + "Coeffs")
    ),
    alpha_("alpha", dimTime, GuoCoeffs_),
    beta_("beta", dimless, GuoCoeffs_),
    tau0OverRho_("tau0OverRho", GuoCoeffs_),

    nu_
    (
        IOobject
        (
            name,
            U_.time().timeName(),
            U_.db(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        calcNu()
    )
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::Guo::read
(
    const dictionary& viscosityProperties
)
{
    // Call the "read()" function defined in paraent class
    viscosityModel::read(viscosityProperties);

    GuoCoeffs_ = viscosityProperties.optionalSubDict(typeName + "Coeffs");

    GuoCoeffs_.readEntry("alpha", alpha_);
    GuoCoeffs_.readEntry("beta", beta_);
    GuoCoeffs_.readEntry("tau0OverRho", tau0OverRho_);
    
    return true;
}


// ************************************************************************* //
