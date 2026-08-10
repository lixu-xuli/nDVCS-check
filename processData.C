#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include "readBank.h"
#include "saveDVCS.h"
#include "QADB.h"

using namespace std;

void processData(string fileName, string dir) {
	auto time_start = chrono::high_resolution_clock::now();
	TChain myChain;
	string path = "/cache/clas12/rg-b/production/recon/spring2019/torus-1/pass2/v0/dst/train/sidisdvcs/";
	if (stoi(fileName) > 10000)
		path = "/cache/clas12/rg-b/production/recon/spring2020/torus-1/pass2/v1/dst/train/sidisdvcs/";
	//string path = "/gpfs02/eic/ztu/CLAS12/forLi/";
	myChain.Add((path+"sidisdvcs_"+fileName+".hipo").c_str());
	auto files = myChain.GetListOfFiles();
	cout << files->At(0)->GetTitle() << endl;
	hipo::reader reader;
	reader.open(files->At(0)->GetTitle());
	hipo::dictionary factory;
	reader.readDictionary(factory);
	//factory.show();
	hipo::bank configBank(factory.getSchema("RUN::config"));
	hipo::bank eventBank(factory.getSchema("REC::Event"));
	hipo::bank particleBank(factory.getSchema("REC::Particle"));
	hipo::bank calBank(factory.getSchema("REC::Calorimeter"));
	hipo::bank sciBank(factory.getSchema("REC::Scintillator"));
	hipo::bank sciExBank(factory.getSchema("REC::ScintExtras"));
	hipo::bank trajBank(factory.getSchema("REC::Traj"));
	hipo::bank trackBank(factory.getSchema("REC::Track"));
	hipo::bank ftBank(factory.getSchema("REC::ForwardTagger"));
	hipo::event event;
	TFile myFile((dir+"/data_"+fileName+".root").c_str(), "recreate");
	recSingleElTree mySingleElTree("singleElTree", 0, 1);
	recDVCSTree myNeDVCSTree("nDVCSTree", 0, 1);
	int iEvent = 0;
	QA::QADB * qa = new QA::QADB("latest");
  	qa->CheckForDefect("TotalOutlier", true);
  	qa->CheckForDefect("TerminalOutlier", true);
  	qa->CheckForDefect("MarginalOutlier", true);
  	qa->CheckForDefect("SectorLoss", true);
  	qa->CheckForDefect("LowLiveTime", true);
  	qa->CheckForDefect("Misc", true);
	qa->CheckForDefect("ChargeHigh", true);
  	qa->CheckForDefect("ChargeNegative", true);
  	qa->CheckForDefect("ChargeUnknown", true);
	qa->CheckForDefect("PossiblyNoBeam", true);
	while (reader.next()) {
		reader.read(event);
		event.getStructure(configBank);
		event.getStructure(eventBank);
		event.getStructure(particleBank);
		event.getStructure(calBank);
		event.getStructure(sciBank);
		event.getStructure(sciExBank);
		event.getStructure(trajBank);
		event.getStructure(trackBank);
		event.getStructure(ftBank);
		globalInfo myGlobalInfo = readGlobalInfo(configBank, eventBank, iEvent);
		if(qa->Pass(myGlobalInfo.runNumber, myGlobalInfo.eventNumber)) {
			mySingleElTree.initialEvent(myGlobalInfo);
			myNeDVCSTree.initialEvent(myGlobalInfo);
			vector<recParticle> elVect;
			vector<recParticle> neVect;
			vector<recParticle> prVect;
			vector<recParticle> phVect;
			readRecParticleBank(particleBank, elVect, neVect, prVect, phVect);
			vector<elDeteInfo> elDeteVect;
			vector<nuDeteInfo> neDeteVect;
			vector<phDeteInfo> phDeteVect;
			CVTInfo trackCVTInfo;
			CTOFInfo clusterCTOFInfo;
			CNDInfo trackCNDInfo;
			CALInfo clusterCALInfo;
			readElDeteBank(calBank, trajBank, trackBank, phVect, elVect, elDeteVect);
			readNuDeteBank(calBank, sciBank, sciExBank, trajBank, neVect, neDeteVect);
			readPhDeteBank(calBank, ftBank, phVect, phDeteVect);
			readCVTTracks(particleBank, trajBank, trackCVTInfo);
			readCTOFClusters(particleBank, sciBank, sciExBank, clusterCTOFInfo);
			readCNDTracks(particleBank, sciBank, sciExBank, trackCNDInfo);
			readCALClusters(particleBank, calBank, clusterCALInfo);
			mySingleElTree.fill(elVect, elDeteVect);
			myNeDVCSTree.fill(elVect, neVect, phVect, elDeteVect, neDeteVect, phDeteVect, trackCVTInfo, clusterCTOFInfo, trackCNDInfo, clusterCALInfo);
		}
		iEvent ++;
	}
	mySingleElTree.write();
	myNeDVCSTree.write();
	myFile.Close();
	auto time_end = chrono::high_resolution_clock::now();
	double elapsed_time_ms = chrono::duration<double, milli> (time_end-time_start).count();
	cout << elapsed_time_ms/1000 << endl;
}
