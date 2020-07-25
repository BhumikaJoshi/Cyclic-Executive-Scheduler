CC=gcc #compiler
TARGET=main
all:	main.o getTasks.o findHyperPeriod.o findBestFrameSize.o findPeriodicSchedule.o findFinalPeriodicSchedule.o
	$(CC) main.c getTasks.c findHyperPeriod.c findBestFrameSize.c findPeriodicSchedule.c findFinalPeriodicSchedule.c getAperiodic.c getSporadic.c getPS.c -o $(TARGET)
run:
	./$(TARGET) $(FILE1) $(FILE2) $(FILE3) $(FILE4) $(FILE5) $(FILE6)
clean:
	rm *.o $(TARGET)
