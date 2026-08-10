#ifndef _SAVEDVPIPP_H
#define _SAVEDVPIPP_H

#include "saveDVCS.h"

class recDVpipPEvent
{
	public:
		recDVpipPEvent(Int_t paraIsMC, Float_t paraEBeam = 10.6): isMC(paraIsMC), EBeam(paraEBeam) {};
		void initial(globalInfo paraInfo) {
			runNumber = paraInfo.runNumber;
			eventNumber = paraInfo.eventNumber;
			helicity = paraInfo.helicity;
			hipoIndex = paraInfo.hipoIndex;
			setEBeam();
			nuTarget = prTarget;
		};
		void setEBeam() {
			if (isMC == 0) {
				EBeam = 10.2;
				if (runNumber < 5600)  EBeam = 10.6;
				else if (runNumber >= 5681 && runNumber <= 5870)  EBeam = 7.546;
				else if (runNumber >= 5875 && runNumber <= 6000)  EBeam = 6.535;
				else if (runNumber > 6000 && runNumber < 6420)  EBeam = 10.6;
				else if (runNumber > 10000)  EBeam = 10.4;
			}
			elBeam.SetPxPyPzE(0, 0, EBeam, EBeam);
		};
		bool findBest(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &piVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<elDeteInfo> &piDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			nElectron = elVect.size();
			nNucleon = nuVect.size();
			nPion = piVect.size();
			nPhoton = phVect.size();
			Float_t excl4DChi2 = 1e9;
			elIndex = -1;
			nuIndex = -1;
			piIndex = -1;
			for (Int_t iEl=0; iEl<nElectron; iEl++) {
				if (elVect[iEl].P < 1)  continue;
				for (Int_t iNu=0; iNu<nNucleon; iNu++) {
					if (nuVect[iNu].P < 0.3)  continue;
					for (Int_t iPi=0; iPi<nPion; iPi++) {
						if (piVect[iPi].P < 1)  continue;
						Float_t exclChi = DVpipP::getExcl4DChi2(elBeam, nuTarget, elVect[iEl].PVec, nuVect[iNu].PVec, piVect[iPi].PVec);
						if (exclChi < excl4DChi2) {
							excl4DChi2 = exclChi;
							elIndex = iEl;
							nuIndex = iNu;
							piIndex = iPi;
						}
					}
				}
			}
			if (elIndex!=-1 && nuIndex!=-1 && piIndex!=-1) {
				elPart = elVect[elIndex];
				nuPart = nuVect[nuIndex];
				piPart = piVect[piIndex];
				elDete = elDeteVect[elIndex];
				nuDete = nuDeteVect[nuIndex];
				piDete = piDeteVect[piIndex];
				trackCVT = trackCVTInfo;
				clusterCTOF = clusterCTOFInfo;
				trackCND = trackCNDInfo;
				clusterCAL = clusterCALInfo;
				DVpipP bestDVpipP(elBeam, nuTarget, elPart.PVec, nuPart.PVec, piPart.PVec);
				myRecDVpipP = bestDVpipP;
				if (myRecDVpipP.mM2ep2ePiX<0.0 || myRecDVpipP.mM2ep2ePiX>1.5)  return false;
				//if (nPhoton > 0)  return false;
				return true;
			}
			return false;
		};
		DVpipP myRecDVpipP;
		recParticle elPart;
		recParticle nuPart;
		recParticle piPart;
		elDeteInfo elDete;
		nuDeteInfo nuDete;
		elDeteInfo piDete;
		CVTInfo trackCVT;
		CTOFInfo clusterCTOF;
		CNDInfo trackCND;
		CALInfo clusterCAL;
		Int_t runNumber;
		Long_t eventNumber;
    	Int_t helicity;
		Long_t hipoIndex;
		Int_t isMC;
		Int_t elIndex;
		Int_t nuIndex;
		Int_t piIndex;
    	Int_t nElectron;
    	Int_t nNucleon;
    	Int_t nPion;
    	Int_t nPhoton;
		Float_t EBeam;
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
};

