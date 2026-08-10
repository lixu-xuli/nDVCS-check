#ifndef _SAVEDVCS_H
#define _SAVEDVCS_H

#include "saveTree.h"

class recSingleElEvent
{
	public:
		recSingleElEvent(Int_t paraIsProton, Int_t paraIsMC, Int_t paraIsPreCut, Float_t paraEBeam = 10.6): isProton(paraIsProton), isMC(paraIsMC), isPreCut(paraIsPreCut), EBeam(paraEBeam) {};
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
		bool findBest(const vector<recParticle> &elVect, const vector<elDeteInfo> &elDeteVect) {
			nElectron = elVect.size();
			elIndex = -1;
			double maxP = 0;
			for (Int_t iEl=0; iEl<nElectron; iEl++) {
				if (elVect[iEl].status < 0 && elVect[iEl].P > maxP) {
					maxP = elVect[iEl].P;
					elIndex = iEl;
				}
			}
			if (elIndex!=-1) {
				elPart = elVect[elIndex];
				elDete = elDeteVect[elIndex];
				singleEl bestSingleEl(elBeam, nuTarget, elPart.PVec);
				myRecSingleEl = bestSingleEl;
				return true;
			}
			return false;
		};
		singleEl myRecSingleEl;
		recParticle elPart;
		elDeteInfo elDete;
		Int_t runNumber;
		Long_t eventNumber;
    	Int_t helicity;
		Long_t hipoIndex;
		Int_t isProton;
		Int_t isMC;
		Int_t isPreCut;
		Int_t elIndex;
    	Int_t nElectron;
		Float_t EBeam;
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
};

class recSingleElTree: public preTree
{
	public:
		recSingleElTree(TString name, Int_t isProton, Int_t isPreCut): preTree(name), myEvent(isProton, 0, isPreCut) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isProton, myEvent.isMC, myEvent.isPreCut, myEvent.EBeam);
			addRecPartBranch("el", myEvent.elPart);
			addElDeteBranch("el", myEvent.elDete);
			addSingleElBranch("", myEvent.myRecSingleEl);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<elDeteInfo> &elDeteVect) {
			if (myEvent.findBest(elVect, elDeteVect)) {
				myTTree.Fill();
			}
		};
		recSingleElEvent myEvent;
};

class recDVCSEvent
{
	public:
		recDVCSEvent(Int_t paraIsProton, Int_t paraIsMC, Int_t paraIsPreCut, Float_t paraEBeam = 10.6): isProton(paraIsProton), isMC(paraIsMC), isPreCut(paraIsPreCut), EBeam(paraEBeam) {};
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
			phIndex = -1;
			for (Int_t iEl=0; iEl<nElectron; iEl++) {
				if (elVect[iEl].P < 1)  continue;
				for (Int_t iNu=0; iNu<nNucleon; iNu++) {
					if (nuVect[iNu].P < 0.3)  continue;
					for (Int_t iPh=0; iPh<nPhoton; iPh++) {
						if (phVect[iPh].P < 2)  continue;
						Float_t exclChi = DVCS::getExcl4DChi2(elBeam, nuTarget, elVect[iEl].PVec, nuVect[iNu].PVec, phVect[iPh].PVec);
						if (exclChi < excl4DChi2) {
							excl4DChi2 = exclChi;
							elIndex = iEl;
							nuIndex = iNu;
							phIndex = iPh;
						}
					}
				}
			}
			if (elIndex!=-1 && nuIndex!=-1 && phIndex!=-1) {
				elPart = elVect[elIndex];
				nuPart = nuVect[nuIndex];
				phPart = phVect[phIndex];
				elDete = elDeteVect[elIndex];
				nuDete = nuDeteVect[nuIndex];
				phDete = phDeteVect[phIndex];
				trackCVT = trackCVTInfo;
				clusterCTOF = clusterCTOFInfo;
				trackCND = trackCNDInfo;
				clusterCAL = clusterCALInfo;
				DVCS bestDVCS(elBeam, nuTarget, elPart.PVec, nuPart.PVec, phPart.PVec);
				myRecDVCS = bestDVCS;
				if (isPreCut) {
					if (myRecDVCS.mM2ed2engX<-1.0 || myRecDVCS.mM2ed2engX>4.0)  return false;
					if (myRecDVCS.mPed2engX>1.5)  return false;
				}
				return true;
			}
			return false;
		};
		DVCS myRecDVCS;
		recParticle elPart;
		recParticle nuPart;
		recParticle phPart;
		elDeteInfo elDete;
		nuDeteInfo nuDete;
		phDeteInfo phDete;
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
		Int_t phIndex;
    	Int_t nElectron;
    	Int_t nNucleon;
    	Int_t nPhoton;
		Float_t EBeam;
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
};

