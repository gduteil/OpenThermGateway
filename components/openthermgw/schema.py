# This file contains a schema for all supported sensors, binary sensors and
# inputs of the OpenThermGW component.

from typing import Dict, Generic, Tuple, TypeVar, TypedDict
from typing_extensions import NotRequired

from esphome.const import (
    UNIT_CELSIUS,
    UNIT_PERCENT,
    DEVICE_CLASS_COLD,
    DEVICE_CLASS_HEAT,
    DEVICE_CLASS_PRESSURE,
    DEVICE_CLASS_PROBLEM,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_EMPTY,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    STATE_CLASS_NONE,
    ENTITY_CATEGORY_CONFIG,
    ENTITY_CATEGORY_DIAGNOSTIC,
)

T = TypeVar("T")
class Schema(Generic[T], Dict[str, T]):
    pass

class EntitySchema(TypedDict):
    description: str
    """Description of the item, based on the OpenTherm spec"""

    message: str
    """OpenTherm message id used to read or write the value"""

    keep_updated: bool
    """Whether the value should be read or write repeatedly (True) or only during
    the initialization phase (False)
    """

    message_data: str
    """Instructions on how to interpret the data in the message
      - flag8_[hb|lb]_[0-7]: data is a byte of single bit flags, 
                             this flag is set in the high (hb) or low byte (lb),
                             at position 0 to 7
      - u8_[hb|lb]: data is an unsigned 8-bit integer, 
                    in the high (hb) or low byte (lb)
      - s8_[hb|lb]: data is an signed 8-bit integer, 
                    in the high (hb) or low byte (lb)
      - f88: data is a signed fixed point value with 
              1 sign bit, 7 integer bits, 8 fractional bits
      - u16: data is an unsigned 16-bit integer
      - s16: data is a signed 16-bit integer
    """

class SensorSchema(EntitySchema):
    unit_of_measurement: NotRequired[str]
    accuracy_decimals: int
    device_class: NotRequired[str]
    icon: NotRequired[str]
    state_class: str

SENSORS: Schema[SensorSchema] = Schema({
    "master_ot_version": SensorSchema({
        "description": "OpenTherm version Master",
        "device_class": DEVICE_CLASS_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,        
        "accuracy_decimals": 1,
	"icon": "mdi:tag",
        "state_class": STATE_CLASS_NONE,   
        "message": "OpenThermVersionMaster",
        "keep_updated": False,
        "message_data": "f88",
    }),
    "slave_ot_version": SensorSchema({
        "description": "OpenTherm version Slave",
        "device_class": DEVICE_CLASS_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,        
        "icon": "mdi:tag",
        "state_class": STATE_CLASS_NONE,
        "accuracy_decimals": 1,
        "message": "OpenThermVersionSlave",
        "keep_updated": False,
        "message_data": "f88",
    }),
    "t_room": SensorSchema({
        "description": "Room temperature",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 2,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "Tr",
        "keep_updated": True,
        "message_data": "f88",
    }),
    "t_boiler": SensorSchema({
        "description": "Boiler water temperature",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 2,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "Tboiler",
        "keep_updated": True,
        "message_data": "f88",
    }),
    "t_dhw": SensorSchema({
        "description": "DHW temperature",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 2,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "Tdhw",
        "keep_updated": True,
        "message_data": "f88",
    }),
    "t_outside": SensorSchema({
        "description": "Outside temperature",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 2,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "Toutside",
        "keep_updated": True,
        "message_data": "f88",
    }),
    "t_ret": SensorSchema({
        "description": "Return water temperature",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 2,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "Tret",
        "keep_updated": True,
        "message_data": "f88",
    }),    
    "t_dhw_set_ub": SensorSchema({
        "description": "Upper bound for adjustment of DHW setpoint",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "TdhwSetUBTdhwSetLB",
        "keep_updated": False,
        "message_data": "s8_hb",
    }),
    "t_dhw_set_lb": SensorSchema({
        "description": "Lower bound for adjustment of DHW setpoint",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "TdhwSetUBTdhwSetLB",
        "keep_updated": False,
        "message_data": "s8_lb",
    }),
    "max_t_set_ub": SensorSchema({
        "description": "Upper bound for adjustment of max CH setpoint",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "MaxTSetUBMaxTSetLB",
        "keep_updated": False,
        "message_data": "s8_hb",
    }),
    "max_t_set_lb": SensorSchema({
        "description": "Lower bound for adjustment of max CH setpoint",
        "unit_of_measurement": UNIT_CELSIUS,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_TEMPERATURE,
        "state_class": STATE_CLASS_MEASUREMENT,
        "message": "MaxTSetUBMaxTSetLB",
        "keep_updated": False,
        "message_data": "s8_lb",
    }),    
})

class BinarySensorSchema(EntitySchema):
    device_class: NotRequired[str]
    icon: NotRequired[str]
    entity_category: NotRequired[str]