class recDVpipPnoNEvent
{
	public:
		recDVpipPnoNEvent(Int_t paraIsMC, Float_t paraEBeam = 10.6): isMC(paraIsMC), EBeam(paraEBeam) {};
		void initial(globalInfo paraInfo) {
			runNumber = paraInfo.runNumber;
			eventNumber = paraInfo.eventNumber;
			helicity = paraInfo.helicity;
			hipoIndex = paraInfo.hipoIndex;
			setEBeam();
			nuTarget = prTarget;
		};
		void setEBeam() {
			if (isMC == 0) {
				EBeam = 10.2;
				if (runNumber < 5600)  EBeam = 10.6;
				else if (runNumber >= 5681 && runNumber <= 5870)  EBeam = 7.546;
				else if (runNumber >= 5875 && runNumber <= 6000)  EBeam = 6.535;
				else if (runNumber > 6000 && runNumber < 6420)  EBeam = 10.6;
				else if (runNumber > 10000)  EBeam = 10.4;
			}
			elBeam.SetPxPyPzE(0, 0, EBeam, EBeam);
		};
		bool findBest(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &piVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<elDeteInfo> &piDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			nElectron = elVect.size();
			nNucleon = nuVect.size();
			nPion = piVect.size();
			nPhoton = phVect.size();
			Float_t excl1DChi2 = 1e9;
			elIndex = -1;
			piIndex = -1;
			for (Int_t iEl=0; iEl<nElectron; iEl++) {
				if (elVect[iEl].P < 1)  continue;
				for (Int_t iPi=0; iPi<nPion; iPi++) {
					if (piVect[iPi].P < 1)  continue;
					Float_t exclChi = DVpipPnoN::getExclChi2(elBeam, nuTarget, elVect[iEl].PVec, piVect[iPi].PVec);
					if (exclChi < excl1DChi2) {
						excl1DChi2 = exclChi;
						elIndex = iEl;
						piIndex = iPi;
					}
				}
			}
			if (elIndex!=-1 && piIndex!=-1) {
				elPart = elVect[elIndex];
				piPart = piVect[piIndex];
				elDete = elDeteVect[elIndex];
				piDete = piDeteVect[piIndex];
				trackCVT = trackCVTInfo;
				clusterCTOF = clusterCTOFInfo;
				trackCND = trackCNDInfo;
				clusterCAL = clusterCALInfo;
				DVpipPnoN bestDVpipPnoN(elBeam, nuTarget, elPart.PVec, piPart.PVec);
				myRecDVpipPnoN = bestDVpipPnoN;
				if (myRecDVpipPnoN.mM2ep2ePiX<0.0 || myRecDVpipPnoN.mM2ep2ePiX>1.5)  return false;
				//if (nPhoton > 0)  return false;
				return true;
			}
			return false;
		};
		DVpipPnoN myRecDVpipPnoN;
		recParticle elPart;
		recParticle piPart;
		elDeteInfo elDete;
		elDeteInfo piDete;
		CVTInfo trackCVT;
		CTOFInfo clusterCTOF;
		CNDInfo trackCND;
		CALInfo clusterCAL;
		Int_t runNumber;
		Long_t eventNumber;
    	Int_t helicity;
		Long_t hipoIndex;
		Int_t isMC;
		Int_t elIndex;
		Int_t piIndex;
    	Int_t nElectron;
    	Int_t nNucleon;
    	Int_t nPion;
    	Int_t nPhoton;
		Float_t EBeam;
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
};

