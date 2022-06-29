#ifndef MQTTDataStreamer_HH
#define MQTTDataStreamer_HH

#include <chrono>
#include <cstdint>
#include <string>

#include "HelperClasses.hh"
#include "mqtt/async_client.h"

class MQTTDataStreamer {
  std::string addr;      // server Universal Resource Indicator(URI)
  std::string client_id; // unique ID for the client
  std::string topic; // string representing the MQTT topic over which the images
                     // are sent
  uint8_t QoS; // Quality of Service parameter. It can take values 0, 1 and 2
  bool retain_msg; // checks if the message should be retained.
  std::chrono::seconds timeout;
  std::unique_ptr<mqtt::async_client> mqtt_async_client;
  mqtt::message_ptr createMessage(const unsigned char *payload,
                                  std::size_t len);
  mqtt::connect_options buildConnectOptions();

public:
  MQTTDataStreamer() = delete;
  MQTTDataStreamer(std::string addr_, std::string client_id_,
                    std::string topic_, uint8_t QoS_ = 2,
                    bool retain_msg_ = false,
                    std::chrono::seconds timeout_ = std::chrono::seconds(10));
  ~MQTTDataStreamer();
  void
  publishMessage(const unsigned char *payload, std::size_t len,
                 DeliveryActionListener listener = DeliveryActionListener());
};

#endif
