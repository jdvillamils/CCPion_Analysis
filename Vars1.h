#pragma once




namespace ana
{

//-------------CONTROL-------------------

const MultiVar kPiCvn([](const caf::SRProxy* sr){
	std::vector<double> cvn = {-5};
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          cvn.push_back(sr->vtx.elastic.fuzzyk.png[png].cvnpart.pionid);
	}
	return cvn;
 });

const MultiVar kPDG_PNG([](const caf::SRProxy* sr){
	std::vector<double> cvn = {-1000};
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          cvn.push_back(sr->vtx.elastic.fuzzyk.png[png].truth.pdg);
	}
	return cvn;
 });

 const NuTruthMultiVar kPDG_NT([](const caf::SRNeutrinoProxy*nu){
    int nPrims = nu->prim.size();
    std::vector<double> pdgs = {-1000};
    if(nPrims>0){
      for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
        pdgs.push_back(nu->prim[prim_idx].pdg);
      }
  }
    return pdgs;                                                                                                           
  }); 

  const MultiVar kPDG_NT_mvfntmv = MultiVarFromNuTruthMultiVar(kPDG_NT);

//track id
 const NuTruthMultiVar ktrkID_NT([](const caf::SRNeutrinoProxy*nu){
    int nPrims = nu->prim.size();
    std::vector<double> trk = {-1000};
    if(nPrims>0){
      for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
        trk.push_back(nu->prim[prim_idx].trkID);
      }
  }
    return trk;                                                                                                           
  }); 

const MultiVar ktrkID_NT_mvfntmv = MultiVarFromNuTruthMultiVar(ktrkID_NT);


const MultiVar ktrkID([](const caf::SRProxy* sr){
	std::vector<double> trkk = {-5};
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          trkk.push_back(sr->vtx.elastic.fuzzyk.png[png].truth.trkID);
	}
	return trkk;
 });
///--------NuTruth VARS *----------------------------------

//Neutrino energy information
const NuTruthMultiVar kNuE_NT([](const caf::SRNeutrinoProxy*nu){
  std::vector<double> nue = {-5};
  nue.push_back(nu->E);
  return nue;
});

const MultiVar kNuE_NT_mvfntmv = MultiVarFromNuTruthMultiVar(kNuE_NT);

//Vertex information
const NuTruthVar kVtxX_NT([](const caf::SRNeutrinoProxy*nu){                                                                                                                    
    double vtx = nu->vtx.x;
    return vtx;                                                                                                           
  }); 

const NuTruthVar kVtxY_NT([](const caf::SRNeutrinoProxy*nu){                                                                                                                    
    double vtx = nu->vtx.y;
    return vtx;                                                                                                           
  }); 

const NuTruthVar kVtxZ_NT([](const caf::SRNeutrinoProxy*nu){                                                                                                                    
    double vtx = nu->vtx.z;
    return vtx;                                                                                                           
  }); 

//num of primary particles

  const NuTruthVar knumPrim_NT([](const caf::SRNeutrinoProxy*nu)                                       
  {                                                                                                                    
    //bool is_numu=(nu->pdg==14);
    int nPrims = nu->prim.size();
    return nPrims;                                                                                                           
  }); 


 //Num of primary pions
  const NuTruthVar knumPi_NT([](const caf::SRNeutrinoProxy*nu)                                       
  {                                                                                                                    
    //bool is_numu=(nu->pdg==14);
    int nPrims = nu->prim.size();
    int nPi = 0;
    if(nPrims>0){
      for (int prim_idx = 0; prim_idx <nPrims;prim_idx++){
        
        if(abs(nu->prim[prim_idx].pdg)==211) nPi++;
      }
  }
    return nPi;                                                                                                           
  }); 

//All energies
const NuTruthMultiVar kE_NT([](const caf::SRNeutrinoProxy*nu)                                       
  {                                                                                                                     
    // returns energy of pi in event                                                               
    std::vector<double> piPE = {-10};                                                                                                                                                                                                               
                                                                                                                        
    int nPrims = nu->prim.size();                                                                                       
    for(int prim_idx = 0; prim_idx < nPrims; prim_idx++){                                                                                                                                                                                                                                         
      if(nPrims>0){  
        if(nu->prim[prim_idx].p.E>0){                                                                  
        piPE.push_back(nu->prim[prim_idx].p.E);
        }                                                                                                                                                           
      }// end of if() statement                                                                                         
    } // end of for() loop                                                                                              
    return piPE;                                                                                                                     
  }); 

  const MultiVar kE_NT_mvfntmv = MultiVarFromNuTruthMultiVar(kE_NT);

