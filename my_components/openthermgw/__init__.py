from typing import Any, Dict

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor
from esphome.const import CONF_ID
from . import const, schema, validate, generate

AUTO_LOAD = [ "binary_sensor", "text_sensor", "sensor", "switch", "number", "output" ]
MULTI_CONF = True

openthermgw_ns = cg.esphome_ns.namespace("OpenThermGateway")
openthermgw = openthermgw_ns.class_("OpenThermGateway", cg.Component)

CONFIG_SCHEMA = cv.All(
    cv.Schema({
        cv.GenerateID(): cv.declare_id(generate.openthermgw),
        cv.Required("pin_thermostat_in"): pins.internal_gpio_input_pin_number,
        cv.Required("pin_thermostat_out"): pins.internal_gpio_input_pin_number,
        cv.Required("pin_boiler_in"): pins.internal_gpio_input_pin_number,
        cv.Required("pin_boiler_out"): pins.internal_gpio_input_pin_number,
        cv.Optional("ch_enable", True): cv.boolean,
        cv.Optional("dhw_enable", True): cv.boolean,
        cv.Optional("cooling_enable", False): cv.boolean,
        cv.Optional("otc_active", False): cv.boolean,
        cv.Optional("ch2_active", False): cv.boolean,
    }).extend(validate.create_entities_schema(schema.INPUTS, (lambda _: cv.use_id(sensor.Sensor))))
      .extend(cv.COMPONENT_SCHEMA),
    cv.only_with_arduino,
)

async def to_code(config: Dict[str, Any]) -> None:
    cg.add_global(openthermgw_ns.using)
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    input_sensors = []
    for key, value in config.items():
        if key != CONF_ID:
            if key in schema.INPUTS:
                sensor = await cg.get_variable(value)
                cg.add(getattr(var, f"set_{key}_{const.INPUT_SENSOR.lower()}")(sensor))
                input_sensors.append(key)
            else:
                cg.add(getattr(var, f"set_{key}")(value))

    if len(input_sensors) > 0:
        generate.define_has_component(const.INPUT_SENSOR, input_sensors)
        generate.define_message_handler(const.INPUT_SENSOR, input_sensors, schema.INPUTS)
        generate.define_readers(const.INPUT_SENSOR, input_sensors)
        generate.add_messages(var, input_sensors, schema.INPUTS)     
        
