# OpenThermGateway

This is another ESPHome implementation for OpenThermGateway based on [@arthurrump's ESPHome OpenTherm](https://github.com/arthurrump/esphome-opentherm) and [@ihormelnyk's OpenTherm Library](https://github.com/ihormelnyk/opentherm_library)

Communication is stable, values will be requested from boiler at initialization, and updated periodically if the thermostat doesn't request them.
There is an override for room temperature setpoint, boiler should return it's target temperature but the thermostat will still show the previous temperature requested.

I'm using this hardware [DIYLESS OpenTherm Gateway](https://diyless.com/product/esp8266-opentherm-gateway) with a ESP32 (WROOM), but it should work with other hardwares.

My boiler is an Atlantic NAEMA 2 MICRO 25 with a Navilink 128 RADIO-CONNECT.

## Installation

- Clone this repo and copy my_components in your "config/esphome" folder
- Add the configuration in your YAML file (an example is in the repo)

## Configuration
After cloning you need to add the external_components section
```yaml
external_components:  
  - source:
      type: local
      path: my_components
```

### OTGW Configuration
Change the pins to match your hardware
```yaml
openthermgw:
  pin_thermostat_in: 17
  pin_thermostat_out: 18
  pin_boiler_in: 13
  pin_boiler_out: 27

  ch_enable: true
  dhw_enable: true
  cooling_enable: false
  otc_active: false
  ch2_active: false
```

### OTGW Temperature sensor
Change the pins and address to match your hardware (see https://esphome.io/components/sensor/dallas.html for information on getting the address)
```yaml
dallas:
  - pin: 16

sensor:
  # OTGW Temperature sensor
  - platform: dallas
    address: 0x7dc76a750e64ff28
    name: "T°C OTGW"
```

### OpenTherm binary sensors

Example for binary sensors
```yaml
binary_sensor:
  - platform: openthermgw
    flame_on:
      name: "Flame"
```

Available binary sensors are :
- fault_indication : Fault indication
- ch_active : Central Heating active
- dhw_active : Domestic Hot Water active
- flame_on : Flame on
- cooling_active : Cooling active
- ch2_active : Central Heating 2 active
- diagnostic_indication : Diagnostic event
- fault_service : Service required
- fault_lockout : Lockout reset enabled
- fault_waterpress : Water pressure fault
- fault_gasflame : Gas/flame fault
- fault_airpress : Air pressure fault
- fault_watertemp : Water over-temp fault
- fault_watertemp : Water over-temp fault
- func_manualoverridepriority : Remote override manual change priority
- func_programoverridepriority : Remote override program change priority

### OpenTherm sensors

Example for sensors
```yaml
sensor:
  - platform: openthermgw
    t_roomset:
      name: "Room setpoint"  
```

Available sensors are :
- fault_oem : OEM Fault code
- t_set : Temperature setpoint for the boiler's supply water
- tr_override : Remote override room setpoint
- t_set_ch2 : Temperature setpoint for the boiler's supply water on the second heating circuit
- t_set_dhw : Domestic hot water temperature setpoint (°C)
- diag_oem : An OEM-specific diagnostic/service code
- master_ot_version : OpenTherm version Master
- slave_ot_version : OpenTherm version Slave
- t_roomset : Current room temperature setpoint
- pc_relmod : Relative Modulation Level (%)
- bar_chpress : Water pressure in CH circuit (bar)
- ls_dhwflowrate : Water flow rate in DHW circuit. (litres/minute)
- t_room : Room temperature
- t_boiler : Boiler water temperature
- t_dhw : DHW temperature
- t_outside : Outside temperature
- t_ret : Return water temperature
- t_exhaust : Exhaust temperature
- t_dhw_set_ub : Upper bound for adjustment of DHW setpoint
- t_dhw_set_lb : Lower bound for adjustment of DHW setpoint
- max_t_set_ub : Upper bound for adjustment of max CH setpoint
- max_t_set_lb : Lower bound for adjustment of max CH setpoint
- max_t_set : Maximum allowable CH water setpoint (°C)
- nb_startburner : Number of starts burner
- nb_startchpump : Number of starts CH pump
- nb_startdhwpump : Number of starts DHW pump/valve
- nb_burnerhours : Number of hours that burner is in operation (i.e. flame on)
- nb_chpumphours : Number of hours that CH pump has been running
- nb_dhwpumphours : Number of hours that DHW pump has been running or DHW valve has been opened
- nb_dhwburnerhours : Number of hours that burner is in operation during DHW mode
- master_memberid : MemberID code of the master
- slave_memberid : MemberID code of the slave

### OpenTherm text sensors

Text sensors
```yaml
    time_date:
      name: "Date"
    dhw_present:
      name: "DHW Present"
      filters:
        - substitute:
          - "OFF -> Not present"
          - "ON -> Present"
    control_type:
      name: "Control type"
      filters:
        - substitute:
          - "OFF -> Modulating"
          - "ON -> On/Off"
    cooling_supported:
      name: "Cooling Supported"
      filters:
        - substitute:
          - "OFF -> No"
          - "ON -> Yes"
    dhw_config:
      name: "DHW Config"
      filters:
        - substitute:
          - "OFF -> Instantaneous"
          - "ON -> Storage tank"
    lowoff_pumpcontrol_allowed:
      name: "Pump Control"
      filters:
        - substitute:
          - "OFF -> Allowed"
          - "ON -> Not allowed"
    ch2_present:
      name: "CH2"
      filters:
        - substitute:
          - "OFF -> Not present"
          - "ON -> Present"
```

### OpenTherm switches

```yaml
switch:
  - platform: openthermgw
    ch_enable:
      name: "Heater"
    dhw_enable:
      name: "DHW"
    cooling_enable:
      name: "Cooling"
    otc_active:
      name: "OTC"
    ch2_active:
      name: "CH2"
```

### OpenTherm number

Number is used used for overrides, setting '0' will disable the override.

number:
  - platform: openthermgw
    t_roomset_override:
      name: "Temperature Override"


