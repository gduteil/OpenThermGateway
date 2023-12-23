#pragma once

#include "esphome.h"
#include "OpenTherm.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "switch.h"

// Ensure that all component macros are defined, even if the component is not used
#ifndef OPENTHERMGW_SENSOR_LIST
#define OPENTHERMGW_SENSOR_LIST(F, sep)
#endif
#ifndef OPENTHERMGW_BINARY_SENSOR_LIST
#define OPENTHERMGW_BINARY_SENSOR_LIST(F, sep)
#endif
#ifndef OPENTHERMGW_TEXT_SENSOR_LIST
#define OPENTHERMGW_TEXT_SENSOR_LIST(F, sep)
#endif
#ifndef OPENTHERMGW_SWITCH_LIST
#define OPENTHERMGW_SWITCH_LIST(F, sep)
#endif
#ifndef OPENTHERMGW_NUMBER_LIST
#define OPENTHERMGW_NUMBER_LIST(F, sep)
#endif
#ifndef OPENTHERMGW_OUTPUT_LIST
#define OPENTHERMGW_OUTPUT_LIST(F, sep)
#endif
#ifndef OPENTHERMGW_INPUT_SENSOR_LIST
#define OPENTHERMGW_INPUT_SENSOR_LIST(F, sep)
#endif

#ifndef OPENTHERMGW_SENSOR_MESSAGE_HANDLERS
#define OPENTHERMGW_SENSOR_MESSAGE_HANDLERS(MESSAGE, ENTITY, entity_sep, postscript, msg_sep)
#endif
#ifndef OPENTHERMGW_BINARY_SENSOR_MESSAGE_HANDLERS
#define OPENTHERMGW_BINARY_SENSOR_MESSAGE_HANDLERS(MESSAGE, ENTITY, entity_sep, postscript, msg_sep)
#endif
#ifndef OPENTHERMGW_TEXT_SENSOR_MESSAGE_HANDLERS
#define OPENTHERMGW_TEXT_SENSOR_MESSAGE_HANDLERS(MESSAGE, ENTITY, entity_sep, postscript, msg_sep)
#endif
#ifndef OPENTHERMGW_SWITCH_MESSAGE_HANDLERS
#define OPENTHERMGW_SWITCH_MESSAGE_HANDLERS(MESSAGE, ENTITY, entity_sep, postscript, msg_sep)
#endif
#ifndef OPENTHERMGW_NUMBER_MESSAGE_HANDLERS
#define OPENTHERMGW_NUMBER_MESSAGE_HANDLERS(MESSAGE, ENTITY, entity_sep, postscript, msg_sep)
#endif
#ifndef OPENTHERMGW_OUTPUT_MESSAGE_HANDLERS
#define OPENTHERMGW_OUTPUT_MESSAGE_HANDLERS(MESSAGE, ENTITY, entity_sep, postscript, msg_sep)
#endif
#ifndef OPENTHERMGW_INPUT_SENSOR_MESSAGE_HANDLERS
#define OPENTHERMGW_INPUT_SENSOR_MESSAGE_HANDLERS(MESSAGE, ENTITY, entity_sep, postscript, msg_sep)
#endif

namespace esphome {
    namespace OpenThermGateway {    
    	struct SAutoUpdateMessage
    	{
    		unsigned long msTimeUpdate=0;
    		unsigned long msTimeSinceLastUpdate=0;
    	};
    	
        class OpenThermGateway: public PollingComponent, public api::CustomAPIDevice {
        	public: 
			OpenThermGateway();
			virtual ~OpenThermGateway();
			
			void set_pin_thermostat_in(uint8_t pin) { m_pinThermostatIn=pin; }
			void set_pin_thermostat_out(uint8_t pin) { m_pinThermostatOut=pin; }
			void set_pin_boiler_in(uint8_t pin) { m_pinBoilerIn=pin; }
			void set_pin_boiler_out(uint8_t pin) { m_pinBoilerOut=pin; }
			
			void set_ch_enable(bool bCHEnable) { m_bCHEnable = bCHEnable; }
			void set_dhw_enable(bool bDHWEnable) { m_bDHWEnable = bDHWEnable; }
			void set_cooling_enable(bool bCoolingEnable) { m_bCoolingEnable = bCoolingEnable; }
			void set_otc_active(bool bOTCActive) { m_bOTCActive = bOTCActive; }
			void set_ch2_active(bool bCH2Active) { m_bCH2Active = bCH2Active; }
			
			void add_initial_message(OpenThermMessageID message_id);			
			void add_auto_update_message(OpenThermMessageID message_id, int32_t secUpdateTime);
			
			#define OPENTHERMGW_SET_SENSOR(entity) void set_ ## entity(sensor::Sensor* sensor) { this->entity = sensor; }
			OPENTHERMGW_SENSOR_LIST(OPENTHERMGW_SET_SENSOR, )

			#define OPENTHERMGW_SET_BINARY_SENSOR(entity) void set_ ## entity(binary_sensor::BinarySensor* binary_sensor) { this->entity = binary_sensor; }
			OPENTHERMGW_BINARY_SENSOR_LIST(OPENTHERMGW_SET_BINARY_SENSOR, )

			#define OPENTHERMGW_SET_TEXT_SENSOR(entity) void set_ ## entity(text_sensor::TextSensor* text_sensor) { this->entity = text_sensor; }
			OPENTHERMGW_TEXT_SENSOR_LIST(OPENTHERMGW_SET_TEXT_SENSOR, )

