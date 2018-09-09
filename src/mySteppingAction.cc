#include "mySteppingAction.hh"
#include "myEventAction.hh"
#include "myDetectorConstruction.hh"
#include "myHitsData.hh"

#include "TTree.h"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

extern myHitsData alphaHits;

mySteppingAction::mySteppingAction(myEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

mySteppingAction::~mySteppingAction()
{}

void mySteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const myDetectorConstruction* detectorConstruction
      = static_cast<const myDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  // step->GetTrack()->GetCurrentStepNumber()
  // StepNumber: 1 World
  // 		 2 Target
  // 		 3 World
  // 		 4 Sensor
  // 		 5 World
  if (volume != fScoringVolume){
    if(step->GetTrack()->GetCurrentStepNumber() == 2){
      alphaHits.TargetPos_X = step->GetTrack()->GetPosition().x();
      alphaHits.TargetPos_Y = step->GetTrack()->GetPosition().y();
      alphaHits.TargetPos_Z = step->GetTrack()->GetPosition().z();
    }
    return;
  }
  else{
    alphaHits.passSensor = true;
    alphaHits.SensorPos_X = step->GetTrack()->GetPosition().x();
    alphaHits.SensorPos_Y = step->GetTrack()->GetPosition().y();
    alphaHits.SensorPos_Z = step->GetTrack()->GetPosition().z();
  }

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);  
}
