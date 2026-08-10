#ifndef _READBANK_H
#define _READBANK_H

#include "hipo4/reader.h"
#include "info.h"

globalInfo readGlobalInfo(const hipo::bank &configBank, const hipo::bank &eventBank, const Int_t &index) {
	globalInfo bankInfo;
	bankInfo.runNumber = configBank.getInt("run", 0);
	bankInfo.eventNumber = configBank.getInt("event", 0);
	bankInfo.helicity = eventBank.getInt("helicity", 0);
	bankInfo.hipoIndex = index;
	return bankInfo;
}

recPartInfo readRecParticle(const hipo::bank &particleBank, Int_t iPart) {
	recPartInfo partInfo;
	partInfo.pid = particleBank.getInt("pid", iPart);
	partInfo.px = particleBank.getFloat("px", iPart);
	partInfo.py = particleBank.getFloat("py", iPart);
	partInfo.pz = particleBank.getFloat("pz", iPart);
	partInfo.vx = particleBank.getFloat("vx", iPart);
	partInfo.vy = particleBank.getFloat("vy", iPart);
	partInfo.vz = particleBank.getFloat("vz", iPart);
	partInfo.vt = particleBank.getFloat("vt", iPart);
	partInfo.charge = particleBank.getInt("charge", iPart);
	partInfo.beta = particleBank.getFloat("beta", iPart);
	partInfo.chi2pid = particleBank.getFloat("chi2pid", iPart);
	partInfo.status = particleBank.getInt("status", iPart);
	partInfo.pindex = iPart;
	return partInfo;
}

Int_t readRecMatch(const hipo::bank &matchBank, Int_t iPart) {
	return matchBank.getInt("mcindex", iPart);
}

void addParticle(vector<recParticle> &elVect, vector<recParticle> &neVect, vector<recParticle> &prVect, vector<recParticle> &phVect, recPartInfo partInfo, Int_t mcindex = iniVal) {
	if (partInfo.pid == 0)  return;
	if (abs(partInfo.px) < 1e-6 && abs(partInfo.py) < 1e-6 && abs(partInfo.pz) < 1e-6)  return;
	if (partInfo.beta < 0)  return;
	recParticle newPart(partInfo, mcindex);
	if (partInfo.charge==-1 && partInfo.pid==11)
	    elVect.emplace_back(newPart);
	else if (partInfo.charge==0 && partInfo.pid==2112)
	    neVect.emplace_back(newPart);
	else if (partInfo.charge==1 && partInfo.pid==2212)
	    prVect.emplace_back(newPart);
	else if (partInfo.charge==0 && partInfo.pid==22)
	    phVect.emplace_back(newPart);
}

void readRecParticleBank(const hipo::bank &particleBank, vector<recParticle> &elVect, vector<recParticle> &neVect, vector<recParticle> &prVect, vector<recParticle> &phVect) {
	elVect.clear();
	neVect.clear();
	prVect.clear();
	phVect.clear();
	Int_t nParticle = particleBank.getRows();
	for (Int_t iPart=0; iPart<nParticle; iPart++) {
		recPartInfo partInfo = readRecParticle(particleBank, iPart);
		addParticle(elVect, neVect, prVect, phVect, partInfo);
	}
}

void readRecParticleBank(const hipo::bank &particleBank, const hipo::bank &matchBank, vector<recParticle> &elVect, vector<recParticle> &neVect, vector<recParticle> &prVect, vector<recParticle> &phVect) {
	elVect.clear();
	neVect.clear();
	prVect.clear();
	phVect.clear();
	Int_t nParticle = particleBank.getRows();
	for (Int_t iPart=0; iPart<nParticle; iPart++) {
		recPartInfo partInfo = readRecParticle(particleBank, iPart);
		Int_t mcindex = readRecMatch(matchBank, iPart);
		addParticle(elVect, neVect, prVect, phVect, partInfo, mcindex);
	}
}

void addParticle(vector<recParticle> &elVect, vector<recParticle> &neVect, vector<recParticle> &prVect, vector<recParticle> &phVect, vector<recParticle> &piVect, recPartInfo partInfo, Int_t mcindex = iniVal) {
	if (partInfo.pid == 0)  return;
	if (abs(partInfo.px) < 1e-6 && abs(partInfo.py) < 1e-6 && abs(partInfo.pz) < 1e-6)  return;
	if (partInfo.beta < 0)  return;
	recParticle newPart(partInfo, mcindex);
	if (partInfo.charge==-1 && partInfo.pid==11)
	    elVect.emplace_back(newPart);
	else if (partInfo.charge==0 && partInfo.pid==2112)
	    neVect.emplace_back(newPart);
	else if (partInfo.charge==1 && partInfo.pid==2212)
	    prVect.emplace_back(newPart);
	else if (partInfo.charge==0 && partInfo.pid==22)
	    phVect.emplace_back(newPart);
	else if (partInfo.charge==1 && partInfo.pid==211)
		piVect.emplace_back(newPart);
}

