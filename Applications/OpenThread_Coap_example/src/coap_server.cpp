#include <stdio.h>
#include <string.h>
#include <openthread/coap.h>
#include <openthread/cli.h>

#include <openthread/logging.h>
#include "utils/code_utils.h"
#include "em_gpio.h"
#include "em_cmu.h"

#include "sl_button.h"
#include "sl_simple_button.h"


// Define the multicast address (example: all nodes in the network)
const char *multicastAddress = "ff03::1";
static const char *UriPath = "gpio";
uint8_t gpioState[3] = "OFF";
otCoapResource coapResourcegpio;

static otInstance *sInstance = NULL;

#define OFF 1
#define ON 0


// Function to handle CoAP requests
void coap_request_handler(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo)
{
  otError error = OT_ERROR_NONE;
  otMessage *responseMessage;
  otCoapCode responseCode = OT_COAP_CODE_CHANGED;
  otCoapCode messageCode = otCoapMessageGetCode(aMessage);  // read code (get,put,post..)
  otCoapType messageType = otCoapMessageGetType(aMessage);  // read message type (confirmable or not)

  // read any payload
  char data[32];
  uint16_t offset = otMessageGetOffset(aMessage);
  uint16_t read = otMessageRead(aMessage, offset, data, sizeof(data) - 1);
  data[read] = '\0';

  // prepare and send acknowledge response message
  responseMessage = otCoapNewMessage((otInstance*)aContext, NULL);
  otEXPECT_ACTION(responseMessage != NULL, error = OT_ERROR_NO_BUFS);

  otCoapMessageInitResponse(responseMessage, aMessage, OT_COAP_TYPE_ACKNOWLEDGMENT, responseCode);
  otCoapMessageSetToken(responseMessage, otCoapMessageGetToken(aMessage), otCoapMessageGetTokenLength(aMessage));
  otCoapMessageSetPayloadMarker(responseMessage);

  // treat code action
  switch (messageCode) {

    case OT_COAP_CODE_GET:
      error = otMessageAppend(responseMessage, gpioState, strlen((const char*)gpioState));
      otEXPECT(OT_ERROR_NONE == error);
      error = otCoapSendResponse((otInstance*)aContext, responseMessage, aMessageInfo);
      otEXPECT(OT_ERROR_NONE == error);
      break;

    case OT_COAP_CODE_PUT:
      otLogCritPlat("message: %d, %d,  %s\n",offset,read, data);
      /* process message */
      if(strcmp("ON", data) == 0)
        {
          /* update the attribute state */

          memcpy(gpioState, "ON", sizeof(3));
          GPIO_PinOutClear(gpioPortA, 4);
          otCliOutputFormat("\nGPIO ON\r");
        }
      else if(strcmp("OFF", data) == 0)
        {
          /* update the attribute state */
          memcpy(gpioState, "OFF", sizeof(3));
          GPIO_PinOutSet(gpioPortA, 4);
          otCliOutputFormat("\nGPIO OFF\r");
        }
      else if(strcmp("TOGGLE", data) == 0)
              {
                /* update the attribute state */
                if (strcmp("ON", gpioState) == 0)
                  memcpy(gpioState, "OFF", sizeof(3));
                else
                  memcpy(gpioState, "ON", sizeof(3));

                GPIO_PinOutToggle(gpioPortA, 4);
                otCliOutputFormat("\nGPIO TOGGLE\r");
              }
      else
        {
          /* no valid body, fail without response */
          otEXPECT_ACTION(false, error = OT_ERROR_NO_BUFS);
        }

      if (OT_COAP_TYPE_CONFIRMABLE == messageType)
        {


          error = otMessageAppend(responseMessage, gpioState,strlen((const char*)gpioState));
          otEXPECT(OT_ERROR_NONE == error);
          error = otCoapSendResponse((otInstance*)aContext,responseMessage, aMessageInfo);
          otEXPECT(OT_ERROR_NONE == error);
        }
      break;

    default:
      // nothing to do...
      break;
  }

  exit:

    if (error != OT_ERROR_NONE && responseMessage != NULL)
      {
        otMessageFree(responseMessage);
      }


}


extern "C" void send_command(void)
{
        // Prepare the CoAP message
        otMessage *message = otCoapNewMessage(sInstance, NULL);
        otCoapMessageInit(message, OT_COAP_TYPE_NON_CONFIRMABLE, OT_COAP_CODE_PUT);
        otCoapMessageGenerateToken(message, OT_COAP_DEFAULT_TOKEN_LENGTH);
        otCoapMessageAppendUriPathOptions(message, UriPath);
        otCoapMessageSetPayloadMarker(message);

        // Add payload to the message
        const char *payload = "TOGGLE";
        otMessageAppend(message, payload, strlen(payload));

        // Prepare message info
        otMessageInfo messageInfo;
        memset(&messageInfo, 0, sizeof(messageInfo));
        otIp6AddressFromString(multicastAddress, &messageInfo.mPeerAddr);
        messageInfo.mPeerPort = OT_DEFAULT_COAP_PORT;

        // Send the CoAP message
        otError error = otCoapSendRequest(sInstance, message, &messageInfo, NULL, NULL);

        if (error != OT_ERROR_NONE) {
            otMessageFree(message);
            otCliOutputFormat("\nmessage send error %d\r", error);
        }
        else
          otCliOutputFormat("\nmessage sent\r");

}

extern "C" void coap_server_init(otInstance *aInstance)
{

  sInstance = aInstance;
  //coap_server_init(aInstance);

  // Enable GPIO clock. Note this step is not required for EFR32xG21 devices
   CMU_ClockEnable(cmuClock_GPIO, true);

   GPIO_PinModeSet(gpioPortA, 4, gpioModePushPull, OFF);

   otCoapStart(aInstance, OT_DEFAULT_COAP_PORT);

   coapResourcegpio.mContext=aInstance;
   coapResourcegpio.mUriPath=UriPath;
   coapResourcegpio.mHandler=coap_request_handler;
   coapResourcegpio.mNext=NULL;

   otCoapAddResource(aInstance, &coapResourcegpio);

   otCliOutputFormat("\nCoAP server initialized\r\n");

}



