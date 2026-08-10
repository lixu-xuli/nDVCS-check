#ifndef _INFO_H
#define _INFO_H

#include <vector>
#include <TMath.h>
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>

const Int_t iniVal = -999;
const Float_t electronMass = 0.000511;
const Float_t protonMass = 0.938272;
const Float_t neutronMass = 0.939565;
const Float_t deuteronMass = 1.8756;
const Float_t pi0Mass = 0.134977;
const Float_t pipMass = 0.139570;
const Float_t pimMass = 0.139570;
ROOT::Math::PxPyPzEVector prTarget(0, 0, 0, protonMass);
ROOT::Math::PxPyPzEVector neTarget(0, 0, 0, neutronMass);
ROOT::Math::PxPyPzEVector deTarget(0, 0, 0, deuteronMass);

struct globalInfo
{
	Int_t runNumber;
	Long_t eventNumber;
	Int_t helicity;
	Long_t hipoIndex;
};

struct recPartInfo
{
	Int_t pid;
	Float_t px;
	Float_t py;
	Float_t pz;
	Float_t vx;
	Float_t vy;
	Float_t vz;
	Float_t vt;
	Int_t charge;
	Float_t beta;
	Float_t chi2pid;
	Int_t status;
	Int_t pindex;
};

struct mcPartInfo
{
	Int_t pid;
	Float_t px;
	Float_t py;
	Float_t pz;
	Float_t vx;
	Float_t vy;
	Float_t vz;
	Float_t vt;
	Int_t mcindex;
};

struct elDeteInfo
{
	Int_t sectorCAL[3];
	Float_t energyCAL[3];
	Float_t xCAL[3];
	Float_t yCAL[3];
	Float_t zCAL[3];
	Float_t luCAL[3];
	Float_t lvCAL[3];
	Float_t lwCAL[3];
	Float_t phiCAL[3];
	Float_t thetaCAL[3];
	Float_t timeCAL[3];
	Float_t pathCAL[3];
	Float_t energySumCAL;
	Int_t sectorDC[3];
	Float_t xDC[3];
	Float_t yDC[3];
	Float_t zDC[3];
	Float_t phiDC[3];
	Float_t thetaDC[3];
	Float_t edgeDC[3];
	Int_t sectorTrack;
	Float_t chi2Track;
	Int_t ndfTrack;
	Float_t chi2ndfTrack;
	Int_t nPh;
	Int_t num;
	Int_t pindexPh[10];
	Float_t pPh[10];
	Float_t pxPh[10];
	Float_t pyPh[10];
	Float_t pzPh[10];
	Float_t anglePh[10];
	Float_t dThetaPh[10];
	Float_t dPhiPh[10];
};

struct nuDeteInfo
{
	Int_t nLayerCND;
	Int_t lastLayerCND;
	Int_t layerSciCD[4];
	Float_t energySciCD[4];
	Float_t xSciCD[4];
	Float_t ySciCD[4];
	Float_t zSciCD[4];
	Float_t phiSciCD[4];
	Float_t thetaSciCD[4];
	Float_t timeSciCD[4];
	Float_t pathSciCD[4];
	Float_t dedxSciCD[4];
	Int_t sizeSciCD[4];
	Int_t layermultSciCD[4];
	Int_t sectorCAL[3];
	Float_t energyCAL[3];
	Float_t xCAL[3];
	Float_t yCAL[3];
	Float_t zCAL[3];
	Float_t luCAL[3];
	Float_t lvCAL[3];
	Float_t lwCAL[3];
	Float_t phiCAL[3];
	Float_t thetaCAL[3];
	Float_t timeCAL[3];
	Float_t pathCAL[3];
	Float_t energySumCAL;
	Int_t sectorDC[3];
	Float_t xDC[3];
	Float_t yDC[3];
	Float_t zDC[3];
	Float_t phiDC[3];
	Float_t thetaDC[3];
	Float_t edgeDC[3];
};

struct phDeteInfo
{
	Int_t sectorCAL[3];
	Float_t energyCAL[3];
	Float_t xCAL[3];
	Float_t yCAL[3];
	Float_t zCAL[3];
	Float_t luCAL[3];
	Float_t lvCAL[3];
	Float_t lwCAL[3];
	Float_t phiCAL[3];
	Float_t thetaCAL[3];
	Float_t timeCAL[3];
	Float_t pathCAL[3];
	Float_t energySumCAL;
	Float_t xFT;
	Float_t yFT;
	Float_t zFT;
	Float_t energyFT;
};

struct CVTInfo
{
	Int_t nTrack;
	Int_t nCluster;
	Int_t num;
	Int_t pindexCVT[100];
	Int_t pidCVT[100];
	Int_t nLayerCVT[100];
	Int_t layerCVT[100];
	Float_t xCVT[100];
	Float_t yCVT[100];
	Float_t zCVT[100];
	Float_t phiCVT[100];
	Float_t thetaCVT[100];
};

struct CTOFInfo
{
	Int_t nCluster;
	Int_t num;
	Int_t pindexCTOF[20];
	Int_t pidCTOF[20];
	Int_t layerCTOF[20];
	Float_t energyCTOF[20];
	Float_t xCTOF[20];
	Float_t yCTOF[20];
	Float_t zCTOF[20];
	Float_t tCTOF[20];
	Float_t phiCTOF[20];
	Float_t thetaCTOF[20];
	Float_t dedxCTOF[20];
	Int_t sizeCTOF[20];
	Int_t layermultCTOF[20];
};

