# OpenThermGateway

This is another ESPHome implementation for OpenThermGateway based on [@arthurrump's ESPHome OpenTherm](https://github.com/arthurrump/esphome-opentherm) and [@ihormelnyk's OpenTherm Library](https://github.com/ihormelnyk/opentherm_library)

Communication starts to work, nevertheless some invalid values are sometimes received (every few hours), fix is in progress.

I'm using this hardware [DIYLESS OpenTherm Gateway](https://diyless.com/product/esp8266-opentherm-gateway) with a NodeMCU, but it should work with other hardwares.

My boiler is an Atlantic NAEMA 2 MICRO 25 with a Navilink 128 RADIO-CONNECT.

## Installation

- Clone this repo and copy my_components in your "config/esphome" folder
- Add the configuration in your YAML file (an example is in the repo)

## Configuration

### OTGW Configuration
Change the pins to match your hardware
```yaml
openthermgw:
  pin_thermostat_in: 12
  pin_thermostat_out: 13
  pin_boiler_in: 4
  pin_boiler_out: 5

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
  - pin: 14

sensor:
  # OTGW Temperature sensor
  - platform: dallas
    address: 0x7dc76a750e64ff28
    name: "T°C OTGW"
```

### OpenTherm binary sensors
```yaml
binary_sensor:
  - platform: openthermgw
    fault_indication:
      name: "Erreur Chaudière"
    ch_active:
      name: "Chauffage"
    dhw_active:
      name: "Eau Chaude"
    flame_on:
      name: "Flame"
```

### OpenTherm Informations and Sensors
```yaml
text_sensor:
  # OpenTherm Date
  - platform: openthermgw
    time_date:
      name: "Date"
sensor:
  - platform: openthermgw
  # OpenTherm Informations
    master_ot_version:
      name: "Version OT Master"
    slave_ot_version:
      name: "Version OT Slave"

  # OpenTherm Sensors
    t_room:
      name: "T° Thermostat"
    t_boiler:
      name: "T° Chaudière"
    t_dhw:
      name: "T° Eau"
    t_outside:
      name: "T° Extérieure"
    t_ret:
      name: "T° Eau Retour"

    t_dhw_set_ub:
      name: "T° Ajustement Eau Sup."
    t_dhw_set_lb:
      name: "T° Ajustement Eau Inf."
    max_t_set_ub:
      name: "T° Ajustement Chaudière Sup."
    max_t_set_lb:
      name: "T° Ajustement Chaudière Inf."
```