//Pion energies
const NuTruthMultiVar kPiE_NT([](const caf::SRNeutrinoProxy*nu)                                       
  {                                                                                                                     
    // returns energy of pi in event                                                               
    std::vector<double> piPE = {-10};                                                                                                                                                                                                               
                                                                                                                        
    int nPrims = nu->prim.size();                                                                                       
    for(int prim_idx = 0; prim_idx < nPrims; prim_idx++){                                                                                                                                                                                                                                         
      if(abs(nu->prim[prim_idx].pdg) == 211 && nPrims>0){  
        if(nu->prim[prim_idx].p.E>0){                                                                  
        piPE.push_back(nu->prim[prim_idx].p.E);
        }                                                                                                                                                           
      }// end of if() statement                                                                                         
    } // end of for() loop                                                                                              
    return piPE;                                                                                                                     
  }); 

const MultiVar kPiE_NT_mvfntmv = MultiVarFromNuTruthMultiVar(kPiE_NT);


//Visible Pion energies
const NuTruthMultiVar kVisE_NT([](const caf::SRNeutrinoProxy*nu)                                       
  {                                                                                                                     
    // returns energy of pi in event                                                               
    std::vector<double> piPE = {-10};                                                                                                                                                                                                               
                                                                                                                        
    int nPrims = nu->prim.size();                                                                                       
    for(int prim_idx = 0; prim_idx < nPrims; prim_idx++){                                                                                                                                                                                                                                          
        if(nu->prim[prim_idx].p.E>0){                                                                  
        piPE.push_back(nu->prim[prim_idx].visE);
        }                                                                                         
    } // end of for() loop                                                                                              
    return piPE;                                                                                                                     
  }); 

const MultiVar kVisE_NT_mvfntmv = MultiVarFromNuTruthMultiVar(kVisE_NT);

  //Angle wrt beam
  const NuTruthMultiVar kPionTheta_NT([](const caf::SRNeutrinoProxy* nu)
  {
    /*if(abs(nu->pdg) != 14 || !nu->iscc){
      return -5.0;
    }*/
    std::vector<double> thetavec = {-10};  
    int nPrims = nu->prim.size();
    for(int iprim = 0; iprim < nPrims; iprim++){
      if(abs(nu->prim[iprim].pdg) == 211){
        TVector3  pidir = nu->prim[iprim].p.Vect();
        TVector3 beamdir = NuMIBeamDirection(caf::kNEARDET);
        double costheta= pidir.Unit().Dot(beamdir.Unit());
        double angle = acos(costheta);
        thetavec.push_back(angle);
      }
    }
    return thetavec;
	});

const MultiVar kPionTheta_NT_mvfntmv = MultiVarFromNuTruthMultiVar(kPionTheta_NT);

  //angle wrt lepton
  const NuTruthMultiVar kPionAlpha_NT([](const caf::SRNeutrinoProxy* nu)
  {
    /*if(abs(nu->pdg) != 14 || !nu->iscc){
      return -5.0;
    }*/
    std::vector<double> anglevec = {-10};  
    int nPrims = nu->prim.size();
    TVector3  lepdir;
    TVector3  pidir;
    for(int iprim = 0; iprim < nPrims; iprim++){
      if(abs(nu->prim[iprim].pdg)==11 || abs(nu->prim[iprim].pdg)==13 || abs(nu->prim[iprim].pdg)==15){
        TVector3  lepdir = nu->prim[iprim].p.Vect();
        double lepdir_x = lepdir.X(); // x component
        anglevec.push_back(lepdir_x);
        double lepdir_y = lepdir.Y(); // y component
        anglevec.push_back(lepdir_y);
        double lepdir_z = lepdir.Z(); // z component
        anglevec.push_back(lepdir_z);
      }
    }

    for(int iprim = 0; iprim < nPrims; iprim++){
      if(abs(nu->prim[iprim].pdg) == 211){
        TVector3  pidir = nu->prim[iprim].p.Vect();
        double pidir_x = pidir.X(); // x component
        anglevec.push_back(pidir_x);
        double pidir_y = pidir.Y(); // y component
        anglevec.push_back(pidir_y);
        double pidir_z = pidir.Z(); // z component
        anglevec.push_back(pidir_z);
        //double costheta= pidir.Unit().Dot(lepdir.Unit());
        //double angle = acos(costheta);
        //anglevec.push_back(costheta);
        
    }
    }
    return anglevec;
    //return -5.0;
	});

  const MultiVar kPionAlpha_NT_mvfntmv = MultiVarFromNuTruthMultiVar(kPionAlpha_NT);


  const NuTruthVar run_NT([](const caf::SRNeutrinoProxy*nu){                                                                                               
   return nu->run;                                                                                                           
  }); 
  const NuTruthVar subrun_NT([](const caf::SRNeutrinoProxy*nu){                                                                                               
   return nu->subrun;                                                                                                           
  });   
  const NuTruthVar cycle_NT([](const caf::SRNeutrinoProxy*nu){                                                                                               
   return nu->cycle;                                                                                                           
  }); 
  const NuTruthVar evt_NT([](const caf::SRNeutrinoProxy*nu){                                                                                               
   return nu->evt;                                                                                                           
  }); 


  //--------------Reco variables------------------------------

