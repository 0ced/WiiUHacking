#include "program.h"
#include "common.h"

int MainThread(int argc, void* argv)
{	
    uint64_t TitleID = OSGetTitleID();
	if(TitleID != 0x00050000101d7500) 
    {
        log_print("can't start game with menu..");
        return 0;
    }

	//code here

	return 0;

}