BINARY_SENSORS: Schema = Schema({
    "fault_indication": BinarySensorSchema({
        "description": "Status: Fault indication",
        "device_class": DEVICE_CLASS_PROBLEM,
        "icon": "mdi:water-boiler-alert",
        "message": "Status",
        "keep_updated": True,
        "message_data": "flag8_lb_0",
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    }),
    "ch_active": BinarySensorSchema({
        "description": "Status: Central Heating active",
        "device_class": DEVICE_CLASS_HEAT,
        "icon": "mdi:radiator",
        "message": "Status",
        "keep_updated": True,
        "message_data": "flag8_lb_1",
    }),
    "dhw_active": BinarySensorSchema({
        "description": "Status: Domestic Hot Water active",
        "device_class": DEVICE_CLASS_HEAT,
        "icon": "mdi:faucet",
        "message": "Status",
        "keep_updated": True,
        "message_data": "flag8_lb_2",
    }),
    "flame_on": BinarySensorSchema({
        "description": "Status: Flame on",
        "device_class": DEVICE_CLASS_HEAT,
        "icon": "mdi:fire",
        "message": "Status",
        "keep_updated": True,
        "message_data": "flag8_lb_3",
    }),
    "cooling_active": BinarySensorSchema({
        "description": "Status: Cooling active",
        "device_class": DEVICE_CLASS_COLD,
        "message": "Status",
        "keep_updated": True,
        "message_data": "flag8_lb_4",
    }),
    "ch2_active": BinarySensorSchema({
        "description": "Status: Central Heating 2 active",
        "device_class": DEVICE_CLASS_HEAT,
        "icon": "mdi:radiator",
        "message": "Status",
        "keep_updated": True,
        "message_data": "flag8_lb_5",
    }),
    "diagnostic_indication": BinarySensorSchema({
        "description": "Status: Diagnostic event",
        "device_class": DEVICE_CLASS_PROBLEM,
        "message": "Status",
        "keep_updated": True,
        "message_data": "flag8_lb_6",
    }),
})

class TextSensorSchema(EntitySchema):
    device_class: NotRequired[str]
    icon: NotRequired[str]
    entity_category: NotRequired[str]

TEXT_SENSORS: Schema = Schema({
    "time_date": BinarySensorSchema({
        "description": "Time & Date",
        "device_class": DEVICE_CLASS_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
        "icon": "mdi:calendar-clock-outline",
        "message": "DayTime",
        "keep_updated": True,
        "message_data": "str_date",
    }),
})

class AutoConfigure(TypedDict):
    message: str
    message_data: str
    
class InputSchema(EntitySchema):
    unit_of_measurement: str
    range: Tuple[int, int]
    auto_max_value: NotRequired[AutoConfigure]
    auto_min_value: NotRequired[AutoConfigure]

INPUTS: Schema[InputSchema] = Schema({
    "t_set": InputSchema({
        "description": "Control setpoint: temperature setpoint for the boiler's supply water",
        "unit_of_measurement": UNIT_CELSIUS,
        "message": "TSet",
        "keep_updated": True,
        "message_data": "f88",
        "range": (0, 100),
        "auto_max_value": { "message": "MaxTSet", "message_data": "f88" },
    }),
    "t_set_ch2": InputSchema({
        "description": "Control setpoint 2: temperature setpoint for the boiler's supply water on the second heating circuit",
        "unit_of_measurement": UNIT_CELSIUS,
        "message": "TsetCH2",
        "keep_updated": True,
        "message_data": "f88",
        "range": (0, 100),
        "auto_max_value": { "message": "MaxTSet", "message_data": "f88" },
    }),
    "cooling_control": InputSchema({
        "description": "Cooling control signal",
        "unit_of_measurement": UNIT_PERCENT,
        "message": "CoolingControl",
        "keep_updated": True,
        "message_data": "f88",
        "range": (0, 100),
    }),
    "t_dhw_set": InputSchema({
        "description": "Domestic hot water temperature setpoint",
        "unit_of_measurement": UNIT_CELSIUS,
        "message": "TdhwSet",
        "keep_updated": True,
        "message_data": "f88",
        "range": (0, 127),
        "auto_min_value": { "message": "TdhwSetUBTdhwSetLB", "message_data": "s8_lb" },
        "auto_max_value": { "message": "TdhwSetUBTdhwSetLB", "message_data": "s8_hb" },
    }),
    "max_t_set": InputSchema({
        "description": "Maximum allowable CH water setpoint",
        "unit_of_measurement": UNIT_CELSIUS,
        "message": "MaxTSet",
        "keep_updated": True,
        "message_data": "f88",
        "range": (0, 127),
        "auto_min_value": { "message": "MaxTSetUBMaxTSetLB", "message_data": "s8_lb" },
        "auto_max_value": { "message": "MaxTSetUBMaxTSetLB", "message_data": "s8_hb" },
    }),
    "t_room_set": InputSchema({
        "description": "Current room temperature setpoint (informational)",
        "unit_of_measurement": UNIT_CELSIUS,
        "message": "TrSet",
        "keep_updated": True,
        "message_data": "f88",
        "range": (-40, 127),
    }),
    "t_room_set_ch2": InputSchema({
        "description": "Current room temperature setpoint on CH2 (informational)",
        "unit_of_measurement": UNIT_CELSIUS,
        "message": "TrSetCH2",
        "keep_updated": True,
        "message_data": "f88",
        "range": (-40, 127),
    }),
    "t_room": InputSchema({
        "description": "Current sensed room temperature (informational)",
        "unit_of_measurement": UNIT_CELSIUS,
        "message": "Tr",
        "keep_updated": True,
        "message_data": "f88",
        "range": (-40, 127),
    }),
})
