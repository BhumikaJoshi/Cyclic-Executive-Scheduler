BHUMIKA JOSHI

List of files:

executive.h:implementation file for periodic schedule 
cyclicexe.h: implementation file for cyclic executive periodic schedule
inputFile.txt: to take input tasks
Makefile: 
main.c: 
getTasks.c
findHyperPeriod.c
findBestFrameSize.c
hpU.txt: 
findPeriodicSchedule.c
periodicSchedule.txt:
getPS.c: take schedule input
inputAperiodic.txt: input tasks aperiodic
getAperiodic.c:to take input tasks aperiodic
inputSporadic.txt: input tasks sporadic
getSporadic.c:to take input tasks sporadic
findFinalPeriodicSchedule.c
finalPeriodicSchedule.txt


Assumptions

1. Time when taken as int then stored in float value gives best answer otherwise C makes it lossy.
2. Input file should be terminated with a line to take input correctly.
3. Assumed Granularity to be 0.5 ms


How to run

Open the terminal and go to location where folder is present
Run the following commands one by one:

make all
make run FILE1=inputFile.txt FILE2=hpU.txt FILE3=periodicSchedule.txt FILE4=inputAperiodic.txt FILE5=inputSporadic.txt FILE6=finalPeriodicSchedule.txt

Structure of program: Have implemented task splitting by using some concepts of INF.
Firstly finding best number of frames by implementing frame splitting then finding periodic schedule. 
Have also implemented sporadic tasks using Cyclic EDF.