class recDVpipPwithNEvent
{
	public:
		recDVpipPwithNEvent(Int_t paraIsMC, Float_t paraEBeam = 10.6): isMC(paraIsMC), EBeam(paraEBeam) {};
		void initial(globalInfo paraInfo) {
			runNumber = paraInfo.runNumber;
			eventNumber = paraInfo.eventNumber;
			helicity = paraInfo.helicity;
			hipoIndex = paraInfo.hipoIndex;
			setEBeam();
			nuTarget = prTarget;
		};
		void setEBeam() {
			if (isMC == 0) {
				EBeam = 10.2;
				if (runNumber < 5600)  EBeam = 10.6;
				else if (runNumber >= 5681 && runNumber <= 5870)  EBeam = 7.546;
				else if (runNumber >= 5875 && runNumber <= 6000)  EBeam = 6.535;
				else if (runNumber > 6000 && runNumber < 6420)  EBeam = 10.6;
				else if (runNumber > 10000)  EBeam = 10.4;
			}
			elBeam.SetPxPyPzE(0, 0, EBeam, EBeam);
		};
		bool findBest(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &piVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<elDeteInfo> &piDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			nElectron = elVect.size();
			nNucleon = nuVect.size();
			nPion = piVect.size();
			nPhoton = phVect.size();
			Float_t excl1DChi2 = 1e9;
			elIndex = -1;
			piIndex = -1;
			for (Int_t iEl=0; iEl<nElectron; iEl++) {
				if (elVect[iEl].P < 1)  continue;
				for (Int_t iPi=0; iPi<nPion; iPi++) {
					if (piVect[iPi].P < 1)  continue;
					Float_t exclChi = DVpipPnoN::getExclChi2(elBeam, nuTarget, elVect[iEl].PVec, piVect[iPi].PVec);
					if (exclChi < excl1DChi2) {
						excl1DChi2 = exclChi;
						elIndex = iEl;
						piIndex = iPi;
					}
				}
			}
			if (elIndex!=-1 && piIndex!=-1) {
				elPart = elVect[elIndex];
				piPart = piVect[piIndex];
				elDete = elDeteVect[elIndex];
				piDete = piDeteVect[piIndex];
				DVpipPnoN bestDVpipPnoN(elBeam, nuTarget, elPart.PVec, piPart.PVec);
				myRecDVpipPnoN = bestDVpipPnoN;
				if (myRecDVpipPnoN.mM2ep2ePiX<0.0 || myRecDVpipPnoN.mM2ep2ePiX>1.5)  return false;
				Float_t excl4DChi2 = 1e9;
				nuIndex = -1;
				for (Int_t iNu=0; iNu<nNucleon; iNu++) {
					if (nuVect[iNu].P < 0.3)  continue;
					Float_t exclChi = DVpipP::getExcl4DChi2(elBeam, nuTarget, elPart.PVec, nuVect[iNu].PVec, piPart.PVec);
					if (exclChi < excl4DChi2) {
						excl4DChi2 = exclChi;
						nuIndex = iNu;
					}
				}
				if (nuIndex!=-1) {
					nuPart = nuVect[nuIndex];
					nuDete = nuDeteVect[nuIndex];
					trackCVT = trackCVTInfo;
					clusterCTOF = clusterCTOFInfo;
					trackCND = trackCNDInfo;
					clusterCAL = clusterCALInfo;
					DVpipP bestDVpipP(elBeam, nuTarget, elPart.PVec, nuPart.PVec, piPart.PVec);
					myRecDVpipP = bestDVpipP;
					return true;
				}
			}
			return false;
		};
		DVpipP myRecDVpipP;
		DVpipPnoN myRecDVpipPnoN;
		recParticle elPart;
		recParticle nuPart;
		recParticle piPart;
		elDeteInfo elDete;
		nuDeteInfo nuDete;
		elDeteInfo piDete;
		CVTInfo trackCVT;
		CTOFInfo clusterCTOF;
		CNDInfo trackCND;
		CALInfo clusterCAL;
		Int_t runNumber;
		Long_t eventNumber;
    	Int_t helicity;
		Long_t hipoIndex;
		Int_t isMC;
		Int_t elIndex;
		Int_t nuIndex;
		Int_t piIndex;
    	Int_t nElectron;
    	Int_t nNucleon;
    	Int_t nPion;
    	Int_t nPhoton;
		Float_t EBeam;
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
};

class mcDVpipPEvent
{
	public:
		mcDVpipPEvent(Float_t paraEBeam = 10.6) {
			isMC = 1;
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
				nuPart = mcPartVect[2];
				piPart = mcPartVect[3];
			}
			else if (mcPartVect.size() == 3) {
				spPart = mcParticle(newInfo, -1);
				piPart = mcPartVect[1];
				nuPart = mcPartVect[2];
			}
			DVpipP myDVpipP(elBeam, prTarget, elPart.PVec, nuPart.PVec, piPart.PVec);
			myMCDVpipP = myDVpipP;
			return true;
		};
		DVpipP myMCDVpipP;
		mcParticle elPart;
		mcParticle piPart;
		mcParticle nuPart;
		mcParticle spPart;
		Int_t runNumber;
		Long_t eventNumber;
		Int_t helicity;
		Long_t hipoIndex;
		Int_t isMC;
		Float_t EBeam;
		ROOT::Math::PxPyPzEVector elBeam;
};

