/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern char str_rx[100];
extern char data_rx[96];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


	uint16_t ServoAngle = 0;
	uint8_t Flag = 0;
	const	uint16_t AngleToCCR [] = {
0x1F40, 0x1F51, 0x1F62, 0x1F74, 0x1F85, 0x1F96, 0x1FA8, 0x1FB9, 0x1FCA, 0x1FDC, 0x1FED, 0x1FFF, 0x2010, 0x2021, 0x2033, 0x2044, 0x2055, 0x2067, 0x2078, 0x208A, 0x209B, 0x20AC, 0x20BE, 0x20CF, 0x20E0, 0x20F2, 0x2103, 0x2114, 0x2126, 0x2137, 0x2149, 0x215A, 0x216B, 0x217D, 0x218E, 0x219F, 0x21B1, 0x21C2, 0x21D4, 0x21E5, 0x21F6, 0x2208, 0x2219, 0x222A, 0x223C, 0x224D, 0x225F, 0x2270, 0x2281, 0x2293, 0x22A4, 0x22B5, 0x22C7, 0x22D8, 0x22E9, 0x22FB, 0x230C, 0x231E, 0x232F, 0x2340, 0x2352, 0x2363,
0x2374, 0x2386, 0x2397, 0x23A9, 0x23BA, 0x23CB, 0x23DD, 0x23EE, 0x23FF, 0x2411, 0x2422, 0x2433, 0x2445, 0x2456, 0x2468, 0x2479, 0x248A, 0x249C, 0x24AD, 0x24BE, 0x24D0, 0x24E1, 0x24F3, 0x2504, 0x2515, 0x2527, 0x2538, 0x2549, 0x255B, 0x256C, 0x257E, 0x258F, 0x25A0, 0x25B2, 0x25C3, 0x25D4, 0x25E6, 0x25F7, 0x2608, 0x261A, 0x262B, 0x263D, 0x264E, 0x265F, 0x2671, 0x2682, 0x2693, 0x26A5, 0x26B6, 0x26C8, 0x26D9, 0x26EA, 0x26FC, 0x270D, 0x271E, 0x2730, 0x2741, 0x2753, 0x2764, 0x2775, 0x2787, 0x2798,
0x27A9, 0x27BB, 0x27CC, 0x27DD, 0x27EF, 0x2800, 0x2812, 0x2823, 0x2834, 0x2846, 0x2857, 0x2868, 0x287A, 0x288B, 0x289D, 0x28AE, 0x28BF, 0x28D1, 0x28E2, 0x28F3, 0x2905, 0x2916, 0x2927, 0x2939, 0x294A, 0x295C, 0x296D, 0x297E, 0x2990, 0x29A1, 0x29B2, 0x29C4, 0x29D5, 0x29E7, 0x29F8, 0x2A09, 0x2A1B, 0x2A2C, 0x2A3D, 0x2A4F, 0x2A60, 0x2A72, 0x2A83, 0x2A94, 0x2AA6, 0x2AB7, 0x2AC8, 0x2ADA, 0x2AEB, 0x2AFC, 0x2B0E, 0x2B1F, 0x2B31, 0x2B42, 0x2B53, 0x2B65, 0x2B76, 0x2B87, 0x2B99, 0x2BAA, 0x2BBC, 0x2BCD,
0x2BDE, 0x2BF0, 0x2C01, 0x2C12, 0x2C24, 0x2C35, 0x2C46, 0x2C58, 0x2C69, 0x2C7B, 0x2C8C, 0x2C9D, 0x2CAF, 0x2CC0, 0x2CD1, 0x2CE3, 0x2CF4, 0x2D06, 0x2D17, 0x2D28, 0x2D3A, 0x2D4B, 0x2D5C, 0x2D6E, 0x2D7F, 0x2D91, 0x2DA2, 0x2DB3, 0x2DC5, 0x2DD6, 0x2DE7, 0x2DF9, 0x2E0A, 0x2E1B, 0x2E2D, 0x2E3E, 0x2E50, 0x2E61, 0x2E72, 0x2E84, 0x2E95, 0x2EA6, 0x2EB8, 0x2EC9, 0x2EDB, 0x2EEC, 0x2EFD, 0x2F0F, 0x2F20, 0x2F31, 0x2F43, 0x2F54, 0x2F66, 0x2F77, 0x2F88, 0x2F9A, 0x2FAB, 0x2FBC, 0x2FCE, 0x2FDF, 0x2FF0, 0x3002,
0x3013, 0x3025, 0x3036, 0x3047, 0x3059, 0x306A, 0x307B, 0x308D, 0x309E, 0x30B0, 0x30C1, 0x30D2, 0x30E4, 0x30F5, 0x3106, 0x3118, 0x3129, 0x313A, 0x314C, 0x315D, 0x316F, 0x3180, 0x3191, 0x31A3, 0x31B4, 0x31C5, 0x31D7, 0x31E8, 0x31FA, 0x320B, 0x321C, 0x322E, 0x323F, 0x3250, 0x3262, 0x3273, 0x3285, 0x3296, 0x32A7, 0x32B9, 0x32CA, 0x32DB, 0x32ED, 0x32FE, 0x330F, 0x3321, 0x3332, 0x3344, 0x3355, 0x3366, 0x3378, 0x3389, 0x339A, 0x33AC, 0x33BD, 0x33CF, 0x33E0, 0x33F1, 0x3403, 0x3414, 0x3425, 0x3437,
0x3448, 0x345A, 0x346B, 0x347C, 0x348E, 0x349F, 0x34B0, 0x34C2, 0x34D3, 0x34E4, 0x34F6, 0x3507, 0x3519, 0x352A, 0x353B, 0x354D, 0x355E, 0x356F, 0x3581, 0x3592, 0x35A4, 0x35B5, 0x35C6, 0x35D8, 0x35E9, 0x35FA, 0x360C, 0x361D, 0x362E, 0x3640, 0x3651, 0x3663, 0x3674, 0x3685, 0x3697, 0x36A8, 0x36B9, 0x36CB, 0x36DC, 0x36EE, 0x36FF, 0x3710, 0x3722, 0x3733, 0x3744, 0x3756, 0x3767, 0x3779, 0x378A, 0x379B, 0x37AD, 0x37BE, 0x37CF, 0x37E1, 0x37F2, 0x3803, 0x3815, 0x3826, 0x3838, 0x3849, 0x385A, 0x386C,
0x387D, 0x388E, 0x38A0, 0x38B1, 0x38C3, 0x38D4, 0x38E5, 0x38F7, 0x3908, 0x3919, 0x392B, 0x393C, 0x394D, 0x395F, 0x3970, 0x3982, 0x3993, 0x39A4, 0x39B6, 0x39C7, 0x39D8, 0x39EA, 0x39FB, 0x3A0D, 0x3A1E, 0x3A2F, 0x3A41, 0x3A52, 0x3A63, 0x3A75, 0x3A86, 0x3A98, 0x3AA9, 0x3ABA, 0x3ACC, 0x3ADD, 0x3AEE, 0x3B00, 0x3B11, 0x3B22, 0x3B34, 0x3B45, 0x3B57, 0x3B68, 0x3B79, 0x3B8B, 0x3B9C, 0x3BAD, 0x3BBF, 0x3BD0, 0x3BE2, 0x3BF3, 0x3C04, 0x3C16, 0x3C27, 0x3C38, 0x3C4A, 0x3C5B, 0x3C6D, 0x3C7E, 0x3C8F, 0x3CA1,
0x3CB2, 0x3CC3, 0x3CD5, 0x3CE6, 0x3CF7, 0x3D09, 0x3D1A, 0x3D2C, 0x3D3D, 0x3D4E, 0x3D60, 0x3D71, 0x3D82, 0x3D94, 0x3DA5, 0x3DB7, 0x3DC8, 0x3DD9, 0x3DEB, 0x3DFC, 0x3E0D, 0x3E1F, 0x3E30, 0x3E41, 0x3E53, 0x3E64, 0x3E76, 0x3E87, 0x3E98, 0x3EAA, 0x3EBB, 0x3ECC, 0x3EDE, 0x3EEF, 0x3F01, 0x3F12, 0x3F23, 0x3F35, 0x3F46, 0x3F57, 0x3F69, 0x3F7A, 0x3F8C, 0x3F9D, 0x3FAE, 0x3FC0, 0x3FD1, 0x3FE2, 0x3FF4, 0x4005, 0x4016, 0x4028, 0x4039, 0x404B, 0x405C, 0x406D, 0x407F, 0x4090, 0x40A1, 0x40B3, 0x40C4, 0x40D6,
0x40E7, 0x40F8, 0x410A, 0x411B, 0x412C, 0x413E, 0x414F, 0x4161, 0x4172, 0x4183, 0x4195, 0x41A6, 0x41B7, 0x41C9, 0x41DA, 0x41EB, 0x41FD, 0x420E, 0x4220, 0x4231, 0x4242, 0x4254, 0x4265, 0x4276, 0x4288, 0x4299, 0x42AB, 0x42BC, 0x42CD, 0x42DF, 0x42F0, 0x4301, 0x4313, 0x4324, 0x4335, 0x4347, 0x4358, 0x436A, 0x437B, 0x438C, 0x439E, 0x43AF, 0x43C0, 0x43D2, 0x43E3, 0x43F5, 0x4406, 0x4417, 0x4429, 0x443A, 0x444B, 0x445D, 0x446E, 0x4480, 0x4491, 0x44A2, 0x44B4, 0x44C5, 0x44D6, 0x44E8, 0x44F9, 0x450A,
0x451C, 0x452D, 0x453F, 0x4550, 0x4561, 0x4573, 0x4584, 0x4595, 0x45A7, 0x45B8, 0x45CA, 0x45DB, 0x45EC, 0x45FE, 0x460F, 0x4620, 0x4632, 0x4643, 0x4654, 0x4666, 0x4677, 0x4689, 0x469A, 0x46AB, 0x46BD, 0x46CE, 0x46DF, 0x46F1, 0x4702, 0x4714, 0x4725, 0x4736, 0x4748, 0x4759, 0x476A, 0x477C, 0x478D, 0x479F, 0x47B0, 0x47C1, 0x47D3, 0x47E4, 0x47F5, 0x4807, 0x4818, 0x4829, 0x483B, 0x484C, 0x485E, 0x486F, 0x4880, 0x4892, 0x48A3, 0x48B4, 0x48C6, 0x48D7, 0x48E9, 0x48FA, 0x490B, 0x491D, 0x492E, 0x493F,
0x4951, 0x4962, 0x4974, 0x4985, 0x4996, 0x49A8, 0x49B9, 0x49CA, 0x49DC, 0x49ED, 0x49FE, 0x4A10, 0x4A21, 0x4A33, 0x4A44, 0x4A55, 0x4A67, 0x4A78, 0x4A89, 0x4A9B, 0x4AAC, 0x4ABE, 0x4ACF, 0x4AE0, 0x4AF2, 0x4B03, 0x4B14, 0x4B26, 0x4B37, 0x4B48, 0x4B5A, 0x4B6B, 0x4B7D, 0x4B8E, 0x4B9F, 0x4BB1, 0x4BC2, 0x4BD3, 0x4BE5, 0x4BF6, 0x4C08, 0x4C19, 0x4C2A, 0x4C3C, 0x4C4D, 0x4C5E, 0x4C70, 0x4C81, 0x4C93, 0x4CA4, 0x4CB5, 0x4CC7, 0x4CD8, 0x4CE9, 0x4CFB, 0x4D0C, 0x4D1D, 0x4D2F, 0x4D40, 0x4D52, 0x4D63, 0x4D74,
0x4D86, 0x4D97, 0x4DA8, 0x4DBA, 0x4DCB, 0x4DDD, 0x4DEE, 0x4DFF, 0x4E11, 0x4E22, 0x4E33, 0x4E45, 0x4E56, 0x4E68, 0x4E79, 0x4E8A, 0x4E9C, 0x4EAD, 0x4EBE, 0x4ED0, 0x4EE1, 0x4EF2, 0x4F04, 0x4F15, 0x4F27, 0x4F38, 0x4F49, 0x4F5B, 0x4F6C, 0x4F7D, 0x4F8F, 0x4FA0, 0x4FB2, 0x4FC3, 0x4FD4, 0x4FE6, 0x4FF7, 0x5008, 0x501A, 0x502B, 0x503C, 0x504E, 0x505F, 0x5071, 0x5082, 0x5093, 0x50A5, 0x50B6, 0x50C7, 0x50D9, 0x50EA, 0x50FC, 0x510D, 0x511E, 0x5130, 0x5141, 0x5152, 0x5164, 0x5175, 0x5187, 0x5198, 0x51A9,
0x51BB, 0x51CC, 0x51DD, 0x51EF, 0x5200, 0x5211, 0x5223, 0x5234, 0x5246, 0x5257, 0x5268, 0x527A, 0x528B, 0x529C, 0x52AE, 0x52BF, 0x52D1, 0x52E2, 0x52F3, 0x5305, 0x5316, 0x5327, 0x5339, 0x534A, 0x535B, 0x536D, 0x537E, 0x5390, 0x53A1, 0x53B2, 0x53C4, 0x53D5, 0x53E6, 0x53F8, 0x5409, 0x541B, 0x542C, 0x543D, 0x544F, 0x5460, 0x5471, 0x5483, 0x5494, 0x54A6, 0x54B7, 0x54C8, 0x54DA, 0x54EB, 0x54FC, 0x550E, 0x551F, 0x5530, 0x5542, 0x5553, 0x5565, 0x5576, 0x5587, 0x5599, 0x55AA, 0x55BB, 0x55CD, 0x55DE,
0x55F0, 0x5601, 0x5612, 0x5624, 0x5635, 0x5646, 0x5658, 0x5669, 0x567B, 0x568C, 0x569D, 0x56AF, 0x56C0, 0x56D1, 0x56E3, 0x56F4, 0x5705, 0x5717, 0x5728, 0x573A, 0x574B, 0x575C, 0x576E, 0x577F, 0x5790, 0x57A2, 0x57B3, 0x57C5, 0x57D6, 0x57E7, 0x57F9, 0x580A, 0x581B, 0x582D, 0x583E, 0x584F, 0x5861, 0x5872, 0x5884, 0x5895, 0x58A6, 0x58B8, 0x58C9, 0x58DA, 0x58EC, 0x58FD, 0x590F, 0x5920, 0x5931, 0x5943, 0x5954, 0x5965, 0x5977, 0x5988, 0x599A, 0x59AB, 0x59BC, 0x59CE, 0x59DF, 0x59F0, 0x5A02, 0x5A13,
0x5A24, 0x5A36, 0x5A47, 0x5A59, 0x5A6A, 0x5A7B, 0x5A8D, 0x5A9E, 0x5AAF, 0x5AC1, 0x5AD2, 0x5AE4, 0x5AF5, 0x5B06, 0x5B18, 0x5B29, 0x5B3A, 0x5B4C, 0x5B5D, 0x5B6E, 0x5B80, 0x5B91, 0x5BA3, 0x5BB4, 0x5BC5, 0x5BD7, 0x5BE8, 0x5BF9, 0x5C0B, 0x5C1C, 0x5C2E, 0x5C3F, 0x5C50, 0x5C62, 0x5C73, 0x5C84, 0x5C96, 0x5CA7, 0x5CB9, 0x5CCA, 0x5CDB, 0x5CED, 0x5CFE, 0x5D0F, 0x5D21, 0x5D32, 0x5D43, 0x5D55, 0x5D66, 0x5D78, 0x5D89, 0x5D9A, 0x5DAC, 0x5DBD, 0x5DCE, 0x5DE0, 0x5DF1, 0x5E03, 0x5E14, 0x5E25, 0x5E37, 0x5E48,
0x5E59, 0x5E6B, 0x5E7C, 0x5E8E, 0x5E9F, 0x5EB0, 0x5EC2, 0x5ED3, 0x5EE4, 0x5EF6, 0x5F07, 0x5F18, 0x5F2A, 0x5F3B, 0x5F4D, 0x5F5E, 0x5F6F, 0x5F81, 0x5F92, 0x5FA3, 0x5FB5, 0x5FC6, 0x5FD8, 0x5FE9, 0x5FFA, 0x600C, 0x601D, 0x602E, 0x6040, 0x6051, 0x6062, 0x6074, 0x6085, 0x6097, 0x60A8, 0x60B9, 0x60CB, 0x60DC, 0x60ED, 0x60FF, 0x6110, 0x6122, 0x6133, 0x6144, 0x6156, 0x6167, 0x6178, 0x618A, 0x619B, 0x61AD, 0x61BE, 0x61CF, 0x61E1, 0x61F2, 0x6203, 0x6215, 0x6226, 0x6237, 0x6249, 0x625A, 0x626C, 0x627D,
0x628E, 0x62A0, 0x62B1, 0x62C2, 0x62D4, 0x62E5, 0x62F7, 0x6308, 0x6319, 0x632B, 0x633C, 0x634D, 0x635F, 0x6370, 0x6382, 0x6393, 0x63A4, 0x63B6, 0x63C7, 0x63D8, 0x63EA, 0x63FB, 0x640C, 0x641E, 0x642F, 0x6441, 0x6452, 0x6463, 0x6475, 0x6486, 0x6497, 0x64A9, 0x64BA, 0x64CC, 0x64DD, 0x64EE, 0x6500, 0x6511, 0x6522, 0x6534, 0x6545, 0x6556, 0x6568, 0x6579, 0x658B, 0x659C, 0x65AD, 0x65BF, 0x65D0, 0x65E1, 0x65F3, 0x6604, 0x6616, 0x6627, 0x6638, 0x664A, 0x665B, 0x666C, 0x667E, 0x668F, 0x66A1, 0x66B2,
0x66C3, 0x66D5, 0x66E6, 0x66F7, 0x6709, 0x671A, 0x672B, 0x673D, 0x674E, 0x6760, 0x6771, 0x6782, 0x6794, 0x67A5, 0x67B6, 0x67C8, 0x67D9, 0x67EB, 0x67FC, 0x680D, 0x681F, 0x6830, 0x6841, 0x6853, 0x6864, 0x6875, 0x6887, 0x6898, 0x68AA, 0x68BB, 0x68CC, 0x68DE, 0x68EF, 0x6900, 0x6912, 0x6923, 0x6935, 0x6946, 0x6957, 0x6969, 0x697A, 0x698B, 0x699D, 0x69AE, 0x69C0, 0x69D1, 0x69E2, 0x69F4, 0x6A05, 0x6A16, 0x6A28, 0x6A39, 0x6A4A, 0x6A5C, 0x6A6D, 0x6A7F, 0x6A90, 0x6AA1, 0x6AB3, 0x6AC4, 0x6AD5, 0x6AE7,
0x6AF8, 0x6B0A, 0x6B1B, 0x6B2C, 0x6B3E, 0x6B4F, 0x6B60, 0x6B72, 0x6B83, 0x6B95, 0x6BA6, 0x6BB7, 0x6BC9, 0x6BDA, 0x6BEB, 0x6BFD, 0x6C0E, 0x6C1F, 0x6C31, 0x6C42, 0x6C54, 0x6C65, 0x6C76, 0x6C88, 0x6C99, 0x6CAA, 0x6CBC, 0x6CCD, 0x6CDF, 0x6CF0, 0x6D01, 0x6D13, 0x6D24, 0x6D35, 0x6D47, 0x6D58, 0x6D69, 0x6D7B, 0x6D8C, 0x6D9E, 0x6DAF, 0x6DC0, 0x6DD2, 0x6DE3, 0x6DF4, 0x6E06, 0x6E17, 0x6E29, 0x6E3A, 0x6E4B, 0x6E5D, 0x6E6E, 0x6E7F, 0x6E91, 0x6EA2, 0x6EB4, 0x6EC5, 0x6ED6, 0x6EE8, 0x6EF9, 0x6F0A, 0x6F1C,
0x6F2D, 0x6F3E, 0x6F50, 0x6F61, 0x6F73, 0x6F84, 0x6F95, 0x6FA7, 0x6FB8, 0x6FC9, 0x6FDB, 0x6FEC, 0x6FFE, 0x700F, 0x7020, 0x7032, 0x7043, 0x7054, 0x7066, 0x7077, 0x7089, 0x709A, 0x70AB, 0x70BD, 0x70CE, 0x70DF, 0x70F1, 0x7102, 0x7113, 0x7125, 0x7136, 0x7148, 0x7159, 0x716A, 0x717C, 0x718D, 0x719E, 0x71B0, 0x71C1, 0x71D3, 0x71E4, 0x71F5, 0x7207, 0x7218, 0x7229, 0x723B, 0x724C, 0x725D, 0x726F, 0x7280, 0x7292, 0x72A3, 0x72B4, 0x72C6, 0x72D7, 0x72E8, 0x72FA, 0x730B, 0x731D, 0x732E, 0x733F, 0x7351,
0x7362, 0x7373, 0x7385, 0x7396, 0x73A8, 0x73B9, 0x73CA, 0x73DC, 0x73ED, 0x73FE, 0x7410, 0x7421, 0x7432, 0x7444, 0x7455, 0x7467, 0x7478, 0x7489, 0x749B, 0x74AC, 0x74BD, 0x74CF, 0x74E0, 0x74F2, 0x7503, 0x7514, 0x7526, 0x7537, 0x7548, 0x755A, 0x756B, 0x757C, 0x758E, 0x759F, 0x75B1, 0x75C2, 0x75D3, 0x75E5, 0x75F6, 0x7607, 0x7619, 0x762A, 0x763C, 0x764D, 0x765E, 0x7670, 0x7681, 0x7692, 0x76A4, 0x76B5, 0x76C7, 0x76D8, 0x76E9, 0x76FB, 0x770C, 0x771D, 0x772F, 0x7740, 0x7751, 0x7763, 0x7774, 0x7786,
0x7797, 0x77A8, 0x77BA, 0x77CB, 0x77DC, 0x77EE, 0x77FF, 0x7811, 0x7822, 0x7833, 0x7845, 0x7856, 0x7867, 0x7879, 0x788A, 0x789C, 0x78AD, 0x78BE, 0x78D0, 0x78E1, 0x78F2, 0x7904, 0x7915, 0x7926, 0x7938, 0x7949, 0x795B, 0x796C, 0x797D, 0x798F, 0x79A0, 0x79B1, 0x79C3, 0x79D4, 0x79E6, 0x79F7, 0x7A08, 0x7A1A, 0x7A2B, 0x7A3C, 0x7A4E, 0x7A5F, 0x7A70, 0x7A82, 0x7A93, 0x7AA5, 0x7AB6, 0x7AC7, 0x7AD9, 0x7AEA, 0x7AFB, 0x7B0D, 0x7B1E, 0x7B30, 0x7B41, 0x7B52, 0x7B64, 0x7B75, 0x7B86, 0x7B98, 0x7BA9, 0x7BBB,
0x7BCC, 0x7BDD, 0x7BEF, 0x7C00, 0x7C11, 0x7C23, 0x7C34, 0x7C45, 0x7C57, 0x7C68, 0x7C7A, 0x7C8B, 0x7C9C, 0x7CAE, 0x7CBF, 0x7CD0, 0x7CE2, 0x7CF3, 0x7D05, 0x7D16, 0x7D27, 0x7D39, 0x7D4A, 0x7D5B, 0x7D6D, 0x7D7E, 0x7D90, 0x7DA1, 0x7DB2, 0x7DC4, 0x7DD5, 0x7DE6, 0x7DF8, 0x7E09, 0x7E1A, 0x7E2C };
void TurnServoAngle(uint32_t Angle)
{
		LL_TIM_OC_SetCompareCH3(TIM3, AngleToCCR[Angle]);
}