void readRecParticleBank(const hipo::bank &particleBank, vector<recParticle> &elVect, vector<recParticle> &neVect, vector<recParticle> &prVect, vector<recParticle> &phVect, vector<recParticle> &piVect) {
	elVect.clear();
	neVect.clear();
	prVect.clear();
	phVect.clear();
	piVect.clear();
	Int_t nParticle = particleBank.getRows();
	for (Int_t iPart=0; iPart<nParticle; iPart++) {
		recPartInfo partInfo = readRecParticle(particleBank, iPart);
		addParticle(elVect, neVect, prVect, phVect, piVect, partInfo);
	}
}

void readRecParticleBank(const hipo::bank &particleBank, const hipo::bank &matchBank, vector<recParticle> &elVect, vector<recParticle> &neVect, vector<recParticle> &prVect, vector<recParticle> &phVect, vector<recParticle> &piVect) {
	elVect.clear();
	neVect.clear();
	prVect.clear();
	phVect.clear();
	piVect.clear();
	Int_t nParticle = particleBank.getRows();
	for (Int_t iPart=0; iPart<nParticle; iPart++) {
		recPartInfo partInfo = readRecParticle(particleBank, iPart);
		Int_t mcindex = readRecMatch(matchBank, iPart);
		addParticle(elVect, neVect, prVect, phVect, piVect, partInfo, mcindex);
	}
}

void addParticle(vector<recParticle> &elVect, vector<recParticle> &neVect, vector<recParticle> &prVect, vector<recParticle> &phVect, vector<recParticle> &pipVect, vector<recParticle> &pimVect, recPartInfo partInfo, Int_t mcindex = iniVal) {
	if (partInfo.pid == 0)  return;
	if (abs(partInfo.px) < 1e-6 && abs(partInfo.py) < 1e-6 && abs(partInfo.pz) < 1e-6)  return;
	if (partInfo.beta < 0)  return;
	recParticle newPart(partInfo, mcindex);
	if (partInfo.charge==-1 && partInfo.pid==11)
	    elVect.emplace_back(newPart);
	else if (partInfo.charge==0 && partInfo.pid==2112)
	    neVect.emplace_back(newPart);
	else if (partInfo.charge==1 && partInfo.pid==2212)
	    prVect.emplace_back(newPart);
	else if (partInfo.charge==0 && partInfo.pid==22)
	    phVect.emplace_back(newPart);
	else if (partInfo.charge==1 && partInfo.pid==211)
		pipVect.emplace_back(newPart);
	else if (partInfo.charge==-1 && partInfo.pid==-211)
		pimVect.emplace_back(newPart);
}

void readRecParticleBank(const hipo::bank &particleBank, vector<recParticle> &elVect, vector<recParticle> &neVect, vector<recParticle> &prVect, vector<recParticle> &phVect, vector<recParticle> &pipVect, vector<recParticle> &pimVect) {
	elVect.clear();
	neVect.clear();
	prVect.clear();
	phVect.clear();
	pipVect.clear();
	pimVect.clear();
	Int_t nParticle = particleBank.getRows();
	for (Int_t iPart=0; iPart<nParticle; iPart++) {
		recPartInfo partInfo = readRecParticle(particleBank, iPart);
		addParticle(elVect, neVect, prVect, phVect, pipVect, pimVect, partInfo);
	}
}

void readMCParticleBank(const hipo::bank &particleBank, const hipo::bank &matchBank, vector<mcParticle> &mcPartVect) {
	mcPartVect.clear();
	Int_t nParticle = particleBank.getRows();
	for (Int_t iPart=0; iPart<nParticle; iPart++) {
		mcPartInfo myInfo;
		myInfo.pid = particleBank.getInt("pid", iPart);
		myInfo.px = particleBank.getFloat("px", iPart);
		myInfo.py = particleBank.getFloat("py", iPart);
		myInfo.pz = particleBank.getFloat("pz", iPart);
		myInfo.vx = particleBank.getFloat("vx", iPart);
		myInfo.vy = particleBank.getFloat("vy", iPart);
		myInfo.vz = particleBank.getFloat("vz", iPart);
		myInfo.vt = particleBank.getFloat("vt", iPart);
		myInfo.mcindex = iPart;
		Int_t pindex = matchBank.getInt("pindex", iPart);
		mcParticle newPart(myInfo, pindex);
        mcPartVect.emplace_back(newPart);
	}
}