			#define OPENTHERMGW_SET_SWITCH(entity) void set_ ## entity(OpenThermGatewaySwitch* sw) { this->entity = sw; }
			OPENTHERMGW_SWITCH_LIST(OPENTHERMGW_SET_SWITCH, )

			#define OPENTHERMGW_SET_NUMBER(entity) void set_ ## entity(OpenthermNumber* number) { this->entity = number; }
			OPENTHERMGW_NUMBER_LIST(OPENTHERMGW_SET_NUMBER, )

			#define OPENTHERMGW_SET_OUTPUT(entity) void set_ ## entity(OpenthermOutput* output) { this->entity = output; }
			OPENTHERMGW_OUTPUT_LIST(OPENTHERMGW_SET_OUTPUT, )

			#define OPENTHERMGW_SET_INPUT_SENSOR(entity) void set_ ## entity(sensor::Sensor* sensor) { this->entity = sensor; }
			OPENTHERMGW_INPUT_SENSOR_LIST(OPENTHERMGW_SET_INPUT_SENSOR, )
			
			void setup() override;
			void on_shutdown() override;			
			void dump_config() override;
//			void control(const climate::ClimateCall & call) override;
//		 	climate::ClimateTraits traits() override;
			
			void loop() override;
			void update() override;
        	
			static void processRequestThermostat(unsigned long request, OpenThermResponseStatus status, void *pCallbackUser)
			{
				if(pCallbackUser!=NULL)
					((OpenThermGateway *)pCallbackUser)->processRequestThermostat(request, status);
			}

	        protected:

		private:
			uint8_t m_pinThermostatIn = 0;
			uint8_t m_pinThermostatOut = 0;
			uint8_t m_pinBoilerIn = 0;
			uint8_t m_pinBoilerOut = 0;
			    
			bool m_bCHEnable = true;
			bool m_bDHWEnable = true;
			bool m_bCoolingEnable = false;
			bool m_bOTCActive = false;
			bool m_bCH2Active = false;

			uint16_t m_dateYear = 0xFFFF;
			uint8_t m_dateMonth = 0xFF;
			uint8_t m_dateDay = 0xFF;
			uint8_t m_dateDOW = 0xFF;
			uint8_t m_dateHour = 0xFF;		
			uint8_t m_dateMinute = 0xFF;
			std::string m_strDate;
			
			unsigned long m_msLastLoop=0;
			unsigned long m_msTimeSinceLastAutoUpdate=0;
			
			// Use macros to create fields for every entity specified in the ESPHome configuration
			#define OPENTHERMGW_DECLARE_SENSOR(entity) sensor::Sensor* entity;
			OPENTHERMGW_SENSOR_LIST(OPENTHERMGW_DECLARE_SENSOR, )

			#define OPENTHERMGW_DECLARE_BINARY_SENSOR(entity) binary_sensor::BinarySensor* entity;
			OPENTHERMGW_BINARY_SENSOR_LIST(OPENTHERMGW_DECLARE_BINARY_SENSOR, )

			#define OPENTHERMGW_DECLARE_TEXT_SENSOR(entity) text_sensor::TextSensor* entity;
			OPENTHERMGW_TEXT_SENSOR_LIST(OPENTHERMGW_DECLARE_TEXT_SENSOR, )

			#define OPENTHERMGW_DECLARE_SWITCH(entity) OpenThermGatewaySwitch* entity;
			OPENTHERMGW_SWITCH_LIST(OPENTHERMGW_DECLARE_SWITCH, )

			#define OPENTHERMGW_DECLARE_NUMBER(entity) OpenthermNumber* entity;
			OPENTHERMGW_NUMBER_LIST(OPENTHERMGW_DECLARE_NUMBER, )

			#define OPENTHERMGW_DECLARE_OUTPUT(entity) OpenthermOutput* entity;
			OPENTHERMGW_OUTPUT_LIST(OPENTHERMGW_DECLARE_OUTPUT, )

			#define OPENTHERMGW_DECLARE_INPUT_SENSOR(entity) sensor::Sensor* entity;
			OPENTHERMGW_INPUT_SENSOR_LIST(OPENTHERMGW_DECLARE_INPUT_SENSOR, )
			    
			// The set of initial messages to send on starting communication with the boiler
			std::unordered_set<OpenThermMessageID> m_initial_messages;
			
			// Map with periodic messages
			std::unordered_map<OpenThermMessageID, SAutoUpdateMessage> m_map_auto_update_messages;
			
			bool m_bStatusReceived = false;
			bool m_bInitializing = true;
			
			std::unordered_set<OpenThermMessageID>::const_iterator m_current_message_iterator;
			std::unordered_map<OpenThermMessageID, SAutoUpdateMessage>::const_iterator m_auto_update_message_iterator;
			
    			static OpenTherm *m_otThermostat;
			static OpenTherm *m_otBoiler;
			
			static void IRAM_ATTR handleInterruptThermostat();
			static void IRAM_ATTR handleInterruptBoiler();

			unsigned int build_request(OpenThermMessageID request_id);
			
			void processRequestThermostat(unsigned long request, OpenThermResponseStatus status);		
			
			void parseRequest(OpenThermMessageType type, OpenThermMessageID dataID, uint16_t data);
			void parseResponse(OpenThermMessageType type, OpenThermMessageID dataID, uint16_t data);
			
			void publishDate();
        };

    } // namespace OpenThermGateway
} // namespace esphome
