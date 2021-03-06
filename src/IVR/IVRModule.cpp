#include "IVRModule.h"
#include "../Device/Device.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/config.h>
#include <json/json.h>


namespace chilli{
namespace IVR{

IVRModule::IVRModule(const std::string & id, uint32_t threadSize):ProcessModule(id, threadSize)
{
	log =log4cplus::Logger::getInstance("chilli.IVRModule");
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Constuction a IVR module.");
}


IVRModule::~IVRModule(void)
{
	LOG4CPLUS_DEBUG(log, "." + this->getId(), " Destruction a IVR module.");
}

bool IVRModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if (config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS){
		LOG4CPLUS_ERROR(log, "." + this->getId(), " load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}


	for (XMLElement *child = config.FirstChildElement("Extension"); 
		child != nullptr; 
		child = child->NextSiblingElement("Extension")) {

		const char * num = child->Attribute("ExtensionNumber");
		const char * sm = child->Attribute("StateMachine");
		num = num ? num : "";
		sm = sm ? sm : "";

		model::PerformElementPtr ext(new Device::Device(this, num, sm));

		if (ext != nullptr && addPerformElement(num,ext)) {
			ext->setVar("_extension.Extension", num);
		}
		else {
			LOG4CPLUS_ERROR(log, "." + this->getId(), " alredy had extension:" << num);
		}
	}
	return true;
}

void IVRModule::run()
{
}

void IVRModule::execute(helper::CEventBuffer<model::EventType_t>* eventQueue)
{
	fsm::threadIdle();
	fsm::threadCleanup();
	log4cplus::threadCleanup();
}


void IVRModule::fireSend(const fsm::FireDataType & fireData, const void * param)
{
	LOG4CPLUS_WARN(log, "." + this->getId(), " fireSend not implement.");
}
}
}
