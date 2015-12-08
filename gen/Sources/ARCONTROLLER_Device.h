/**********************************************************
 *            AUTOGENERATED FILE                          *
 *             DO NOT MODIFY IT                           *
 *                                                        *
 * To add new commands :                                  *
 *  - Modify ../Xml/commands.xml file                     *
 *  - Re-run generateDeviceControllers.py script          *
 *                                                        *
 **********************************************************/

/**
* @file ARCONTROLLER_Device.h
* @brief Device controller allow to drive a device.
*/

#ifndef _ARCONTROLLER_DEVICE_PRIVATE_H_
#define _ARCONTROLLER_DEVICE_PRIVATE_H_

#include <libARSAL/ARSAL_Mutex.h>
#include <libARController/ARCONTROLLER_DICTIONARY_Key.h>
#include <libARCommands/ARCommands.h>
#include <libARController/ARCONTROLLER_Feature.h>

#define ARCONTROLLER_DEVICE_DEFAULT_LOOPER_CMD_BUFFER_SIZE 1024

/**
 * @brief 
 */
typedef struct ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t;

struct ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t
{
    ARCONTROLLER_Device_StateChangedCallback_t callback; /**< callback used when the state is changed. */
    void *customData;  /**< custom data given as parameter to the callback. */
    
    ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t *next;
    ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t *prev;
};

typedef struct ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t;

struct ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t
{
    ARCONTROLLER_Device_ExtensionStateChangedCallback_t callback; /**< callback used when the extension state is changed. */
    void *customData;  /**< custom data given as parameter to the callback. */
    
    ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t *next;
    ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t *prev;
};

/**
 * @brief Device controller allow to drive a device.
 */
struct ARCONTROLLER_Device_Private_t
{
    ARDISCOVERY_Device_t *discoveryDevice; /**< the device to drive */
    ARDISCOVERY_NetworkConfiguration_t networkConfiguration; /**< the networkConfiguration of the device*/
    ARCONTROLLER_Network_t *networkController; /**< the networkController to used to send and receive  */
    ARSAL_Sem_t initSem; /**< semaphore used for the initialisation */
    ARSAL_Mutex_t mutex; /**< Mutex for multithreading */
    eARCONTROLLER_DEVICE_STATE state; /**< state of the deviceController*/
    ARSAL_Thread_t controllerLooperThread; /**< looper threads used to send data in loop */
    ARCONTROLLER_DICTIONARY_CALLBAK_LIST_ELEMENT_t *commandCallbacks; /**< Array storing callbacks to use when a command is received. */
    ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t *stateChangedCallbacks; /**< Array storing callbacks to use when a state is changed. */
    ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t *extensionStateChangedCallbacks; /**< Array storing callbacks to use when a state of the extension is changed. */
    int startCancelled; /**< 1 if the start is canceled*/
    //video part
    int hasVideo; /**< 0 if the device has not Video stream ; otherwide 1 */
    ARNETWORKAL_Stream_DidReceiveFrameCallback_t videoReceiveCallback;
    ARNETWORKAL_Stream_TimeoutFrameCallback_t videoTimeoutCallback;
    void *videoReceiveCustomData;
    //extension part
    eARCONTROLLER_DEVICE_STATE extensionState; /**< extension state of the deviceController*/
    char *extensionName;
    eARDISCOVERY_PRODUCT extensionProduct;
};

