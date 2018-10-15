    MRF.correctBoundaryVelocity(U);

    fvVectorMatrix UEqn
    (

        (1.0 + cPorField) * fvm::ddt(rho, U)
        + fvm::div(rhoPhi/porosityF, U)
        + (1.0 + cPorField) * MRF.DDt(rho, U)       
	+ turbulence->divDevRhoReff(rho, U)
        + aPorField * pow(1.0 - porosity, 3) / pow(porosity,2)
            * mixture.mu() / pow(D50Field,2) * U
        + bPorField * rho * (1.0 - porosity) / pow(porosity,2) / D50Field
            * mag(U) * U * 
            (1.0 + useTransMask * 7.5 / KCPorField)
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
            porosity * fvc::reconstruct
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
