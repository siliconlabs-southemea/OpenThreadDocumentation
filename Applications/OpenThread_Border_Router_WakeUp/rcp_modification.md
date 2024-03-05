---
sort: 2
---

# RCP firmware
When using Silicon Labs hardware, developers have 2 options to build the RCP firmware
  1.  Either from the OpenThread repository
  2.  Directly within [Simplicity Studio](https://www.silabs.com/developers/simplicity-studio)

      **This first method will not be covered in this guide**

## Modify RCP firmware

In order to be woken-up on a specifc 802.15.4 packet some modificationare necessary in RCP firmware. 

1.  Modify `ncp_base_radio.cpp` located in `gecko_sdk_x.x\util\third_party\openthread\src\ncp` as following:

    ```bash
    extern "C"  void magic_packet_test(otRadioFrame *aFrame);

    void NcpBase::LinkRawReceiveDone(otRadioFrame *aFrame, otError aError)
    {
      uint8_t header = SPINEL_HEADER_FLAG;

      OT_ASSERT(aFrame->mIid < kSpinelHeaderMaxNumIID);

      header |= SPINEL_HEADER_IID(aFrame->mIid);

      magic_packet_test(aFrame);

      // Append frame header
      SuccessOrExit(mEncoder.BeginFrame(header, SPINEL_CMD_PROP_VALUE_IS, SPINEL_PROP_STREAM_RAW));
      SuccessOrExit(PackRadioFrame(aFrame, aError));
      SuccessOrExit(mEncoder.EndFrame());

      exit:
          return;
    }
    ```
    The `LinkRawReceiveDone` function is called on receipt of a IEEE 802.15.4 frame.

2.  Create a magic_packet.c file in the RCP project directory and add the following content to it: 

    ```bash
    #include <stdio.h>

    #include <openthread/ncp.h>
    #include "openthread-system.h"

    #include "em_gpio.h"
    #include "gpiointerrupt.h"

    #define GO_TO_SLEEP_GPIO_PORT gpioPortD
    #define GO_TO_SLEEP_GPIO_PIN  14

    #define WAKE_UP_CMD_GPIO_PORT gpioPortD
    #define WAKE_UP_CMD_GPIO_PIN  8

    uint8_t volatile sleeping = 0;
    static otInstance* sInstance = NULL;

    /* Use a GPIO to enter sleep mode */
    void GO_TO_SLEEP_gpio_callback(void)
    {
      uint8_t v = GPIO_PinInGet(GO_TO_SLEEP_GPIO_PORT, GO_TO_SLEEP_GPIO_PIN);

      /* Check if falling edge */
      if (v == 0)
        sleeping = 1;
    }

    /* Raise a GPIO when magic packet is detected */
    void magic_packet_test(otRadioFrame *aFrame)
    {
      uint16_t panId = *(uint16_t *)((aFrame->mPsdu) + 3);
      uint16_t dst = *(uint16_t *)((aFrame->mPsdu) + 5);
      uint16_t src = *(uint16_t *)((aFrame->mPsdu) + 7);

      /* Any other tests can be added there */
      if ((sleeping == 1) && (panId == otLinkGetPanId(sInstance)) &&
          (dst == 0xFFFF) && (src == 0xFFFF))
      {
        GPIO_PinOutSet(WAKE_UP_CMD_GPIO_PORT, WAKE_UP_CMD_GPIO_PIN);
        sleeping = 0;
      }
    }

    void magic_packet_init(otInstance *aInstance)
    {
      sInstance = aInstance;
      
      //GPIOINT_Init() and CMU_ClockEnable(cmuClock_GPIO) have already been called

      // Configure Button PB1 as input and enable interrupt
      GPIO_PinModeSet(GO_TO_SLEEP_GPIO_PORT, GO_TO_SLEEP_GPIO_PIN, gpioModeInputPull, 1);
      GPIO_ExtIntConfig(GO_TO_SLEEP_GPIO_PORT,
                        GO_TO_SLEEP_GPIO_PIN,
                        GO_TO_SLEEP_GPIO_PIN,
                        false,
                        true,
                        true);


      // Register callback functions and enable interrupts
      GPIOINT_CallbackRegister(GO_TO_SLEEP_GPIO_PIN, GO_TO_SLEEP_gpio_callback);
      GPIO_IntEnable(1<<GO_TO_SLEEP_GPIO_PIN);

      // Configure LED0 as a push pull output for LED drive
      GPIO_PinModeSet(WAKE_UP_CMD_GPIO_PORT, WAKE_UP_CMD_GPIO_PIN, gpioModePushPull, 0);
    }
    ```
    We discriminate the magic packet here based on panId, SrcId and DstId of 802.15.4 received packet. We also use A GPIO to know when sleeping 
    mode has been entered. This code has been tested on BRD4166a only. You will have to modify `WAKE_UP_CMD_GPIO` and `GO_TO_SLEEP_GPIO` to have 
    it work on another platform.
    
3.  Call `magic_packet_init()` function from app_init():

    ```bash
    void app_init(void)
    {
      OT_SETUP_RESET_JUMP(argv);

      magic_packet_init(sInstance);
    }
    ```


## Build and Flash the RCP

After compilation, flash the firmware into EFR32. Don't forget to add a bootloader.
