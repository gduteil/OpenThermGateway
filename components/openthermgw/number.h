#pragma once

#include "esphome/components/number/number.h"
#include "input.h"

namespace esphome {
namespace OpenThermGateway {

class OpenThermGatewayNumber : public number::Number, public Component, public OpenThermGatewayInput {
protected:
    void setup() override;
    
    void control(float value) override {
        this->publish_state(value);
    }

public:
    void set_min_value(float min_value) override { this->traits.set_min_value(min_value); }
    void set_max_value(float max_value) override { this->traits.set_max_value(max_value); }
    void set_step(float step) override { this->traits.set_step(step); }
};

} // namespace OpenThermGateway
} // namespace esphome
