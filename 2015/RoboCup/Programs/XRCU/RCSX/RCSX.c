#include "JMLib.c"
#include <GetADScable10.h>
#include "HardwareInfo.c"
#include <GetCompoI3.h>
#include <GetCompassB.h>
#include <SetMotor.h>
signed int vd[361][2]={{100,100},{100,97},{100,93},{100,90},{100,87},{100,84},{100,81},{100,78},{100,75},{100,73},{100,70},{100,67},{100,65},{100,62},{100,60},{100,58},{100,55},{100,53},{100,51},{100,49},{100,47},{100,45},{100,42},{100,40},{100,38},{100,36},{100,34},{100,32},{100,31},{100,29},{100,27},{100,25},{100,23},{100,21},{100,19},{100,18},{100,16},{100,14},{100,12},{100,11},{100,9},{100,7},{100,5},{100,3},{100,2},{100,0},{100,-2},{100,-3},{100,-5},{100,-7},{100,-9},{100,-11},{100,-12},{100,-14},{100,-16},{100,-18},{100,-19},{100,-21},{100,-23},{100,-25},{100,-27},{100,-29},{100,-31},{100,-32},{100,-34},{100,-36},{100,-38},{100,-40},{100,-42},{100,-45},{100,-47},{100,-49},{100,-51},{100,-53},{100,-55},{100,-58},{100,-60},{100,-62},{100,-65},{100,-67},{100,-70},{100,-73},{100,-75},{100,-78},{100,-81},{100,-84},{100,-87},{100,-90},{100,-93},{100,-97},{100,-100},{97,-100},{93,-100},{90,-100},{87,-100},{84,-100},{81,-100},{78,-100},{75,-100},{73,-100},{70,-100},{67,-100},{65,-100},{62,-100},{60,-100},{58,-100},{55,-100},{53,-100},{51,-100},{49,-100},{47,-100},{45,-100},{42,-100},{40,-100},{38,-100},{36,-100},{34,-100},{32,-100},{31,-100},{29,-100},{27,-100},{25,-100},{23,-100},{21,-100},{19,-100},{18,-100},{16,-100},{14,-100},{12,-100},{11,-100},{9,-100},{7,-100},{5,-100},{3,-100},{2,-100},{0,-100},{-2,-100},{-3,-100},{-5,-100},{-7,-100},{-9,-100},{-11,-100},{-12,-100},{-14,-100},{-16,-100},{-18,-100},{-19,-100},{-21,-100},{-23,-100},{-25,-100},{-27,-100},{-29,-100},{-31,-100},{-32,-100},{-34,-100},{-36,-100},{-38,-100},{-40,-100},{-42,-100},{-45,-100},{-47,-100},{-49,-100},{-51,-100},{-53,-100},{-55,-100},{-58,-100},{-60,-100},{-62,-100},{-65,-100},{-67,-100},{-70,-100},{-73,-100},{-75,-100},{-78,-100},{-81,-100},{-84,-100},{-87,-100},{-90,-100},{-93,-100},{-97,-100},{-100,-100},{-100,-97},{-100,-93},{-100,-90},{-100,-87},{-100,-84},{-100,-81},{-100,-78},{-100,-75},{-100,-73},{-100,-70},{-100,-67},{-100,-65},{-100,-62},{-100,-60},{-100,-58},{-100,-55},{-100,-53},{-100,-51},{-100,-49},{-100,-47},{-100,-45},{-100,-42},{-100,-40},{-100,-38},{-100,-36},{-100,-34},{-100,-32},{-100,-31},{-100,-29},{-100,-27},{-100,-25},{-100,-23},{-100,-21},{-100,-19},{-100,-18},{-100,-16},{-100,-14},{-100,-12},{-100,-11},{-100,-9},{-100,-7},{-100,-5},{-100,-3},{-100,-2},{-100,0},{-100,2},{-100,3},{-100,5},{-100,7},{-100,9},{-100,11},{-100,12},{-100,14},{-100,16},{-100,18},{-100,19},{-100,21},{-100,23},{-100,25},{-100,27},{-100,29},{-100,31},{-100,32},{-100,34},{-100,36},{-100,38},{-100,40},{-100,42},{-100,45},{-100,47},{-100,49},{-100,51},{-100,53},{-100,55},{-100,58},{-100,60},{-100,62},{-100,65},{-100,67},{-100,70},{-100,73},{-100,75},{-100,78},{-100,81},{-100,84},{-100,87},{-100,90},{-100,93},{-100,97},{-100,100},{-97,100},{-93,100},{-90,100},{-87,100},{-84,100},{-81,100},{-78,100},{-75,100},{-73,100},{-70,100},{-67,100},{-65,100},{-62,100},{-60,100},{-58,100},{-55,100},{-53,100},{-51,100},{-49,100},{-47,100},{-45,100},{-42,100},{-40,100},{-38,100},{-36,100},{-34,100},{-32,100},{-31,100},{-29,100},{-27,100},{-25,100},{-23,100},{-21,100},{-19,100},{-18,100},{-16,100},{-14,100},{-12,100},{-11,100},{-9,100},{-7,100},{-5,100},{-3,100},{-2,100},{0,100},{2,100},{3,100},{5,100},{7,100},{9,100},{11,100},{12,100},{14,100},{16,100},{18,100},{19,100},{21,100},{23,100},{25,100},{27,100},{29,100},{31,100},{32,100},{34,100},{36,100},{38,100},{40,100},{42,100},{45,100},{47,100},{49,100},{51,100},{53,100},{55,100},{58,100},{60,100},{62,100},{65,100},{67,100},{70,100},{73,100},{75,100},{78,100},{81,100},{84,100},{87,100},{90,100},{93,100},{97,100},{100,100}};

