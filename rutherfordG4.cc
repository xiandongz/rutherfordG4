#include "myDetectorConstruction.hh"
#include "myActionInitialization.hh"
#include "myHitsData.hh"

#include "TFile.h"
#include "TTree.h"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

TTree* myTree = new TTree("myTree","my simple tree");
myHitsData alphaHits;

int main(int argc, char** argv){

  //
  // set the branch for TTree
  //

  myTree->Branch("InitEnergy",&alphaHits.InitEnergy,"InitEnergy/F");
  myTree->Branch("InitKineE",&alphaHits.InitKineE,"InitKineE/F");
  myTree->Branch("InitPos_X",&alphaHits.InitPos_X,"InitPos_X/F");
  myTree->Branch("InitPos_Y",&alphaHits.InitPos_Y,"InitPos_Y/F");
  myTree->Branch("InitPos_Z",&alphaHits.InitPos_Z,"InitPos_Z/F");
  myTree->Branch("InitPx",&alphaHits.InitPx,"InitPx/F");
  myTree->Branch("InitPy",&alphaHits.InitPy,"InitPy/F");
  myTree->Branch("InitPz",&alphaHits.InitPz,"InitPz/F");
  myTree->Branch("SensorPos_X",&alphaHits.SensorPos_X,"SensorPos_X/F");
  myTree->Branch("SensorPos_Y",&alphaHits.SensorPos_Y,"SensorPos_Y/F");
  myTree->Branch("SensorPos_Z",&alphaHits.SensorPos_Z,"SensorPos_Z/F");
  myTree->Branch("TargetPos_X",&alphaHits.TargetPos_X,"TargetPos_X/F");
  myTree->Branch("TargetPos_Y",&alphaHits.TargetPos_Y,"TargetPos_Y/F");
  myTree->Branch("TargetPos_Z",&alphaHits.TargetPos_Z,"TargetPos_Z/F");


  G4UIExecutive* ui = 0;
  if(argc == 1){
    ui = new G4UIExecutive(argc, argv);
  }

  G4Random::setTheEngine(new CLHEP::RanecuEngine);

#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  runManager->SetUserInitialization(new myDetectorConstruction());

  G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new myActionInitialization);

//  G4VisManager* visManager = new G4VisExecutive;
//  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if(!ui){
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else{
    UImanager->ApplyCommand("/control/execute init_vis.mac");
//    UImanager->ApplyCommand("/run/beamOn 10000");
    ui->SessionStart();
    delete ui;
  }

  TFile *f = new TFile("TestRoot.root","recreate");
  myTree->Write();

//  delete visManager;
  delete runManager;
  delete myTree;
  delete f;

  return 0;
}