/**
 * @brief Start the Network.
 * @post ARCONTROLLER_Device_StopNetwork must be call to stop the device Controller before destroy it.
 * @warning This is a blocking function.
 * @param deviceController The device controller to start its network.
 * @return executing error.
 * @see ARCONTROLLER_Device_StopNetwork.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_StartNetwork (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Stop the Network.
 * @param deviceController The device controller to stop its network.
 * @return executing error.
 * @see ARCONTROLLER_Device_StartNetwork.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_StopNetwork (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Function called on start of the device.
 * @param deviceController The device controller on start.
 * @param[in] isExtensionDevice 1 if the device started is the extension device, 0 otherwise.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_OnStart (ARCONTROLLER_Device_t *deviceController, int isExtensionDevice);

/**
 * @brief Set the network controller of the device controller to its features.
 * @param deviceController The device controller.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_SetNetworkControllerToFeatures (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Register callback for each command received.
 * @param deviceController The device controller.
 * @param[in] specificFeature The feature to register. If null, register callbacks of all features.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_RegisterCallbacks (ARCONTROLLER_Device_t *deviceController, void* specificFeature);

/**
 * @brief Unregister callback for each command received.
 * @param deviceController The device controller.
 * @param[in] specificFeature The feature to unregister. If null, unregister callbacks of all features.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_UnregisterCallbacks (ARCONTROLLER_Device_t *deviceController, void* specificFeature);

/**
 * @brief Start the looper thread sending pcmd commands.
 * @param deviceController The device controller.
 * @return executing error.
 * @see ARCONTROLLER_Device_StopControllerLooperThread.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_StartControllerLooperThread (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Stop the looper thread sending pcmd commands.
 * @param deviceController The device controller.
 * @return executing error.
 * @see ARCONTROLLER_Device_StartControllerLooperThread.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_StopControllerLooperThread (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Run of the looper thread.
 * @param data The device controller.
 * @return NULL.
 * @see ARCONTROLLER_Device_StartControllerLooperThread.
 * @see ARCONTROLLER_Device_StopControllerLooperThread.
 */
void *ARCONTROLLER_Device_ControllerLooperThread (void *data);

/**
 * @brief Set the Initial Date for the device.
 * @param deviceController The device controller.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_SetInitialDate (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Get the Initial Settings of the device.
 * @param deviceController The device controller.
 * @param[in] onExtensionDevice 1 if the device started is the extension device, 0 otherwise.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_GetInitialSettings (ARCONTROLLER_Device_t *deviceController, int onExtensionDevice);

/**
 * @brief Get the Initial States of the device.
 * @param deviceController The device controller.
 * @param[in] onExtensionDevice 1 if the device started is the extension device, 0 otherwise.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_GetInitialStates (ARCONTROLLER_Device_t *deviceController, int onExtensionDevice);

/**
 * @brief Callback used when the settings or states of the device are changed.
 * @param deviceController The device controller.
 * @return executing error.
 */
void ARCONTROLLER_Device_DictionaryChangedCallback (eARCONTROLLER_DICTIONARY_KEY commandKey, ARCONTROLLER_DICTIONARY_ELEMENT_t *elementDictionary, void *customData); // TODO int -> ARCommands Big 

/**
 * @brief Function called when all initials states of the device are received.
 * @param deviceController The device controller.
 */
