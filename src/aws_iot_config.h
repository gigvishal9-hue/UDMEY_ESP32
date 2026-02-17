/*
 * aws_iot_config.h
 *
 * AWS IoT MQTT Configuration Header
 *
 * Created on: Oct 17, 2021
 *      Author: kjagu
 */

#ifndef MAIN_AWS_IOT_CONFIG_H_
#define MAIN_AWS_IOT_CONFIG_H_

/**
 * @brief AWS IoT MQTT Broker Host URL
 *
 * Replace this with your AWS IoT Core endpoint.
 * Format: https://your-endpoint.iot.your-region.amazonaws.com
 * Or just the hostname: your-endpoint.iot.your-region.amazonaws.com
 */
#define AWS_IOT_MQTT_HOST               "your-endpoint.iot.us-east-1.amazonaws.com"

/**
 * @brief AWS IoT MQTT Port
 *
 * Default port for MQTT over TLS is 8883
 */
#define AWS_IOT_MQTT_PORT              8883

/**
 * @brief AWS IoT MQTT Minimum Reconnect Wait Interval (in milliseconds)
 *
 * Minimum time to wait before attempting to reconnect to the MQTT broker
 */
#define AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL     1000

/**
 * @brief AWS IoT MQTT Maximum Reconnect Wait Interval (in milliseconds)
 *
 * Maximum time to wait before attempting to reconnect to the MQTT broker
 * This is used in exponential backoff algorithm
 */
#define AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL     128000

#endif /* MAIN_AWS_IOT_CONFIG_H_ */
