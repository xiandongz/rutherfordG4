#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class myDetectorConstruction: public G4VUserDetectorConstruction{

public:
	myDetectorConstruction();
	virtual ~myDetectorConstruction();

	virtual G4VPhysicalVolume* Construct();

	G4LogicalVolume* GetScoringVolume() const {return fScoringVolume;}

protected:
	G4LogicalVolume* fScoringVolume;

};

#endif