class recDVpipPTree: public preTree
{
	public:
		recDVpipPTree(TString name): preTree(name), myEvent(0) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isMC, myEvent.EBeam, myEvent.nElectron, myEvent.nNucleon, myEvent.nPion, myEvent.nPhoton);
			addRecPartBranch("el", myEvent.elPart);
			addElDeteBranch("el", myEvent.elDete);
			addRecPartBranch("nu", myEvent.nuPart);
			addNuDeteBranch("nu", myEvent.nuDete, 0);
			addCVTBranch(myEvent.trackCVT);
			addCTOFBranch(myEvent.clusterCTOF);
			addCNDBranch(myEvent.trackCND);
			addCALBranch(myEvent.clusterCAL);
			addRecPartBranch("pi", myEvent.piPart);
			addElDeteBranch("pi", myEvent.piDete);
			addDVpipPBranch("", myEvent.myRecDVpipP);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &piVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<elDeteInfo> &piDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myEvent.findBest(elVect, nuVect, piVect, phVect, elDeteVect, nuDeteVect, piDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				myTTree.Fill();
			}
		};
		recDVpipPEvent myEvent;
};

class recDVpipPnoNTree: public preTree
{
	public:
		recDVpipPnoNTree(TString name): preTree(name), myEvent(0) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isMC, myEvent.EBeam, myEvent.nElectron, myEvent.nNucleon, myEvent.nPion, myEvent.nPhoton);
			addRecPartBranch("el", myEvent.elPart);
			addElDeteBranch("el", myEvent.elDete);
			addCVTBranch(myEvent.trackCVT);
			addCTOFBranch(myEvent.clusterCTOF);
			addCNDBranch(myEvent.trackCND);
			addCALBranch(myEvent.clusterCAL);
			addRecPartBranch("pi", myEvent.piPart);
			addElDeteBranch("pi", myEvent.piDete);
			addDVpipPnoNBranch("", myEvent.myRecDVpipPnoN);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &piVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<elDeteInfo> &piDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myEvent.findBest(elVect, nuVect, piVect, phVect, elDeteVect, piDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				myTTree.Fill();
			}
		};
		recDVpipPnoNEvent myEvent;
};

class recDVpipPwithNTree: public preTree
{
	public:
		recDVpipPwithNTree(TString name): preTree(name), myEvent(0) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isMC, myEvent.EBeam, myEvent.nElectron, myEvent.nNucleon, myEvent.nPion, myEvent.nPhoton);
			addRecPartBranch("el", myEvent.elPart);
			addElDeteBranch("el", myEvent.elDete);
			addRecPartBranch("nu", myEvent.nuPart);
			addNuDeteBranch("nu", myEvent.nuDete, 0);
			addCVTBranch(myEvent.trackCVT);
			addCTOFBranch(myEvent.clusterCTOF);
			addCNDBranch(myEvent.trackCND);
			addCALBranch(myEvent.clusterCAL);
			addRecPartBranch("pi", myEvent.piPart);
			addElDeteBranch("pi", myEvent.piDete);
			addDVpipPBranch("", myEvent.myRecDVpipP);
			addDVpipPnoNBranch("recNoN_", myEvent.myRecDVpipPnoN);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &piVect, const vector<recParticle> &phVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<elDeteInfo> &piDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myEvent.findBest(elVect, nuVect, piVect, phVect, elDeteVect, nuDeteVect, piDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				myTTree.Fill();
			}
		};
		recDVpipPwithNEvent myEvent;
};