struct CNDInfo
{
	Int_t nTrack;
	Int_t nCluster;
	Int_t num;
	Int_t pindexCND[30];
	Int_t pidCND[30];
	Int_t layerCND[30];
	Float_t energyCND[30];
	Float_t xCND[30];
	Float_t yCND[30];
	Float_t zCND[30];
	Float_t tCND[30];
	Float_t phiCND[30];
	Float_t thetaCND[30];
	Float_t dedxCND[30];
	Int_t sizeCND[30];
	Int_t layermultCND[30];
};

struct CALInfo
{
	Int_t nParticle;
	Int_t nNeutron;
	Int_t nNeutronNew;
	Int_t nCluster;
	Int_t num;
	Int_t pindexCAL[30];
	Int_t pidCAL[30];
	Int_t layerCAL[30];
	Int_t sectorCAL[30];
	Float_t energyCAL[30];
	Float_t timeCAL[30];
	Float_t pathCAL[30];
	Float_t xCAL[30];
	Float_t yCAL[30];
	Float_t zCAL[30];
};

class preParticle
{
	public:
		preParticle() {};
		preParticle(Int_t paraPid, Float_t paraPx, Float_t paraPy, Float_t paraPz, Float_t paraVx, Float_t paraVy, Float_t paraVz, Float_t paraVt): pid(paraPid), px(paraPx), py(paraPy), pz(paraPz), vx(paraVx), vy(paraVy), vz(paraVz), vt(paraVt) {
			setPVec();
		};
		void setPVec() {
			M = 0;
			if (pid == 11)
				M = electronMass;
			else if (pid == 2112)
				M = neutronMass;
			else if (pid == 2212)
				M = protonMass;
			else if (pid == 22)
				M = 0;
			else if (pid == 211)
				M = pipMass;
			else if (pid == -211)
				M = pimMass;
			P = TMath::Sqrt(px*px + py*py + pz*pz);
			E = TMath::Sqrt(P*P + M*M);
			PVec.SetPxPyPzE(px, py, pz, E);
			phi = PVec.Phi() / TMath::Pi() * 180;
			theta = PVec.Theta() / TMath::Pi() * 180;
		};
		Int_t pid;
		Float_t px;
		Float_t py;
		Float_t pz;
		Float_t vx;
		Float_t vy;
		Float_t vz;
		Float_t vt;
		Float_t M;
		Float_t P;
		Float_t E;
		Float_t phi;
		Float_t theta;
		ROOT::Math::PxPyPzEVector PVec;
};

class recParticle: public preParticle
{
	public:
		recParticle(): preParticle() {};
		recParticle(recPartInfo paraInfo, Int_t paraMCIndex): preParticle(paraInfo.pid, paraInfo.px, paraInfo.py, paraInfo.pz, paraInfo.vx, paraInfo.vy, paraInfo.vz, paraInfo.vt), charge(paraInfo.charge), beta(paraInfo.beta), chi2pid(paraInfo.chi2pid), status(paraInfo.status), pindex(paraInfo.pindex), mcindex(paraMCIndex) {};
		Int_t charge;
		Float_t beta;
		Float_t chi2pid;
		Int_t status;
		Int_t pindex;
		Int_t mcindex;
};

class mcParticle: public preParticle
{
	public:
		mcParticle(): preParticle() {};
		mcParticle(mcPartInfo paraInfo, Int_t paraPIndex): preParticle(paraInfo.pid, paraInfo.px, paraInfo.py, paraInfo.pz, paraInfo.vx, paraInfo.vy, paraInfo.vz, paraInfo.vt), mcindex(paraInfo.mcindex), pindex(paraPIndex) {};
		Int_t mcindex;
		Int_t pindex;
};

class singleEl{
	public:
		singleEl() {};
		singleEl(ROOT::Math::PxPyPzEVector paraBeam, ROOT::Math::PxPyPzEVector paraTarget, ROOT::Math::PxPyPzEVector paraEl): elBeam(paraBeam), nuTarget(paraTarget), elPVec(paraEl){
			calculateVars();
		};
		void calculateVars() {
			Q2 = -(elBeam - elPVec).M2();
			W = (nuTarget + elBeam - elPVec).M();
			Xbj = Q2 / (2 * nuTarget.M() * (elBeam.E() - elPVec.E()));
		};
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
		ROOT::Math::PxPyPzEVector elPVec;
		Float_t Q2;
		Float_t W;
		Float_t Xbj;
};

