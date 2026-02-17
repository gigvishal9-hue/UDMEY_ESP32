/*
 * aws_iot_log.h
 *
 * AWS IoT Logging Header
 * Provides logging macros compatible with AWS IoT SDK
 * 
 * Created on: Mar 13, 2022
 *      Author: kjagu
 */

#ifndef MAIN_AWS_IOT_LOG_H_
#define MAIN_AWS_IOT_LOG_H_

#include "esp_log.h"

/**
 * @brief AWS IoT Log Tag
 * 
 * Tag used for AWS IoT related log messages
 */
#define AWS_IOT_LOG_TAG "aws_iot"

/**
 * @brief AWS IoT Error Log Macro
 * 
 * Logs error level messages for AWS IoT operations
 */
#define IOT_ERROR(...) ESP_LOGE(AWS_IOT_LOG_TAG, __VA_ARGS__)

/**
 * @brief AWS IoT Warning Log Macro
 * 
 * Logs warning level messages for AWS IoT operations
 */
#define IOT_WARN(...) ESP_LOGW(AWS_IOT_LOG_TAG, __VA_ARGS__)

/**
 * @brief AWS IoT Info Log Macro
 * 
 * Logs info level messages for AWS IoT operations
 */
#define IOT_INFO(...) ESP_LOGI(AWS_IOT_LOG_TAG, __VA_ARGS__)

/**
 * @brief AWS IoT Debug Log Macro
 * 
 * Logs debug level messages for AWS IoT operations
 */
#define IOT_DEBUG(...) ESP_LOGD(AWS_IOT_LOG_TAG, __VA_ARGS__)

/**
 * @brief AWS IoT Verbose Log Macro
 * 
 * Logs verbose level messages for AWS IoT operations
 */
#define IOT_VERBOSE(...) ESP_LOGV(AWS_IOT_LOG_TAG, __VA_ARGS__)

/**
 * @brief AWS IoT Connection Status Log
 * 
 * Helper macro for logging connection status
 */
#define IOT_LOG_CONN_STATUS(status) \
    do { \
        if (status == SUCCESS) { \
            IOT_INFO("Connection status: SUCCESS"); \
        } else if (status == FAILURE) { \
            IOT_ERROR("Connection status: FAILURE"); \
        } else { \
            IOT_WARN("Connection status: %d", status); \
        } \
    } while(0)

/**
 * @brief AWS IoT MQTT Error String Helper
 * 
 * Converts MQTT error codes to human-readable strings
 */
#define IOT_MQTT_ERROR_STRING(err) \
    ((err) == SUCCESS ? "SUCCESS" : \
    (err) == FAILURE ? "FAILURE" : \
    (err) == NETWORK_TCP_SOCKET_ERROR ? "NETWORK_TCP_SOCKET_ERROR" : \
    (err) == NETWORK_SSL_CONNECT_ERROR ? "NETWORK_SSL_CONNECT_ERROR" : \
    (err) == NETWORK_TIMEOUT_ERROR ? "NETWORK_TIMEOUT_ERROR" : \
    (err) == NETWORK_RECONNECTED ? "NETWORK_RECONNECTED" : \
    (err) == NETWORK_ATTEMPTING_RECONNECT ? "NETWORK_ATTEMPTING_RECONNECT" : \
    (err) == MQTT_REQUEST_TIMEOUT_ERROR ? "MQTT_REQUEST_TIMEOUT_ERROR" : \
    (err) == MQTT_CONNECTION_ERROR ? "MQTT_CONNECTION_ERROR" : \
    (err) == MQTT_NOTHING_TO_READ ? "MQTT_NOTHING_TO_READ" : \
    (err) == MQTT_UNEXPECTED_CLIENT_STATE ? "MQTT_UNEXPECTED_CLIENT_STATE" : \
    (err) == MQTT_INVALID_TLS_HANDSHAKE ? "MQTT_INVALID_TLS_HANDSHAKE" : \
    "UNKNOWN_ERROR")

/**
 * @brief AWS IoT Publish Log Helper
 * 
 * Logs publish operation details
 */
#define IOT_LOG_PUBLISH(topic, qos, payload_len) \
    IOT_INFO("Publishing to topic: %s, QoS: %d, Payload Length: %d", \
             topic, qos, payload_len)

/**
 * @brief AWS IoT Subscribe Log Helper
 * 
 * Logs subscribe operation details
 */
#define IOT_LOG_SUBSCRIBE(topic, qos) \
    IOT_INFO("Subscribing to topic: %s, QoS: %d", topic, qos)

/**
 * @brief AWS IoT Message Received Log Helper
 * 
 * Logs received message details
 */
#define IOT_LOG_MESSAGE_RECEIVED(topic, payload, payload_len) \
    IOT_INFO("Message received on topic: %.*s, Payload: %.*s", \
             strlen(topic), topic, payload_len, payload)

#endif /* MAIN_AWS_IOT_LOG_H_ */
