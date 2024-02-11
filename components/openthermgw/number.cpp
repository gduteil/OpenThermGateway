#include "number.h"
#include "esphome/core/log.h"
#include "OpenThermGateway.h"

static const char * TAG = "OpenThermGatewayNumber";

namespace esphome {
namespace OpenThermGateway {

void OpenThermGatewayNumber::setup() {
    this->publish_state(0);
}

} // namespace opentherm
} // namespace esphome
