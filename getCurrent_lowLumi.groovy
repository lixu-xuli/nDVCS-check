import org.jlab.jnp.hipo4.io.HipoReader;
import org.jlab.jnp.hipo4.data.Event;
import org.jlab.jnp.hipo4.data.Bank;
import org.jlab.jnp.hipo4.data.SchemaFactory;
import org.jlab.detector.scalers.DaqScalersSequence;
import java.util.Arrays;
import clasqa.QADB

String runArg = args[0];
int runNo = runArg.toInteger();

String basePath = "/cache/clas12/rg-b/production/recon/spring2019/torus-1/pass2/v0/dst/train/sidisdvcs/";
if (runNo > 10000) {
    basePath = "/cache/clas12/rg-b/production/recon/spring2020/torus-1/pass2/v1/dst/train/sidisdvcs/";
}

String filePath = basePath + "sidisdvcs_" + runArg + ".hipo";
double Ithreshold = 0.0;

println(">>> Initializing QADB...");
QADB qa = new QADB("latest");
qa.checkForDefect("TotalOutlier", true);
qa.checkForDefect("TerminalOutlier", true);
qa.checkForDefect("MarginalOutlier", true);
qa.checkForDefect("SectorLoss", true);
qa.checkForDefect("LowLiveTime", true);
qa.checkForDefect("Misc", false);
qa.checkForDefect("ChargeHigh", true);
qa.checkForDefect("ChargeNegative", true);
qa.checkForDefect("ChargeUnknown", true);
qa.checkForDefect("PossiblyNoBeam", true);

DaqScalersSequence currentSeq = DaqScalersSequence.readSequence([filePath]);
HipoReader reader = new HipoReader();
reader.open(filePath);
SchemaFactory schema = reader.getSchemaFactory();

double sumCurrentAboveThreshold_e = 0.0;
double sumCurrentAboveThreshold2_e = 0.0;
long eventsAboveThreshold_e = 0;
long n_e_events = 0;

Event dataEvent = new Event();
Bank runConfigBank = new Bank(schema.getSchema("RUN::config"));

println(">>> Starting to traverse HIPO file and extract beam current...");

while(reader.hasNext()){
	reader.nextEvent(dataEvent);
	dataEvent.read(runConfigBank);
	if (runConfigBank.getRows() > 0) {
		long timeStamp = runConfigBank.getLong("timestamp", 0);
		int eventNumber = runConfigBank.getInt("event", 0);
		int runNumber = runConfigBank.getInt("run", 0);
		if (qa.pass(runNumber, eventNumber)) {
			double getI = currentSeq.getInterval(timeStamp).getBeamCurrent();
			n_e_events++;
			if (getI > Ithreshold) {
				sumCurrentAboveThreshold_e += getI;
				sumCurrentAboveThreshold2_e += Math.pow(getI, 2);
				eventsAboveThreshold_e++;
			}
		}
	}
}
reader.close();

if (eventsAboveThreshold_e > 0) {
	double aveI_e = sumCurrentAboveThreshold_e / eventsAboveThreshold_e;
	double daveI_e = Math.sqrt((sumCurrentAboveThreshold2_e / eventsAboveThreshold_e) - Math.pow(aveI_e, 2));

	println("==========================================");
	println("                  Results                 ");
	println("==========================================");
	System.out.printf("For e:  Average I = %9.4f +/- %9.4f nA for %12d events with threshold = %6.1f nA.\n", 
			aveI_e, daveI_e, eventsAboveThreshold_e, Ithreshold);
	System.out.printf("Total processed physics events = %9d\n", n_e_events);
	println("==========================================");
} else {
	println("Warning: No valid events found meeting the beam current threshold condition.");
}
