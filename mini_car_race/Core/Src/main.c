/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  * 本文件内含BMI270�????螺仪的使用示�????
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dodo_BMI270.h" //陀螺仪驱动
#include "multiplexer.h"//多路复用器驱动，用于读取光电管读数
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
//直线修正
uint16_t photo_values[12];  // 12路光电管数值
int16_t base_speed = 700;  // 基础速度
float Kp = 1.2f;            // 路线偏差系数
float Kd = 0.8f;            // 阻尼系数
int ks = 17;               //光电管调用函数加权返回参数，凭感觉调
float gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z;//陀螺仪数据
//

//直角转弯
int16_t right_angle_flag=0;//直角转弯标识符
int16_t durtime=0;
uint32_t turn_start_time = 0;//直角转弯持续时间
void slow(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}



//PWM部分算法
void set_motor(int i, int16_t pwm);//第一个int：0表示左，1表示右,第二个表示设定pwm
struct PIDController {
int16_t targetVal;
int16_t currentError; 
int16_t preError; 
int16_t derivative; 
int32_t integral; 
int16_t output; 
float Kp, Ki, Kd; 
}PIDL={0,0,0,0,0,0,1.5,0.1,0.15},PIDR={0,0,0,0,0,0,1.5,0.1,0.15};
int Lpwm,Rpwm;
void ComputePID(struct PIDController *, int16_t ,int );
int16_t measureVal,integralLimit=1500;
//
	