Int_t trajSector(Float_t phi) {
    if (phi < 30 && phi >= -30)
        return 1;
    else if (phi < 90 && phi >= 30)
        return 2;
    else if (phi < 150 && phi >= 90)
        return 3;
    else if (phi >= 150 || phi < -150)
        return 4;
    else if (phi < -90 && phi >= -150)
        return 5;
    else if (phi < -30 && phi >= -90)
        return 6;
    return 0;
}

Float_t getPhi(Float_t x, Float_t y) {
	return TMath::ATan2(y, x) / TMath::Pi() * 180;
}

Float_t getTheta(Float_t x, Float_t y, Float_t z) {
	return TMath::ACos(z / TMath::Sqrt(x*x + y*y + z*z)) / TMath::Pi() * 180;
}

Float_t getConeAngle(Float_t x1, Float_t y1, Float_t z1, Float_t x2, Float_t y2, Float_t z2) {
	Float_t r1 = TMath::Sqrt(x1*x1 + y1*y1 + z1*z1);
	Float_t r2 = TMath::Sqrt(x2*x2 + y2*y2 + z2*z2);
	return TMath::ACos((x1*x2 + y1*y2 + z1*z2) / (r1*r2)) / TMath::Pi() * 180;
}

void readCALInfo(const hipo::bank &calBank, Int_t nCal, Int_t pindex, Int_t (&sectorCAL)[3], Float_t (&energyCAL)[3], Float_t (&xCAL)[3], Float_t (&yCAL)[3], Float_t (&zCAL)[3], Float_t (&luCAL)[3], Float_t (&lvCAL)[3], Float_t (&lwCAL)[3], Float_t (&phiCAL)[3], Float_t (&thetaCAL)[3], Float_t (&timeCAL)[3], Float_t (&pathCAL)[3], Float_t &energySumCAL) {
	for (Int_t iCal=0; iCal<nCal; iCal++) {
		Int_t pindexCal = calBank.getInt("pindex", iCal);
		if (pindexCal != pindex)  continue;
		Int_t layerCal = calBank.getInt("layer", iCal);
		Int_t iLayer = -1;
		if (layerCal == 1)  iLayer = 0;
		else if (layerCal == 4)  iLayer = 1;
		else if (layerCal == 7)  iLayer = 2;
		else  continue;
		sectorCAL[iLayer] = calBank.getInt("sector", iCal);
		energyCAL[iLayer] = calBank.getFloat("energy", iCal);
		xCAL[iLayer] = calBank.getFloat("x", iCal);
		yCAL[iLayer] = calBank.getFloat("y", iCal);
		zCAL[iLayer] = calBank.getFloat("z", iCal);
		luCAL[iLayer] = calBank.getFloat("lu", iCal);
		lvCAL[iLayer] = calBank.getFloat("lv", iCal);
		lwCAL[iLayer] = calBank.getFloat("lw", iCal);
		phiCAL[iLayer] = getPhi(xCAL[iLayer], yCAL[iLayer]);
		thetaCAL[iLayer] = getTheta(xCAL[iLayer], yCAL[iLayer], zCAL[iLayer]);
		timeCAL[iLayer] = calBank.getFloat("time", iCal);
		pathCAL[iLayer] = calBank.getFloat("path", iCal);
	}
	energySumCAL = energyCAL[0] + energyCAL[1] + energyCAL[2];
}

