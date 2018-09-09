#ifndef MyEventAction_h
#define MyEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class myRunAction;

/// Event action class
///

class myEventAction : public G4UserEventAction
{
  public:
    myEventAction(myRunAction* runAction);
    virtual ~myEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    myRunAction* fRunAction;
    G4double     fEdep;
};

#endif

    
