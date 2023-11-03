from typing import Any, Dict

import esphome.config_validation as cv
from esphome.components import text_sensor

from . import const, schema, validate, generate

DEPENDENCIES = [ const.OPENTHERMGW ]
COMPONENT_TYPE = const.TEXT_SENSOR

def get_entity_validation_schema(entity: schema.TextSensorSchema) -> cv.Schema:
    return text_sensor.text_sensor_schema(
#        device_class = entity["device_class"] if "device_class" in entity else text_sensor._UNDEF,
        icon = entity["icon"] if "icon" in entity else text_sensor._UNDEF,
        entity_category = entity["entity_category"] if "entity_category" in entity else text_sensor._UNDEF
    )

CONFIG_SCHEMA = validate.create_component_schema(schema.TEXT_SENSORS, get_entity_validation_schema)

async def to_code(config: Dict[str, Any]) -> None:
    await generate.component_to_code(
        COMPONENT_TYPE,
        schema.TEXT_SENSORS,
        text_sensor.TextSensor, 
        generate.create_only_conf(text_sensor.new_text_sensor), 
        config
    )