void readDCInfo(const hipo::bank &trajBank, Int_t nTraj, Int_t pindex, Int_t (&sectorDC)[3], Float_t (&xDC)[3], Float_t (&yDC)[3], Float_t (&zDC)[3], Float_t (&phiDC)[3], Float_t (&thetaDC)[3], Float_t (&edgeDC)[3]) {
	for (Int_t iTraj=0; iTraj<nTraj; iTraj++) {
		Int_t pindexTraj = trajBank.getInt("pindex", iTraj);
		if (pindexTraj != pindex)  continue;
		Int_t detectorTraj = trajBank.getInt("detector", iTraj);
		if (detectorTraj != 6)  continue;
		Int_t layerTraj = trajBank.getInt("layer", iTraj);
		Int_t iLayer = -1;
		if (layerTraj == 6)  iLayer = 0;
		else if (layerTraj == 18)  iLayer = 1;
		else if (layerTraj == 36)  iLayer = 2;
		else  continue;
		xDC[iLayer] = trajBank.getFloat("x", iTraj);
		yDC[iLayer] = trajBank.getFloat("y", iTraj);
		zDC[iLayer] = trajBank.getFloat("z", iTraj);
		edgeDC[iLayer] = trajBank.getFloat("edge", iTraj);
		phiDC[iLayer] = getPhi(xDC[iLayer], yDC[iLayer]);
		thetaDC[iLayer] = getTheta(xDC[iLayer], yDC[iLayer], zDC[iLayer]);
		sectorDC[iLayer] = trajSector(phiDC[iLayer]);
	}
}

void readTrackInfo(const hipo::bank &trackBank, Int_t nTrack, Int_t pindex, Int_t &sectorTrack, Float_t &chi2Track, Int_t &ndfTrack, Float_t &chi2ndfTrack) {
	for (Int_t iTrack=0; iTrack<nTrack; iTrack++) {
		Int_t pindexTrack = trackBank.getInt("pindex", iTrack);
		if (pindexTrack != pindex)  continue;
		Int_t detectorTrack = trackBank.getInt("detector", iTrack);
		if (detectorTrack != 6)  continue;
		sectorTrack = trackBank.getInt("sector", iTrack);
		chi2Track = trackBank.getFloat("chi2", iTrack);
		ndfTrack = trackBank.getInt("NDF", iTrack);
		chi2ndfTrack = chi2Track / ndfTrack;
	}
}

void readSciCDInfo(const hipo::bank &sciBank, const hipo::bank &sciExBank, Int_t nSci, Int_t pindex, Int_t &nLayerCND, Int_t &lastLayerCND, Int_t (&layerSciCD)[4], Float_t (&energySciCD)[4], Float_t (&xSciCD)[4], Float_t (&ySciCD)[4], Float_t (&zSciCD)[4], Float_t (&phiSciCD)[4], Float_t (&thetaSciCD)[4], Float_t (&timeSciCD)[4], Float_t (&pathSciCD)[4], Float_t (&dedxSciCD)[4], Int_t (&sizeSciCD)[4], Int_t (&layermultSciCD)[4]) {
	nLayerCND = 0;
	lastLayerCND = -1;
	for (Int_t iSci=0; iSci<nSci; iSci++) {
		Int_t pindexSci = sciBank.getInt("pindex", iSci);
		if (pindexSci != pindex)  continue;
		Int_t detectorSci = sciBank.getInt("detector", iSci);
		if (detectorSci != 3 && detectorSci != 4)  continue;
		Int_t layerSci = sciBank.getInt("layer", iSci);
		Int_t iLayer = -1;
		if (detectorSci == 3 && layerSci == 1) {
			iLayer = 1;
			nLayerCND += 1;
			if (lastLayerCND < iLayer)  lastLayerCND = iLayer;
		}
		else if (detectorSci == 3 && layerSci == 2) {
			iLayer = 2;
			nLayerCND += 1;
			if (lastLayerCND < iLayer)  lastLayerCND = iLayer;
		}
		else if (detectorSci == 3 && layerSci == 3) {
			iLayer = 3;
			nLayerCND += 1;
			if (lastLayerCND < iLayer)  lastLayerCND = iLayer;
		}
		else if (detectorSci == 4 && layerSci == 1)  iLayer = 0;
		else  continue;
		layerSciCD[iLayer] = layerSci;
		energySciCD[iLayer] = sciBank.getFloat("energy", iSci);
		xSciCD[iLayer] = sciBank.getFloat("x", iSci);
		ySciCD[iLayer] = sciBank.getFloat("y", iSci);
		zSciCD[iLayer] = sciBank.getFloat("z", iSci);
		phiSciCD[iLayer] = getPhi(xSciCD[iLayer], ySciCD[iLayer]);
		thetaSciCD[iLayer] = getTheta(xSciCD[iLayer], ySciCD[iLayer], zSciCD[iLayer]);
		timeSciCD[iLayer] = sciBank.getFloat("time", iSci);
		pathSciCD[iLayer] = sciBank.getFloat("path", iSci);
		dedxSciCD[iLayer] = sciExBank.getFloat("dedx", iSci);
		sizeSciCD[iLayer] = sciExBank.getInt("size", iSci);
		layermultSciCD[iLayer] = sciExBank.getInt("layermult", iSci);
	}
}

