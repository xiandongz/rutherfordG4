#include "myPrimaryGeneratorAction.hh"

#include "TTree.h"
#include "TFile.h"
#include "TMath.h"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

myPrimaryGeneratorAction::myPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "alpha";
  G4ParticleDefinition* particle = 
    particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->SetParticleEnergy(5.488*MeV);

}

myPrimaryGeneratorAction::~myPrimaryGeneratorAction()
{
delete fParticleGun;
}

void myPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

  TFile* dataInput = 
    new TFile("/users/xiandongz/work/G4Rutherford/initAlphaData/RutherfordData.root","read");
  TTree* initAlphaDataTree;
  dataInput->GetObject("rutherfordData",initAlphaDataTree);
  double px,py,pz;
  double posX, posY;
  initAlphaDataTree->SetBranchAddress("initMovX",&px);
  initAlphaDataTree->SetBranchAddress("initMovY",&py);
  initAlphaDataTree->SetBranchAddress("initMovZ",&pz);
  initAlphaDataTree->SetBranchAddress("initPosX",&posX);
  initAlphaDataTree->SetBranchAddress("initPosY",&posY);
  initAlphaDataTree->GetEntry(anEvent->GetEventID());

  G4double vx = px/TMath::Sqrt(px*px+py*py+pz*pz);
  G4double vy = py/TMath::Sqrt(px*px+py*py+pz*pz);
  G4double vz = pz/TMath::Sqrt(px*px+py*py+pz*pz);

  fParticleGun->SetParticlePosition(G4ThreeVector(posX*mm,posY*mm,-30.*mm));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vx,vy,vz));
  fParticleGun->GeneratePrimaryVertex(anEvent);

  dataInput->Close();

}
