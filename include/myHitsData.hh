#ifndef MyHitsData_h
#define MyHitsData_h 1

#include "Rtypes.h"

class myHitsData
{
public:
  myHitsData(){
    passSensor = false;
    InitEnergy = 0.0;
    InitKineE = 0.0;
    InitPos_X = 0.0;
    InitPos_Y = 0.0;
    InitPos_Z = 0.0;
    InitPx = 0.0;
    InitPy = 0.0;
    InitPz = 0.0;
    SensorPos_X = 0.0;
    SensorPos_Y = 0.0;
    SensorPos_Z = 0.0;
    TargetPos_X = 0.0;
    TargetPos_Y = 0.0;
    TargetPos_Z = 0.0;
  }
  virtual ~myHitsData(){;}

  bool passSensor;
  Float_t InitEnergy;
  Float_t InitKineE;
  Float_t InitPos_X;
  Float_t InitPos_Y;
  Float_t InitPos_Z;
  Float_t InitPx;
  Float_t InitPy;
  Float_t InitPz;
  Float_t SensorPos_X;
  Float_t SensorPos_Y;
  Float_t SensorPos_Z;
  Float_t TargetPos_X;
  Float_t TargetPos_Y;
  Float_t TargetPos_Z;
};



#endif