void readFTInfo(const hipo::bank &ftBank, Int_t nFT, Int_t pindex, Float_t &xFT, Float_t &yFT, Float_t &zFT, Float_t &energyFT) {
	for (Int_t iFT=0; iFT<nFT; iFT++) {
		Int_t pindexFT = ftBank.getInt("pindex", iFT);
		if (pindexFT != pindex)  continue;
		Int_t detectorFT = ftBank.getInt("detector", iFT);
		if (detectorFT != 10)  continue;
		Int_t layerFT = ftBank.getInt("layer", iFT);
		if (layerFT == 1) {
			xFT = ftBank.getFloat("x", iFT);
			yFT = ftBank.getFloat("y", iFT);
			zFT = ftBank.getFloat("z", iFT);
			energyFT = ftBank.getFloat("energy", iFT);
		}
	}
}

void readRadPhInfo(const vector<recParticle> &phVect, const recParticle &elPart, Int_t &nPh, Int_t &numPh, Int_t (&pindex)[10], Float_t (&pPh)[10], Float_t (&pxPh)[10], Float_t (&pyPh)[10], Float_t (&pzPh)[10], Float_t (&anglePh)[10], Float_t (&dThetaPh)[10], Float_t (&dPhiPh)[10]) {
	Int_t num = phVect.size();
	nPh = 0;
	numPh = 0;
	for (Int_t iPh=0; iPh<num; iPh++) {
		Float_t dTheta = getTheta(phVect[iPh].px, phVect[iPh].py, phVect[iPh].pz) - getTheta(elPart.px, elPart.py, elPart.pz);
		Float_t dPhi = getPhi(phVect[iPh].px, phVect[iPh].py) - getPhi(elPart.px, elPart.py);
		if (dPhi < -180)  dPhi += 360;
		else if (dPhi > 180)  dPhi -= 360;
		if (abs(dTheta) < 2 && abs(dPhi) < 45) {
			if (nPh < 10) {
				pindex[numPh] = phVect[iPh].pindex;
				pxPh[numPh] = phVect[iPh].px;
				pyPh[numPh] = phVect[iPh].py;
				pzPh[numPh] = phVect[iPh].pz;
				pPh[numPh] = TMath::Sqrt(pxPh[nPh]*pxPh[nPh] + pyPh[nPh]*pyPh[nPh] + pzPh[nPh]*pzPh[nPh]);
				anglePh[numPh] = getConeAngle(elPart.px, elPart.py, elPart.pz, phVect[iPh].px, phVect[iPh].py, phVect[iPh].pz);
				dThetaPh[numPh] = dTheta;
				dPhiPh[numPh] = dPhi;
				numPh ++;
			}
			nPh ++;
		}
	}
}

void readElDeteBank(const hipo::bank &calBank, const hipo::bank &trajBank, const hipo::bank &trackBank, const vector<recParticle> &phVect, const vector<recParticle> &elVect, vector<elDeteInfo> &elDeteVect) {
	elDeteVect.clear();
	Int_t num = elVect.size();
	Int_t nCal = calBank.getRows();
	Int_t nTraj = trajBank.getRows();
	Int_t nTrack = trackBank.getRows();
	for (Int_t iEl=0; iEl<num; iEl++) {
		elDeteInfo myInfo = {0};
		Int_t pindex = elVect[iEl].pindex;
		readCALInfo(calBank, nCal, pindex, myInfo.sectorCAL, myInfo.energyCAL, myInfo.xCAL, myInfo.yCAL, myInfo.zCAL, myInfo.luCAL, myInfo.lvCAL, myInfo.lwCAL, myInfo.phiCAL, myInfo.thetaCAL, myInfo.timeCAL, myInfo.pathCAL, myInfo.energySumCAL);
		readDCInfo(trajBank, nTraj, pindex, myInfo.sectorDC, myInfo.xDC, myInfo.yDC, myInfo.zDC, myInfo.phiDC, myInfo.thetaDC, myInfo.edgeDC);
		readTrackInfo(trackBank, nTrack, pindex, myInfo.sectorTrack, myInfo.chi2Track, myInfo.ndfTrack, myInfo.chi2ndfTrack);
		readRadPhInfo(phVect, elVect[iEl], myInfo.nPh, myInfo.num, myInfo.pindexPh, myInfo.pPh, myInfo.pxPh, myInfo.pyPh, myInfo.pzPh, myInfo.anglePh, myInfo.dThetaPh, myInfo.dPhiPh);
		elDeteVect.emplace_back(myInfo);
	}
}

