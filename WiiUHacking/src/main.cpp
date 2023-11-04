#include "program.h"
#include "main.h"
#include "common.h"

struct pygecko_bss_t {
	int error, line;
	void *thread;
	unsigned char stack[0x6F00];
};

void *thread;

#define ASSERT_ALLOCATED(variable, name) \
    if(variable == 0) { \
        char buffer[50] = {0}; \
        __os_snprintf(buffer, 50, "%s allocation failed", name); \
        OSFatal(buffer); \
    }

int Installer(int agrc, char **argv) {
	unsigned int stack = (unsigned int) memalign(0x40, 0x100);
	ASSERT_ALLOCATED(stack, "WiiUHacking stack")
	stack += 0x100;
	OSThread *thread = (OSThread*) memalign(0x40, 0x1000);
	ASSERT_ALLOCATED(thread, "WiiUHacking thread")

	int ret = OSCreateThread(thread, MainThread, 0, NULL, (uint32_t)stack + 0x1000, 0x1000, 0, ((1 << 2) | 8 | 16));
	if(!ret)
	{
		log_printf("Can't creating new thread..\n");
		os_sleep(2);
		return 0;
	}

	if(OSGetTitleID() == 0x000500101004A100 || OSGetTitleID() == 0x000500101004A000 || OSGetTitleID() == 0x000500101004A200)
	{
		log_printf("Can't start game..\n");
		SYSLaunchMenu();
		return -3;
	}

	OSSetThreadName(thread, "WiiUHackingThread");
	OSResumeThread(thread);

	log_print("\n\nWiiUHackingThread starting...\n");
	log_print("Created by cedkeChat and Azaee\n");

    return -3;
}