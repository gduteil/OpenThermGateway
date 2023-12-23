import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, binary_sensor, switch, number
from esphome.automation import maybe_simple_id
from esphome import pins
from esphome.const import *
from esphome.const import CONF_ID, ENTITY_CATEGORY_CONFIG, CONF_NAME
from esphome.core import coroutine_with_priority

from . import const, schema, validate, generate

#CONF_OPENTHERM_ID = "opentherm_id"

opentherm_ns = cg.esphome_ns.namespace("OpenThermGateway")

OpenThermGW = opentherm_ns.class_("OpenThermGateway", cg.Component)

AUTO_LOAD = ['sensor', 'binary_sensor', 'switch']
MULTI_CONF = True

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(OpenThermGW),
        cv.Required("pin_thermostat_in"): pins.internal_gpio_input_pin_number,
        cv.Required("pin_thermostat_out"): pins.internal_gpio_input_pin_number,
        cv.Required("pin_boiler_in"): pins.internal_gpio_input_pin_number,
        cv.Required("pin_boiler_out"): pins.internal_gpio_input_pin_number,
        cv.Optional("ch_enable", True): cv.boolean,
        cv.Optional("dhw_enable", True): cv.boolean,
        cv.Optional("cooling_enable", False): cv.boolean,
        cv.Optional("otc_active", False): cv.boolean,
        cv.Optional("ch2_active", False): cv.boolean,
    }
).extend(cv.COMPONENT_SCHEMA)


@coroutine_with_priority(2.0)
async def to_code(config):
    cg.add_global(opentherm_ns.using)
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    for key, value in config.items():
        if key != CONF_ID:
            cg.add(getattr(var, f"set_{key}")(value))
            

def opentherm_component_schema():
    """Create a schema for a OpenTherm component.
    :return: The OpenTherm component schema, `extend` this in your config schema.
    """
    schema = {
        cv.GenerateID(CONF_OPENTHERMGW_ID): cv.use_id(OpenThermGW),
    }
    return cv.Schema(schema)
