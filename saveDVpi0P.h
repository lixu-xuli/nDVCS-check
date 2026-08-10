#ifndef _SAVEDVPI0P_H
#define _SAVEDVPI0P_H

#include "saveDVCS.h"

class recDVpi0PEvent
{
	public:
		recDVpi0PEvent(Int_t paraIsProton, Int_t paraIsMC, Int_t paraIsPreCut, Float_t paraEBeam = 10.6): isProton(paraIsProton), isMC(paraIsMC), isPreCut(paraIsPreCut), EBeam(paraEBeam) {};
		void initial(globalInfo paraInfo) {
			runNumber = paraInfo.runNumber;
			eventNumber = paraInfo.eventNumber;
			helicity = paraInfo.helicity;
			hipoIndex = paraInfo.hipoIndex;
			setEBeam();
			if (isProton)  nuTarget = prTarget;
			else  nuTarget = neTarget;
		};
		void setEBeam() {
			if (isMC == 0) {
				EBeam = 10.2;
				if (runNumber < 6420)  EBeam = 10.6;
				else if (runNumber > 10000)  EBeam = 10.4;
			}
			elBeam.SetPxPyPzE(0, 0, EBeam, EBeam);
		};
		bool findBest(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<phDeteInfo> &phDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			nElectron = elVect.size();
			nNucleon = nuVect.size();
			nPhoton = phVect.size();
			Float_t excl4DChi2 = 1e9;
			elIndex = -1;
			nuIndex = -1;
			ph1Index = -1;
			ph2Index = -1;
			for (Int_t iEl=0; iEl<nElectron; iEl++) {
				if (elVect[iEl].P < 1)  continue;
				for (Int_t iNu=0; iNu<nNucleon; iNu++) {
					if (nuVect[iNu].P < 0.3)  continue;
					for (Int_t iPh1=0; iPh1<nPhoton; iPh1++) {
						if (phVect[iPh1].P < 0.3)  continue;
						for (Int_t iPh2=iPh1+1; iPh2<nPhoton; iPh2++) {
							if (phVect[iPh2].P < 0.3)  continue;
							Float_t deltaM = (phVect[iPh1].PVec + phVect[iPh2].PVec).M() - pi0Mass;
							if (abs(deltaM) > pi0Mass)  continue;
							Float_t exclChi = DVpi0P::getExcl4DChi2(elBeam, nuTarget, elVect[iEl].PVec, nuVect[iNu].PVec, phVect[iPh1].PVec, phVect[iPh2].PVec);
							if (exclChi < excl4DChi2) {
								excl4DChi2 = exclChi;
								elIndex = iEl;
								nuIndex = iNu;
								ph1Index = iPh1;
								ph2Index = iPh2;
							}
						}
					}
				}
			}
			if (elIndex!=-1 && nuIndex!=-1 && ph1Index!=-1 && ph2Index!=-1) {
				elPart = elVect[elIndex];
				nuPart = nuVect[nuIndex];
				ph1Part = phVect[ph1Index];
				ph2Part = phVect[ph2Index];
				elDete = elDeteVect[elIndex];
				nuDete = nuDeteVect[nuIndex];
				ph1Dete = phDeteVect[ph1Index];
				ph2Dete = phDeteVect[ph2Index];
				trackCVT = trackCVTInfo;
				clusterCTOF = clusterCTOFInfo;
				trackCND = trackCNDInfo;
				clusterCAL = clusterCALInfo;
				DVpi0P bestDVpi0P(elBeam, nuTarget, elPart.PVec, nuPart.PVec, ph1Part.PVec, ph2Part.PVec);
				myRecDVpi0P = bestDVpi0P;
				if (isPreCut) {
					if (myRecDVpi0P.mM2ed2enggX<-1.0 || myRecDVpi0P.mM2ed2enggX>4.0)  return false;
					if (myRecDVpi0P.mPed2enggX>1.5)  return false;
				}
				if (nuPart.status<3000 || nuPart.status>6000)  return false;
				return true;
			}
			return false;
		};
		DVpi0P myRecDVpi0P;
		recParticle elPart;
		recParticle nuPart;
		recParticle ph1Part;
		recParticle ph2Part;
		elDeteInfo elDete;
		nuDeteInfo nuDete;
		phDeteInfo ph1Dete;
		phDeteInfo ph2Dete;
		CVTInfo trackCVT;
		CTOFInfo clusterCTOF;
		CNDInfo trackCND;
		CALInfo clusterCAL;
		Int_t runNumber;
		Long_t eventNumber;
    	Int_t helicity;
		Long_t hipoIndex;
		Int_t isProton;
		Int_t isMC;
		Int_t isPreCut;
		Int_t elIndex;
		Int_t nuIndex;
		Int_t ph1Index;
		Int_t ph2Index;
    	Int_t nElectron;
    	Int_t nNucleon;
    	Int_t nPhoton;
		Float_t EBeam;
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
};