class DVCS{
	public:
		DVCS() {};
		DVCS(ROOT::Math::PxPyPzEVector paraBeam, ROOT::Math::PxPyPzEVector paraTarget, ROOT::Math::PxPyPzEVector paraEl, ROOT::Math::PxPyPzEVector paraNu, ROOT::Math::PxPyPzEVector paraPh): elBeam(paraBeam), nuTarget(paraTarget), elPVec(paraEl), nuPVec(paraNu), phPVec(paraPh) {
			calculateVars();
		};
		void calculateVars() {
			Q2 = -(elBeam - elPVec).M2();
			W = (nuTarget + elBeam - elPVec).M();
			Xbj = Q2 / (2 * nuTarget.M() * (elBeam.E() - elPVec.E()));
			deltaT = getDeltaT(elBeam, nuTarget, elPVec, nuPVec, phPVec, tNucleon, tPhoton);
			ROOT::Math::PxPyPzEVector misX = elBeam + nuTarget - elPVec - nuPVec - phPVec;
			mM2en2engX = misX.M2();
			mPen2engX = misX.P();
			ROOT::Math::PxPyPzEVector misPh = elBeam + nuTarget - elPVec - nuPVec;
			mM2en2enX = misPh.M2();
			mPen2enX = misPh.P();
			ROOT::Math::PxPyPzEVector misNu = elBeam + nuTarget - elPVec - phPVec;
			mM2en2egX = misNu.M2();
			mPen2egX = misNu.P();
			ROOT::Math::PxPyPzEVector misEl = elBeam + nuTarget - nuPVec - phPVec;
			mM2en2ngX = misEl.M2();
			mPen2ngX = misEl.P();
			ROOT::Math::PxPyPzEVector misSp = elBeam + deTarget - elPVec - nuPVec - phPVec;
			mM2ed2engX = misSp.M2();
			mPed2engX = misSp.P();
			deltaPhi = getDeltaPhi(elBeam, elPVec, nuPVec, phPVec, phiNuVirPh, phiNuOutPh);
			thetaMisPhPh = getThetaMisPhPh(elBeam, nuTarget, elPVec, nuPVec, phPVec);
			thetaMisNuNu = ROOT::Math::VectorUtil::Angle(misNu.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaElPh = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), phPVec.Vect()) / TMath::Pi() * 180;
			thetaElNu = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaPhNu = ROOT::Math::VectorUtil::Angle(phPVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			excl4DChi2 = pow(mM2en2enX/1.21, 2) + pow(deltaT/0.19, 2) + pow(deltaPhi/0.74, 2) + pow(thetaMisPhPh/0.85, 2);
		};
		static Float_t getMM2en2enX(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec) {
			return (elBeam + target - elPVec - nuPVec).M2();
		};
		static Float_t getDeltaT(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &phPVec, Float_t &t1, Float_t &t2) {
			t1 = (nuPVec - target).M2();
			t2 = (elBeam - elPVec - phPVec).M2();
			return t1 - t2;
		};
		static Float_t getDeltaPhi(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &phPVec, Float_t &phi1, Float_t &phi2) {
			ROOT::Math::XYZVector zAxis = (elBeam - elPVec).Vect();  //virtual photon direction
			ROOT::Math::XYZVector yAxis = elBeam.Vect().Cross(elPVec.Vect());  //vertical to leptonic plane
			ROOT::Math::XYZVector xAxis = yAxis.Cross(zAxis);
			ROOT::Math::XYZVector y1Axis = nuPVec.Vect().Cross(zAxis);  //vertical to hadronic plane
			ROOT::Math::XYZVector y2Axis = nuPVec.Vect().Cross(phPVec.Vect());  //vertical to hadronic plane
			phi1 = ROOT::Math::VectorUtil::Angle(y1Axis, yAxis) / TMath::Pi() * 180;
			if (y1Axis.Dot(xAxis) > 0)  phi1 = 360 - phi1;
			phi2 = ROOT::Math::VectorUtil::Angle(y2Axis, yAxis) / TMath::Pi() * 180;
			if (y2Axis.Dot(xAxis) > 0)  phi2 = 360 - phi2;
			Float_t dPhi = phi1 - phi2;
			if (dPhi > 180)  dPhi -= 360;
			else if (dPhi < -180)  dPhi += 360;
			return dPhi;
		};
		static Float_t getThetaMisPhPh(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &phPVec) {
			return ROOT::Math::VectorUtil::Angle((elBeam+target-elPVec-nuPVec).Vect(), phPVec.Vect()) / TMath::Pi() * 180;
		};
		static Float_t getExcl4DChi2(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &phPVec) {
			Float_t mM2 = getMM2en2enX(elBeam, target, elPVec, nuPVec);
			Float_t t1, t2;
			Float_t dT = getDeltaT(elBeam, target, elPVec, nuPVec, phPVec, t1, t2);
			Float_t phi1, phi2;
			Float_t dPhi = getDeltaPhi(elBeam, elPVec, nuPVec, phPVec, phi1, phi2);
			Float_t theta = getThetaMisPhPh(elBeam, target, elPVec, nuPVec, phPVec);
			return pow(mM2/1.21, 2) + pow(dT/0.19, 2) + pow(dPhi/0.74, 2) + pow(theta/0.85, 2);
		}
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
		ROOT::Math::PxPyPzEVector elPVec;
		ROOT::Math::PxPyPzEVector nuPVec;
		ROOT::Math::PxPyPzEVector phPVec;
		Float_t Q2;
		Float_t W;
		Float_t Xbj;
		Float_t tNucleon;
		Float_t tPhoton;
		Float_t deltaT;
		Float_t mM2en2engX;
		Float_t mPen2engX;
		Float_t mM2en2enX;
		Float_t mPen2enX;
		Float_t mM2en2egX;
		Float_t mPen2egX;
		Float_t mM2en2ngX;
		Float_t mPen2ngX;
		Float_t mM2ed2engX;
		Float_t mPed2engX;
		Float_t phiNuVirPh;
		Float_t phiNuOutPh;
		Float_t deltaPhi;
		Float_t thetaMisPhPh;
		Float_t thetaMisNuNu;
		Float_t thetaElPh;
		Float_t thetaElNu;
		Float_t thetaPhNu;
		Float_t excl4DChi2;
};