void readNuDeteBank(const hipo::bank &calBank, const hipo::bank &sciBank, const hipo::bank &sciExBank, const hipo::bank &trajBank, vector<recParticle> &nuVect, vector<nuDeteInfo> &nuDeteVect) {
	nuDeteVect.clear();
	Int_t num = nuVect.size();
	Int_t nCal = calBank.getRows();
	Int_t nSci = sciBank.getRows();
	Int_t nTraj = trajBank.getRows();
	for (Int_t iNu=0; iNu<num; iNu++) {
		nuDeteInfo myInfo = {0};
		Int_t pindex = nuVect[iNu].pindex;
		readCALInfo(calBank, nCal, pindex, myInfo.sectorCAL, myInfo.energyCAL, myInfo.xCAL, myInfo.yCAL, myInfo.zCAL, myInfo.luCAL, myInfo.lvCAL, myInfo.lwCAL, myInfo.phiCAL, myInfo.thetaCAL, myInfo.timeCAL, myInfo.pathCAL, myInfo.energySumCAL);
		readSciCDInfo(sciBank, sciExBank, nSci, pindex, myInfo.nLayerCND, myInfo.lastLayerCND, myInfo.layerSciCD, myInfo.energySciCD, myInfo.xSciCD, myInfo.ySciCD, myInfo.zSciCD, myInfo.phiSciCD, myInfo.thetaSciCD, myInfo.timeSciCD, myInfo.pathSciCD, myInfo.dedxSciCD, myInfo.sizeSciCD, myInfo.layermultSciCD);
		readDCInfo(trajBank, nTraj, pindex, myInfo.sectorDC, myInfo.xDC, myInfo.yDC, myInfo.zDC, myInfo.phiDC, myInfo.thetaDC, myInfo.edgeDC);
		nuDeteVect.emplace_back(myInfo);
	}
	Float_t minTime[6] = {1e3, 1e3, 1e3, 1e3, 1e3, 1e3};
	Float_t minIndex[6] = {-1, -1, -1, -1, -1, -1};
	vector<Int_t> neFlag(num, 0);
	for (Int_t iNu=0; iNu<num; iNu++) {
		Int_t pid = nuVect[iNu].pid;
		Int_t status = nuVect[iNu].status;
		if (pid == 2112 && status < 3000) {
			Int_t sector = nuDeteVect[iNu].sectorCAL[0];
			Float_t time = nuDeteVect[iNu].timeCAL[0];
			if (sector == 0) {
				sector = nuDeteVect[iNu].sectorCAL[1];
				time = nuDeteVect[iNu].timeCAL[1];
				if (sector == 0) {
					sector = nuDeteVect[iNu].sectorCAL[2];
					time = nuDeteVect[iNu].timeCAL[2];
				}
			}
			//cout << iNu << " in " << num << " " << sector << " " << nuDeteVect[iNu].timeCAL[0] << " " << nuDeteVect[iNu].timeCAL[1] << " " << nuDeteVect[iNu].timeCAL[2] << endl;
			if (time < minTime[sector-1]) {
				if (minIndex[sector-1] != -1) {
					neFlag[minIndex[sector-1]] = 1;
				}
				minTime[sector-1] = time;
				minIndex[sector-1] = iNu;
			}
			else {
				neFlag[iNu] = 1;
			}
		}
	}
	Int_t nDel = 0;
	for (Int_t iNu=0; iNu<num; iNu++) {
		if (neFlag[iNu]) {
			nuVect.erase(nuVect.begin() + iNu - nDel);
			nuDeteVect.erase(nuDeteVect.begin() + iNu - nDel);
			nDel++;
		}
	}
	/*
	for (Int_t iNu=0; iNu<nuDeteVect.size(); iNu++) {
		Int_t pid = nuVect[iNu].pid;
		Int_t status = nuVect[iNu].status;
		if (pid == 2112 && status < 3000) {
			Int_t sector = nuDeteVect[iNu].sectorCAL[0];
			Float_t time = nuDeteVect[iNu].timeCAL[0];
			if (sector == 0) {
				sector = nuDeteVect[iNu].sectorCAL[1];
				time = nuDeteVect[iNu].timeCAL[1];
				if (sector == 0) {
					sector = nuDeteVect[iNu].sectorCAL[2];
					time = nuDeteVect[iNu].timeCAL[2];
				}
			}
			cout << "after " << iNu << " in " << nuDeteVect.size() << " " << sector << " " << nuDeteVect[iNu].timeCAL[0] << " " << nuDeteVect[iNu].timeCAL[1] << " " << nuDeteVect[iNu].timeCAL[2] << endl;
		}
	}
	*/
}