int firval = 0;
int birval = 0;
int firno,birno;
int cpval,apval,cpno,apno,valdiff;

int usf,usb,usl,usr;
int nusf,nusb,nusl,nusr;
int skipf,skipb,skipl,skipr;
int sf,sb,sl,sr;
int cmpr = 0;

int mtrP[4] = {0,0,0,0};
int mtrS[4] = {0,0,0,0};
int mtrC = 0;
int rotD,rotS,rotA;
int traD,traS;
int ballpos,balldist;

int main(void)
{
    X1RCU_Init();
    int traM(int D,int S,int A) { 
    	mtrP[0] = mtrP[3] = vd[D][0]*S/100;
    	mtrP[1] = mtrP[2] = vd[D][1]*S/100;
    	
    	cmpr = (cmpr - A)%360;
    	if (cmpr > 180) {
    		rotS = (360 - cmpr)*5/9;
    		rotD = 0;
    	} else {
    		rotS = cmpr*5/9;
    		rotD = 1;
    	}
    	
    	mtrC = S + rotS;
    	
    	if (rotD == 0) {
    		mtrP[0] -= rotS;
    		mtrP[1] += rotS;
    		mtrP[2] -= rotS;
    		mtrP[3] += rotS;
    	} else if (rotD == 1) {
    		mtrP[0] += rotS;
    		mtrP[1] -= rotS;
    		mtrP[2] += rotS;
    		mtrP[3] -= rotS;
    	}
    	
    	for (int i = 0;i < 4;i++) {
    		if (mtrP[i] < 0) {
    			mtrP[i] = -mtrP[i];
    			mtrS[i] = 2;
    		} else {
    			mtrS[i] = 0;
    		}
    		if (mtrP[i] > 100) {
    			mtrP[i] *= 100/mtrC;
    		}
    		//SetLCD3Char((i*4+1),mtrP[i]);
    	}
    	
    	SetMotor( _MOTOR_NE_,mtrS[0],mtrP[0]);
    	SetMotor( _MOTOR_NW_,mtrS[1],mtrP[1]);
    	SetMotor( _MOTOR_SE_,mtrS[2],mtrP[2]);
    	SetMotor( _MOTOR_SW_,mtrS[3],mtrP[3]);
    	return;
    }
    
    while (1)
    {
        traM(0,30,40);
    }
    return 1;
}

