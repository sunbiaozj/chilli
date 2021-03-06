#pragma once
#include "../model/ProcessModule.h"
#include <log4cplus/logger.h>
#include <thread>
#include <atomic>

namespace chilli{
namespace DataBase{

class MySqlModule :public model::ProcessModule
{
public:
	explicit MySqlModule(const std::string & id, uint32_t threadSize = 16);
	virtual ~MySqlModule(void);
	virtual int Start() override;
	virtual int Stop() override;
	virtual bool LoadConfig(const std::string & configContext) override;
	virtual void run() override;
	virtual void execute(helper::CEventBuffer<model::EventType_t> * eventQueue) override;

	Json::Value executeQuery(const std::string & sql);
private:
	//inherit from SendInterface
	virtual void fireSend(const fsm::FireDataType & fireData, const void * param) override;
private:
	std::thread m_thread;
	helper::CEventBuffer<chilli::model::SQLEventType_t> m_SqlBuffer;
	std::string m_Host;
	uint32_t m_Port = 3306;
	std::string m_UserID;
	std::string m_Password;
	std::string m_DataBase;
	uint32_t m_connect_timeout = 5;
	void executeSql();
};
}
}

