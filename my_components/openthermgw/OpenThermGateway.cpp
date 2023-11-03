#include "OpenThermGateway.h"
#include "esphome/core/log.h"

namespace message_data {
    bool parse_flag8_lb_0(const unsigned long response) { return response & 0b0000000000000001; }
    bool parse_flag8_lb_1(const unsigned long response) { return response & 0b0000000000000010; }
    bool parse_flag8_lb_2(const unsigned long response) { return response & 0b0000000000000100; }
    bool parse_flag8_lb_3(const unsigned long response) { return response & 0b0000000000001000; }
    bool parse_flag8_lb_4(const unsigned long response) { return response & 0b0000000000010000; }
    bool parse_flag8_lb_5(const unsigned long response) { return response & 0b0000000000100000; }
    bool parse_flag8_lb_6(const unsigned long response) { return response & 0b0000000001000000; }
    bool parse_flag8_lb_7(const unsigned long response) { return response & 0b0000000010000000; }
    bool parse_flag8_hb_0(const unsigned long response) { return response & 0b0000000100000000; }
    bool parse_flag8_hb_1(const unsigned long response) { return response & 0b0000001000000000; }
    bool parse_flag8_hb_2(const unsigned long response) { return response & 0b0000010000000000; }
    bool parse_flag8_hb_3(const unsigned long response) { return response & 0b0000100000000000; }
    bool parse_flag8_hb_4(const unsigned long response) { return response & 0b0001000000000000; }
    bool parse_flag8_hb_5(const unsigned long response) { return response & 0b0010000000000000; }
    bool parse_flag8_hb_6(const unsigned long response) { return response & 0b0100000000000000; }
    bool parse_flag8_hb_7(const unsigned long response) { return response & 0b1000000000000000; }
    uint8_t parse_u8_lb(const unsigned long response) { return (uint8_t) (response & 0xff); }
    uint8_t parse_u8_hb(const unsigned long response) { return (uint8_t) ((response >> 8) & 0xff); }
    int8_t parse_s8_lb(const unsigned long response) { return (int8_t) (response & 0xff); }
    int8_t parse_s8_hb(const unsigned long response) { return (int8_t) ((response >> 8) & 0xff); }
    uint16_t parse_u16(const unsigned long response) { return (uint16_t) (response & 0xffff); }
    int16_t parse_s16(const unsigned long response) { return (int16_t) (response & 0xffff); }
    float parse_f88(const unsigned long response) {
        unsigned int data = response & 0xffff;
        return (data & 0x8000) ? -(0x10000L - data) / 256.0f : data / 256.0f; 
    }

    std::string parse_str_date(const unsigned long response) { return "00:00 00/00/0000"; }

    unsigned int write_flag8_lb_0(const bool value, const unsigned int data) { return value ? data | 0b0000000000000001 : data & 0b1111111111111110; }
    unsigned int write_flag8_lb_1(const bool value, const unsigned int data) { return value ? data | 0b0000000000000010 : data & 0b1111111111111101; }
    unsigned int write_flag8_lb_2(const bool value, const unsigned int data) { return value ? data | 0b0000000000000100 : data & 0b1111111111111011; }
    unsigned int write_flag8_lb_3(const bool value, const unsigned int data) { return value ? data | 0b0000000000001000 : data & 0b1111111111110111; }
    unsigned int write_flag8_lb_4(const bool value, const unsigned int data) { return value ? data | 0b0000000000010000 : data & 0b1111111111101111; }
    unsigned int write_flag8_lb_5(const bool value, const unsigned int data) { return value ? data | 0b0000000000100000 : data & 0b1111111111011111; }
    unsigned int write_flag8_lb_6(const bool value, const unsigned int data) { return value ? data | 0b0000000001000000 : data & 0b1111111110111111; }
    unsigned int write_flag8_lb_7(const bool value, const unsigned int data) { return value ? data | 0b0000000010000000 : data & 0b1111111101111111; }
    unsigned int write_flag8_hb_0(const bool value, const unsigned int data) { return value ? data | 0b0000000100000000 : data & 0b1111111011111111; }
    unsigned int write_flag8_hb_1(const bool value, const unsigned int data) { return value ? data | 0b0000001000000000 : data & 0b1111110111111111; }
    unsigned int write_flag8_hb_2(const bool value, const unsigned int data) { return value ? data | 0b0000010000000000 : data & 0b1111101111111111; }
    unsigned int write_flag8_hb_3(const bool value, const unsigned int data) { return value ? data | 0b0000100000000000 : data & 0b1111011111111111; }
    unsigned int write_flag8_hb_4(const bool value, const unsigned int data) { return value ? data | 0b0001000000000000 : data & 0b1110111111111111; }
    unsigned int write_flag8_hb_5(const bool value, const unsigned int data) { return value ? data | 0b0010000000000000 : data & 0b1101111111111111; }
    unsigned int write_flag8_hb_6(const bool value, const unsigned int data) { return value ? data | 0b0100000000000000 : data & 0b1011111111111111; }
    unsigned int write_flag8_hb_7(const bool value, const unsigned int data) { return value ? data | 0b1000000000000000 : data & 0b0111111111111111; }
    unsigned int write_u8_lb(const uint8_t value, const unsigned int data) { return (data & 0xff00) | value; }
    unsigned int write_u8_hb(const uint8_t value, const unsigned int data) { return (data & 0x00ff) | (value << 8); }
    unsigned int write_s8_lb(const int8_t value, const unsigned int data) { return (data & 0xff00) | value; }
    unsigned int write_s8_hb(const int8_t value, const unsigned int data) { return (data & 0x00ff) | (value << 8); }
    unsigned int write_u16(const uint16_t value, const unsigned int data) { return value; }
    unsigned int write_s16(const int16_t value, const unsigned int data) { return value; }
    unsigned int write_f88(const float value, const unsigned int data) { return (unsigned int) (value * 256.0f); }    
    
