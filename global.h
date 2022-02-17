#define ledGroup1		P10
#define ledGroup2		P11
#define ledGroup3		P12

#define PWMP	0x07CF

extern bit g_bTrigIn50us, g_bTrigInMs;

void init();
void workingManager(void);