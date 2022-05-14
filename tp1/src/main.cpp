#include "../include/manager.h"

int main(int argc, char* argv[]){
    Manager mainSchedule;
	mainSchedule.registration();
    mainSchedule.schedule();
    mainSchedule.printSchedule();
    return 0;
}
