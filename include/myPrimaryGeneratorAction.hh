#ifndef MyPrimaryGeneratorAction_h
#define MyPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class myPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{

public:
  myPrimaryGeneratorAction();
  virtual ~myPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);

  const G4ParticleGun* GetParticleGun() const {return fParticleGun;}

private:
  G4ParticleGun* fParticleGun;

};

#endif