//直角转弯
void test_right_angle(void);
void MUX_read_value();//读数
void LineFollow();//直线循迹
void turn(void);
//
	
	
	
	
//十字判定
uint16_t cross_flag=0;
void cross_test(void);
uint32_t cross_time=0;
//
	
	
//错误检测
void errortest(void);

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
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART3_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	dodo_BMI270_init();//初始化陀螺仪
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);//右
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);//左
	printf("Line Follow Ready\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		/*
    //以下为陀螺仪使用示例
    dodo_BMI270_get_data();//调用此函数会更新陀螺仪数据
    gyro_x=BMI270_gyro_transition(BMI270_gyro_x);//将原始陀螺仪数据转换为物理值，单位为度每秒
    gyro_y=BMI270_gyro_transition(BMI270_gyro_y);
    gyro_z=BMI270_gyro_transition(BMI270_gyro_z);

    accel_x=BMI270_acc_transition(BMI270_accel_x);//将原始加速度计数据转换为物理值，单位为g，一般不需要使用此数据
    accel_y=BMI270_acc_transition(BMI270_accel_y);
    accel_z=BMI270_acc_transition(BMI270_accel_z);
    printf("G: %f %f %f | A: %f %f %f\r\n", gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z);//输出陀螺仪读数，测试是否成功启动，正常使用时不需要这行代码

    
   
		*/
		//以下为读取光电管的示例（从左到右编号0~11）
    //uint16_t mux_value;
    //MUX_get_value(&mux_value);
		//for(int i=0;i<=11;i++){
      //printf("%d,",MUX_GET_CHANNEL(mux_value,i));//获取第i个光电管的数值并输出
    //}
		//printf("\n");
		MUX_read_value();//读数
		cross_test();
		if(cross_flag==0)
		{
		if(durtime==0)//如果当前未进行直角转弯
		test_right_angle();//直角检测
		if(right_angle_flag==0)
		{
    LineFollow();//直线循迹
		}
		else if (right_angle_flag!=0)
		{
			//slow();
			turn();
		}
	  }
		else if(cross_flag==1)
		{
		   LineFollow();
		}
		
		
		set_motor(0,-Lpwm);
		set_motor(1,-1.475f*Rpwm);
		//printf("%d %d \n",PIDL.targetVal,PIDL.output);
		errortest();
		HAL_Delay(2);
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 7199;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 71;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|R_DIR_Pin|MUX_0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, L_DIR_Pin|MUX_1_Pin|MUX_2_Pin|MUX_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : L_DIR_Pin */
  GPIO_InitStruct.Pin = L_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(L_DIR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : R_DIR_Pin */
  GPIO_InitStruct.Pin = R_DIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(R_DIR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MUX_READ_Pin */
  GPIO_InitStruct.Pin = MUX_READ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MUX_READ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MUX_0_Pin */
  GPIO_InitStruct.Pin = MUX_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(MUX_0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MUX_1_Pin MUX_2_Pin MUX_3_Pin */
  GPIO_InitStruct.Pin = MUX_1_Pin|MUX_2_Pin|MUX_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */



//PWM算法
void set_motor(int i, int16_t pwm)
{
	if(i==0)
	{
		PIDL.targetVal=pwm;
		ComputePID(&PIDL,(__HAL_TIM_GET_COUNTER(&htim4)),0);
		__HAL_TIM_SET_COUNTER(&htim4, 0);
	}if(i==1)
	{
		PIDR.targetVal=pwm;
		ComputePID(&PIDR,(__HAL_TIM_GET_COUNTER(&htim3)),1);
		__HAL_TIM_SET_COUNTER(&htim3, 0);
	}
}
void ComputePID(struct PIDController *pid, int16_t measuredVal,int i) {
    float gear_ratio = 9.0f / 40.0f;
    int16_t motor_equivalent_val = measuredVal * gear_ratio;   
    pid->preError = pid->currentError;
    pid->currentError = pid->targetVal - motor_equivalent_val;
    pid->derivative = pid->currentError - pid->preError;
    pid->integral += pid->currentError;   
    if (pid->integral > integralLimit) {
        pid->integral = integralLimit;
    } else if (pid->integral < -integralLimit) {
        pid->integral = -integralLimit;
    }
    pid->output = pid->Kp * pid->currentError + pid->Ki * pid->integral + pid->Kd * pid->derivative;
    if (pid->output > 2000) pid->output = 2000;
    if (pid->output < -2000) pid->output = -2000;
    
int16_t pwm;
if(i==0)
pwm = PIDL.output;
if(i==1)
pwm = PIDR.output;	

if (pwm >= 0&&i==0) {
TIM1->CCR1 = pwm, HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
} else if((pwm <0&&i==0)){
TIM1->CCR1 = -pwm, HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
}
else if (pwm >= 0&&i==1) {
TIM1->CCR2 = pwm, HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10, GPIO_PIN_SET);
} else if (pwm <0&&i==1){
TIM1->CCR2 = -pwm, HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
}
}
//






//路线修正
// 计算路线偏差（简单加权平均）
int16_t GetLineError(void)
{
    int32_t sum = 0;
    int8_t count = 0;
	  static int16_t last_error = 0;
    int8_t active_sensors = 0;
    for(int i = 0; i <= 11; i++)
  	{
        if(photo_values[i] == 1){
            int weight = 1;
            if(i >= 4 && i <= 7) weight = 2; 
            sum += (2*i - 11) * 5 * weight;
            count += weight;
            active_sensors++;
        }
    }
		if(active_sensors == 0)
		{
        
        return last_error * 0.7f; // 无标识时可以缓慢衰减，避免剧烈变化
    }
    
    
    //if(count == 12) return 0;
    
    return (count > 0) ? (sum * ks / count) : 0;
}

// 直线循迹控制
void LineFollow(void)
{
    int16_t line_error = GetLineError();
	  static int16_t last_error = 0;//平均滤波，平稳变化，静态变量，一次赋值
	  line_error = 0.85f * line_error + 0.15f * last_error;
    last_error = line_error;
    float turn = Kp * line_error + Kd * gyro_z;//调用函数获取 z ，调整左右轮差速
    
	  /*float dynamic_speed = base_speed;
    if(abs(line_error) > 30) {
	dynamic_speed = base_speed * 0.7f; // 刹不住可以加上
    }
	  */
    Lpwm = base_speed + turn*1.1;
	  Rpwm = base_speed - turn*1.1;//一左一右，可在上面取反
    
  
}
//封装光电管、陀螺仪
void MUX_read_value(){
	//以下为读取光电管的示例（从左到右编号0~11）
    uint16_t mux_value;
    MUX_get_value(&mux_value);
    for(int i=0;i<=11;i++){
			photo_values[i] = MUX_GET_CHANNEL(mux_value,i);
    //  printf("%d,",MUX_GET_CHANNEL(mux_value,i));//获取第i个光电管的数值并输出，跑的时候删掉
    }
		//printf("\n");//调试用
		dodo_BMI270_get_data();//调用此函数会更新陀螺仪数据，权宜之计
    gyro_z=BMI270_gyro_transition(BMI270_gyro_z);
}



//直角转弯
void test_right_angle(void)//直角检测
{
	
        if (right_angle_flag == 0 && durtime == 0 && turn_start_time == 0) {
        int left_count = 0, right_count = 0;
        
        for(int i = 0; i <= 5; i++) {
            if(photo_values[i] == 1) left_count++;
        }
        for(int i = 6; i <= 11; i++) {
            if(photo_values[i] == 1) right_count++;
        }
    
				if(left_count >= 5) {
            right_angle_flag = -1;
          //  printf("左直角触发，计数=%d\n", left_count);
        } 
        else if(right_count >= 5) {
            right_angle_flag = 1;
           // printf("右直角触发，计数=%d\n", right_count);
        }
			}
    return;
}
void turn()
{
	if (turn_start_time == 0) 
	{
        turn_start_time = HAL_GetTick();
  }
	durtime=1;
	uint32_t current_time = HAL_GetTick();
  uint32_t turn_duration = current_time - turn_start_time;//转弯时间
	
    
	float turn_ratio=0.85;
    
	if(right_angle_flag==-1){
		Lpwm=-250;
		Rpwm=turn_ratio*base_speed;
	}
	if(right_angle_flag==1){
		Lpwm=turn_ratio*base_speed;
		Rpwm=-250;
	}
	
	if (turn_duration > 1200) {
        right_angle_flag = 0;
    turn_start_time = 0;
    durtime = 0;
        return;
    }//超时保护
	if (turn_duration >=150) {
        if (right_angle_flag == -1) { 
            // 左转完成
            if (photo_values[6] == 1 || photo_values[7] == 1 || photo_values[8] == 1)
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
        } 
        else if (right_angle_flag == 1) { 
            // 右转完成
            if (photo_values[3] == 1 || photo_values[4] == 1 || photo_values[5] == 1) 
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
						durtime=0;
        }
				return;
    }
	if (turn_duration >=100) {
        if (right_angle_flag == -1) { 
            // 左转完成
            if (photo_values[6] == 1 || photo_values[7] == 1 || photo_values[8] == 1)
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
        } 
        else if (right_angle_flag == 1) { 
            // 右转完成
            if (photo_values[3] == 1 || photo_values[4] == 1 || photo_values[5] == 1) 
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
						durtime=0;
        }
				return;
    }
	if (turn_duration >=74) {
        if (right_angle_flag == -1) { 
            // 左转完成
            if (photo_values[6] == 1 || photo_values[7] == 1 || photo_values[8] == 1)
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
        } 
        else if (right_angle_flag == 1) { 
            // 右转完成
            if (photo_values[3] == 1 || photo_values[4] == 1 || photo_values[5] == 1) 
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
						durtime=0;
        }
				return;
    }
	if (turn_duration >=40) {
        if (right_angle_flag == -1) { 
            // 左转完成
            if (photo_values[6] == 1 || photo_values[7] == 1 || photo_values[8] == 1)
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
        } 
        else if (right_angle_flag == 1) { 
            // 右转完成
            if (photo_values[3] == 1 || photo_values[4] == 1 || photo_values[5] == 1) 
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
						durtime=0;
        }
				return;
    }
	
	if (turn_duration >=16) {
        if (right_angle_flag == -1) { 
            // 左转完成
            if (photo_values[6] == 1 || photo_values[7] == 1 || photo_values[8] == 1)
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
        } 
        else if (right_angle_flag == 1) { 
            // 右转完成
            if (photo_values[3] == 1 || photo_values[4] == 1 || photo_values[5] == 1) 
						{
                 right_angle_flag = 0;
                 turn_start_time = 0;
                 durtime = 0;
            }
						durtime=0;
        }
				return;
    }
}
//


//十字判定
void cross_test(void)
{
	uint16_t count=0;
	for(int i = 0; i <= 11; i++) {
            if(photo_values[i] == 1) count++;
        }
	if(count>=10)
	{
	cross_flag=1;
	cross_time=HAL_GetTick();
	}
	if(HAL_GetTick()-cross_time>=60)
	{
		cross_flag=0;
		count=0;
	}
}
//

//
void errortest(void)
{
    static uint32_t startimec = 0;
    uint16_t scount = 0;
    
    for(int i = 0; i <= 11; i++) 
    {
        if(photo_values[i] == 1) 
            scount++;
    }
    
    if(scount == 0)
    {
        if(startimec == 0)
        {
            startimec = HAL_GetTick();
        }
        else if((HAL_GetTick() - startimec) >= 2000)
        {
            startimec = 0;
            HAL_TIM_Base_Stop_IT(&htim2);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
  HAL_TIM_Encoder_Stop(&htim3, TIM_CHANNEL_ALL);//右
	HAL_TIM_Encoder_Stop(&htim4, TIM_CHANNEL_ALL);//左
      
              
                while(1);
            
        }
    }
    else 
    {
        startimec = 0;
    
    }
}
/*
void slow(void)
{
	uint16_t time=4;
	Lpwm=-base_speed*0.1f;
	Rpwm=-base_speed*0.1f;
	set_motor(0,-Lpwm);
	set_motor(1,-1.475f*Rpwm);
	HAL_Delay(time);
}
*/


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