    unsigned int write_str_date(const std::string value, const unsigned int data) { return 0; }
} // namespace message_data

#define OPENTHERMGW_IGNORE_1(x)
#define OPENTHERMGW_IGNORE_2(x, y)

namespace esphome {
    namespace OpenThermGateway {

        static const char * TAG = "OpenThermGateway";
	OpenTherm *OpenThermGateway::m_otThermostat=NULL;
	OpenTherm *OpenThermGateway::m_otBoiler=NULL;

        OpenThermGateway::OpenThermGateway() : PollingComponent(10000)
	{
	}

        OpenThermGateway::~OpenThermGateway()
	{
		if(m_otThermostat!=NULL)
		{
			delete m_otThermostat;
			m_otThermostat=NULL;
		}
		
		if(m_otThermostat!=NULL)
		{
			delete m_otBoiler;
			m_otBoiler=NULL;
		}		
	}

	void OpenThermGateway::dump_config() 
	{
		#define ID(x) x
		#define SHOW2(x) #x
		#define SHOW(x) SHOW2(x)
	
		ESP_LOGCONFIG(TAG, "OpenTherm:");
		ESP_LOGCONFIG(TAG, "  Thermostat In: GPIO%d", m_pinThermostatIn);
		ESP_LOGCONFIG(TAG, "  Thermostat Out: GPIO%d", m_pinThermostatOut);
		ESP_LOGCONFIG(TAG, "  Boiler In: GPIO%d", m_pinBoilerIn);
		ESP_LOGCONFIG(TAG, "  Boiler Out: GPIO%d", m_pinBoilerOut);
		ESP_LOGCONFIG(TAG, "  Sensors: %s", SHOW(OPENTHERMGW_SENSOR_LIST(ID, )));
		ESP_LOGCONFIG(TAG, "  Binary sensors: %s", SHOW(OPENTHERMGW_BINARY_SENSOR_LIST(ID, )));
		ESP_LOGCONFIG(TAG, "  Text sensors: %s", SHOW(OPENTHERMGW_TEXT_SENSOR_LIST(ID, )));
		ESP_LOGCONFIG(TAG, "  Switches: %s", SHOW(OPENTHERMGW_SWITCH_LIST(ID, )));
		ESP_LOGCONFIG(TAG, "  Input sensors: %s", SHOW(OPENTHERMGW_INPUT_SENSOR_LIST(ID, )));
		ESP_LOGCONFIG(TAG, "  Outputs: %s", SHOW(OPENTHERMGW_OUTPUT_LIST(ID, )));
		ESP_LOGCONFIG(TAG, "  Numbers: %s", SHOW(OPENTHERMGW_NUMBER_LIST(ID, )));
	}

        void OpenThermGateway::setup() 
        {
	        m_otThermostat=new OpenTherm(m_pinThermostatIn, m_pinThermostatOut, true);
	        m_otThermostat->begin(handleInterruptThermostat, processRequestThermostat, this);

	        m_otBoiler=new OpenTherm(m_pinBoilerIn, m_pinBoilerOut);
	        m_otBoiler->begin(handleInterruptBoiler);
        }

	void IRAM_ATTR OpenThermGateway::handleInterruptThermostat()
	{
		if(m_otThermostat!=NULL)
			m_otThermostat->handleInterrupt();
	}

	void IRAM_ATTR OpenThermGateway::handleInterruptBoiler()
	{
		if(m_otBoiler!=NULL)
			m_otBoiler->handleInterrupt();
	}

