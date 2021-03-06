#include "HardwareInfo.c"
#include "JMLib.c"
#include <GetADScable10.h>
#include <GetAdUltrasound.h>
#include <SetMotor.h>
#include <SetLCDBack.h>
#include <SetLCD3Char.h>
#include <GetCompassB.h>
#include <GetCompoI3.h>
#include <Math.h>

//important arrays
signed int vd[361][2]={{100,100},{100,97},{100,93},{100,90},{100,87},{100,84},{100,81},{100,78},{100,75},{100,73},{100,70},{100,67},{100,65},{100,62},{100,60},{100,58},{100,55},{100,53},{100,51},{100,49},{100,47},{100,45},{100,42},{100,40},{100,38},{100,36},{100,34},{100,32},{100,31},{100,29},{100,27},{100,25},{100,23},{100,21},{100,19},{100,18},{100,16},{100,14},{100,12},{100,11},{100,9},{100,7},{100,5},{100,3},{100,2},{100,0},{100,-2},{100,-3},{100,-5},{100,-7},{100,-9},{100,-11},{100,-12},{100,-14},{100,-16},{100,-18},{100,-19},{100,-21},{100,-23},{100,-25},{100,-27},{100,-29},{100,-31},{100,-32},{100,-34},{100,-36},{100,-38},{100,-40},{100,-42},{100,-45},{100,-47},{100,-49},{100,-51},{100,-53},{100,-55},{100,-58},{100,-60},{100,-62},{100,-65},{100,-67},{100,-70},{100,-73},{100,-75},{100,-78},{100,-81},{100,-84},{100,-87},{100,-90},{100,-93},{100,-97},{100,-100},{97,-100},{93,-100},{90,-100},{87,-100},{84,-100},{81,-100},{78,-100},{75,-100},{73,-100},{70,-100},{67,-100},{65,-100},{62,-100},{60,-100},{58,-100},{55,-100},{53,-100},{51,-100},{49,-100},{47,-100},{45,-100},{42,-100},{40,-100},{38,-100},{36,-100},{34,-100},{32,-100},{31,-100},{29,-100},{27,-100},{25,-100},{23,-100},{21,-100},{19,-100},{18,-100},{16,-100},{14,-100},{12,-100},{11,-100},{9,-100},{7,-100},{5,-100},{3,-100},{2,-100},{0,-100},{-2,-100},{-3,-100},{-5,-100},{-7,-100},{-9,-100},{-11,-100},{-12,-100},{-14,-100},{-16,-100},{-18,-100},{-19,-100},{-21,-100},{-23,-100},{-25,-100},{-27,-100},{-29,-100},{-31,-100},{-32,-100},{-34,-100},{-36,-100},{-38,-100},{-40,-100},{-42,-100},{-45,-100},{-47,-100},{-49,-100},{-51,-100},{-53,-100},{-55,-100},{-58,-100},{-60,-100},{-62,-100},{-65,-100},{-67,-100},{-70,-100},{-73,-100},{-75,-100},{-78,-100},{-81,-100},{-84,-100},{-87,-100},{-90,-100},{-93,-100},{-97,-100},{-100,-100},{-100,-97},{-100,-93},{-100,-90},{-100,-87},{-100,-84},{-100,-81},{-100,-78},{-100,-75},{-100,-73},{-100,-70},{-100,-67},{-100,-65},{-100,-62},{-100,-60},{-100,-58},{-100,-55},{-100,-53},{-100,-51},{-100,-49},{-100,-47},{-100,-45},{-100,-42},{-100,-40},{-100,-38},{-100,-36},{-100,-34},{-100,-32},{-100,-31},{-100,-29},{-100,-27},{-100,-25},{-100,-23},{-100,-21},{-100,-19},{-100,-18},{-100,-16},{-100,-14},{-100,-12},{-100,-11},{-100,-9},{-100,-7},{-100,-5},{-100,-3},{-100,-2},{-100,0},{-100,2},{-100,3},{-100,5},{-100,7},{-100,9},{-100,11},{-100,12},{-100,14},{-100,16},{-100,18},{-100,19},{-100,21},{-100,23},{-100,25},{-100,27},{-100,29},{-100,31},{-100,32},{-100,34},{-100,36},{-100,38},{-100,40},{-100,42},{-100,45},{-100,47},{-100,49},{-100,51},{-100,53},{-100,55},{-100,58},{-100,60},{-100,62},{-100,65},{-100,67},{-100,70},{-100,73},{-100,75},{-100,78},{-100,81},{-100,84},{-100,87},{-100,90},{-100,93},{-100,97},{-100,100},{-97,100},{-93,100},{-90,100},{-87,100},{-84,100},{-81,100},{-78,100},{-75,100},{-73,100},{-70,100},{-67,100},{-65,100},{-62,100},{-60,100},{-58,100},{-55,100},{-53,100},{-51,100},{-49,100},{-47,100},{-45,100},{-42,100},{-40,100},{-38,100},{-36,100},{-34,100},{-32,100},{-31,100},{-29,100},{-27,100},{-25,100},{-23,100},{-21,100},{-19,100},{-18,100},{-16,100},{-14,100},{-12,100},{-11,100},{-9,100},{-7,100},{-5,100},{-3,100},{-2,100},{0,100},{2,100},{3,100},{5,100},{7,100},{9,100},{11,100},{12,100},{14,100},{16,100},{18,100},{19,100},{21,100},{23,100},{25,100},{27,100},{29,100},{31,100},{32,100},{34,100},{36,100},{38,100},{40,100},{42,100},{45,100},{47,100},{49,100},{51,100},{53,100},{55,100},{58,100},{60,100},{62,100},{65,100},{67,100},{70,100},{73,100},{75,100},{78,100},{81,100},{84,100},{87,100},{90,100},{93,100},{97,100},{100,100}};
int hundredsine[101] = {0,2,3,5,7,9,10,12,14,16,17,19,21,22,24,26,28,29,31,33,34,36,37,39,41,42,44,45,47,48,50,52,53,54,56,57,59,60,62,63,64,66,67,68,69,71,72,73,74,75,77,78,79,80,81,82,83,84,85,86,87,87,88,89,90,91,91,92,93,93,94,95,95,96,96,97,97,97,98,98,98,99,99,99,99,100,100,100,100,100,100};

