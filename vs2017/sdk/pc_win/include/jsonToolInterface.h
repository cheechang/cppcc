#ifndef THIS_IS_JSONTOOLINTERFACE_H
#define THIS_IS_JSONTOOLINTERFACE_H
/**
   消息JSON工具类接口
*/
#include <string>
#include "config.h"
#include <vector>

struct calculationRead
{
	int16 msgType;  ///< 消息类型
};

class jsonToolInterface {
public:
	///在oriJson中找到fileName，将对应的值修改为newFileName,修改返回ture，未找到返回false。
	virtual bool  changeFileName(std::string & oriJson, std::string & newFileName) = 0;
	///判断是否计算未读，判断条件 msg.msgType等于8或者18返回false，否则返回true。
	virtual bool  isCalculationRead(calculationRead & msg) = 0;
	///返回撤回消息的消息ID
	virtual std::vector<int64> getRevokeMsgs(std::string & msgProp) = 0;
	///为messageProperty增加敏感词字段
	virtual void setBadWord(std::string &msgPropt, std::vector<std::string> &badWordList, int8 badWordType) = 0;
    ///为Json增加字段
    virtual void setProperty(std::string& strJson, const std::string& key, const std::string& value) = 0;
    ///获取Json字段
    virtual std::string getProperty(const std::string& strJson, const std::string& key) = 0;
    ///判断是否延迟消息
    virtual bool  isDelayMsg(const std::string &msgPropt) = 0;
    ///处理转发消息
    virtual void setFowardMsgProperty(std::string& msgPropt, int8 deviceType) = 0;
    ///解析日志消息
    virtual bool parseGetLogMsg(const std::string&msg, std::string& reason, std::vector<std::string>& files) = 0;
    ///解析上传文件Json
    virtual bool createGetlogMsgByUpload(const std::string& result, const std::string& fileName, std::string& msg) = 0;
    ///解析已读同步消息
    virtual bool parseSyncRead(const std::string& strJson, int64& targetId, int64& msgId) = 0;
    ///解析第一次置顶同步
    virtual bool parseFirstSyncTop(const std::string& strJson, std::vector<int64>& topContacts) = 0;
    ///解析置顶同步消息
    virtual void parseSyncTop(const std::string& strJson, int64& targetId, int& isTop) = 0;
};


#endif