class mcDVCSEvent
{
	public:
		mcDVCSEvent(Float_t paraEBeam = 10.6) {
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
			if (mcPartVect.size() != 3 && mcPartVect.size() != 4) {
				cout << eventNumber << " " << hipoIndex << endl;
				cout << "Number of MC particles is " << mcPartVect.size() << endl;
				return false;
			}
			elPart = mcPartVect[0];
			mcPartInfo newInfo = {0};
			if (mcPartVect.size() == 4) {
				spPart = mcPartVect[1];
				acPart = mcPartVect[2];
				phPart = mcPartVect[3];
			}
			else if (mcPartVect.size() == 3) {
				spPart = mcParticle(newInfo, -1);
				acPart = mcPartVect[1];
				phPart = mcPartVect[2];
			}
			if (acPart.pid == 2212) {
				isProton = 1;
				DVCS mcDVCS(elBeam, prTarget, elPart.PVec, acPart.PVec, phPart.PVec);
				myMCDVCS = mcDVCS;
				return true;
			}
			else if (acPart.pid == 2112) {
				isProton = 0;
				DVCS mcDVCS(elBeam, neTarget, elPart.PVec, acPart.PVec, phPart.PVec);
				myMCDVCS = mcDVCS;
				return true;
			}
			else {
				cout << "No proton or neutron!" << endl;
				return false;
			}
		};
		DVCS myMCDVCS;
		mcParticle elPart;
		mcParticle spPart;
		mcParticle acPart;
		mcParticle phPart;
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

class recDVCSTree: public preTree
{
	public:
		recDVCSTree(TString name, Int_t isProton, Int_t isPreCut): preTree(name), myEvent(isProton, 0, isPreCut) {
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
			addRecPartBranch("ph", myEvent.phPart);
			addPhDeteBranch("ph", myEvent.phDete);
			addDVCSBranch("", myEvent.myRecDVCS);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<phDeteInfo> &phDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myEvent.findBest(elVect, nuVect, phVect, elDeteVect, nuDeteVect, phDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				myTTree.Fill();
			}
		};
		recDVCSEvent myEvent;
};

class mcDVCSTree: public preTree
{
	public:
		mcDVCSTree(TString name, Float_t EBeam): preTree(name), myEvent(EBeam) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isProton, myEvent.isMC, myEvent.isPreCut, myEvent.EBeam);
			addMCPartBranch("el_true", myEvent.elPart);
			addMCPartBranch("sp_true", myEvent.spPart);
			addMCPartBranch("ac_true", myEvent.acPart);
			addMCPartBranch("ph_true", myEvent.phPart);
			addDVCSBranch("true_", myEvent.myMCDVCS);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<mcParticle> &mcPartVect) {
			if (myEvent.setParticle(mcPartVect)) {
				myTTree.Fill();
			}
		};
		mcDVCSEvent myEvent;
};

class mcRecSingleElTree: public preTree
{
	public:
		mcRecSingleElTree(TString name, Int_t isProton, Float_t EBeam): preTree(name), myRecEvent(isProton, 2, 0, EBeam), myMCEvent(EBeam) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myRecEvent.runNumber, myRecEvent.eventNumber, myRecEvent.helicity, myRecEvent.hipoIndex, myRecEvent.isProton, myRecEvent.isMC, myRecEvent.isPreCut, myRecEvent.EBeam);
			addRecPartBranch("el", myRecEvent.elPart);
			addElDeteBranch("el", myRecEvent.elDete);
			addSingleElBranch("", myRecEvent.myRecSingleEl);
			addMCPartBranch("el_true", myMCEvent.elPart);
			addMCPartBranch("sp_true", myMCEvent.spPart);
			addMCPartBranch("ac_true", myMCEvent.acPart);
			addMCPartBranch("ph_true", myMCEvent.phPart);
			addDVCSBranch("true_", myMCEvent.myMCDVCS);
		};
		void initialEvent(globalInfo paraInfo) {
			myRecEvent.initial(paraInfo);
			myMCEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<mcParticle> &mcVect, const vector<elDeteInfo> &elDeteVect) {
			if (myRecEvent.findBest(elVect, elDeteVect)) {
				if (myMCEvent.setParticle(mcVect)) {
					myTTree.Fill();
				}
			}
		};
		recSingleElEvent myRecEvent;
		mcDVCSEvent myMCEvent;
};

class mcRecDVCSTree: public preTree
{
	public:
		mcRecDVCSTree(TString name, Int_t isProton, Float_t EBeam): preTree(name), myRecEvent(isProton, 2, 0, EBeam), myMCEvent(EBeam) {
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
			addMCPartBranch("ph_true", myMCEvent.phPart);
			addDVCSBranch("true_", myMCEvent.myMCDVCS);
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
		mcDVCSEvent myMCEvent;
};

#endif
