#pragma once

namespace ana
{


//Check cut - basic
const Cut checkCut([](const caf::SRProxy *sr){	
	if (sr->vtx.elastic.fuzzyk.png.size() == 0 || sr->mc.nu.size() == 0 || sr->trk.cosmic.tracks.size()==0 || sr->trk.kalman.tracks.size()==0 || sr->vtx.elastic.IsValid != true) return false;
	else return true;
  });

//Quality Cut
const Cut kNMMyQuality([](const caf::SRProxy* sr)  //kNumuMyQuality
			   {
			     return (sr->trk.kalman.ntracks > 0   &&
				     sr->slc.nhit           > 20  &&
				     sr->slc.ncontplanes    > 4);
 });

//Fiducial Cut
const NuTruthCut kMyFiducial_NT([](const caf::SRNeutrinoProxy* sr)
                                    {
             return (sr->vtx.X() <  160 &&  sr->vtx.X() >  -150 &&  sr->vtx.Y() >  -150 && sr->vtx.Y() <  160 && sr->vtx.Z() >  50 &&  sr->vtx.Z() <  1200 );
 });

}


//-------------------- ADDITIONAL CUTS --------------------------

  /*const Cut kIsCC ([](const caf::SRProxy *sr){
    if(sr->mc.nnu==0) return false;
    assert(sr->mc.nnu==1);
    bool isCC=sr->mc.nu[0].iscc;
    return isCC;});

    const NuTruthCut kIsNueCCST([](const caf::SRNeutrinoProxy* truth){
    return (truth->iscc &&  truth->pdg == 12);
    });
    
    const Cut kIsNueCC = CutFromNuTruthCut(kIsNueCCST);
*/


