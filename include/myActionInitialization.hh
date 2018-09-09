#ifndef MyActionInitialization_h
#define MyActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class myActionInitialization : public G4VUserActionInitialization
{
  public:
    myActionInitialization();
    virtual ~myActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
