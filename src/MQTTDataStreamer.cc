#include "HelperClasses.hh"
#include "MQTTDatatStreamer.hh"

MQTTDatatStreamer::MQTTDatatStreamer(std::string addr_, std::string client_id_,
                                     std::string topic_, uint8_t QoS_,
                                     bool retain_msg_,
                                     std::chrono::seconds timeout_)
    : addr(addr_), client_id(client_id_), topic(topic_), QoS(QoS_),
      retain_msg(retain_msg_), timeout(timeout_) {
  mqtt_async_client = std::make_unique<mqtt::async_client>(addr, client_id);

  MqttCallback cb;
  mqtt_async_client->set_callback(cb);

  mqtt::connect_options connection_options = buildConnectOptions();
  try {
    std::cout << "Connecting ... ";
    mqtt_async_client->connect(connection_options)->wait();
    std::cout << "OK!\n";
  } catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << "\n";
  }
}

MQTTDatatStreamer::~MQTTDatatStreamer() {
  try {
    std::cout << "Disconnecting ... ";
    mqtt_async_client->disconnect()->wait();
    std::cout << "OK!\n";
  } catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << "\n";
  }
}

mqtt::connect_options MQTTDatatStreamer::buildConnectOptions() {
  mqtt::connect_options opt;
  opt.set_clean_session(true);
  opt.set_keep_alive_interval(std::chrono::seconds(10));
  std::string lwt_payload = "SOMETHING_WENT_WRONG";
  opt.set_will(mqtt::message(topic, lwt_payload, QoS, false));
  return (opt);
}

mqtt::message_ptr MQTTDatatStreamer::createMessage(const unsigned char *payload,
                                                   std::size_t len) {
  mqtt::message_ptr msg = mqtt::make_message(
      topic, reinterpret_cast<const void *>(payload), len, QoS, retain_msg);
  return (msg);
}

void MQTTDatatStreamer::publishMessage(const unsigned char *payload,
                                       std::size_t len,
                                       DeliveryActionListener listener) {
  mqtt::message_ptr msg = createMessage(payload, len);
  // I am not using PERSISTANCE property of MQTT. This can be added
  // if there need be.
  try {
    std::cout << "Sending Image ... ";
    mqtt::delivery_token_ptr publish_tok =
        mqtt_async_client->publish(msg, nullptr, listener);
    while (!listener.isDone())
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "OK!\n";

  } catch (const mqtt::exception &exc) {
    std::cerr << exc.what() << "\n";
  }
}