	void OpenThermGateway::processRequestThermostat(unsigned long request, OpenThermResponseStatus status)
	{
		if(status==OpenThermResponseStatus::SUCCESS)
		{
			OpenThermMessageType requestType=m_otThermostat->getMessageType(request);
			OpenThermMessageID requestDataID=m_otThermostat->getDataID(request);
			uint16_t requestData=(uint16_t)request;
			
		        //ESP_LOGD(TAG, "Thermostat request (%08X) : MessageType: %s, DataID: %d, Data: %x (%s)", request, m_otThermostat->messageTypeToString(requestType), requestDataID, requestData, m_otThermostat->statusToString(status));	
			parseRequest(requestType, requestDataID, requestData);
			if(m_otBoiler!=NULL)
			{
				unsigned long response = m_otBoiler->sendRequest(request);
				if (response!=0) 
				{		
					OpenThermMessageType responseType=m_otThermostat->getMessageType(response);
					OpenThermMessageID responseDataID=m_otThermostat->getDataID(response);
					uint16_t responseData=(uint16_t)response;
						
					//ESP_LOGD(TAG, "Boiler response (%08X) : MessageType: %s, DataID: %d, Data: %x] (%s)", response, m_otBoiler->messageTypeToString(responseType), responseDataID, responseData, m_otBoiler->statusToString(status));					
					m_otThermostat->sendResponse(response);
					parseResponse(responseType, responseDataID, responseData);
				}
			}
		}
	}

	void OpenThermGateway::parseRequest(OpenThermMessageType type, OpenThermMessageID dataID, uint16_t data)
	{
	}

	void OpenThermGateway::parseResponse(OpenThermMessageType type, OpenThermMessageID dataID, uint16_t data)
	{
		bool bHandled=false;
		
		// Special messages
		switch(dataID)
		{
			case OpenThermMessageID::DayTime:
				m_dateDOW=(data>>13)&0x03;
				m_dateHour=(uint8_t)data;
				m_dateMinute=(data>>8)&0x1F;
				publishDate();
				bHandled=true;
				break;

			case OpenThermMessageID::Date:
				m_dateMonth=data>>8;
				m_dateDay=(uint8_t)data;
				publishDate();
				bHandled=true;
				break;

			case OpenThermMessageID::Year:
				m_dateYear=data;
				bHandled=true;
				publishDate();
				break;
				
			default:
				break;
		}
		
		
		if(!bHandled)
		{
			// Define the handler helpers to publish the results to all sensors
			#define OPENTHERMGW_MESSAGE_RESPONSE_MESSAGE(msg) \
				case OpenThermMessageID::msg: \
				    ESP_LOGD(TAG, "Received %s response", #msg); \
				    bHandled=true;
			#define OPENTHERMGW_MESSAGE_RESPONSE_ENTITY(key, msg_data) \
			    	this->key->publish_state(message_data::parse_ ## msg_data(data));
			#define OPENTHERMGW_MESSAGE_RESPONSE_POSTSCRIPT \
			    	break;

			// Then use those to create a switch statement for each thing we would want
			// to report. We use a separate switch statement for each type, because some
			// messages include results for multiple types, like flags and a number.
			switch (dataID) 
			{
				OPENTHERMGW_SENSOR_MESSAGE_HANDLERS(OPENTHERMGW_MESSAGE_RESPONSE_MESSAGE, OPENTHERMGW_MESSAGE_RESPONSE_ENTITY, , OPENTHERMGW_MESSAGE_RESPONSE_POSTSCRIPT, )			
				default: break;
			}
			
			switch (dataID) 
			{
				OPENTHERMGW_BINARY_SENSOR_MESSAGE_HANDLERS(OPENTHERMGW_MESSAGE_RESPONSE_MESSAGE, OPENTHERMGW_MESSAGE_RESPONSE_ENTITY, , OPENTHERMGW_MESSAGE_RESPONSE_POSTSCRIPT, )
				default: break;
			}

			switch (dataID) 
			{
				OPENTHERMGW_TEXT_SENSOR_MESSAGE_HANDLERS(OPENTHERMGW_MESSAGE_RESPONSE_MESSAGE, OPENTHERMGW_MESSAGE_RESPONSE_ENTITY, , OPENTHERMGW_MESSAGE_RESPONSE_POSTSCRIPT, )
				default: break;
			}
		}
		if(!bHandled)		
			ESP_LOGD(TAG, "Unhandled response [MessageType: %s, DataID: %d, Data: %x]", m_otBoiler->messageTypeToString(type), dataID, data);
	}
	
	void OpenThermGateway::publishDate()
	{
		if(m_dateMinute==0 || m_dateHour==0 || m_dateDay==0 || m_dateMonth==0 || m_dateYear==0)
			return;
			
		char szDate[64];
		snprintf(szDate, sizeof(szDate), "%02d:%02d %02d/%02d/%04d", m_dateMinute, m_dateHour, m_dateDay, m_dateMonth, m_dateYear);
		if(m_strDate!=szDate)
		{
			this->time_date_text_sensor->publish_state(szDate);
			m_strDate=szDate;
		}			
	}


/*        void OpenThermGateway::control(const climate::ClimateCall & call) 
        {
        }

        climate::ClimateTraits OpenThermGateway::traits() 
        {
            auto traits = climate::ClimateTraits();
            return traits;
        }*/

        void OpenThermGateway::loop() 
        {        	
		if(m_otThermostat!=NULL)
			m_otThermostat->process();
        }

	void OpenThermGateway::update()
	{
	}	
    } // namespace OpenThermGateway
} // namespace esphome
