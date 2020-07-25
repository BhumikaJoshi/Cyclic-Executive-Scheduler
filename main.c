#include "executive.h"
#include "cyclicexe.h"  

int main(int argc, char *argv[])
{
    getTasks(argv[1]);
    findHyperPeriod(argv[2]);
    findBestFrameSize();
    findPeriodicSchedule(argv[3]);
    findFinalPeriodicSchedule(argv[4],argv[5],argv[3],argv[6]);
    return 0;
}