class DVpi0P{
	public:
		DVpi0P() {};
		DVpi0P(ROOT::Math::PxPyPzEVector paraBeam, ROOT::Math::PxPyPzEVector paraTarget, ROOT::Math::PxPyPzEVector paraEl, ROOT::Math::PxPyPzEVector paraNu, ROOT::Math::PxPyPzEVector paraPh1, ROOT::Math::PxPyPzEVector paraPh2): elBeam(paraBeam), nuTarget(paraTarget), elPVec(paraEl), nuPVec(paraNu), ph1PVec(paraPh1), ph2PVec(paraPh2) {
			pi0PVec = ph1PVec + ph2PVec;
			pi0Px = pi0PVec.Px();
			pi0Py = pi0PVec.Py();
			pi0Pz = pi0PVec.Pz();
			pi0M = pi0PVec.M();
			pi0P = pi0PVec.P();
			pi0E = pi0PVec.E();
			pi0Phi = pi0PVec.Phi() / TMath::Pi() * 180;
			pi0Theta = pi0PVec.Theta() / TMath::Pi() * 180;
			pi0OpenAng = ROOT::Math::VectorUtil::Angle(ph1PVec.Vect(), ph2PVec.Vect());
			pi0OpenAng0 = 2 * TMath::ASin( TMath::Sqrt(pi0Mass*pi0Mass / (4*ph1PVec.E()*ph2PVec.E())) );
			calculateVars();
		};
		void calculateVars() {
			Q2 = -(elBeam - elPVec).M2();
			W = (nuTarget + elBeam - elPVec).M();
			Xbj = Q2 / (2 * nuTarget.M() * (elBeam.E() - elPVec.E()));
			deltaT = getDeltaT(elBeam, nuTarget, elPVec, nuPVec, ph1PVec, ph2PVec, tNucleon, tPhoton);
			ROOT::Math::PxPyPzEVector misX = elBeam + nuTarget - elPVec - nuPVec - pi0PVec;
			mM2en2enggX = misX.M2();
			mPen2enggX = misX.P();
			ROOT::Math::PxPyPzEVector misPi0 = elBeam + nuTarget - elPVec - nuPVec;
			mM2en2enX = misPi0.M2();
			mPen2enX = misPi0.P();
			ROOT::Math::PxPyPzEVector misNu = elBeam + nuTarget - elPVec - pi0PVec;
			mM2en2eggX = misNu.M2();
			mPen2eggX = misNu.P();
			ROOT::Math::PxPyPzEVector misPh2 = elBeam + nuTarget - elPVec - nuPVec - ph1PVec;
			mM2en2eng1X = misPh2.M2();
			mPen2eng1X = misPh2.P();
			ROOT::Math::PxPyPzEVector misPh1 = elBeam + nuTarget - elPVec - nuPVec - ph2PVec;
			mM2en2eng2X = misPh1.M2();
			mPen2eng2X = misPh1.P();
			ROOT::Math::PxPyPzEVector misEl = elBeam + nuTarget - nuPVec - pi0PVec;
			mM2en2nggX = misEl.M2();
			mPen2nggX = misEl.P();
			ROOT::Math::PxPyPzEVector misSp = elBeam + deTarget - elPVec - nuPVec - pi0PVec;
			mM2ed2enggX = misSp.M2();
			mPed2enggX = misSp.P();
			deltaPhi = getDeltaPhi(elBeam, elPVec, nuPVec, ph1PVec, ph2PVec, phiNuVirPh, phiNuOutPi0);
			thetaMisPi0Pi0 = getThetaMisPi0Pi0(elBeam, nuTarget, elPVec, nuPVec, ph1PVec, ph2PVec);
			thetaMisNuNu = ROOT::Math::VectorUtil::Angle(misNu.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaElPh1 = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), ph1PVec.Vect()) / TMath::Pi() * 180;
			thetaElPh2 = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), ph2PVec.Vect()) / TMath::Pi() * 180;
			thetaElNu = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaPh1Nu = ROOT::Math::VectorUtil::Angle(ph1PVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaPh2Nu = ROOT::Math::VectorUtil::Angle(ph2PVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaPh1Ph2 = ROOT::Math::VectorUtil::Angle(ph1PVec.Vect(), ph2PVec.Vect()) / TMath::Pi() * 180;
			excl4DChi2 = pow((mM2en2enX-pi0Mass*pi0Mass)/0.68, 2) + pow(deltaT/0.26, 2) + pow(deltaPhi/1.17, 2) + pow(thetaMisPi0Pi0/1.39, 2);
		};
		static Float_t getMM2en2enX(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec) {
			return (elBeam + target - elPVec - nuPVec).M2();
		};
		static Float_t getDeltaT(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &ph1PVec, const ROOT::Math::PxPyPzEVector &ph2PVec, Float_t &t1, Float_t &t2) {
			t1 = (nuPVec - target).M2();
			t2 = (elBeam - elPVec - ph1PVec - ph2PVec).M2();
			return t1 - t2;
		};
		static Float_t getDeltaPhi(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &ph1PVec, const ROOT::Math::PxPyPzEVector &ph2PVec, Float_t &phi1, Float_t &phi2) {
			ROOT::Math::XYZVector zAxis = (elBeam - elPVec).Vect();  //virtual photon direction
			ROOT::Math::XYZVector yAxis = elBeam.Vect().Cross(elPVec.Vect());  //vertical to leptonic plane
			ROOT::Math::XYZVector xAxis = yAxis.Cross(zAxis);
			ROOT::Math::XYZVector y1Axis = nuPVec.Vect().Cross(zAxis);  //vertical to hadronic plane
			ROOT::Math::XYZVector y2Axis = nuPVec.Vect().Cross((ph1PVec+ph2PVec).Vect());  //vertical to hadronic plane
			phi1 = ROOT::Math::VectorUtil::Angle(y1Axis, yAxis) / TMath::Pi() * 180;
			if (y1Axis.Dot(xAxis) > 0)  phi1 = 360 - phi1;
			phi2 = ROOT::Math::VectorUtil::Angle(y2Axis, yAxis) / TMath::Pi() * 180;
			if (y2Axis.Dot(xAxis) > 0)  phi2 = 360 - phi2;
			Float_t dPhi = phi1 - phi2;
			if (dPhi > 180)  dPhi -= 360;
			else if (dPhi < -180)  dPhi += 360;
			return dPhi;
		};
		static Float_t getThetaMisPi0Pi0(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &ph1PVec, const ROOT::Math::PxPyPzEVector &ph2PVec) {
			return ROOT::Math::VectorUtil::Angle((elBeam+target-elPVec-nuPVec).Vect(), (ph1PVec+ph2PVec).Vect()) / TMath::Pi() * 180;
		};
		static Float_t getExcl4DChi2(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &ph1PVec, const ROOT::Math::PxPyPzEVector &ph2PVec) {
			Float_t mM2 = getMM2en2enX(elBeam, target, elPVec, nuPVec);
			Float_t t1, t2;
			Float_t dT = getDeltaT(elBeam, target, elPVec, nuPVec, ph1PVec, ph2PVec, t1, t2);
			Float_t phi1, phi2;
			Float_t dPhi = getDeltaPhi(elBeam, elPVec, nuPVec, ph1PVec, ph2PVec, phi1, phi2);
			Float_t theta = getThetaMisPi0Pi0(elBeam, target, elPVec, nuPVec, ph1PVec, ph2PVec);
			return pow((mM2-pi0Mass*pi0Mass)/0.68, 2) + pow(dT/0.26, 2) + pow(dPhi/1.17, 2) + pow(theta/1.39, 2);
		}
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
		ROOT::Math::PxPyPzEVector elPVec;
		ROOT::Math::PxPyPzEVector nuPVec;
		ROOT::Math::PxPyPzEVector ph1PVec;
		ROOT::Math::PxPyPzEVector ph2PVec;
		ROOT::Math::PxPyPzEVector pi0PVec;
		Float_t pi0Px;
		Float_t pi0Py;
		Float_t pi0Pz;
		Float_t pi0M;
		Float_t pi0P;
		Float_t pi0E;
		Float_t pi0Phi;
		Float_t pi0Theta;
		Float_t pi0OpenAng;
		Float_t pi0OpenAng0;
		Float_t Q2;
		Float_t W;
		Float_t Xbj;
		Float_t tNucleon;
		Float_t tPhoton;
		Float_t deltaT;
		Float_t mM2en2enggX;
		Float_t mPen2enggX;
		Float_t mM2en2enX;
		Float_t mPen2enX;
		Float_t mM2en2eggX;
		Float_t mPen2eggX;
		Float_t mM2en2eng1X;
		Float_t mPen2eng1X;
		Float_t mM2en2eng2X;
		Float_t mPen2eng2X;
		Float_t mM2en2nggX;
		Float_t mPen2nggX;
		Float_t mM2ed2enggX;
		Float_t mPed2enggX;
		Float_t phiNuVirPh;
		Float_t phiNuOutPi0;
		Float_t deltaPhi;
		Float_t thetaMisPi0Pi0;
		Float_t thetaMisNuNu;
		Float_t thetaElPh1;
		Float_t thetaElPh2;
		Float_t thetaElNu;
		Float_t thetaPh1Nu;
		Float_t thetaPh2Nu;
		Float_t thetaPh1Ph2;
		Float_t excl4DChi2;
};

