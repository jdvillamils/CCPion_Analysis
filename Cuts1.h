#pragma once

namespace ana
{

const NuTruthCut kIsOneLepton_NT([](const caf::SRNeutrinoProxy*nu)
 {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
    if(abs(nu->prim[prim_idx].pdg)==11 || abs(nu->prim[prim_idx].pdg)==13 || abs(nu->prim[prim_idx].pdg)==15) nPi++;
  }
  return is_numu && (nPi==1);
 });

const NuTruthCut kIsNoPionCut_NT([](const caf::SRNeutrinoProxy*nu)
 {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){ 
    if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
  }
  return is_numu && (nPi==0);
 });

const NuTruthCut kIsPionCut_NT([](const caf::SRNeutrinoProxy*nu)
 {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
    if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
  }
  return is_numu && (nPi>0);
 });

const NuTruthCut kIs1PionCut_NT([](const caf::SRNeutrinoProxy*nu)
 {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
    if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
  }
  return is_numu && (nPi==1);
 });

const NuTruthCut kIs2PionCut_NT([](const caf::SRNeutrinoProxy*nu)
 {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
    
    if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
  }
  return is_numu && (nPi==2);
 });

const NuTruthCut kIs3PionCut_NT([](const caf::SRNeutrinoProxy*nu)
 {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
    
    if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
  }
  return is_numu && (nPi==3);
 });

const NuTruthCut kIs4PionCut_NT([](const caf::SRNeutrinoProxy*nu)
 {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
    
    if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
  }
  return is_numu && (nPi==4);
 });

const NuTruthCut kIs5PionCut_NT([](const caf::SRNeutrinoProxy*nu)
 {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
    
    if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
  }
  return is_numu && (nPi==5);
 });

const NuTruthCut kIs6PionCut_NT([](const caf::SRNeutrinoProxy*nu)
  {
  bool is_numu=(nu->pdg==14);
  int nPrims = nu->prim.size();
  int nPi = 0;
  for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
    
    if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
  }
  return is_numu && (nPi==6);
  });
//


const NuTruthCut kTruthContainedND_NT([](const caf::SRNeutrinoProxy*nu)
{//if(nu->nnu==0) return false;
if(fabs(nu->vtx.x) > 200|| fabs(nu->vtx.y) > 200 || nu->vtx.z < 0|| nu->vtx.z > 1650) return false;
return true;});



const Cut kIs1PionCut([](const caf::SRProxy* sr)  
 {
  double npi = 0;
        for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          if(abs(sr->vtx.elastic.fuzzyk.png[png].truth.pdg)==211){
            npi++;;
    }}
    return (npi==1);
 });

 const Cut kIs2PionCut([](const caf::SRProxy* sr)  
 {
  double npi = 0;
        for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          if(abs(sr->vtx.elastic.fuzzyk.png[png].truth.pdg)==211){
            npi++;;
    }}
    return (npi==2);
 });

 const Cut kIs3PionCut([](const caf::SRProxy* sr)  
 {
  double npi = 0;
        for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          if(abs(sr->vtx.elastic.fuzzyk.png[png].truth.pdg)==211){
            npi++;;
    }}
    return (npi==3);
 });

 const Cut kIs4PionCut([](const caf::SRProxy* sr)  
 {
  double npi = 0;
        for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          if(abs(sr->vtx.elastic.fuzzyk.png[png].truth.pdg)==211){
            npi++;;
    }}
    return (npi==4);
 });

 const Cut kIs5PionCut([](const caf::SRProxy* sr)  
 {
  double npi = 0;
        for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          if(abs(sr->vtx.elastic.fuzzyk.png[png].truth.pdg)==211){
            npi++;;
    }}
    return (npi==5);
 });

 const Cut kIs6PionCut([](const caf::SRProxy* sr)  
 {
  double npi = 0;
        for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          if(abs(sr->vtx.elastic.fuzzyk.png[png].truth.pdg)==211){
            npi++;;
    }}
    return (npi==6);
 });

}