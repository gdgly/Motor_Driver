#ifndef __DRV8305_H
#define __DRV8305_H
#include "board.h"

#define RCC_DRV8305	     RCC_AHB1Periph_GPIOC 

#define DRV8305_PORT      GPIOC

#define DRV8305_Pin_SCS      GPIO_Pin_4
#define DRV8305_Pin_PWRGD    GPIO_Pin_1
#define DRV8305_Pin_ENGATE   GPIO_Pin_0
#define DRV8305_Pin_WAKE      GPIO_Pin_5

#define DRV8305_SCS_H     GPIO_SetBits(DRV8305_PORT   ,   DRV8305_Pin_SCS)
#define DRV8305_SCS_L     GPIO_ResetBits(DRV8305_PORT ,    DRV8305_Pin_SCS)

#define DRV8305_ENGATE_H     GPIO_SetBits(DRV8305_PORT   ,   DRV8305_Pin_ENGATE)
#define DRV8305_ENGATE_L     GPIO_ResetBits(DRV8305_PORT ,    DRV8305_Pin_ENGATE)

//#define DRV8305_SCS_H     GPIO_SetBits(DRV8305_PORT   ,   DRV8305_Pin_SCS)
//#define DRV8305_SCS_L     GPIO_ResetBits(DRV8305_PORT ,    DRV8305_Pin_SCS)

//#define DRV8305_SCS_H     GPIO_SetBits(DRV8305_PORT   ,   DRV8305_Pin_SCS)
//#define DRV8305_SCS_L     GPIO_ResetBits(DRV8305_PORT ,    DRV8305_Pin_SCS)
 
//#define READ   

typedef struct 
{
    long Ia;     //输入，A相定子电流
    long Ib;     //输入，B相定子电流
    long Ic;     //输入，C相定子电流
    long IAlpha;  //输出，静止坐标系Alpha轴定子电流
    long IBeta;   //输出，静止坐标系Beta轴定子电流
    void (*calcClark)();    
    void (*calcAntiClark)();
}_CLARK;

typedef struct 
{
    long Id;     //输出，旋转坐标系下的D坐标值电流
    long Iq;         //输出，旋转坐标系下的Q坐标值电流
    long IAlpha;  //输入，静止坐标系Alpha轴定子电流
    long IBeta;   //输入，静止坐标系Beta轴定子电流
    float Ud;     //输出，旋转坐标系下的D坐标值电压
    float Uq;          //输出，旋转坐标系下的Q坐标值电压
    long UAlpha;  //输入，静止坐标系Alpha轴定子电压
    long UBeta;   //输入，静止坐标系Beta轴定子电压
    long Theta;    //旋转坐标角度
    float ActId;  //实际D轴电流
    float ActIq;  //实际Q轴电流
    void (*calcPark)();      
    void (*calcAntiPark)();  
}_PARK;

typedef struct 
{
    float UAlpha; //输入，静止坐标系Alpha轴定子电压
    float UBeta;  //输入，静止坐标系Beta轴定子电压
    long Ua;      //
    long Ub;      //
    long Uc;      //
    long Tx;        //
    long Ty;        //
    long Tz;        //
    long taOn;    //A相时间
    long tbOn;      //B相时间
    long tcOn;      //C相时间
} _SVPWM;

typedef struct  _phase{
                   int   H_duty;
                   int   L_duty;   
}phase;

typedef struct {
                 int MOTA;
                 int MOTB;
                 int MOTC;  
}_duty;

typedef struct{
               _duty  Duty;
               _SVPWM Svpwm;
               _CLARK Clack;
               _PARK  Park;
               
}_DRV8305;

extern _DRV8305 DRV8305;
extern u8 Step_Flag;


void DRV8305_Init(void);
void DRV8305_Output(int Duty[6]);
void DRC8305_Driver_Control(float T);
void Svpwm_Module(void);
void Anti_Park_Calc(void);
#endif