class DVpipP{
	public:
		DVpipP() {};
		DVpipP(ROOT::Math::PxPyPzEVector paraBeam, ROOT::Math::PxPyPzEVector paraTarget, ROOT::Math::PxPyPzEVector paraEl, ROOT::Math::PxPyPzEVector paraNu, ROOT::Math::PxPyPzEVector paraPi): elBeam(paraBeam), nuTarget(paraTarget), elPVec(paraEl), nuPVec(paraNu), piPVec(paraPi) {
			calculateVars();
		};
		void calculateVars() {
			Q2 = -(elBeam - elPVec).M2();
			W = (nuTarget + elBeam - elPVec).M();
			Xbj = Q2 / (2 * nuTarget.M() * (elBeam.E() - elPVec.E()));
			deltaT = getDeltaT(elBeam, nuTarget, elPVec, nuPVec, piPVec, tNucleon, tPhoton);
			ROOT::Math::PxPyPzEVector misX = elBeam + nuTarget - elPVec - nuPVec - piPVec;
			mM2ep2enPiX = misX.M2();
			mPep2enPiX = misX.P();
			ROOT::Math::PxPyPzEVector misPi = elBeam + nuTarget - elPVec - nuPVec;
			mM2ep2enX = misPi.M2();
			mPep2enX = misPi.P();
			ROOT::Math::PxPyPzEVector misNu = elBeam + nuTarget - elPVec - piPVec;
			mM2ep2ePiX = misNu.M2();
			mPep2ePiX = misNu.P();
			ROOT::Math::PxPyPzEVector misEl = elBeam + nuTarget - nuPVec - piPVec;
			mM2ep2nPiX = misEl.M2();
			mPep2nPiX = misEl.P();
			deltaPhi = getDeltaPhi(elBeam, elPVec, nuPVec, piPVec, phiNuVirPh, phiNuOutPi);
			thetaMisPiPi = getThetaMisPiPi(elBeam, nuTarget, elPVec, nuPVec, piPVec);
			thetaMisNuNu = ROOT::Math::VectorUtil::Angle(misNu.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaElPi = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), piPVec.Vect()) / TMath::Pi() * 180;
			thetaElNu = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaPiNu = ROOT::Math::VectorUtil::Angle(piPVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			excl4DChi2 = (mM2ep2enX-pipMass*pipMass)*(mM2ep2enX-pipMass*pipMass) + deltaT*deltaT + deltaPhi*deltaPhi + thetaMisPiPi*thetaMisPiPi;
		};
		static Float_t getMM2ep2enX(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec) {
			return (elBeam + target - elPVec - nuPVec).M2();
		};
		static Float_t getDeltaT(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &piPVec, Float_t &t1, Float_t &t2) {
			t1 = (nuPVec - target).M2();
			t2 = (elBeam - elPVec - piPVec).M2();
			return t1 - t2;
		};
		static Float_t getDeltaPhi(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &piPVec, Float_t &phi1, Float_t &phi2) {
			ROOT::Math::XYZVector zAxis = (elBeam - elPVec).Vect();  //virtual photon direction
			ROOT::Math::XYZVector yAxis = elBeam.Vect().Cross(elPVec.Vect());  //vertical to leptonic plane
			ROOT::Math::XYZVector xAxis = yAxis.Cross(zAxis);
			ROOT::Math::XYZVector y1Axis = nuPVec.Vect().Cross(zAxis);  //vertical to hadronic plane
			ROOT::Math::XYZVector y2Axis = nuPVec.Vect().Cross(piPVec.Vect());  //vertical to hadronic plane
			phi1 = ROOT::Math::VectorUtil::Angle(y1Axis, yAxis) / TMath::Pi() * 180;
			if (y1Axis.Dot(xAxis) > 0)  phi1 = 360 - phi1;
			phi2 = ROOT::Math::VectorUtil::Angle(y2Axis, yAxis) / TMath::Pi() * 180;
			if (y2Axis.Dot(xAxis) > 0)  phi2 = 360 - phi2;
			Float_t dPhi = phi1 - phi2;
			if (dPhi > 180)  dPhi -= 360;
			else if (dPhi < -180)  dPhi += 360;
			return dPhi;
		};
		static Float_t getThetaMisPiPi(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &piPVec) {
			return ROOT::Math::VectorUtil::Angle((elBeam+target-elPVec-nuPVec).Vect(), piPVec.Vect()) / TMath::Pi() * 180;
		};
		static Float_t getExcl4DChi2(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &piPVec) {
			Float_t mM2 = getMM2ep2enX(elBeam, target, elPVec, nuPVec);
			Float_t t1, t2;
			Float_t dT = getDeltaT(elBeam, target, elPVec, nuPVec, piPVec, t1, t2);
			Float_t phi1, phi2;
			Float_t dPhi = getDeltaPhi(elBeam, elPVec, nuPVec, piPVec, phi1, phi2);
			Float_t theta = getThetaMisPiPi(elBeam, target, elPVec, nuPVec, piPVec);
			return (mM2-pipMass*pipMass)*(mM2-pipMass*pipMass) + dT*dT + dPhi*dPhi + theta*theta;
		}
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
		ROOT::Math::PxPyPzEVector elPVec;
		ROOT::Math::PxPyPzEVector nuPVec;
		ROOT::Math::PxPyPzEVector piPVec;
		Float_t Q2;
		Float_t W;
		Float_t Xbj;
		Float_t tNucleon;
		Float_t tPhoton;
		Float_t deltaT;
		Float_t mM2ep2enPiX;
		Float_t mPep2enPiX;
		Float_t mM2ep2enX;
		Float_t mPep2enX;
		Float_t mM2ep2ePiX;
		Float_t mPep2ePiX;
		Float_t mM2ep2nPiX;
		Float_t mPep2nPiX;
		Float_t phiNuVirPh;
		Float_t phiNuOutPi;
		Float_t deltaPhi;
		Float_t thetaMisPiPi;
		Float_t thetaMisNuNu;
		Float_t thetaElPi;
		Float_t thetaElNu;
		Float_t thetaPiNu;
		Float_t excl4DChi2;
};

