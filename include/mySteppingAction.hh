#ifndef MySteppingAction_h
#define MySteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class myEventAction;

class G4LogicalVolume;

/// Stepping action class
/// 

class mySteppingAction : public G4UserSteppingAction
{
  public:
    mySteppingAction(myEventAction* eventAction);
    virtual ~mySteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    myEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

#endif
