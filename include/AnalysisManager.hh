#ifndef AnalysisManager_h
#define AnalysisManager_h 1

#include "globals.hh"
#include "PrimaryGeneratorAction.hh"
#include "AnalysisMessenger.hh"

#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "Rtypes.h"
#include "TVector3.h"
#include "TString.h"
#include "PMTHit.hh"

class TTree;
class TFile;

//---------------------------------------------------------------------------

class AnalysisManager {

public:

  AnalysisManager();
  ~AnalysisManager();

  void InitOutput();

  void ZeroArray();
  void FillArray( Int_t );
  void FillTree();

  inline void SetOutFileName     ( TString fname )             { fOutFileName  = fname; }

  inline void SetPrimaryEnergy   ( G4double       ene  )       { fPEne  = ene;  }
  inline void SetPrimaryTime     ( G4double       time )       { fPTime = time; }
  inline void SetPrimaryPDef     ( G4ParticleDefinition* pdef) { fPPDef = pdef; }
  inline void SetPrimaryDirection( G4ThreeVector  dir  )       { fPdir  = dir;  }

  inline void SetPMTNumber       ( G4int          pno )        { fPMTNo    = pno; }
  inline void SetPhotonCount       ( G4int pno, G4int snp )        { 
		fNphotons[pno]    = snp; 
	}
  
  inline void SetPMTKE ( PMTHit* hit2 ) {
		G4int snp = hit2->GetPhotonCount();
		G4int pno = hit2->GetPMTNumber();
	    	for (G4int iii = 0; iii < snp; iii++) { 
			fPMTKineticEnergy[pno][iii] = hit2->GetPMTKineticEnergy(iii); 
		}
	}

  inline void SetStepPDef        ( G4ParticleDefinition* sp )  { fSteppdef = sp;       }
  inline void SetStepPosPre      ( G4ThreeVector  spos )       { fSteppospre  = spos;  }
  inline void SetStepPosPost     ( G4ThreeVector  spos )       { fSteppospost  = spos; }
  inline void SetStepP3          ( G4ThreeVector  smom )       { fStepp3   = smom;     }
  inline void SetStepTime        ( G4double       stime )      { fSteptime = stime;    }
  inline void SetStepID          ( G4int          sid )        { fStepid   = sid;      }
  inline void SetStepEdep        ( G4double       sedep)       { fStepedep = sedep;    }

private:
  
  AnalysisMessenger*    fAnaMessenger;
  TString               fOutFileName;
  TFile*                fROOTfile;
  TTree*                fROOTtree;
  
  // Primary
  Float_t               fPEne;
  Float_t               fPth;
  Float_t               fPph;
  Float_t               fPTime;
  G4ParticleDefinition* fPPDef;
  Int_t                 fPpdg;
  G4ThreeVector         fPdir;

  // PMT
  Int_t                 fPMTNo;
  static const Int_t	fMaxPMTNo = 20;
  static const Int_t    fMaxPMTHits = 5000;
  Int_t			fNphotons[fMaxPMTNo];
  Float_t 		fPMTKineticEnergy[fMaxPMTNo][fMaxPMTHits];

  // Detector (step information) 
  G4ParticleDefinition* fSteppdef;
  G4ThreeVector         fStepp3;
  G4ThreeVector         fSteppospre;
  G4ThreeVector         fSteppospost;
  G4double              fSteptime;
  G4int                 fStepid;
  G4double              fStepedep;

  static const Int_t    fMaxhits = 50000;

  Int_t                 fRAW_Nhits;
  Int_t                 fRAW_id[fMaxhits];
  Float_t               fRAW_time[fMaxhits];
  Float_t               fRAW_Edep[fMaxhits];
  Int_t                 fRAW_pdg[fMaxhits];
  Float_t               fRAW_mass[fMaxhits];
  Float_t               fRAW_mom[fMaxhits];
  Float_t               fRAW_px[fMaxhits];
  Float_t               fRAW_py[fMaxhits];
  Float_t               fRAW_pz[fMaxhits];
  Float_t               fRAW_xpre[fMaxhits];
  Float_t               fRAW_ypre[fMaxhits];
  Float_t               fRAW_zpre[fMaxhits];
  Float_t               fRAW_xpost[fMaxhits];
  Float_t               fRAW_ypost[fMaxhits];
  Float_t               fRAW_zpost[fMaxhits];
  Float_t               fRAW_Energy[fMaxhits];

};

#endif

//---------------------------------------------------------------------------