class DVpipPnoN{
	public:
		DVpipPnoN() {};
		DVpipPnoN(ROOT::Math::PxPyPzEVector paraBeam, ROOT::Math::PxPyPzEVector paraTarget, ROOT::Math::PxPyPzEVector paraEl, ROOT::Math::PxPyPzEVector paraPi): elBeam(paraBeam), nuTarget(paraTarget), elPVec(paraEl), piPVec(paraPi) {
			misNuPVec = elBeam + nuTarget - elPVec - piPVec;
			misNuPx = misNuPVec.Px();
			misNuPy = misNuPVec.Py();
			misNuPz = misNuPVec.Pz();
			misNuM = misNuPVec.M();
			misNuP = misNuPVec.P();
			misNuE = misNuPVec.E();
			misNuPhi = misNuPVec.Phi() / TMath::Pi() * 180;
			misNuTheta = misNuPVec.Theta() / TMath::Pi() * 180;
			calculateVars();
		};
		void calculateVars() {
			Q2 = -(elBeam - elPVec).M2();
			W = (nuTarget + elBeam - elPVec).M();
			Xbj = Q2 / (2 * nuTarget.M() * (elBeam.E() - elPVec.E()));
			t = (elBeam - elPVec - piPVec).M2();
			ROOT::Math::XYZVector zAxis = (elBeam - elPVec).Vect();  //virtual photon direction
			ROOT::Math::XYZVector yAxis = elBeam.Vect().Cross(elPVec.Vect());  //vertical to leptonic plane
			ROOT::Math::XYZVector xAxis = yAxis.Cross(zAxis);
			ROOT::Math::XYZVector y1Axis = misNuPVec.Vect().Cross(zAxis);  //vertical to hadronic plane
			phi = ROOT::Math::VectorUtil::Angle(y1Axis, yAxis) / TMath::Pi() * 180;
			if (y1Axis.Dot(xAxis) > 0)  phi = 360 - phi;
			mM2ep2ePiX = misNuPVec.M2();
			mPep2ePiX = misNuPVec.P();
			thetaElPi = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), piPVec.Vect()) / TMath::Pi() * 180;
			exclChi2 = (mM2ep2ePiX-neutronMass*neutronMass) * (mM2ep2ePiX-neutronMass*neutronMass);
		};
		static Float_t getExclChi2(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &piPVec) {
			Float_t mM2 = (elBeam + target - elPVec - piPVec).M2();
			return (mM2-neutronMass*neutronMass) * (mM2-neutronMass*neutronMass);
		};
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
		ROOT::Math::PxPyPzEVector elPVec;
		ROOT::Math::PxPyPzEVector piPVec;
		ROOT::Math::PxPyPzEVector misNuPVec;
		Float_t misNuPx;
		Float_t misNuPy;
		Float_t misNuPz;
		Float_t misNuM;
		Float_t misNuP;
		Float_t misNuE;
		Float_t misNuPhi;
		Float_t misNuTheta;
		Float_t Q2;
		Float_t W;
		Float_t Xbj;
		Float_t t;
		Float_t phi;
		Float_t mM2ep2ePiX;
		Float_t mPep2ePiX;
		Float_t thetaElPi;
		Float_t exclChi2;
};