//num prongs
const Var knumProng([](const caf::SRProxy *sr){                                                                                                                                                                              
    int num = 0;
	num = sr->vtx.elastic.fuzzyk.png.size();
	return num;                                                                                                                   
  }); 


//num of primary pions using png algr
const Var knumPi([](const caf::SRProxy *sr){                                                                                                                                                                              
    int num = 0;
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
        if(abs(sr->vtx.elastic.fuzzyk.png[png].truth.pdg)==211){
          num = num + 1;
	}}
	return num;                                                                                                                   
  }); 

//num tracks
  const Var knumTracks([](const caf::SRProxy *sr){                                                                                                                                                                              
    int num = 0;
	num = sr->trk.kalman.tracks.size();
	return num;                                                                                                                   
  }); 



 const MultiVar kcalEPNG([](const caf::SRProxy *sr){                                                                                                                                                                              
    std::vector<double> energy = {-5};
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          energy.push_back(sr->vtx.elastic.fuzzyk.png[png].calE);
	}
	return energy;                                                                                                                   
  }); 

//prong len

 const MultiVar kProngLength([](const caf::SRProxy *sr){                                                                                                                                                                              
    std::vector<double> length = {-1000};
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          length.push_back(sr->vtx.elastic.fuzzyk.png[png].len);
	}
	return length;                                                                                                                   
  }); 

//number of hits of prong
const MultiVar kProngnhits([](const caf::SRProxy *sr){                                                                                                                                                                              
    std::vector<double> nhits = {-1000};
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          nhits.push_back(sr->vtx.elastic.fuzzyk.png[png].nhit);
	}
	return nhits;                                                                                                                   
  }); 

//start coordinate of prong
 const MultiVar kStartProngCoor([](const caf::SRProxy *sr){                                                                                                                                                                              
    std::vector<double> coor = {-1000};
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          coor.push_back(sr->vtx.elastic.fuzzyk.png[png].start.x);
          coor.push_back(sr->vtx.elastic.fuzzyk.png[png].start.y);
          coor.push_back(sr->vtx.elastic.fuzzyk.png[png].start.z);
	}
	return coor;                                                                                                                   
  }); 

  //direction of prong
  const MultiVar kDirProng([](const caf::SRProxy *sr){                                                                                                                                                                              
    std::vector<double> dir = {-1000};
	    for(unsigned int png = 0; png < sr->vtx.elastic.fuzzyk.png.size(); png++){
          dir.push_back(sr->vtx.elastic.fuzzyk.png[png].dir.x);
          dir.push_back(sr->vtx.elastic.fuzzyk.png[png].dir.y);
          dir.push_back(sr->vtx.elastic.fuzzyk.png[png].dir.z);
	}
	return dir;                                                                                                                   
  }); 
//----MIXED ------------------------------

const Var DiffPrimPart_Prongs = VarFromNuTruthVar(knumPrim_NT) - knumProng;

const Var DiffPrimPi_RecoPi = VarFromNuTruthVar(knumPi_NT) - knumPi;

const Var DiffPrimPart_Tracks = VarFromNuTruthVar(knumPi_NT) - knumTracks;

const Var DiffProngs_Tracks = knumProng - knumTracks;

}