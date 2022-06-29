#ifndef HelperClasses_HH
#define HelperClasses_HH

#include "mqtt/async_client.h"
#include <atomic>
#include <iostream>
#include <string>

class MqttCallback : public virtual mqtt::callback {
public:
  void connection_lost(const std::string &cause) override {
    std::cout << "\nConnection lost ... \n";
    if (!cause.empty())
      std::cout << "cause : " << cause << "\n";
  }
  void delivery_complete(mqtt::delivery_token_ptr tok) override {
    std::cout << "\tDelivery complete for token: "
              << (tok ? tok->get_message_id() : -1) << "\n";
  }
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A base action listener.
 */
class ActionListener : public virtual mqtt::iaction_listener {
protected:
  void on_failure(const mqtt::token &tok) override {
    std::cout << "\tListener failure for token: " << tok.get_message_id()
              << "\n";
  }
  void on_success(const mqtt::token &tok) override {
    std::cout << "\tListener success for token: " << tok.get_message_id()
              << "\n";
  }
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A derived action listener for publish events.
 */
class DeliveryActionListener : public ActionListener {
  std::atomic<bool> done;
  void on_failure(const mqtt::token &tok) override {
    ActionListener::on_failure(tok);
    done = true;
  }
  void on_success(const mqtt::token &tok) override {
    ActionListener::on_success(tok);
    done = true;
  }

public:
  DeliveryActionListener() : done(false) {}
  bool isDone() const { return done; }
};

#endif