class mcRecDVpipPnoNTree: public preTree
{
	public:
		mcRecDVpipPnoNTree(TString name, Float_t EBeam): preTree(name), myEvent(2, EBeam), myMCEvent(EBeam) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isMC, myEvent.EBeam, myEvent.nElectron, myEvent.nNucleon, myEvent.nPion, myEvent.nPhoton);
			addRecPartBranch("el", myEvent.elPart);
			addElDeteBranch("el", myEvent.elDete);
			addCVTBranch(myEvent.trackCVT);
			addCTOFBranch(myEvent.clusterCTOF);
			addCNDBranch(myEvent.trackCND);
			addCALBranch(myEvent.clusterCAL);
			addRecPartBranch("pi", myEvent.piPart);
			addElDeteBranch("pi", myEvent.piDete);
			addDVpipPnoNBranch("", myEvent.myRecDVpipPnoN);
			addMCPartBranch("el_true", myMCEvent.elPart);
			addMCPartBranch("pi_true", myMCEvent.piPart);
			addMCPartBranch("nu_true", myMCEvent.nuPart);
			addMCPartBranch("sp_true", myMCEvent.spPart);
			addDVpipPBranch("true_", myMCEvent.myMCDVpipP);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &piVect, const vector<recParticle> &phVect, const vector<mcParticle> &mcPartVect, const vector<elDeteInfo> &elDeteVect, const vector<elDeteInfo> &piDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myEvent.findBest(elVect, nuVect, piVect, phVect, elDeteVect, piDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				if (myMCEvent.setParticle(mcPartVect)) {
					myTTree.Fill();
				}
			}
		};
		recDVpipPnoNEvent myEvent;
		mcDVpipPEvent myMCEvent;
};

class mcRecDVpipPwithNTree: public preTree
{
	public:
		mcRecDVpipPwithNTree(TString name, Float_t EBeam): preTree(name), myEvent(2, EBeam), myMCEvent(EBeam) {
			addBranch();
		};
		void addBranch() {
			addGlobalBranch(myEvent.runNumber, myEvent.eventNumber, myEvent.helicity, myEvent.hipoIndex, myEvent.isMC, myEvent.EBeam, myEvent.nElectron, myEvent.nNucleon, myEvent.nPion, myEvent.nPhoton);
			addRecPartBranch("el", myEvent.elPart);
			addElDeteBranch("el", myEvent.elDete);
			addRecPartBranch("nu", myEvent.nuPart);
			addNuDeteBranch("nu", myEvent.nuDete, 0);
			addCVTBranch(myEvent.trackCVT);
			addCTOFBranch(myEvent.clusterCTOF);
			addCNDBranch(myEvent.trackCND);
			addCALBranch(myEvent.clusterCAL);
			addRecPartBranch("pi", myEvent.piPart);
			addElDeteBranch("pi", myEvent.piDete);
			addDVpipPBranch("", myEvent.myRecDVpipP);
			addDVpipPnoNBranch("recNoN_", myEvent.myRecDVpipPnoN);
			addMCPartBranch("el_true", myMCEvent.elPart);
			addMCPartBranch("pi_true", myMCEvent.piPart);
			addMCPartBranch("nu_true", myMCEvent.nuPart);
			addMCPartBranch("sp_true", myMCEvent.spPart);
			addDVpipPBranch("true_", myMCEvent.myMCDVpipP);
		};
		void initialEvent(globalInfo paraInfo) {
			myEvent.initial(paraInfo);
		};
		void fill(const vector<recParticle> &elVect, const vector<recParticle> &nuVect, const vector<recParticle> &piVect, const vector<recParticle> &phVect, const vector<mcParticle> &mcPartVect, const vector<elDeteInfo> &elDeteVect, const vector<nuDeteInfo> &nuDeteVect, const vector<elDeteInfo> &piDeteVect, const CVTInfo &trackCVTInfo, const CTOFInfo &clusterCTOFInfo, const CNDInfo &trackCNDInfo, const CALInfo &clusterCALInfo) {
			if (myEvent.findBest(elVect, nuVect, piVect, phVect, elDeteVect, nuDeteVect, piDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo)) {
				if (myMCEvent.setParticle(mcPartVect)) {
					myTTree.Fill();
				}
			}
		};
		recDVpipPwithNEvent myEvent;
		mcDVpipPEvent myMCEvent;
};

#endif
