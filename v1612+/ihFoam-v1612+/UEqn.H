    MRF.correctBoundaryVelocity(U);

    //Gabi
    surfaceScalarField muEff
    (
        "muEff",
        mixture.muf()
      + fvc::interpolate(rho*turbulence->nut())
    );
    //end_Gabi

    fvVectorMatrix UEqn
    (
	//Gabi
//        fvm::ddt(rho, U) + fvm::div(rhoPhi, U)
//      + MRF.DDt(rho, U)
//      + turbulence->divDevRhoReff(rho, U)
        (1.0 + cPorField) / porosity * fvm::ddt(rho, U)
        + (1.0 + cPorField) / porosity * MRF.DDt(rho, U)
        + 1.0/porosity * fvm::div(rhoPhi/porosityF, U)
        // + turbulence->divDevRhoReff(rho, U)
        - fvm::laplacian(muEff/porosityF , U)
        - 1.0/porosity * ( fvc::grad(U) & fvc::grad(muEff) )
        // Closure Terms
        + aPorField * pow(1.0 - porosity, 3) / pow(porosity,3)
            * mixture.mu() / pow(D50Field,2) * U
        + bPorField * rho * (1.0 - porosity) / pow(porosity,3) / D50Field
            * mag(U) * U * 
        // Transient formulation
        (1.0 + useTransMask * 7.5 / KCPorField)
	//end_Gabi
     ==
        fvOptions(rho, U)
    );

    UEqn.relax();

    fvOptions.constrain(UEqn);

    if (pimple.momentumPredictor())
    {
        solve
        (
            UEqn
         ==
            fvc::reconstruct
            (
                (
                    mixture.surfaceTensionForce()
                  - ghf*fvc::snGrad(rho)
                  - fvc::snGrad(p_rgh)
                ) * mesh.magSf()
            )
        );

        fvOptions.correct(U);
    }
