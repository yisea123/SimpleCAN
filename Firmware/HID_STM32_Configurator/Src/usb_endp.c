/**
  ******************************************************************************
  * @file    usb_endp.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Endpoint routines
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_desc.h"
#include "usb_lib.h"
#include "usb_istr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t Receive_Buffer[64];
extern __IO uint8_t PrevXferComplete;
extern uint8_t Buffer[RPT4_COUNT+1];

#define ADDRESS  0x08010000 // ����� ������ �������� ����

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : write_flash.
* Description    : None.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

void write_flash_ep1(void) //������ �� ����
{
    int i=0;

    FLASH_Unlock(); //��������� �������������� ����
    FLASH_ErasePage(ADDRESS); //������� �������� �� ���������� ������
    for (i = 0; i < 10; i++)
    {
        FLASH_ProgramWord(ADDRESS+i*4, Receive_Buffer[i]);
    }
   FLASH_Lock(); //��������� �������������� ����
}
/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_OUT_Callback(void)
{
 // BitAction Led_State;

  //Read received data (2 bytes)
  USB_SIL_Read(EP1_OUT, Receive_Buffer); //������ �������� �����

 /* if (Receive_Buffer[2] == 0xAA) // ������� ��� ������� ������ ��������
  {
    __disable_irq(); //��������� ����������
    write_flash_ep1(); //����� �� ����
    __enable_irq(); //�������� ����������
    NVIC_SystemReset(); //������������� ����������
  }
  else
  {
GPIO_ResetBits(LED_PORT,LED2_PIN);
  }
*/

 if (Receive_Buffer[2] == 0x12) // ��� ����� 1
  {
GPIO_SetBits(LED_PORT,LED2_PIN);
  }
  else
  {
GPIO_ResetBits(LED_PORT,LED2_PIN);
  }


 /* switch (Receive_Buffer[0]) // ��� ����� 2
  {
    case 1:
     if (Led_State != Bit_RESET)
     {
       GPIO_SetBits(LED_PORT,LED2_PIN);
     }
     else
     {
       GPIO_ResetBits(LED_PORT,LED2_PIN);
     }
     break;
    case 2:
     if (Led_State != Bit_RESET)
     {
       GPIO_SetBits(LED_PORT,LED2_PIN);
     }
     else
     {
       GPIO_ResetBits(LED_PORT,LED2_PIN);
     }
      break;
    case 3:
        Buffer[4]=Receive_Buffer[1];
     break;
  }*/

  SetEPRxStatus(ENDP1, EP_RX_VALID);
}

/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void)
{
  /* Set the transfer complete token to inform upper layer that the current
  transfer has been complete */
  PrevXferComplete = 1;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