class mcDVpi0PEvent
{
	public:
		mcDVpi0PEvent(Float_t paraEBeam = 10.6) {
			isMC = 1;
			isPreCut = 0;
			EBeam = paraEBeam;
			elBeam.SetPxPyPzE(0, 0, EBeam, EBeam);
		};
		void initial(globalInfo paraInfo) {
			runNumber = paraInfo.runNumber;
			eventNumber = paraInfo.eventNumber;
			helicity = paraInfo.helicity;
			hipoIndex = paraInfo.hipoIndex;
		};
		bool setParticle(const vector<mcParticle> &mcPartVect) {
			if (mcPartVect.size() != 4 && mcPartVect.size() != 5 && mcPartVect.size() != 6) {
				cout << eventNumber << " " << hipoIndex << endl;
				cout << "Number of MC particles is " << mcPartVect.size() << endl;
				return false;
			}
			elPart = mcPartVect[0];
			mcPartInfo newInfo = {0};
			if (mcPartVect.size() == 4) {
				spPart = mcParticle(newInfo, -1);
				acPart = mcPartVect[1];
				ph1Part = mcPartVect[2];
				ph2Part = mcPartVect[3];
				el1Part = mcParticle(newInfo, -1);
				el2Part = mcParticle(newInfo, -1);
			}
			else if (mcPartVect.size() == 5) {
				spPart = mcPartVect[1];
				acPart = mcPartVect[2];
				ph1Part = mcPartVect[3];
				ph2Part = mcPartVect[4];
				el1Part = mcParticle(newInfo, -1);
				el2Part = mcParticle(newInfo, -1);
			}
			else if (mcPartVect.size() == 6) {
				spPart = mcPartVect[1];
				acPart = mcPartVect[2];
				ph1Part = mcPartVect[3];
				el1Part = mcPartVect[4];
				el2Part = mcPartVect[5];
				newInfo.pid = 22;
				newInfo.px = el1Part.px + el2Part.px;
				newInfo.py = el1Part.py + el2Part.py;
				newInfo.pz = el1Part.pz + el2Part.pz;
				ph2Part = mcParticle(newInfo, -1);
			}
			if (acPart.pid == 2212) {
				isProton = 1;
				DVpi0P mcDVpi0P(elBeam, prTarget, elPart.PVec, acPart.PVec, ph1Part.PVec, ph2Part.PVec);
				myMCDVpi0P = mcDVpi0P;
				return true;
			}
			else if (acPart.pid == 2112) {
				isProton = 0;
				DVpi0P mcDVpi0P(elBeam, neTarget, elPart.PVec, acPart.PVec, ph1Part.PVec, ph2Part.PVec);
				myMCDVpi0P = mcDVpi0P;
				return true;
			}
			else {
				cout << "No proton or neutron!" << endl;
				return false;
			}
		};
		DVpi0P myMCDVpi0P;
		mcParticle elPart;
		mcParticle spPart;
		mcParticle acPart;
		mcParticle ph1Part;
		mcParticle ph2Part;
		mcParticle el1Part;
		mcParticle el2Part;
		Int_t runNumber;
		Long_t eventNumber;
    	Int_t helicity;
		Long_t hipoIndex;
		Int_t isProton;
		Int_t isMC;
		Int_t isPreCut;
		Float_t EBeam;
		ROOT::Math::PxPyPzEVector elBeam;
};

