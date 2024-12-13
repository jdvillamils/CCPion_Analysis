//Luckly the start of the final

#include "CAFAna/Core/Binning.h"
#include "CAFAna/Cuts/Cuts.h"
#include "CAFAna/Core/Spectrum.h"
#include "CAFAna/Core/SpectrumLoader.h"
#include "CAFAna/Vars/Vars.h"
#include "CAFAna/Core/Cut.h"
#include "CAFAna/Vars/Vars.h"
#include "CAFAna/Core/Cut.cxx"
#include "3FlavorAna/Cuts/NumuCuts.h"
#include "3FlavorAna/Cuts/NumuCuts2020.h"
#include "CAFAna/Core/MultiVar.h"
#include "CAFAna/Core/MultiVar.cxx"
#include "CAFAna/Core/HistAxis.h"
#include "CAFAna/Cuts/SpillCuts.h"
#include "StandardRecord/Proxy/SRProxy.h"
#include "3FlavorAna/Cuts/OverlayCuts.h"
#include "CAFAna/Core/Instantiations.cxx"
#include "CAFAna/Core/EventList.h"


#include "BasicCuts.h"
#include "Vars1.h"
#include "Cuts1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2.h"
#include <math.h>
#include <stdio.h>


#include<iostream>  

using namespace ana;


//----------INTERACTION CUT
  //Not defined in the Novasoft....
const NuTruthCut kIsMEC_NT([](const caf::SRNeutrinoProxy* nu){                           
        return (nu->mode==caf::kMEC); //MEC                        
  });  

  const NuTruthCut kIsCC_NT([](const caf::SRNeutrinoProxy *nu){if(nu->iscc) return true;else return false;});
  const NuTruthCut kIsOther_NT = !kIsQE_NT && !kIsRes_NT && !kIsDIS_NT && !kIsMEC_NT;
  const NuTruthCut InteractionCut = kNoCut_NT && kIsCC_NT; //kIsQE_NT; kIsMEC_NT; kIsRes_NT; kIsDIS_NT; kIsOther_NT; kNoCut_NT;

//


//---------------------------------------MAIN------------------------------------