class DVpipiP{
	public:
		DVpipiP() {};
		DVpipiP(ROOT::Math::PxPyPzEVector paraBeam, ROOT::Math::PxPyPzEVector paraTarget, ROOT::Math::PxPyPzEVector paraEl, ROOT::Math::PxPyPzEVector paraNu, ROOT::Math::PxPyPzEVector paraPip, ROOT::Math::PxPyPzEVector paraPim): elBeam(paraBeam), nuTarget(paraTarget), elPVec(paraEl), nuPVec(paraNu), pipPVec(paraPip), pimPVec(paraPim) {
			calculateVars();
		};
		void calculateVars() {
			Q2 = -(elBeam - elPVec).M2();
			W = (nuTarget + elBeam - elPVec).M();
			Xbj = Q2 / (2 * nuTarget.M() * (elBeam.E() - elPVec.E()));
			deltaT = getDeltaT(elBeam, nuTarget, elPVec, nuPVec, pipPVec, pimPVec, tNucleon, tPhoton);
			ROOT::Math::PxPyPzEVector misX = elBeam + nuTarget - elPVec - nuPVec - pipPVec - pimPVec;
			mM2ep2epPiPiX = misX.M2();
			mPep2epPiPiX = misX.P();
			mEep2epPiPiX = misX.E();
			mPXep2epPiPiX = misX.Px();
			mPYep2epPiPiX = misX.Py();
			mPZep2epPiPiX = misX.Pz();
			ROOT::Math::PxPyPzEVector misPim = elBeam + nuTarget - elPVec - nuPVec - pipPVec;
			mM2ep2epPipX = misPim.M2();
			mPep2epPipX = misPim.P();
			ROOT::Math::PxPyPzEVector misPip = elBeam + nuTarget - elPVec - nuPVec - pimPVec;
			mM2ep2epPimX = misPip.M2();
			mPep2epPimX = misPip.P();
			ROOT::Math::PxPyPzEVector misNu = elBeam + nuTarget - elPVec - pipPVec - pimPVec;
			mM2ep2ePiPiX = misNu.M2();
			mPep2ePiPiX = misNu.P();
			ROOT::Math::PxPyPzEVector misEl = elBeam + nuTarget - nuPVec - pipPVec - pimPVec;
			mM2ep2pPiPiX = misEl.M2();
			mPep2pPiPiX = misEl.P();
			deltaPhi = getDeltaPhi(elBeam, elPVec, nuPVec, pipPVec, pimPVec, phiNuVirPh, phiNuOutPi);
			thetaMisPipPip = getThetaMisPipPip(elBeam, nuTarget, elPVec, nuPVec, pipPVec, pimPVec);
			thetaMisPimPim = getThetaMisPimPim(elBeam, nuTarget, elPVec, nuPVec, pipPVec, pimPVec);
			thetaMisNuNu = ROOT::Math::VectorUtil::Angle(misNu.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaElPip = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), pipPVec.Vect()) / TMath::Pi() * 180;
			thetaElPim = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), pimPVec.Vect()) / TMath::Pi() * 180;
			thetaElNu = ROOT::Math::VectorUtil::Angle(elPVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaPipNu = ROOT::Math::VectorUtil::Angle(pipPVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			thetaPimNu = ROOT::Math::VectorUtil::Angle(pimPVec.Vect(), nuPVec.Vect()) / TMath::Pi() * 180;
			excl4DChi2 = deltaT*deltaT + deltaPhi*deltaPhi + thetaMisPipPip*thetaMisPipPip + thetaMisPimPim*thetaMisPimPim;
		};
		static Float_t getDeltaT(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &pipPVec, const ROOT::Math::PxPyPzEVector &pimPVec, Float_t &t1, Float_t &t2) {
			t1 = (nuPVec - target).M2();
			t2 = (elBeam - elPVec - pipPVec - pimPVec).M2();
			return t1 - t2;
		};
		static Float_t getDeltaPhi(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &pipPVec, const ROOT::Math::PxPyPzEVector &pimPVec, Float_t &phi1, Float_t &phi2) {
			ROOT::Math::XYZVector zAxis = (elBeam - elPVec).Vect();  //virtual photon direction
			ROOT::Math::XYZVector yAxis = elBeam.Vect().Cross(elPVec.Vect());  //vertical to leptonic plane
			ROOT::Math::XYZVector xAxis = yAxis.Cross(zAxis);
			ROOT::Math::XYZVector y1Axis = nuPVec.Vect().Cross(zAxis);  //vertical to hadronic plane
			ROOT::Math::XYZVector y2Axis = nuPVec.Vect().Cross((pipPVec+pimPVec).Vect());  //vertical to hadronic plane
			phi1 = ROOT::Math::VectorUtil::Angle(y1Axis, yAxis) / TMath::Pi() * 180;
			if (y1Axis.Dot(xAxis) > 0)  phi1 = 360 - phi1;
			phi2 = ROOT::Math::VectorUtil::Angle(y2Axis, yAxis) / TMath::Pi() * 180;
			if (y2Axis.Dot(xAxis) > 0)  phi2 = 360 - phi2;
			Float_t dPhi = phi1 - phi2;
			if (dPhi > 180)  dPhi -= 360;
			else if (dPhi < -180)  dPhi += 360;
			return dPhi;
		};
		static Float_t getThetaMisPipPip(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &pipPVec, const ROOT::Math::PxPyPzEVector &pimPVec) {
			return ROOT::Math::VectorUtil::Angle((elBeam+target-elPVec-nuPVec-pimPVec).Vect(), pipPVec.Vect()) / TMath::Pi() * 180;
		};
		static Float_t getThetaMisPimPim(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &pipPVec, const ROOT::Math::PxPyPzEVector &pimPVec) {
			return ROOT::Math::VectorUtil::Angle((elBeam+target-elPVec-nuPVec-pipPVec).Vect(), pimPVec.Vect()) / TMath::Pi() * 180;
		};
		static Float_t getExcl4DChi2(const ROOT::Math::PxPyPzEVector &elBeam, const ROOT::Math::PxPyPzEVector &target, const ROOT::Math::PxPyPzEVector &elPVec, const ROOT::Math::PxPyPzEVector &nuPVec, const ROOT::Math::PxPyPzEVector &pipPVec, const ROOT::Math::PxPyPzEVector &pimPVec) {
			Float_t t1, t2;
			Float_t dT = getDeltaT(elBeam, target, elPVec, nuPVec, pipPVec, pimPVec, t1, t2);
			Float_t phi1, phi2;
			Float_t dPhi = getDeltaPhi(elBeam, elPVec, nuPVec, pipPVec, pimPVec, phi1, phi2);
			Float_t theta1 = getThetaMisPipPip(elBeam, target, elPVec, nuPVec, pipPVec, pimPVec);
			Float_t theta2 = getThetaMisPimPim(elBeam, target, elPVec, nuPVec, pipPVec, pimPVec);
			return dT*dT + dPhi*dPhi + theta1*theta1 + theta2*theta2;
		}
		ROOT::Math::PxPyPzEVector elBeam;
		ROOT::Math::PxPyPzEVector nuTarget;
		ROOT::Math::PxPyPzEVector elPVec;
		ROOT::Math::PxPyPzEVector nuPVec;
		ROOT::Math::PxPyPzEVector pipPVec;
		ROOT::Math::PxPyPzEVector pimPVec;
		Float_t Q2;
		Float_t W;
		Float_t Xbj;
		Float_t tNucleon;
		Float_t tPhoton;
		Float_t deltaT;
		Float_t mM2ep2epPiPiX;
		Float_t mPep2epPiPiX;
		Float_t mEep2epPiPiX;
		Float_t mPXep2epPiPiX;
		Float_t mPYep2epPiPiX;
		Float_t mPZep2epPiPiX;
		Float_t mM2ep2epPipX;
		Float_t mPep2epPipX;
		Float_t mM2ep2epPimX;
		Float_t mPep2epPimX;
		Float_t mM2ep2ePiPiX;
		Float_t mPep2ePiPiX;
		Float_t mM2ep2pPiPiX;
		Float_t mPep2pPiPiX;
		Float_t phiNuVirPh;
		Float_t phiNuOutPi;
		Float_t deltaPhi;
		Float_t thetaMisPipPip;
		Float_t thetaMisPimPim;
		Float_t thetaMisNuNu;
		Float_t thetaElPip;
		Float_t thetaElPim;
		Float_t thetaElNu;
		Float_t thetaPipNu;
		Float_t thetaPimNu;
		Float_t excl4DChi2;
};

#endif
