#include "myDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"


myDetectorConstruction::myDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{}

myDetectorConstruction::~myDetectorConstruction()
{}

G4VPhysicalVolume* myDetectorConstruction::Construct(){

  // 
  // For Materials
  //

//  G4NistManager* nist = G4NistManager::Instance();
  G4double a;
  G4double z;
  G4double density; 
  G4double pressure;
  G4double temperature;

  //
  // For Definition
  //

  G4bool checkOverlaps = true;

  //
  // World
  //

  G4double world_sizeXY = 25*mm;
  G4double world_sizeZ = 50*mm;

  a = 1.01*g/mole;
  z = 1.;
  density = universe_mean_density;
  pressure = 1.e-19*pascal;
  temperature = 0.1*kelvin;

  G4Material* Vacuo =
    new G4Material("Galactic",z,a,density,kStateGas,temperature,pressure);

  G4Box* solidWorld = 
    new G4Box("World",world_sizeXY,world_sizeXY,world_sizeZ);
  G4LogicalVolume* logicWorld = 
    new G4LogicalVolume(solidWorld, Vacuo, "World");
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,
		      G4ThreeVector(),
		      logicWorld,
		      "World",
		      0,
		      false,
		      0,
		      checkOverlaps);

  //
  // Collimator Tube 1
  //
  
  G4double tube01_Rmin = 0.5*mm;
  G4double tube01_Rmax = 0.55*mm;
  G4double tube01_Dz = 25.*mm;

  a = 55.845*g/mole;
  z = 26.;
  density = 7.87*g/cm3;
  G4Material* Iron =
    new G4Material("Iron",z,a,density);

  G4Tubs * solidTube_01 =
    new G4Tubs("Tube_01",tube01_Rmin,tube01_Rmax,tube01_Dz/2.0,0.0,twopi);
  G4LogicalVolume* logicTube_01 = 
    new G4LogicalVolume(solidTube_01, Iron, "Tube_01");

  new G4PVPlacement(0,
		    G4ThreeVector(0.*mm,0.*mm,-17.5*mm),
		    logicTube_01,
		    "Tube_01",
		    logicWorld,
		    false,
		    0,
		    checkOverlaps);

  //
  // Collimator Frame Tube
  //

  a = 1.01*g/mole;
  z = 1.0;
  G4Element* elH = new G4Element("Hydrogen","H",z,a);

  a = 12.01*g/mole;
  z = 6.;
  G4Element* elC = new G4Element("Carbon","C",z,a);

  a = 16.00*g/mole;
  z = 8.;
  G4Element* elO = new G4Element("Oxygen","O",z,a);

  density = 1.32*g/cm3;
  G4int natoms;
  G4int ncomponents = 3;
  G4Material* PLA = new G4Material("Polylatic",density,ncomponents);
  PLA->AddElement(elC, natoms=3);
  PLA->AddElement(elH, natoms=4);
  PLA->AddElement(elO, natoms=2);

  G4double frameTube_Rmin = 0.55*mm;
  G4double frameTube_Rmax = 15.*mm;
  G4double frameTube_Dz = 25.*mm;

  G4Tubs * solidFrameTube =
    new G4Tubs("FrameTube",frameTube_Rmin,frameTube_Rmax,frameTube_Dz/2.0,0.0,twopi);
  G4LogicalVolume* logicFrameTube =
    new G4LogicalVolume(solidFrameTube, PLA, "FrameTube");

  new G4PVPlacement(0,
                    G4ThreeVector(0.*mm,0.*mm,7.5*mm),
                    logicFrameTube,
                    "FrameTube",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  //
  // Collimator Tube 2
  //

  G4double tube02_Rmin = 0.5*mm;
  G4double tube02_Rmax = 0.55*mm;
  G4double tube02_Dz = 25.*mm;

  G4Tubs * solidTube_02 =
    new G4Tubs("Tube_02",tube02_Rmin,tube02_Rmax,tube02_Dz/2.0,0.0,twopi);
  G4LogicalVolume* logicTube_02 =
    new G4LogicalVolume(solidTube_02, Iron, "Tube_02");

  new G4PVPlacement(0,
                    G4ThreeVector(0.*mm,0.*mm,7.5*mm),
                    logicTube_02,
                    "Tube_02",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);


  //
  // Target
  //

  G4double target_sizeXY = 2.5*mm;
  G4double target_sizeZ = 0.00065*mm;

  a = 196.97*g/mole;
  z = 79.;
  density = 19.32*g/cm3;

  G4Material* Au = 
    new G4Material("Gold",z,a,density);

  G4Box* solidTarget = 
    new G4Box("Target",target_sizeXY,target_sizeXY,target_sizeZ);
  G4LogicalVolume* logicTarget = 
    new G4LogicalVolume(solidTarget, Au, "Target");//Au

  new G4PVPlacement(0,
	 	    G4ThreeVector(0.*mm,0.*mm,20.0005*mm),
		    logicTarget,
		    "Target",
		    logicWorld,
		    false,
		    0,
		    checkOverlaps);

  //
  // Sensor
  //
  G4double sensor_sizeXY = 2.5*mm;
  G4double sensor_sizeZ = 0.0005*mm;

  G4Box* solidSensor =
    new G4Box("Sensor",sensor_sizeXY,sensor_sizeXY,sensor_sizeZ);
  G4LogicalVolume* logicSensor =
    new G4LogicalVolume(solidSensor, Vacuo, "Sensor");

  new G4PVPlacement(0,
                    G4ThreeVector(0.*mm,0.*mm,30.*mm),
                    logicSensor,
                    "Sensor",
                    logicWorld,
                    false,
                    0,
                    checkOverlaps);

  //
  // Set Target as scoring volume
  //
  fScoringVolume = logicSensor;


  //
  // Visualization attributes
  //
  G4VisAttributes* visAtt_World = new G4VisAttributes(G4Colour(0,0,0));
  logicWorld->SetVisAttributes(visAtt_World);

  G4VisAttributes* visAtt_Tube = new G4VisAttributes(G4Colour(0.91,0.91,0.85));
  visAtt_Tube->SetForceSolid(true);
  logicTube_01->SetVisAttributes(visAtt_Tube);
  logicTube_02->SetVisAttributes(visAtt_Tube);

  G4VisAttributes* visAtt_FrameTube = new G4VisAttributes(G4Colour(0.33,0.33,0.33));
  visAtt_FrameTube->SetForceSolid(true);
  logicFrameTube->SetVisAttributes(visAtt_FrameTube);

  G4VisAttributes* visAtt_Target = new G4VisAttributes(G4Colour(1.0,0.84,0.0));
  visAtt_Target->SetForceSolid(true);
  logicTarget->SetVisAttributes(visAtt_Target);

  G4VisAttributes* visAtt_Sensor = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
  logicSensor->SetVisAttributes(visAtt_Sensor);

  //
  // always return the physical World
  //
  return physWorld;
}
