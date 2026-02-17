/*
 * aws_iot_mqtt_client_interface.h
 *
 * AWS IoT MQTT Client Interface Header
 * Defines types, structures, and function prototypes for AWS IoT MQTT operations
 *
 * Created on: Mar 13, 2022
 *      Author: kjagu
 */

#ifndef MAIN_AWS_IOT_MQTT_CLIENT_INTERFACE_H_
#define MAIN_AWS_IOT_MQTT_CLIENT_INTERFACE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief MQTT Version types
 */
typedef enum {
    MQTT_3_1_1 = 4
} MQTTVersion_t;

/**
 * @brief Quality of Service levels
 */
typedef enum {
    QOS0 = 0,
    QOS1 = 1
} QoS_t;

/**
 * @brief AWS IoT Error codes
 */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    NETWORK_TCP_SOCKET_ERROR = -2,
    NETWORK_SSL_CONNECT_ERROR = -3,
    NETWORK_TIMEOUT_ERROR = -4,
    NETWORK_RECONNECTED = -5,
    NETWORK_ATTEMPTING_RECONNECT = -6,
    MQTT_REQUEST_TIMEOUT_ERROR = -7,
    MQTT_CONNECTION_ERROR = -8,
    MQTT_NOTHING_TO_READ = -9,
    MQTT_UNEXPECTED_CLIENT_STATE = -10,
    MQTT_INVALID_TLS_HANDSHAKE = -11
} IoT_Error_t;

/**
 * @brief MQTT Client states
 */
typedef enum {
    CLIENT_STATE_INVALID = 0,
    CLIENT_STATE_INITIALIZED = 1,
    CLIENT_STATE_CONNECTING = 2,
    CLIENT_STATE_CONNECTED = 3,
    CLIENT_STATE_DISCONNECTED = 4,
    CLIENT_STATE_DISCONNECTING = 5,
    CLIENT_STATE_PUBLISHING = 6,
    CLIENT_STATE_SUBSCRIBING = 7,
    CLIENT_STATE_UNSUBSCRIBING = 8
} IoT_Client_State_t;

/**
 * @brief AWS IoT Client structure
 * Forward declaration - actual implementation is hidden
 */
typedef struct AWS_IoT_Client AWS_IoT_Client;

/**
 * @brief MQTT publish message parameters
 */
typedef struct {
    QoS_t qos;
    void *payload;
    size_t payloadLen;
    bool isRetained;
} IoT_Publish_Message_Params;

/**
 * @brief MQTT message callback function type
 */
typedef void (*IoT_Callback_t)(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
                                IoT_Publish_Message_Params *params, void *pData);

/**
 * @brief MQTT disconnect callback function type
 */
typedef void (*IoT_Disconnect_Handler)(AWS_IoT_Client *pClient, void *data);

/**
 * @brief MQTT client initialization parameters
 */
typedef struct {
    char *pHostURL;
    uint16_t port;
    char *pRootCALocation;
    char *pDeviceCertLocation;
    char *pDevicePrivateKeyLocation;
    uint32_t mqttCommandTimeout_ms;
    uint32_t tlsHandshakeTimeout_ms;
    bool isSSLHostnameVerify;
    bool enableAutoReconnect;
    IoT_Disconnect_Handler disconnectHandler;
    void *disconnectHandlerData;
} IoT_Client_Init_Params;

/**
 * @brief MQTT client connection parameters
 */
typedef struct {
    char *pClientID;
    uint16_t clientIDLen;
    char *pUsername;
    uint16_t usernameLen;
    char *pPassword;
    uint16_t passwordLen;
    bool isCleanSession;
    MQTTVersion_t MQTTVersion;
    uint16_t keepAliveIntervalInSec;
    bool isWillMsgPresent;
    char *pWillTopicName;
    uint16_t willTopicNameLen;
    IoT_Publish_Message_Params willMessage;
} IoT_Client_Connect_Params;

/**
 * @brief Default initialization parameters for MQTT client
 * This is used to initialize the client with default values
 */
extern const IoT_Client_Init_Params iotClientInitParamsDefault;

/**
 * @brief Default connection parameters for MQTT client
 * This is used to connect with default values
 */
extern const IoT_Client_Connect_Params iotClientConnectParamsDefault;

/**
 * @brief Initialize the AWS IoT MQTT client
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @param pInitParams Pointer to initialization parameters
 * @return IoT_Error_t SUCCESS if initialization succeeds, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_init(AWS_IoT_Client *pClient, IoT_Client_Init_Params *pInitParams);

/**
 * @brief Connect to AWS IoT MQTT broker
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @param pConnectParams Pointer to connection parameters
 * @return IoT_Error_t SUCCESS if connection succeeds, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_connect(AWS_IoT_Client *pClient, IoT_Client_Connect_Params *pConnectParams);

/**
 * @brief Attempt to reconnect to AWS IoT MQTT broker
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @return IoT_Error_t SUCCESS if reconnect succeeds, NETWORK_RECONNECTED if reconnected, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_attempt_reconnect(AWS_IoT_Client *pClient);

/**
 * @brief Set auto reconnect status
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @param status true to enable auto reconnect, false to disable
 * @return IoT_Error_t SUCCESS if operation succeeds, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_autoreconnect_set_status(AWS_IoT_Client *pClient, bool status);

/**
 * @brief Subscribe to an MQTT topic
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @param pTopic Topic name to subscribe to
 * @param topicLen Length of the topic name
 * @param qos Quality of Service level for the subscription
 * @param pCallback Callback function to handle incoming messages
 * @param pCallbackData Additional data to pass to callback
 * @return IoT_Error_t SUCCESS if subscription succeeds, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_subscribe(AWS_IoT_Client *pClient, char *pTopic, uint16_t topicLen,
                                    QoS_t qos, IoT_Callback_t pCallback, void *pCallbackData);

/**
 * @brief Publish an MQTT message
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @param pTopic Topic name to publish to
 * @param topicLen Length of the topic name
 * @param pParams Pointer to publish message parameters
 * @return IoT_Error_t SUCCESS if publish succeeds, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_publish(AWS_IoT_Client *pClient, char *pTopic, uint16_t topicLen,
                                  IoT_Publish_Message_Params *pParams);

/**
 * @brief Yield to process incoming MQTT messages
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @param timeout_ms Timeout in milliseconds to wait for messages
 * @return IoT_Error_t SUCCESS if successful, NETWORK_ATTEMPTING_RECONNECT if reconnecting,
 *         NETWORK_RECONNECTED if reconnected, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_yield(AWS_IoT_Client *pClient, uint32_t timeout_ms);

/**
 * @brief Check if auto reconnect is enabled
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @return true if auto reconnect is enabled, false otherwise
 */
bool aws_iot_is_autoreconnect_enabled(AWS_IoT_Client *pClient);

/**
 * @brief Disconnect from AWS IoT MQTT broker
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @return IoT_Error_t SUCCESS if disconnection succeeds, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_disconnect(AWS_IoT_Client *pClient);

/**
 * @brief Unsubscribe from an MQTT topic
 *
 * @param pClient Pointer to the AWS IoT client structure
 * @param pTopic Topic name to unsubscribe from
 * @param topicLen Length of the topic name
 * @return IoT_Error_t SUCCESS if unsubscription succeeds, otherwise error code
 */
IoT_Error_t aws_iot_mqtt_unsubscribe(AWS_IoT_Client *pClient, char *pTopic, uint16_t topicLen);

#endif /* MAIN_AWS_IOT_MQTT_CLIENT_INTERFACE_H_ */