void readPhDeteBank(const hipo::bank &calBank, const hipo::bank &ftBank, const vector<recParticle> &phVect, vector<phDeteInfo> &phDeteVect) {
	phDeteVect.clear();
	Int_t num = phVect.size();
	Int_t nCal = calBank.getRows();
	Int_t nFT = ftBank.getRows();
	for (Int_t iPh=0; iPh<num; iPh++) {
		phDeteInfo myInfo = {0};
		Int_t pindex = phVect[iPh].pindex;
		readCALInfo(calBank, nCal, pindex, myInfo.sectorCAL, myInfo.energyCAL, myInfo.xCAL, myInfo.yCAL, myInfo.zCAL, myInfo.luCAL, myInfo.lvCAL, myInfo.lwCAL, myInfo.phiCAL, myInfo.thetaCAL, myInfo.timeCAL, myInfo.pathCAL, myInfo.energySumCAL);
		readFTInfo(ftBank, nFT, pindex, myInfo.xFT, myInfo.yFT, myInfo.zFT, myInfo.energyFT);
		phDeteVect.emplace_back(myInfo);
	}
}

void readCVTTracks(const hipo::bank &particleBank, const hipo::bank &trajBank, CVTInfo &myInfo) {
	myInfo = {0};
	Int_t nTraj = trajBank.getRows();
	Int_t iCVT = 0;
	Int_t startP = -1;
	for (Int_t iTraj=0; iTraj<nTraj; iTraj++) {
		Int_t detectorTraj = trajBank.getInt("detector", iTraj);
		if (detectorTraj != 5)  continue;
		myInfo.nCluster += 1;
		Int_t pindex = trajBank.getInt("pindex", iTraj);
		if (pindex > startP) {
			startP = pindex;
			myInfo.nTrack += 1;
		}
		if (iCVT >= 100)  continue;
		myInfo.num += 1;
		myInfo.pindexCVT[iCVT] = pindex;
		myInfo.pidCVT[iCVT] = particleBank.getInt("pid", pindex);
		myInfo.layerCVT[iCVT] = trajBank.getInt("layer", iTraj);
		myInfo.xCVT[iCVT] = trajBank.getFloat("x", iTraj);
		myInfo.yCVT[iCVT] = trajBank.getFloat("y", iTraj);
		myInfo.zCVT[iCVT] = trajBank.getFloat("z", iTraj);
		myInfo.phiCVT[iCVT] = getPhi(myInfo.xCVT[iCVT], myInfo.yCVT[iCVT]);
		myInfo.thetaCVT[iCVT] = getTheta(myInfo.xCVT[iCVT], myInfo.yCVT[iCVT], myInfo.zCVT[iCVT]);
		iCVT ++;
	}
}

void readCTOFClusters(const hipo::bank &particleBank, const hipo::bank &sciBank, const hipo::bank &sciExBank, CTOFInfo &myInfo) {
	myInfo = {0};
	Int_t nSci = sciBank.getRows();
	Int_t iCTOF = 0;
	for (Int_t iSci=0; iSci<nSci; iSci++) {
		Int_t detectorSci = sciBank.getInt("detector", iSci);
		if (detectorSci != 4)  continue;
		myInfo.nCluster += 1;
		Int_t pindex = sciBank.getInt("pindex", iSci);
		if (iCTOF >= 20)  continue;
		myInfo.num += 1;
		myInfo.pindexCTOF[iCTOF] = pindex;
		myInfo.pidCTOF[iCTOF] = particleBank.getInt("pid", pindex);
		myInfo.layerCTOF[iCTOF] = sciBank.getInt("layer", iSci);
		myInfo.energyCTOF[iCTOF] = sciBank.getFloat("energy", iSci);
		myInfo.xCTOF[iCTOF] = sciBank.getFloat("x", iSci);
		myInfo.yCTOF[iCTOF] = sciBank.getFloat("y", iSci);
		myInfo.zCTOF[iCTOF] = sciBank.getFloat("z", iSci);
		myInfo.tCTOF[iCTOF] = sciBank.getFloat("time", iSci);
		myInfo.phiCTOF[iCTOF] = getPhi(myInfo.xCTOF[iCTOF], myInfo.yCTOF[iCTOF]);
		myInfo.thetaCTOF[iCTOF] = getTheta(myInfo.xCTOF[iCTOF], myInfo.yCTOF[iCTOF], myInfo.zCTOF[iCTOF]);
		myInfo.dedxCTOF[iCTOF] = sciExBank.getFloat("dedx", iSci);
		myInfo.sizeCTOF[iCTOF] = sciExBank.getInt("size", iSci);
		myInfo.layermultCTOF[iCTOF] = sciExBank.getInt("layermult", iSci);
		iCTOF ++;
	}
}