void ARCONTROLLER_Device_OnAllStatesEnd (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Function called when all initials settings of the device are received.
 * @param deviceController The device controller.
 */
void ARCONTROLLER_Device_OnAllSettingsEnd (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Function called when an extension connection to the SkyController has changed.
 * @param deviceController The device controller.
 */
void ARCONTROLLER_Device_OnSkyControllerConnectionChangedReceived (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Callback used to add a json part during the device connection.
 * @param jsonObj The json in which to add.
 * @param customData The device controller.
 */
eARDISCOVERY_ERROR ARCONTROLLER_Device_SendJsonCallback (json_object *jsonObj, void *customData);

/**
 * @brief Callback used to receive a json part during the device connection.
 * @param jsonObj The json in which to read.
 * @param customData The device controller.
 */
eARDISCOVERY_ERROR ARCONTROLLER_Device_ReceiveJsonCallback (json_object *jsonObj, void *customData);

/**
 * @brief Callback used when the Network Controller is Disconnected.
 * @param customData The device controller on diconnection.
 */
void ARCONTROLLER_Device_OnDisconnectCallback (void *customData);

/**
 * @brief Start thread run .
 * @param data The device controller on diconnection.
 * @return NULL.
 */
void *ARCONTROLLER_Device_StartRun (void *data);

/**
 * @brief Stop thread run .
 * @param data The device controller on diconnection.
 * @return NULL.
 */
void *ARCONTROLLER_Device_StopRun (void *data);

/**
 * @brief Start extension thread run .
 * @param data The device controller.
 * @return NULL.
 */
void *ARCONTROLLER_Device_ExtensionStartRun (void *data);

/**
 * @brief Stop extension thread run .
 * @param data The device controller.
 * @return NULL.
 */
void *ARCONTROLLER_Device_ExtensionStopRun (void *data);

/**
 * @brief Add a callback in a list.
 * @param callbackList The list of callbacks.
 * @param[in] callback The callback to add.
 * @param[in] customData Data given as parameter to the callback.
 * @return Executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_AddCallbackInList (ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t **callbackList, ARCONTROLLER_Device_StateChangedCallback_t callback, void *customData);

/**
 * @brief Remove a callback from a list.
 * @param callbackList The list of callbacks.
 * @param[in] callback The callback to remove.
 * @param[in] customData Data given at the adding of the callback.
 * @return Executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_RemoveCallbackFromList (ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t **callbackList, ARCONTROLLER_Device_StateChangedCallback_t callback, void *customData);

 /**
  * @brief Delete all callback of a list.
  * @param callbackList The list of callbacks.
  */
void ARCONTROLLER_Device_DeleteCallbackList (ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t **callbackList);

/**
 * @brief Notify all callback of a list.
 * @param callbackList The list of callbacks.
 * @param[in] state The state of the device Controller ; given as parameter to the callback.
 * @param[in] error Error causing this new state.
 */
void ARCONTROLLER_Device_NotifyAllCallbackInList (ARCONTROLLER_Device_STATE_CHANGED_CALLBACK_ELEMENT_t **callbackList, eARCONTROLLER_DEVICE_STATE state, eARCONTROLLER_ERROR error);

/**
 * @brief Add an extension callback in a list.
 * @param callbackList The list of extension callbacks.
 * @param[in] callback The callback to add.
 * @param[in] customData Data given as parameter to the callback.
 * @return Executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_AddExtensionCallbackInList (ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t **callbackList, ARCONTROLLER_Device_ExtensionStateChangedCallback_t callback, void *customData);

/**
 * @brief Remove an extension callback from a list.
 * @param callbackList The list of extension callbacks.
 * @param[in] callback The callback to remove.
 * @param[in] customData Data given at the adding of the callback.
 * @return Executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_RemoveExtensionCallbackFromList (ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t **callbackList, ARCONTROLLER_Device_ExtensionStateChangedCallback_t callback, void *customData);

 /**
  * @brief Delete all extension callbacks of a list.
  * @param callbackList The list of callbacks.
  */
void ARCONTROLLER_Device_DeleteExtensionCallbackList (ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t **callbackList);

/**
 * @brief Notify all extension callback of a list.
 * @param callbackList The list of callbacks.
 * @param[in] state The state of the extension device Controller ; given as parameter to the callback.
 * @param[in] product The product type of the extension ; given as parameter to the callback.
 * @param[in] name The name of the extension ; given as parameter to the callback.
 * @param[in] error Error causing this new state.
 */
void ARCONTROLLER_Device_NotifyAllExtensionCallbackInList (ARCONTROLLER_Device_EXTENSION_STATE_CHANGED_CALLBACK_ELEMENT_t **callbackList, eARCONTROLLER_DEVICE_STATE state, eARDISCOVERY_PRODUCT product, const char *name, eARCONTROLLER_ERROR error);

/**
 * @brief Set the Device Controller state and notify all listeners.
 * @param deviceController The device controller.
 * @param[in] state The new state to set.
 * @param[in] error Error causing this new state.
 */
void ARCONTROLLER_Device_SetState (ARCONTROLLER_Device_t *deviceController, eARCONTROLLER_DEVICE_STATE state, eARCONTROLLER_ERROR error);

/**
 * @brief Set the Device Controller extension state and notify all listeners.
 * @param deviceController The device controller.
 * @param[in] state The new extension state to set.
 * @param[in] error Error causing this new state.
 */
void ARCONTROLLER_Device_SetExtensionState (ARCONTROLLER_Device_t *deviceController, eARCONTROLLER_DEVICE_STATE state, eARCONTROLLER_ERROR error);

/**
 * @brief Delete the extension device.
 * @param deviceController The device controller.
 * @return Executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_DeleteExtension (ARCONTROLLER_Device_t *deviceController);

#endif /* _ARCONTROLLER_DEVICE_PRIVATE_H_ */

// END GENERATED CODE