void ServoGo(uint16_t Angle)
{
		if (Flag == 0)
		{
			if (ServoAngle < Angle)
			{
				ServoAngle = ServoAngle + 1;
			}
			else
			{
				Flag = 1;
			}
		}
		else
		{
			if (ServoAngle > 0)
			{
				ServoAngle = ServoAngle - 1;
			}
			else
			{
				Flag = 0;
			}
		}
		TurnServoAngle(ServoAngle);
//		LL_mDelay(1);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_TIM3_Init();
  MX_USB_DEVICE_Init();
  MX_TIM22_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */
  LL_GPIO_SetOutputPin(EN_DC_DC_GPIO_Port, EN_DC_DC_Pin);
  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH3);
  LL_TIM_EnableCounter(TIM3);
  LL_TIM_OC_SetCompareCH3(TIM3, 0x1F40);
  LL_TIM_CC_EnableChannel(TIM22, LL_TIM_CHANNEL_CH1);
  LL_TIM_EnableCounter(TIM22);
  LL_TIM_OC_SetCompareCH1(TIM22, 0x16);

  LL_GPIO_SetOutputPin(Vibration_GPIO_Port, Vibration_Pin);
  LL_TIM_EnableCounter(TIM22);
  LL_mDelay(100);
  LL_GPIO_ResetOutputPin(Vibration_GPIO_Port, Vibration_Pin);
//  LL_TIM_DisableCounter(TIM22);
  LL_mDelay(100);
  LL_GPIO_SetOutputPin(Vibration_GPIO_Port, Vibration_Pin);
  LL_mDelay(100);
  LL_GPIO_ResetOutputPin(Vibration_GPIO_Port, Vibration_Pin);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

//	LL_mDelay(1000);
//	CDC_Transmit_FS(str_rx, strlen(str_rx));
	TurnServoAngle(data_rx[1] + data_rx[0] * 256);

//	ServoGo(1200);
//	TurnServoAngle(1200);
//	LL_mDelay(5000);
//	TurnServoAngle(0);
//	LL_mDelay(5000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_1)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLL_MUL_12, LL_RCC_PLL_DIV_3);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_SetSystemCoreClock(32000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
  LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