class recDVpi0PTree: public preTree
{
	public:
		recDVpi0PTree(TString name, Int_t isProton, Int_t isPreCut): preTree(name), myEvent(isProton, 0, isPreCut) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isProton, myEvent.isMC, myEvent.isPreCut, myEvent.EBeam, myEvent.nElectron, myEvent.nNucleon, myEvent.nPhoton);
			addRecPartBranch("el", myEvent.elPart);
			addElDeteBranch("el", myEvent.elDete);
			addRecPartBranch("nu", myEvent.nuPart);
			addNuDeteBranch("nu", myEvent.nuDete, myEvent.isProton);
			addCVTBranch(myEvent.trackCVT);
			addCTOFBranch(myEvent.clusterCTOF);
			addCNDBranch(myEvent.trackCND);
			addCALBranch(myEvent.clusterCAL);
			addRecPartBranch("ph1", myEvent.ph1Part);
			addPhDeteBranch("ph1", myEvent.ph1Dete);
			addRecPartBranch("ph2", myEvent.ph2Part);
			addPhDeteBranch("ph2", myEvent.ph2Dete);
			addDVpi0PBranch("", myEvent.myRecDVpi0P);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<phDeteInfo> &phDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myEvent.findBest(elVect, nuVect, phVect, elDeteVect, nuDeteVect, phDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				myTTree.Fill();
			}
		};
		recDVpi0PEvent myEvent;
};

class mcDVpi0PTree: public preTree
{
	public:
		mcDVpi0PTree(TString name, Float_t EBeam): preTree(name), myEvent(EBeam) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isProton, myEvent.isMC, myEvent.isPreCut, myEvent.EBeam);
			addMCPartBranch("el_true", myEvent.elPart);
			addMCPartBranch("sp_true", myEvent.spPart);
			addMCPartBranch("ac_true", myEvent.acPart);
			addMCPartBranch("ph1_true", myEvent.ph1Part);
			addMCPartBranch("ph2_true", myEvent.ph2Part);
			addMCPartBranch("el1_true", myEvent.el1Part);
			addMCPartBranch("el2_true", myEvent.el2Part);
			addDVpi0PBranch("true_", myEvent.myMCDVpi0P);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<mcParticle> &mcPartVect) {
			if (myEvent.setParticle(mcPartVect)) {
				myTTree.Fill();
			}
		};
		mcDVpi0PEvent myEvent;
};