void readCNDTracks(const hipo::bank &particleBank, const hipo::bank &sciBank, const hipo::bank &sciExBank, CNDInfo &myInfo) {
	myInfo = {0};
	Int_t nSci = sciBank.getRows();
	Int_t iCND = 0;
	Int_t startP = -1;
	for (Int_t iSci=0; iSci<nSci; iSci++) {
		Int_t detectorSci = sciBank.getInt("detector", iSci);
		if (detectorSci != 3)  continue;
		myInfo.nCluster += 1;
		Int_t pindex = sciBank.getInt("pindex", iSci);
		if (pindex > startP) {
			startP = pindex;
			myInfo.nTrack += 1;
		}
		if (iCND >= 30)  continue;
		myInfo.num += 1;
		myInfo.pindexCND[iCND] = pindex;
		myInfo.pidCND[iCND] = particleBank.getInt("pid", pindex);
		myInfo.layerCND[iCND] = sciBank.getInt("layer", iSci);
		myInfo.energyCND[iCND] = sciBank.getFloat("energy", iSci);
		myInfo.xCND[iCND] = sciBank.getFloat("x", iSci);
		myInfo.yCND[iCND] = sciBank.getFloat("y", iSci);
		myInfo.zCND[iCND] = sciBank.getFloat("z", iSci);
		myInfo.tCND[iCND] = sciBank.getFloat("time", iSci);
		myInfo.phiCND[iCND] = getPhi(myInfo.xCND[iCND], myInfo.yCND[iCND]);
		myInfo.thetaCND[iCND] = getTheta(myInfo.xCND[iCND], myInfo.yCND[iCND], myInfo.zCND[iCND]);
		myInfo.dedxCND[iCND] = sciExBank.getFloat("dedx", iSci);
		myInfo.sizeCND[iCND] = sciExBank.getInt("size", iSci);
		myInfo.layermultCND[iCND] = sciExBank.getInt("layermult", iSci);
		iCND ++;
	}
}

void readCALClusters(const hipo::bank &particleBank, const hipo::bank &calBank, CALInfo &myInfo) {
	myInfo = {0};
	Int_t nCal = calBank.getRows();
	Int_t startP = -1;
	for (Int_t iCal=0; iCal<nCal; iCal++) {
		Int_t detectorCal = calBank.getInt("detector", iCal);
		myInfo.nCluster += 1;
		Int_t pindex = calBank.getInt("pindex", iCal);
		Int_t pid = particleBank.getInt("pid", pindex);
		Int_t px = particleBank.getFloat("px", pindex);
		Int_t py = particleBank.getFloat("py", pindex);
		Int_t pz = particleBank.getFloat("pz", pindex);
		if (pindex > startP) {
			startP = pindex;
			myInfo.nParticle += 1;
			if (pid == 2112)
				myInfo.nNeutron += 1;
			if (pid == 2112 && (abs(px)>1e-6 || abs(py)>1e-6 || abs(pz)>1e-6))
				myInfo.nNeutronNew += 1;
		}
		if (iCal >= 30)  continue;
		myInfo.num += 1;
		myInfo.pindexCAL[iCal] = pindex;
		myInfo.pidCAL[iCal] = pid;
		myInfo.layerCAL[iCal] = calBank.getInt("layer", iCal);
		myInfo.sectorCAL[iCal] = calBank.getInt("sector", iCal);
		myInfo.energyCAL[iCal] = calBank.getFloat("energy", iCal);
		myInfo.timeCAL[iCal] = calBank.getFloat("time", iCal);
		myInfo.pathCAL[iCal] = calBank.getFloat("path", iCal);
		myInfo.xCAL[iCal] = calBank.getFloat("x", iCal);
		myInfo.yCAL[iCal] = calBank.getFloat("y", iCal);
		myInfo.zCAL[iCal] = calBank.getFloat("z", iCal);
	}
}

#endif
