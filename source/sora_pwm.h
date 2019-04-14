/* 
 * @date   2019年02月26日最后修改
 * @name   Sora_lib
 * @group  Akko
 * @author Afisora
 * @brief  eFlexPWM Driver
 */


#ifndef __SORA_PWM_H__
#define __SORA_PWM_H__

 //定义PWM子模块号
typedef enum PWM_SMn
{
	PWM_SM0,
	PWM_SM1,
	PWM_SM2,
	PWM_SM3,
} PWM_SMn;

typedef enum PWM_CHn
{
	PWM_CHA,
	PWM_CHB,
	PWM_CHX,
} PWM_CHn;

void FlexPWM_Independent_Init(PWM_Type* base, PWM_SMn subModule);

#endif