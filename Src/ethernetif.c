/**
  ******************************************************************************
  * File Name          : ethernetif.c
  * Description        : This file provides code for the configuration
  *                      of the ethernetif.c MiddleWare.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "lwip/opt.h"

#include "lwip/lwip_timers.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include <string.h>
#include "cmsis_os.h"
/* Within 'USER CODE' section, code will be kept by default at each generation */
/* USER CODE BEGIN 0 */
#include "enc28j60.h"
#include "myspi.h"
#include "myled.h"
#include "tcpip.h"
/* USER CODE END 0 */

/* Private define ------------------------------------------------------------*/
/* The time to block waiting for input. */
#define TIME_WAITING_FOR_INPUT ( portMAX_DELAY )
/* Stack size of the interface thread */
#define INTERFACE_THREAD_STACK_SIZE ( 350 )
/* Network interface name */
#define IFNAME0 'r'
#define IFNAME1 'u'

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* Private variables ---------------------------------------------------------*/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif

__ALIGN_BEGIN ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB] __ALIGN_END;/* Ethernet Rx MA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
__ALIGN_BEGIN ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB] __ALIGN_END;/* Ethernet Tx DMA Descriptor */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE] __ALIGN_END; /* Ethernet Receive Buffer */

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE] __ALIGN_END; /* Ethernet Transmit Buffer */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/* Semaphore to signal incoming packets */
osSemaphoreId s_xSemaphore = NULL;
/* Global Ethernet handle*/
//ETH_HandleTypeDef heth; Modified by Yang , we will not use this handle here
ENC_HandleTypeDef EncHandle;
extern SPI_HandleTypeDef hspi1;

extern osSemaphoreId Netif_IRQSemaphore;

/* USER CODE BEGIN 3 */

/* USER CODE END 3 */

/* Private functions ---------------------------------------------------------*/

//void HAL_ETH_MspInit(ETH_HandleTypeDef* ethHandle)
//{
//GPIO_InitTypeDef GPIO_InitStruct;
//if(ethHandle->Instance==ETH)
//changed by yang
//{
/* USER CODE BEGIN ETH_MspInit 0 */

/* USER CODE END ETH_MspInit 0 */
/* Enable Peripheral clock */
//__HAL_RCC_ETH_CLK_ENABLE();

/**ETH GPIO Configuration
PC1     ------> ETH_MDC
PA1     ------> ETH_REF_CLK
PA2     ------> ETH_MDIO
PA7     ------> ETH_CRS_DV
PC4     ------> ETH_RXD0
PC5     ------> ETH_RXD1
PB11     ------> ETH_TX_EN
PB12     ------> ETH_TXD0
PB13     ------> ETH_TXD1
*/
//GPIO_InitStruct.Pin = GPIO_PIN_1;
//GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

//GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_7;
//GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//GPIO_InitStruct.Pull = GPIO_NOPULL;
//HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//GPIO_InitStruct.Pin = GPIO_PIN_2;
//GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
//GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//GPIO_InitStruct.Pull = GPIO_NOPULL;
//HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

//GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
//GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* Peripheral interrupt init */
//HAL_NVIC_SetPriority(ETH_IRQn, 5, 0);
//HAL_NVIC_EnableIRQ(ETH_IRQn);
// Changed by Yang
/* USER CODE BEGIN ETH_MspInit 1 */

/* USER CODE END ETH_MspInit 1 */
//} Changed by Yang
//}

//void HAL_ETH_MspDeInit(ETH_HandleTypeDef* ethHandle)
//{
//if(ethHandle->Instance==ETH)
//{
/* USER CODE BEGIN ETH_MspDeInit 0 */

/* USER CODE END ETH_MspDeInit 0 */
/* Disable Peripheral clock */
//__HAL_RCC_ETH_CLK_DISABLE();

/**ETH GPIO Configuration
PC1     ------> ETH_MDC
PA1     ------> ETH_REF_CLK
PA2     ------> ETH_MDIO
PA7     ------> ETH_CRS_DV
PC4     ------> ETH_RXD0
PC5     ------> ETH_RXD1
PB11     ------> ETH_TX_EN
PB12     ------> ETH_TXD0
PB13     ------> ETH_TXD1
*/
//HAL_GPIO_DeInit(GPIOC, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5);

//HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_7);

//HAL_GPIO_DeInit(GPIOB, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13);

/* Peripheral interrupt Deinit*/
//HAL_NVIC_DisableIRQ(ETH_IRQn);

/* USER CODE BEGIN ETH_MspDeInit 1 */

/* USER CODE END ETH_MspDeInit 1 */
//}
//}

/**
  * @brief  Ethernet Rx Transfer completed callback
  * @param  heth: ETH handle
  * @retval None
  */
//void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
//{
//  osSemaphoreRelease(s_xSemaphore);
//}

/* USER CODE BEGIN 4 */
/******************************************************************************
*
                       ENC28J60 MSP Routines
*******************************************************************************/
/**
  * @brief  Initializes the ENC28J60 MSP.
  * @param  heth: ENC28J60 handle
  * @retval None
  */
void ENC_MSPInit(ENC_HandleTypeDef *heth)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIOs clocks */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /* ENC28J60 pins configuration
    ************************************************/
    /*
          ENC28J60_CS ----------------------> PA4
          ENC28J60_INT ---------------------> PC4
    */

    /*Configure GPIO pins : PA4 */
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Deselect ENC28J60 module */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

//#ifdef ENC28J60_INTERRUPT
    /*Configure GPIO pin : PC4 */
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
//#endif /* ENC28J60_INTERRUPT */

    /* Initialize SPI */
    My_Spi_Init();

//#ifdef ENC28J60_INTERRUPT
    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI4_IRQn, 0x0F, 0x0F);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
//#endif /* ENC28J60_INTERRUPT */

}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//    if(GPIO_Pin == GPIO_PIN_4)
//    {
//        /* Toggle LED3 */
//        LED3_Toggle();
//        printf("i\n");
//
//    }
//
//}

/* USER CODE END 4 */