void mainMEC()
{

const std::string fname = "prod_caf_25000_files_JDV"; //"prod_caf_4000_files_JDV_1";
//const std::string fname = "prod_caf_R20-11-25-prod5.1reco.a_nd_genie_N1810j0211a_nonswap_fhc_nova_v08_full_v1";

//---------------NuTruth Simulation part -----------------------
//Neutrino energy
MultiVar nuENT = kNuE_NT_mvfntmv;
std::vector<const MultiVar *> nuevarsNT = {&nuENT};

//vertex
Var vtxxNT = VarFromNuTruthVar(kVtxX_NT);
Var vtxyNT = VarFromNuTruthVar(kVtxY_NT);
Var vtxzNT = VarFromNuTruthVar(kVtxZ_NT);
//counting
Var numprimNT = VarFromNuTruthVar(knumPrim_NT);
Var numpiNT = VarFromNuTruthVar(knumPi_NT);

std::vector<const Var *> numpivtxvarsNT = {&numprimNT, &numpiNT, &vtxxNT, &vtxyNT, &vtxzNT};

//Energies
MultiVar energiesNT = kPiE_NT_mvfntmv;
std::vector<const MultiVar *> energiesvarsNT = {&energiesNT};
MultiVar energiesALLNT = kE_NT_mvfntmv;
std::vector<const MultiVar *> energiesALLvarsNT = {&energiesALLNT};
MultiVar visenergiesALLNT = kVisE_NT_mvfntmv;
std::vector<const MultiVar *> visenergiesALLvarsNT = {&visenergiesALLNT};


//Angles
MultiVar thetaNT = kPionTheta_NT_mvfntmv;
std::vector<const MultiVar *> thetavarsNT = {&thetaNT};
MultiVar alphaNT = kPionAlpha_NT_mvfntmv;
std::vector<const MultiVar *> alphavarsNT = {&alphaNT};

//run subrun info for event display
 Var kRun    = VarFromNuTruthVar(run_NT);
 Var kSubrun = VarFromNuTruthVar(subrun_NT);
 Var kCycle  = VarFromNuTruthVar(cycle_NT);
 Var kEvt    = VarFromNuTruthVar(evt_NT);

 std::vector<const Var *> runvars = {&kRun, &kSubrun, &kCycle, &kEvt, &kSlc};


 //------------Reco info---------------------

 Var numprongs = knumProng;
 Var diffprimprongs = DiffPrimPart_Prongs;
 Var numpi = knumPi;
 Var diffprimpirecopi = DiffPrimPi_RecoPi;
 Var numtracks = knumTracks;
 Var diffprimparttracks = DiffPrimPart_Tracks;
 Var diffprongstracks = DiffProngs_Tracks;

 std::vector<const Var *> recovars = {&numprongs, &diffprimprongs, &numpi, &diffprimpirecopi, &numtracks, &diffprimparttracks, &diffprongstracks};

//energies

MultiVar calenergies = kcalEPNG;
std::vector<const MultiVar *> calenergiesvars = {&calenergies};

//length
MultiVar pronglength = kProngLength;
std::vector<const MultiVar *> pronglengthvars = {&pronglength};

//nhits
MultiVar pronghits = kProngnhits;
std::vector<const MultiVar *> pronghitshvars = {&pronghits};

//coordinates start prong
MultiVar coorstart = kStartProngCoor;
std::vector<const MultiVar *> coorstartvars = {&coorstart};

//Prong directions
MultiVar dirprong = kDirProng;
std::vector<const MultiVar *> dirprongtvars = {&dirprong};


//------------ CONTROL INFO -----------------------

MultiVar pdgnt = kPDG_NT_mvfntmv;
MultiVar pdgpng = kPDG_PNG;
MultiVar cvn = kPiCvn;
MultiVar trkNT = ktrkID_NT_mvfntmv;
MultiVar trk = ktrkID;

std::vector<const MultiVar *> pdgntvars = {&pdgnt};
std::vector<const MultiVar *> pdgpngvars = {&pdgpng};
std::vector<const MultiVar *> cvnvars = {&cvn};
std::vector<const MultiVar *> trkNTvars = {&trkNT};
std::vector<const MultiVar *> trkvars = {&trk};




//----------------MAKELISTS------------------------------

//neutrino energy
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"nuevarsNT.txt"}, nuevarsNT, &kStandardSpillCuts);
//first three vector NT
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"numpivtxvarsNT.txt"}, numpivtxvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"thetavarsNT.txt"}, thetavarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"alphavarsNT.txt"}, alphavarsNT, &kStandardSpillCuts);

//runvars
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"runvars.txt"}, runvars, &kStandardSpillCuts);

//Energies NT
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"energiesvarsNT.txt"}, energiesvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"energiesALLvarsNT.txt"}, energiesALLvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"visenergiesALLvarsNT.txt"}, visenergiesALLvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIs1PionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"energies1varsNT.txt"}, energiesvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIs2PionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"energies2varsNT.txt"}, energiesvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIs3PionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"energies3varsNT.txt"}, energiesvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIs4PionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"energies4varsNT.txt"}, energiesvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIs5PionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"energies5varsNT.txt"}, energiesvarsNT, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIs6PionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"energies6varsNT.txt"}, energiesvarsNT, &kStandardSpillCuts);

//recovars
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"recovars.txt"}, recovars, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"pronglengthvars.txt"}, pronglengthvars, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"pronghitshvars.txt"}, pronghitshvars, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"coorstartvars.txt"}, coorstartvars, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"dirprongtvars.txt"}, dirprongtvars, &kStandardSpillCuts);

//reco energies
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"calenergiesvars.txt"}, calenergiesvars, &kStandardSpillCuts);

//control 
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"pdgntvars.txt"}, pdgntvars, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"pdgpngvars.txt"}, pdgpngvars, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"cvnvars.txt"}, cvnvars, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"trkNTvars.txt"}, trkNTvars, &kStandardSpillCuts);
MakeTextListFile(fname, {checkCut && kContained && CutFromNuTruthCut(kMyFiducial_NT) && CutFromNuTruthCut(kTruthContainedND_NT) && CutFromNuTruthCut(kIsOneLepton_NT) && CutFromNuTruthCut(kIsPionCut_NT) && CutFromNuTruthCut(InteractionCut)}, {"trkvars.txt"}, trkvars, &kStandardSpillCuts);
}