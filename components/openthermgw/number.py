from typing import Any, Dict

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import CONF_ID, CONF_UNIT_OF_MEASUREMENT

from . import const, schema, validate, input, generate

DEPENDENCIES = [ const.OPENTHERMGW ]
COMPONENT_TYPE = const.NUMBER

OpenThermGatewayNumber = generate.openthermgw_ns.class_("OpenThermGatewayNumber", number.Number, cg.Component, input.OpenThermGatewayInput)

async def new_openthermgwnumber(config: Dict[str, Any]) -> cg.Pvariable:
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await number.register_number(var, config, min_value = config[input.CONF_min_value], max_value = config[input.CONF_max_value], step = config[input.CONF_step])
    input.generate_setters(var, config)
    return var

def get_entity_validation_schema(entity: schema.InputSchema) -> cv.Schema:
    return number.NUMBER_SCHEMA \
        .extend({
            cv.GenerateID(): cv.declare_id(OpenThermGatewayNumber),
            cv.Optional(CONF_UNIT_OF_MEASUREMENT, entity["unit_of_measurement"]): cv.string_strict
        }) \
        .extend(input.input_schema(entity)) \
        .extend(cv.COMPONENT_SCHEMA)

CONFIG_SCHEMA = validate.create_component_schema(schema.INPUTS, get_entity_validation_schema)

async def to_code(config: Dict[str, Any]) -> None:
    keys = await generate.component_to_code(
        COMPONENT_TYPE,
        schema.INPUTS,
        OpenThermGatewayNumber, 
        generate.create_only_conf(new_openthermgwnumber), 
        config
    )
    generate.define_readers(COMPONENT_TYPE, keys)
    
