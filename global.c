#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "global.h"
#include "math.h"

bit g_bTrigIn50us, g_bTrigInMs;

void init()
{
	//GPIO INITIAL
	P10_PushPull_Mode;
	P11_PushPull_Mode;
	P12_PushPull_Mode;

	//TIMER 0 須控制在50us，因為有些信號只有300us而已
	//set_M1_T0;
	TIMER0_MODE2_ENABLE;
	TH0=189;
	set_ET0;                                    //enable Timer0 interrupt
	set_EA;                                     //enable interrupts
	set_TR0;                                    //Timer0 run
	
	//PWM Setup
	PWM2_P10_OUTPUT_ENABLE;
	PWM1_P11_OUTPUT_ENABLE;
	PWM0_P12_OUTPUT_ENABLE;
	PWM_IMDEPENDENT_MODE;
	PWM_CLOCK_DIV_2;
	PWMPH = HIBYTE(PWMP);
	PWMPL = LOBYTE(PWMP);
/**********************************************************************
	PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
								= (16MHz/8)/(0x7CF + 1)
								= 1KHz (1ms)
***********************************************************************/

	
	set_LOAD;
  set_PWMRUN;
	

}
/************************************************************************************************************
*    TIMER 0 interrupt subroutine
************************************************************************************************************/
void Timer0_ISR (void) interrupt 1              //interrupt address is 0x000B
{
	static uint8_t o;
	g_bTrigIn50us=1;
		o++;
	if(o==20)
	{
		o=0;
		g_bTrigInMs=1;
	}

}
void workingManager(void)
{
	static float x0=0,x1=3.14*2/3,x2=3.14*4/3;
	uint16_t PHASE0,PHASE1,PHASE2;
	

	x0+=0.01;
	x1+=0.01;
	x2+=0.01;

	PHASE0=((sin(x0)+1)*PWMP)/2;
	PHASE1=((sin(x1)+1)*PWMP)/2;
	PHASE2=((sin(x2)+1)*PWMP)/2;
	
	PWM0H = HIBYTE(PHASE0);		
	PWM0L = HIBYTE(PHASE0);
	
	PWM1H = HIBYTE(PHASE1);		
	PWM1L = HIBYTE(PHASE1);
	
	PWM2H = HIBYTE(PHASE2);		
	PWM2L = HIBYTE(PHASE2);
	set_LOAD;
	


}