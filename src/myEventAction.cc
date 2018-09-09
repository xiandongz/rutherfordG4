#include "myEventAction.hh"
#include "myRunAction.hh"
#include "myHitsData.hh"

#include "TTree.h"

#include "G4Event.hh"
#include "G4RunManager.hh"

extern TTree* myTree;
extern myHitsData alphaHits;

myEventAction::myEventAction(myRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{} 

myEventAction::~myEventAction()
{}

void myEventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
}

void myEventAction::EndOfEventAction(const G4Event* evt)
{   
  G4int event_id = evt->GetEventID();
  if(event_id%1000 == 0)
    G4cout<<"Event "<<event_id<<" finish!"<<G4endl;

  //
  // Fill the tree
  //

  // Get the initial info for each alpha particle
  if(alphaHits.passSensor){
    G4PrimaryVertex *myVertex = evt->GetPrimaryVertex(0);
    G4PrimaryParticle *myPrimaryParticle = myVertex->GetPrimary(0);
    alphaHits.InitEnergy = myPrimaryParticle->GetTotalEnergy();
    alphaHits.InitKineE = myPrimaryParticle->GetKineticEnergy();
    alphaHits.InitPos_X = myVertex->GetX0();
    alphaHits.InitPos_Y = myVertex->GetY0();
    alphaHits.InitPos_Z = myVertex->GetZ0();
    alphaHits.InitPx = myPrimaryParticle->GetPx();
    alphaHits.InitPy = myPrimaryParticle->GetPy();
    alphaHits.InitPz = myPrimaryParticle->GetPz();
    myTree->Fill();
  }
  alphaHits.passSensor = false;

  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
}