class mcRecDVpi0PTree: public preTree
{
	public:
		mcRecDVpi0PTree(TString name, Int_t isProton, Float_t EBeam): preTree(name), myRecEvent(isProton, 2, 0, EBeam) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myRecEvent.runNumber, myRecEvent.eventNumber, myRecEvent.helicity, myRecEvent.hipoIndex, myRecEvent.isProton, myRecEvent.isMC, myRecEvent.isPreCut, myRecEvent.EBeam, myRecEvent.nElectron, myRecEvent.nNucleon, myRecEvent.nPhoton);
			addRecPartBranch("el", myRecEvent.elPart);
			addElDeteBranch("el", myRecEvent.elDete);
			addRecPartBranch("nu", myRecEvent.nuPart);
			addNuDeteBranch("nu", myRecEvent.nuDete, myRecEvent.isProton);
			addCVTBranch(myRecEvent.trackCVT);
			addCTOFBranch(myRecEvent.clusterCTOF);
			addCNDBranch(myRecEvent.trackCND);
			addCALBranch(myRecEvent.clusterCAL);
			addRecPartBranch("ph1", myRecEvent.ph1Part);
			addPhDeteBranch("ph1", myRecEvent.ph1Dete);
			addRecPartBranch("ph2", myRecEvent.ph2Part);
			addPhDeteBranch("ph2", myRecEvent.ph2Dete);
			addDVpi0PBranch("", myRecEvent.myRecDVpi0P);
			addMCPartBranch("el_true", myMCEvent.elPart);
			addMCPartBranch("sp_true", myMCEvent.spPart);
			addMCPartBranch("ac_true", myMCEvent.acPart);
			addMCPartBranch("ph1_true", myMCEvent.ph1Part);
			addMCPartBranch("ph2_true", myMCEvent.ph2Part);
			addMCPartBranch("el1_true", myMCEvent.el1Part);
			addMCPartBranch("el2_true", myMCEvent.el2Part);
			addDVpi0PBranch("true_", myMCEvent.myMCDVpi0P);
		};
		void initialEvent(globalInfo paraInfo) {
			myRecEvent.initial(paraInfo);
			myMCEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &phVect, const vector<mcParticle> &mcVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<phDeteInfo> &phDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myRecEvent.findBest(elVect, nuVect, phVect, elDeteVect, nuDeteVect, phDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				if (myMCEvent.setParticle(mcVect)) {
					myTTree.Fill();
				}
			}
		};
		recDVpi0PEvent myRecEvent;
		mcDVpi0PEvent myMCEvent;
};

class mcRecMisDVCSTree: public preTree
{
	public:
		mcRecMisDVCSTree(TString name, Int_t isProton, Float_t EBeam): preTree(name), myRecEvent(isProton, 2, 0, EBeam), myMCEvent(EBeam) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myRecEvent.runNumber, myRecEvent.eventNumber, myRecEvent.helicity, myRecEvent.hipoIndex, myRecEvent.isProton, myRecEvent.isMC, myRecEvent.isPreCut, myRecEvent.EBeam, myRecEvent.nElectron, myRecEvent.nNucleon, myRecEvent.nPhoton);
			addRecPartBranch("el", myRecEvent.elPart);
			addElDeteBranch("el", myRecEvent.elDete);
			addRecPartBranch("nu", myRecEvent.nuPart);
			addNuDeteBranch("nu", myRecEvent.nuDete, myRecEvent.isProton);
			addCVTBranch(myRecEvent.trackCVT);
			addCTOFBranch(myRecEvent.clusterCTOF);
			addCNDBranch(myRecEvent.trackCND);
			addCALBranch(myRecEvent.clusterCAL);
			addRecPartBranch("ph", myRecEvent.phPart);
			addPhDeteBranch("ph", myRecEvent.phDete);
			addDVCSBranch("", myRecEvent.myRecDVCS);
			addMCPartBranch("el_true", myMCEvent.elPart);
			addMCPartBranch("sp_true", myMCEvent.spPart);
			addMCPartBranch("ac_true", myMCEvent.acPart);
			addMCPartBranch("ph1_true", myMCEvent.ph1Part);
			addMCPartBranch("ph2_true", myMCEvent.ph2Part);
			addMCPartBranch("el1_true", myMCEvent.el1Part);
			addMCPartBranch("el2_true", myMCEvent.el2Part);
			addDVpi0PBranch("true_", myMCEvent.myMCDVpi0P);
		};
		void initialEvent(globalInfo paraInfo) {
			myRecEvent.initial(paraInfo);
			myMCEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &phVect, const vector<mcParticle> &mcVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<phDeteInfo> &phDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myRecEvent.findBest(elVect, nuVect, phVect, elDeteVect, nuDeteVect, phDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				if (myMCEvent.setParticle(mcVect)) {
					myTTree.Fill();
				}
			}
		};
		recDVCSEvent myRecEvent;
		mcDVpi0PEvent myMCEvent;
};

#endif