/*******************************************************************************
                       LL Driver Interface ( LwIP stack --> ETH)
*******************************************************************************/
/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void low_level_init(struct netif *netif)
{
    //uint32_t regvalue = 0;
    //HAL_StatusTypeDef hal_eth_init_status;

    /* Init ETH */
    /* set MAC hardware address length */
    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    /* set MAC hardware address */
    netif->hwaddr[0] =  MAC_ADDR0;
    netif->hwaddr[1] =  MAC_ADDR1;
    netif->hwaddr[2] =  MAC_ADDR2;
    netif->hwaddr[3] =  MAC_ADDR3;
    netif->hwaddr[4] =  MAC_ADDR4;
    netif->hwaddr[5] =  MAC_ADDR5;

    EncHandle.Init.MACAddr = netif->hwaddr;
    EncHandle.Init.DuplexMode = ETH_MODE_HALFDUPLEX;
    EncHandle.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
    EncHandle.Init.InterruptEnableBits =  EIE_LINKIE | EIE_PKTIE;

    /* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
    ENC_MSPInit(&EncHandle);
    /* Set netif link flag */
//  netif->flags |= NETIF_FLAG_LINK_UP;

    /* maximum transfer unit */
    netif->mtu = 1500;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;


    /* Start the EN28J60 module */
    if(ENC_Start(&EncHandle))
    {
        /* Set the MAC address */
        ENC_SetMacAddr(&EncHandle);

        /* Set netif link flag */
        netif->flags |= NETIF_FLAG_LINK_UP;
    }

//  uint8_t MACAddr[6] ;
//  heth.Instance = ETH;
//  heth.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
//  heth.Init.PhyAddress = LAN8742A_PHY_ADDRESS;
//  MACAddr[0] = 0x00;
//  MACAddr[1] = 0x80;
//  MACAddr[2] = 0xE1;
//  MACAddr[3] = 0x00;
//  MACAddr[4] = 0x00;
//  MACAddr[5] = 0x00;
//  heth.Init.MACAddr = &MACAddr[0];
//  heth.Init.RxMode = ETH_RXINTERRUPT_MODE;
//  heth.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
//  heth.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;
    // changed by Yang

    /* USER CODE BEGIN MACADDRESS */

    /* USER CODE END MACADDRESS */

    //hal_eth_init_status = HAL_ETH_Init(&heth);

    //if (hal_eth_init_status == HAL_OK)
    //{
    /* Set netif link flag */
    //  netif->flags |= NETIF_FLAG_LINK_UP;
    //}

    /* Initialize Tx Descriptors list: Chain Mode */
    //HAL_ETH_DMATxDescListInit(&heth, DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);

    /* Initialize Rx Descriptors list: Chain Mode  */
    //HAL_ETH_DMARxDescListInit(&heth, DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);

#if LWIP_ARP || LWIP_ETHERNET
    /* set MAC hardware address length */
    //netif->hwaddr_len = ETHARP_HWADDR_LEN;

    /* set MAC hardware address */
    //netif->hwaddr[0] =  heth.Init.MACAddr[0];
    //netif->hwaddr[1] =  heth.Init.MACAddr[1];
    //netif->hwaddr[2] =  heth.Init.MACAddr[2];
    //netif->hwaddr[3] =  heth.Init.MACAddr[3];
    //netif->hwaddr[4] =  heth.Init.MACAddr[4];
    //netif->hwaddr[5] =  heth.Init.MACAddr[5];

    /* maximum transfer unit */
    //netif->mtu = 1500;

    /* Accept broadcast address and ARP traffic */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
#if LWIP_ARP
    //netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;
#else
    //netif->flags |= NETIF_FLAG_BROADCAST;
#endif /* LWIP_ARP */

    /* create a binary semaphore used for informing ethernetif of frame reception */
    //osSemaphoreDef(SEM);
    //s_xSemaphore = osSemaphoreCreate(osSemaphore(SEM) , 1 );

    /* create the task that handles the ETH_MAC */
    //osThreadDef(EthIf, ethernetif_input, osPriorityRealtime, 0, INTERFACE_THREAD_STACK_SIZE);
    //osThreadCreate (osThread(EthIf), netif);
    /* Enable MAC and DMA transmission and reception */
    //HAL_ETH_Start(&heth);

    /* USER CODE BEGIN PHY_PRE_CONFIG */

    /* USER CODE END PHY_PRE_CONFIG */


    /* Read Register Configuration */
    //HAL_ETH_ReadPHYRegister(&heth, PHY_ISFR, &regvalue);
    //regvalue |= (PHY_ISFR_INT4);

    /* Enable Interrupt on change of link status */
    //HAL_ETH_WritePHYRegister(&heth, PHY_ISFR , regvalue );

    /* Read Register Configuration */
    //HAL_ETH_ReadPHYRegister(&heth, PHY_ISFR , &regvalue);

    /* USER CODE BEGIN PHY_POST_CONFIG */

    /* USER CODE END PHY_POST_CONFIG */

#endif /* LWIP_ARP || LWIP_ETHERNET */

    /* USER CODE BEGIN LOW_LEVEL_INIT */

    /* USER CODE END LOW_LEVEL_INIT */
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    err_t errval;

    struct pbuf *q;
    uint32_t framelength = 0;

    q=p;

    if(EncHandle.transmitLength != 0)
    {
//#ifdef USE_PROTOTHREADS
//     while (PT_SCHEDULE(ENC_Transmit(&transmit_pt, &EncHandle))) {
        /* Wait for end of previous transmission */
//     }
//#else
        do
        {
            ENC_Transmit(&EncHandle);
        }
        while(EncHandle.transmitLength != 0);
//#endif
    }

    /* Prepare ENC28J60 Tx buffer */
    errval = ENC_RestoreTXBuffer(&EncHandle, p->tot_len);
    if(errval != ERR_OK)
    {
        return errval;
    }


    /* copy frame from pbufs to driver buffers and send packet */
    for(q = p; q != NULL; q = q->next)
    {
        ENC_WriteBuffer(q->payload, q->len);
        framelength += q->len;
    }

    if(framelength != p->tot_len)
    {
        return ERR_BUF;
    }

    EncHandle.transmitLength = p->tot_len;


    /* If PROTOTHREADS are use, actual transmission is triggered in main loop */
#ifndef USE_PROTOTHREADS
    ENC_Transmit(&EncHandle);
#endif

    return ERR_OK;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
   */
static struct pbuf * low_level_input(struct netif *netif)
{
    struct pbuf *p = NULL;
    struct pbuf *q = NULL;

    uint16_t len;
    uint8_t *buffer;
    uint32_t bufferoffset = 0;

    if(!ENC_GetReceivedFrame(&EncHandle))
    {
        return NULL;
    }

    /* Obtain the size of the packet and put it into the "len" variable. */
    len = EncHandle.RxFrameInfos.length;
    buffer = (uint8_t *)EncHandle.RxFrameInfos.buffer;

    if(len > 0)
    {
        /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    }

    if(p != NULL)
    {
        bufferoffset = 0;

        for(q = p; q != NULL; q = q->next)
        {
            /* Copy data in pbuf */
            memcpy((uint8_t*)((uint8_t*)q->payload), (uint8_t*)((uint8_t*)buffer 
            + bufferoffset), q->len);
            bufferoffset = bufferoffset + q->len;
        }
    }


//  uint16_t len = 0;
//  uint8_t *buffer;
//  __IO ETH_DMADescTypeDef *dmarxdesc;
//  uint32_t bufferoffset = 0;
//  uint32_t payloadoffset = 0;
//  uint32_t byteslefttocopy = 0;
//  uint32_t i=0;
//
//
//  /* get received frame */
//  if (HAL_ETH_GetReceivedFrame_IT(&heth) != HAL_OK)
//    return NULL;
//
//  /* Obtain the size of the packet and put it into the "len" variable. */
//  len = heth.RxFrameInfos.length;
//  buffer = (uint8_t *)heth.RxFrameInfos.buffer;
//
//  if (len > 0)
//  {
//    /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
//    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
//  }
//
//  if (p != NULL)
//  {
//    dmarxdesc = heth.RxFrameInfos.FSRxDesc;
//    bufferoffset = 0;
//    for(q = p; q != NULL; q = q->next)
//    {
//      byteslefttocopy = q->len;
//      payloadoffset = 0;
//
//      /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size*/
//      while( (byteslefttocopy + bufferoffset) > ETH_RX_BUF_SIZE )
//      {
//        /* Copy data to pbuf */
//        memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset), (uint8_t*)((uint8_t*)buffer + bufferoffset), (ETH_RX_BUF_SIZE - bufferoffset));
//
//        /* Point to next descriptor */
//        dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
//        buffer = (uint8_t *)(dmarxdesc->Buffer1Addr);
//
//        byteslefttocopy = byteslefttocopy - (ETH_RX_BUF_SIZE - bufferoffset);
//        payloadoffset = payloadoffset + (ETH_RX_BUF_SIZE - bufferoffset);
//        bufferoffset = 0;
//      }
//      /* Copy remaining data in pbuf */
//      memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset), (uint8_t*)((uint8_t*)buffer + bufferoffset), byteslefttocopy);
//      bufferoffset = bufferoffset + byteslefttocopy;
//    }
//  }
//
//    /* Release descriptors to DMA */
//    /* Point to first descriptor */
//    dmarxdesc = heth.RxFrameInfos.FSRxDesc;
//    /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
//    for (i=0; i< heth.RxFrameInfos.SegCount; i++)
//    {
//      dmarxdesc->Status |= ETH_DMARXDESC_OWN;
//      dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
//    }
//
//    /* Clear Segment_Count */
//    heth.RxFrameInfos.SegCount =0;
//
//  /* When Rx Buffer unavailable flag is set: clear it and resume reception */
//  if ((heth.Instance->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)
//  {
//    /* Clear RBUS ETHERNET DMA flag */
//    heth.Instance->DMASR = ETH_DMASR_RBUS;
//    /* Resume DMA reception */
//    heth.Instance->DMARPDR = 0;
//  }
    return p;
}



/**
  * @brief This function should be called when a packet is ready to be read
  * from the interface. It uses the function low_level_input() that
  * should handle the actual reception of bytes from the network
  * interface. Then the type of the received packet is determined and
  * the appropriate input function is called.
  *
  * @param netif the lwip network interface structure for this ethernetif
  */
void ethernetif_input_do(struct netif * netif)
{
    struct pbuf *p;

    do {
        p = low_level_input(netif);
        if (p != NULL)
        {
          if (netif->input(p, netif) != ERR_OK )
          {
            pbuf_free(p);
          }
        }
    }while(p!=NULL);
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void ethernetif_input(void const * argument)
{
    struct pbuf *p;
    struct netif *netif = (struct netif *) argument;

    for(;;)
    {
        if(osSemaphoreWait(s_xSemaphore, TIME_WAITING_FOR_INPUT)==osOK)
        {
            do
            {
                p = low_level_input(netif);
                if(p != NULL)
                {
                    if(netif->input(p, netif) != ERR_OK)
                    {
                        pbuf_free(p);
                    }
                }
            }
            while(p!=NULL);
        }
    }
}

#if !LWIP_ARP
/**
 * This function has to be completed by user in case of ARP OFF.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if ...
 */
static err_t low_level_output_arp_off(struct netif *netif, struct pbuf *q, ip_addr_t *ipaddr)
{
    err_t errval;
    errval = ERR_OK;

    /* USER CODE BEGIN 5 */

    /* USER CODE END 5 */

    return errval;

}
#endif /* LWIP_ARP */

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t ethernetif_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "ruff1";
#endif /* LWIP_NETIF_HOSTNAME */

    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function an call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
#if LWIP_ARP || LWIP_ETHERNET
#if LWIP_ARP
    netif->output = etharp_output;
#else
    /* The user should write ist own code in low_level_output_arp_off function */
    netif->output = low_level_output_arp_off;
#endif /* LWIP_ARP */
#endif  /* LWIP_ARP || LWIP_ETHERNET */

    netif->linkoutput = low_level_output;

    /* initialize the hardware */
    low_level_init(netif);

    return ERR_OK;
}

/* USER CODE BEGIN 6 */

/**
* @brief  Returns the current time in milliseconds
*         when LWIP_TIMERS == 1 and NO_SYS == 1
* @param  None
* @retval Time
*/
u32_t sys_jiffies(void)
{
    return HAL_GetTick();
}

/**
* @brief  Returns the current time in milliseconds
*         when LWIP_TIMERS == 1 and NO_SYS == 1
* @param  None
* @retval Time
*/
u32_t sys_now(void)
{
    return HAL_GetTick();
}

/* USER CODE END 6 */

/* USER CODE BEGIN 7 */

/* USER CODE END 7 */

#if LWIP_NETIF_LINK_CALLBACK
/**
  * @brief  Link callback function, this function is called on change of link status
  *         to update low level driver configuration.
* @param  netif: The network interface
  * @retval None
  */
void ethernetif_update_config(struct netif *netif)
{
  if(netif_is_link_up(netif)) {
      /* Restart the EN28J60 module */
      low_level_init(netif);
  }

//    if(netif_is_link_up(netif))
//    {
//        /* Restart the auto-negotiation */
//        if(heth.Init.AutoNegotiation != ETH_AUTONEGOTIATION_DISABLE)
//        {
//            /* Enable Auto-Negotiation */
//            HAL_ETH_WritePHYRegister(&heth, PHY_BCR, PHY_AUTONEGOTIATION);
//
//            /* Get tick */
//            tickstart = HAL_GetTick();
//
//            /* Wait until the auto-negotiation will be completed */
//            do
//            {
//                HAL_ETH_ReadPHYRegister(&heth, PHY_BSR, &regvalue);
//
//                /* Check for the Timeout ( 1s ) */
//                if((HAL_GetTick() - tickstart) > 1000)
//                {
//                    /* In case of timeout */
//                    goto error;
//                }
//            }
//            while(((regvalue & PHY_AUTONEGO_COMPLETE) != PHY_AUTONEGO_COMPLETE));
//
//            /* Read the result of the auto-negotiation */
//            HAL_ETH_ReadPHYRegister(&heth, PHY_SR, &regvalue);
//
//            /* Configure the MAC with the Duplex Mode fixed by the auto-negotiation process */
//            if((regvalue & PHY_DUPLEX_STATUS) != (uint32_t)RESET)
//            {
//                /* Set Ethernet duplex mode to Full-duplex following the auto-negotiation */
//                heth.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
//            }
//            else
//            {
//                /* Set Ethernet duplex mode to Half-duplex following the auto-negotiation */
//                heth.Init.DuplexMode = ETH_MODE_HALFDUPLEX;
//            }
//            /* Configure the MAC with the speed fixed by the auto-negotiation process */
//            if(regvalue & PHY_SPEED_STATUS)
//            {
//                /* Set Ethernet speed to 10M following the auto-negotiation */
//                heth.Init.Speed = ETH_SPEED_10M;
//            }
//            else
//            {
//                /* Set Ethernet speed to 100M following the auto-negotiation */
//                heth.Init.Speed = ETH_SPEED_100M;
//            }
//        }
//        else /* AutoNegotiation Disable */
//        {
//        error :
//            /* Check parameters */
//            assert_param(IS_ETH_SPEED(heth.Init.Speed));
//            assert_param(IS_ETH_DUPLEX_MODE(heth.Init.DuplexMode));
//
//            /* Set MAC Speed and Duplex Mode to PHY */
//            HAL_ETH_WritePHYRegister(&heth, PHY_BCR, ((uint16_t)(heth.Init.DuplexMode >> 3) |
//                                     (uint16_t)(heth.Init.Speed >> 1)));
//        }
//
//        /* ETHERNET MAC Re-Configuration */
//        HAL_ETH_ConfigMAC(&heth, (ETH_MACInitTypeDef *) NULL);
//
//        /* Restart MAC interface */
//        HAL_ETH_Start(&heth);
//    }
//    else
//    {
//        /* Stop MAC interface */
//        HAL_ETH_Stop(&heth);
//    }

    ethernetif_notify_conn_changed(netif);
}

/* USER CODE BEGIN 8 */
/**
  * @brief  This function notify user about link status changement.
  * @param  netif: the network interface
  * @retval None
  */
__weak void ethernetif_notify_conn_changed(struct netif *netif)
{
    /* NOTE : This is function could be implemented in user file
              when the callback is needed,
    */

}
/* USER CODE END 8 */
#endif /* LWIP_NETIF_LINK_CALLBACK */

/* USER CODE BEGIN 9 */
/**
  * @brief  This function actually process pending IRQs.
  * @param  handler: Reference to the driver state structure
  * @retval None
  */
void ethernetif_process_irq_do(void const *argument)
{
    struct enc_irq_str *irq_arg = (struct enc_irq_str *)argument;

    /* Handle ENC28J60 interrupt */
    ENC_IRQHandler(&EncHandle);

    /* Check whether the link is up or down*/
    if((EncHandle.interruptFlags & EIE_LINKIE) != 0)
    {
        if((EncHandle.LinkStatus & PHSTAT2_LSTAT)!= 0)
        {
            netif_set_link_up(irq_arg->netif);
        }
        else
        {
            netif_set_link_down(irq_arg->netif);
        }
    }

    /* Check whether we have received a packet */
    if((EncHandle.interruptFlags & EIR_PKTIF) != 0)
    {
        ethernetif_input_do(irq_arg->netif);
    }

    /* Renable global interrupts */
    ENC_EnableInterrupts(EIE_INTIE);
}



/**
  * @brief  This function triggers the interrupt service callback.
  * @param  netif: the network interface
  * @retval None
  */
void ethernetif_process_irq(void const *argument)
{
  struct enc_irq_str *irq_arg = (struct enc_irq_str *)argument;

  for(;;)
  {
    if (osSemaphoreWait(irq_arg->semaphore, TIME_WAITING_FOR_INPUT) == osOK)
    {
        /* Handle ENC28J60 interrupt */
        tcpip_callback((tcpip_callback_fn) ethernetif_process_irq_do, (void *
) argument);
    }
  }
}

/**
  * @brief  This function unblocks ethernetif_process_irq when a new 
interrupt is received
  * @param  netif: the network interface
  * @retval None
  */
void ethernet_irq_handler(osSemaphoreId Netif_IrqSemaphore)
{
    /* Release thread to check interrupt flags */
     osSemaphoreRelease(Netif_IrqSemaphore);
}


/**
  * Implement SPI single byte send and receive.
  * The ENC28J60 slave SPI must already be selected and wont be deselected
after transmission
  * Must be provided by user code
  * param  command: command or data to be sent to ENC28J60
  * retval answer from ENC28J60
  */

uint8_t ENC_SPI_SendWithoutSelection(uint8_t command)
{
    HAL_SPI_TransmitReceive(&hspi1, &command, &command, 1, 1000);
    return command;
}

/**
  * Implement SPI single byte send and receive. Must be provided by user code
  * param  command: command or data to be sent to ENC28J60
  * retval answer from ENC28J60
  */

uint8_t ENC_SPI_Send(uint8_t command)
{
    /* Select ENC28J60 module */
    HAL_NVIC_DisableIRQ(EXTI4_IRQn);
    HAL_GPIO_WritePin(GPIOA, ENC_CS_PIN, GPIO_PIN_RESET);
    up_udelay(1);

    HAL_SPI_TransmitReceive(&hspi1, &command, &command, 1, 1000);

    /* De-select ENC28J60 module */
    HAL_GPIO_WritePin(GPIOA, ENC_CS_PIN, GPIO_PIN_SET);
    up_udelay(1);

    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    return command;
}

/**
  * Implement SPI buffer send and receive. Must be provided by user code
  * param  master2slave: data to be sent from host to ENC28J60, can be NULL
if we only want to receive data from slave
  * param  slave2master: answer from ENC28J60 to host, can be NULL if we only
want to send data to slave
  * retval none
  */

void ENC_SPI_SendBuf(uint8_t *master2slave, uint8_t *slave2master, uint16_t
                     bufferSize)
{
    /* Select ENC28J60 module */
    HAL_NVIC_DisableIRQ(EXTI4_IRQn);
    HAL_GPIO_WritePin(GPIOA, ENC_CS_PIN, GPIO_PIN_RESET);
    up_udelay(1);

    /* Transmit or receuve data */
    if(slave2master == NULL)
    {
        if(master2slave != NULL)
        {
            HAL_SPI_Transmit(&hspi1, master2slave, bufferSize, 1000);
        }
    }
    else if(master2slave == NULL)
    {
        HAL_SPI_Receive(&hspi1, slave2master, bufferSize, 1000);
    }
    else
    {
        HAL_SPI_TransmitReceive(&hspi1, master2slave, slave2master, bufferSize, 1000);
    }

    /* De-select ENC28J60 module */
    HAL_GPIO_WritePin(GPIOA, ENC_CS_PIN, GPIO_PIN_SET);
    up_udelay(1);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

/**
  * Implement SPI Slave selection and deselection. Must be provided by user
code
  * param  select: true if the ENC28J60 slave SPI if selected, false otherwise
  * retval none
  */

void ENC_SPI_Select(bool select)
{
    /* Select or de-select ENC28J60 module */
    if(select)
    {
        HAL_NVIC_DisableIRQ(EXTI4_IRQn);
        HAL_GPIO_WritePin(GPIOA, ENC_CS_PIN, GPIO_PIN_RESET);
        up_udelay(1);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOA, ENC_CS_PIN, GPIO_PIN_SET);
        up_udelay(1);
        HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    }
}


/**
  * @brief  EXTI line detection callbacks
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == ENC_INT_PIN)
  {
      ethernet_irq_handler(Netif_IRQSemaphore);
  }
}

/* USER CODE END 9 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

