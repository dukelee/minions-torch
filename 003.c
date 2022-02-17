#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "global.h"



void main(void)
{
	init();
    while(1)
    {
			if(g_bTrigIn50us)
			{
				g_bTrigIn50us=0;
			}
			if(g_bTrigInMs)
			{
				g_bTrigInMs=0;
				workingManager();
			}
			set_WDCLR;
    }
}