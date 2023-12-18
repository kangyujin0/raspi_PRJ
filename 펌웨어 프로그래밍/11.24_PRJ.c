/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TEMP  0
#define HUMI  1
/**************************** Command set 8 ***********************************/
#define SHT2x_ADDR				(0x40 << 1)
#define SHT2x_HOLD_MASTER_T		0xE3
#define SHT2x_HOLD_MASTER_RH	0xE5
#define SHT2x_NOHOLD_MASTER_T	0xF3
#define SHT2x_NOHOLD_MASTER_RH	0xF5
#define SHT2x_WRITE_USER_REG	0xE6
#define SHT2x_READ_USER_RGE		0xE7
#define SHT2x_SOFT_RESET		0xFE
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
FILE __stdout;
uint16_t adcData[2];
uint8_t rxData;
volatile int userBtnisr = 0;
uint32_t CCRVal = 0;
uint32_t pwmF;
uint8_t piano = 0;
uint16_t scale[] = {523, 587, 659, 698, 783, 880, 987, 1046};
double temperature, humidity;
int select;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int fputc(int ch, FILE* stream)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 10);
	return ch;
}
void SHT20_Init();
float SHT20(int);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void UI();			// main 메뉴보드
void led_write();		// LED 이동
void mood();		// 타이머로 무드등 on/off
void Piano();		// PWM으로 초음파 음계소리내기
void cds();		// ACD로 밝기에 따른 가로등 on/off
void TEMP_HUMI();		// 온드/습도 제어
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT (&huart2, &rxData, sizeof(rxData));
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);		// Mood
  //HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);	// Piano
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adcData, 1);
  UI();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	  
		if(rxData == '1') {
			printf("LedShift\n\r");
			led_write();			
			rxData = '\0';			
		}
		HAL_Delay(100);
		
		if(rxData == '2') {
			printf("MoodLight\n\r");
			mood();			
			rxData = '\0';
		}
		HAL_Delay(100);
		if(rxData == '3') {
			printf("Piano\n\r");
			Piano();
			rxData = '\0';
		}
		HAL_Delay(100);
		if(rxData == '4') {
			printf("StreetLight\n\r");
			cds();
			rxData = '\0';
		}
		HAL_Delay(100);
		if(rxData == '5') {
			printf("TEMP_HUMI\n\r");
			TEMP_HUMI();
			rxData = '\0';
		}
		HAL_Delay(100);
		if(rxData == '0') {
			printf("Program Exit\n\r");
			break;
			rxData = '\0';
		}
		HAL_Delay(100);
	}
}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
    /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2) {
		printf("rxData : %c\n\r", rxData);                      
	}
	HAL_UART_Receive_IT (&huart2, &rxData, sizeof(rxData));	
}
void UI()
{
   printf("\r************Embedded System************\r");
   printf("1.LedShift\r");
   printf("2.MoodLight\r");
   printf("3.Piano\r");
   printf("4.StreetLight\r");
   printf("5.TEMP/HUMI\r");
   printf("0.Program Exit\r");
   printf("Select\r");
}	
void led_write()
{
	while(1)
	{
		for(userBtnisr = LED0_Pin; userBtnisr <= LED7_Pin; userBtnisr <<= 1){
			HAL_GPIO_WritePin(LED0_GPIO_Port, userBtnisr, GPIO_PIN_SET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(LED0_GPIO_Port, userBtnisr, GPIO_PIN_RESET);
		}
		for(userBtnisr = LED7_Pin; userBtnisr > LED0_Pin; userBtnisr >>= 1){
			HAL_GPIO_WritePin(LED7_GPIO_Port, userBtnisr, GPIO_PIN_SET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(LED7_GPIO_Port, userBtnisr, GPIO_PIN_RESET);			
			}
		if(rxData != '1'){
			break;
		}
	}	
	
}
void mood()
{
	while(1)
	{
		for(CCRVal = 0; CCRVal < 100; CCRVal+=5){
			TIM3->CCR2 = CCRVal;
			HAL_Delay(100);
	}		
		for(CCRVal = 100; CCRVal > 0; CCRVal-=5){		
			TIM3->CCR2 = CCRVal;
			HAL_Delay(100);
		}
		if(rxData != '2'){
			break;
		}
	}
}
void Piano()
{
	while(1)
	{		
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		TIM1->EGR = TIM1->EGR | 0x01;	 	
		pwmF = 10000000 / scale[piano++]; 	
		TIM1->ARR = pwmF - 1;				
		TIM1->CCR1 = pwmF / 2; 				
		HAL_Delay(1000);					
		if(piano > 8) piano = 0;			
		printf("%d\n\r", piano);
		if(rxData != '3'){
			break;			
		}
	}
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}
void cds()
{
	static int i = 0;
	while(1)
	{
		printf("ADC : %d\n\r", adcData[0]);
		HAL_Delay(500);

		if(adcData[0] >3500){
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_All, 0);
		}		
		if( (3500 > adcData[0]) &&  (adcData[0] > 3300)){
			for(i = 0; i < 2; i++)
			{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
			}				
		}
		if( (3300 > adcData[0]) &&  (adcData[0] > 3100)){
		for(i = 0; i < 3; i++)
			{
			 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, 1);
			}
		}
		if( (3100 > adcData[0]) &&  (adcData[0] > 2900)){
		for(i = 0; i < 4; i++)
			{
			 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, 1);
			}
		}
		if( (2900 > adcData[0]) &&  (adcData[0] > 2700)){
		for(i = 0; i < 5; i++)
			{
			 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, 1);
			}
		}
		if( (2700 > adcData[0]) &&  (adcData[0] > 2500)){
		for(i = 0; i < 6; i++)
			{
			 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, 1);
			}
		}
		if( (2500 > adcData[0]) &&  (adcData[0] > 2400)){
		for(i = 0; i < 7; i++)
			{
			 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 << i, 1);
			}
		}
		if(adcData[0] < 2400) {
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_All, 1);
		}
		if(rxData != '4'){
			break;
		}
	}
}
void TEMP_HUMI()
{
	while(1){
		temperature = SHT20(TEMP);
		humidity = SHT20(HUMI);
		printf("TEMP: %.2lf \r\nHUMI: %.2lf \r\n", temperature, humidity);
		HAL_Delay(500);
		if(rxData != '5'){
			break;
		}
	}
}
void SHT20_Init(void)
{
	if(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SHT2x_ADDR, (uint8_t*)SHT2x_SOFT_RESET, 1, 0xffff) == HAL_OK) {
	  printf("SHT20 RESET FALL!!");
	} else {
	 printf("SHT20 RESET SUCCESS!");
	}
}
float SHT20(int select)
{
	uint8_t I2CData[3];
	uint16_t SLAVER_ADDR = SHT2x_ADDR;	
	uint16_t sensor;
	float convData = 0.0;
	
	if(select == TEMP) {
		I2CData[0] = SHT2x_NOHOLD_MASTER_T;
		HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SLAVER_ADDR, (uint8_t*)I2CData, 1, 0xffff);
		HAL_Delay(100);
		HAL_I2C_Master_Receive(&hi2c1, (uint16_t)SLAVER_ADDR, (uint8_t*)I2CData, 2, 0xffff);
		sensor = I2CData[0] << 8 | I2CData[1];
		convData = -46.85 + 175.72 / 65536 *(float)sensor;
	}
	if(select == HUMI) {
		I2CData[0] = SHT2x_NOHOLD_MASTER_RH;
		HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)SLAVER_ADDR, (uint8_t*)I2CData, 1, 0xffff);
		HAL_Delay(100);
		HAL_I2C_Master_Receive(&hi2c1, (uint16_t)SLAVER_ADDR, (uint8_t*)I2CData, 2, 0xffff);
		sensor = I2CData[0] << 8 | I2CData[1];
		convData = -6.0 + 125.0 / 65536 *(float)sensor;
	}
	return convData;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
