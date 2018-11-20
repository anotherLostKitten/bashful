#include "control.h"
// The main function shouldn't ever return because the exit command sends a SIGTERM signal to the process, and that is the intended way of exiting. This function exists so far only to call the control loop.
int main(){
    control();
    return 0;
}