//traM(d,s,a) values
mtrP[4] = {0,0,0,0};
mtrS[4] = {0,0,0,0};
int traD = 0;
int rotS = 0;
int rotD = 0;
int cmpr = 0;
int mtrC;
int scaledown = 0;

//basic defining
int firno = 0;
int birno = 0;
int firval = 0;
int birval = 0;

//all us and sl arrays {f,b,l,r}
int nus[4] = {0,0,0,0};
int us[4] = {0,0,0,0};
int skip[4] = {0,0,0,0};
int usc,usd;

int sl[4] = {0,0,0,0};

//basealign values
int valdiff;
int pLR;
int xhome, yhome,bwidth;
int botx = 0;

//border control values
int bcv[4] = {180,0,90,270};

//ball sensing values
int cediff;
int cpno,apno,cpval,apval;
int ballpos;
int balldist;

//scoring
int direction;
int curve;
int curvelvl;

//AOG values
int dist;

int main(void)
{
    X2RCU_Init();
    int traM(int D,int S,int A) { 
    
    	mtrP[0] = mtrP[3] = vd[D][1]*S/100;
    	mtrP[1] = mtrP[2] = vd[D][0]*S/100;
    	
    	cmpr = (cmpr + A)%360;
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
    	}
    	
    	SetMotor( _MOTOR_ne_,mtrS[0],mtrP[0]);
    	SetMotor( _MOTOR_nw_,mtrS[1],mtrP[1]);
    	SetMotor( _MOTOR_se_,mtrS[2],mtrP[2]);
    	SetMotor( _MOTOR_sw_,mtrS[3],mtrP[3]);
    	return;
    }
    
    us[0] = 0;
    us[1] = GetAdUltrasound( _ADULTRASOUND_b_)/10;
    us[2] = GetAdUltrasound( _ADULTRASOUND_l_)/10;
    us[3] = GetAdUltrasound( _ADULTRASOUND_r_)/10;
    
    
    while (1)
    {
        sl[0] = 0;
        sl[1] = GetADScable10( _SCABLEAD_b_ );
        sl[2] = GetADScable10( _SCABLEAD_l_ );
        sl[3] = GetADScable10( _SCABLEAD_r_ );
        
        nus[0] = 0;
        nus[1] = GetAdUltrasound( _ADULTRASOUND_b_)/10;
        nus[2] = GetAdUltrasound( _ADULTRASOUND_l_)/10;
        nus[3] = GetAdUltrasound( _ADULTRASOUND_r_)/10;
        
        usc = 20;
        for (int i = 0;i < 4;i++)
        {
        	usd = nus[i] - us[i];
        	if (usd < 0) usd *= -1;
        	if (usd < usc||skip[i]>20)
        	{
        		us[i] = nus[i];
        		skip[i] = 0;
        	}
        	else skip[i]++;
        }
        
        GetCompoI3( _COMPOUNDEYE3_f_,14);
        GetCompoI3( _COMPOUNDEYE3_b_,14);
        firno = GetCompoI3( _COMPOUNDEYE3_f_,8);
        birno = GetCompoI3( _COMPOUNDEYE3_b_,8);
        firval = GetCompoI3( _COMPOUNDEYE3_f_,9);
        birval = GetCompoI3( _COMPOUNDEYE3_b_,9);
        
        cmpr = GetCompassB( _COMPASS_1_);
        
        xhome = 77;
        yhome = 30;
        bwidth = 155;
        
        if ((us[2]+us[3])>bwidth) {
        	botx = us[2];
        	if (us[2]<us[3]) {
        		pLR = 0;
        	} else if (us[3]<us[2]) {
        		pLR = 1;
        	}
        }
        else if ((us[2]+us[3])<bwidth) {
        	if (us[3]>us[2]&&pLR==1) {
        	//interference on left
        	botx = bwidth - us[3];
        	} else if (us[3]<us[2]&&pLR==0) {
        	//interference on right
        	botx = us[2];
        	}
        }
        
        SetLCDBack(1);
        for (int ab = 0;ab<4;ab++) {
        	SetLCD3Char(0,ab*30 ,us[ab] ,YELLOW,BLACK);
        }
        
        SetLCD3Char(50,30 ,GetCompoI3(_COMPOUNDEYE3_f_,9),YELLOW,BLACK);
        SetLCD3Char(50,60 ,birval,YELLOW,BLACK);
        
        if(firval>birval)
        {
        	apno=firno-1;
        	cpno=firno+1;
        	if(apno==0) apno=14;
        	ballpos = (240 + 30*firno)%360;
        	balldist = firval; 
        }
        else
        {
        	apno=birno+6;
        	cpno=birno+8;
        	if(cpno==15) cpno=1;
        	ballpos = (60 + 30*birno)%360;
        	balldist = birval;
        }
        
        if (apno > 7) {
        	apval = GetCompoI3( _COMPOUNDEYE3_b_,apno-7 );
        } else {
        	apval = GetCompoI3( _COMPOUNDEYE3_f_,apno );
        }
        if (cpno > 7) {
        	cpval = GetCompoI3( _COMPOUNDEYE3_b_,cpno-7 );
        } else {
        	cpval = GetCompoI3( _COMPOUNDEYE3_f_,cpno );
        }
        cediff = (cpval - apval)/5;
        ballpos += cediff;
        
        if (ballpos < 0) ballpos += 360;
        
        if ( us[2]>57&&us[3]>57 )
        {
            if ( firval > 10||birval>10 )
            {
                int direction,speed;
                
                if (us[1] < 20) {
                	if (balldist < 30) {
                		if (us[2] > us[3]) {
                			direction = 270;
                			speed = us[2]-us[3]+15;
                		}
                		else {
                			direction = 90;
                			speed = us[3]-us[2]+15;
                		}
                	}
                	else if (balldist > 30&&balldist < 100) {
                		if (ballpos > 180) {
                			direction = 270;
                			speed = 359-ballpos+20;
                		}
                		else {
                			direction = 90;
                			speed = ballpos+20;
                		}
                	}
                	else if (balldist >= 100) {
                		direction = ballpos;
                		speed = 60;
                	}
                }
                else if (us[1] > 20) {
                	if (balldist >= 100) {
                		direction = ballpos;
                		speed = 60;
                	}
                	else if (balldist < 100) {
                		if (ballpos > 180) {
                			direction = 250;
                			speed = (us[1]-20)*3+20;
                		}
                		else {
                			direction = 110;
                			speed = (us[1]-20)*3+20;
                		}
                	}
                }
                
                if (speed > 80) {speed = 80;}
                traM(direction,speed,0);
                
            }
            else
            {
                valdiff = us[2] - us[3];
                if (valdiff < 0) valdiff *= -1;
                if (valdiff > 100) valdiff = 100;
                
                if (cmpr < 357||cmpr > 3)
                {
                	traM(0,100,0);
                }
                
                if (valdiff > 5)
                {
                	if (us[3] < us[2])
                	{
                		if (us[1]>18)
                		{
                			traM(225,valdiff/2+15,0);
                		}
                		else if (us[1]<20)
                		{
                			traM(315,valdiff/2+15,0);
                		}
                		else if (18<us[1]&&us[1]<20)
                		{
                			traM(270,valdiff/2+15,0);
                		}
                	}
                	else if (us[2] < us[3])
                	{
                		if (us[1]>18)
                		{
                			traM(135,valdiff/2+15,0);
                		}
                		else if (us[1]<20) 
                		{
                			traM(45,valdiff/2+15,0);
                		}
                		else if (18<us[1]&&us[1]<20)
                		{
                			traM(90,valdiff/2+15,0);
                		}
                	}
                }
                else
                {
                	if (us[1] > 20) 
                	{
                		traM(180,(us[1]-5)/2,0);
                	}
                	else if (us[1] < 18)
                	{
                		traM(0,(27-us[1])*2,0);
                	}
                	else if (us[1] > 18&&us[1] < 20)
                	{
                		traM(0,0,0);
                	}
                }
            }
        }
        else
        {
            if (us[2]<70)
            {
            	traM(bcv[2],50,0);
            }
            else if (us[3]<70)
            {
            	traM(bcv[3],50,0);
            }
        }
    }
    while(1);
}

