//Face Normal
surfaceVectorField cellFaceNormals
(
    IOobject
    (
        "cellFaceNormals",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh.Sf()
);


//Face Center
surfaceVectorField cellFaceCenter
(
    IOobject
    (
        "cellFaceCenter",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ, 
        IOobject::AUTO_WRITE
    ),
    mesh.Cf()
);



//Face Magnitude
surfaceScalarField cellFaceMagnitude
(
    IOobject
    (
        "cellFaceMagnitude",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh.magSf()
);


//Cell Volumenes
//volScalarField cellVolumes
////////scalarField cellVolumes
////////(
////////    IOobject
////////    (
////////        "cellVolumes",
////////        runTime.timeName(),
////////        mesh,
////////        IOobject::NO_READ,
////////        IOobject::AUTO_WRITE
////////    ),
////////    mesh.V()
////////);

//Cell Centroids
volVectorField cellCentroids
(
    IOobject
    (
        "cellCentroids",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh.C()
);
