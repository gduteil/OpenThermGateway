#include "switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace OpenThermGateway {
void OpenThermGatewaySwitch::write_state(bool state) {
}

void OpenThermGatewaySwitch::setup() {
    bool initial_state = false;
/*    switch (this->mode) {
        case OPENTHERM_SWITCH_RESTORE_DEFAULT_ON:
            initial_state = this->get_initial_state().value_or(true);
            break;
        case OPENTHERM_SWITCH_RESTORE_DEFAULT_OFF:
            initial_state = this->get_initial_state().value_or(false);
            break;
        case OPENTHERM_SWITCH_START_ON:
            initial_state = true;
            break;
        case OPENTHERM_SWITCH_START_OFF:
            initial_state = false;
            break;
    }*/

    this->write_state(initial_state);
}

} // namespace opentherm
} // namespace esphome
