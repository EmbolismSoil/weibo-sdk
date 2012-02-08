#include "ParsingObject.hxx"
#include <stdio.h>
#include <json/json.h>
#include <util/common/StringUtil.hxx>
#include "ParsingHandle.hxx"

#ifdef LOG_SUPPORT
#	define DEFAULT_SUBSYSTEM "WeiboParsing"
#	include <util/log/Logger.hxx>
#else
#	define CerrLog(args_)
#	define StackLog(args_)
#	define DebugLog(args_)
#	define InfoLog(args_)
#	define WarningLog(args_)
#	define ErrLog(args_)
#	define CritLog(args_)
#endif

using namespace weibo;

ParsingObject::ParsingObject(const char* source)
{
	//mParsingHandle = boost::make_shared<ParsingHandle>((Json::Value*)NULL, false);
    mParsingHandle.reset(new ParsingHandle(NULL, false));
	mParsingHandle->parse(source);
}

ParsingObject::ParsingObject(boost::shared_ptr<ParsingHandle> actHandlPtr)
{
	if (mParsingHandle)
	{
		mParsingHandle.reset();
	}
	mParsingHandle = actHandlPtr;
}

ParsingObject::ParsingObject(ParsingObject& object)
{
	if (mParsingHandle)
	{
		mParsingHandle.reset();
	}
	mParsingHandle = object.mParsingHandle;
}

ParsingObject::~ParsingObject()
{
}

bool ParsingObject::isUseable()
{
	return (mParsingHandle && !mParsingHandle->getValue().isNull());
}

const char* ParsingObject::getErrorMessage()
{
	return mParsingHandle->getErrorMessage();
}

const char* ParsingObject::getOriginString()
{
	return mParsingHandle->getSource();
}

std::string ParsingObject::getKeyName()
{
	std::string value;
	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull())
	{
		value = root.begin().memberName();
	}
	return value;
}

std::string ParsingObject::asAString()
{
	std::string value;
	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull())
	{
		if (root.isString())
		{
			value = root.asString();
		}
		else if (root.isNumeric())
		{
			char number[16] = { 0 };
			sprintf("%lld", number, root.asInt64());
			value = number;
		}
	}
	return value;
}

long long ParsingObject::asANumberic()
{
	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull())
	{
		return root.asInt64();
	}
	return 0;
}

unsigned int ParsingObject::getSubCounts()
{
	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull())
	{
		return root.size();
	}
	return 0;
}

long long ParsingObject::getSubNumbericByKey(const char* key)
{
	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull() && root.isObject())
	{
		Json::Value& value = root[key];
		if (value.isNumeric())
		{
			return value.asInt64();
		}
	}
	return 0;
}

std::string ParsingObject::getSubStringByKey(const char* key)
{
	std::string valString;

	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull() && root.isObject() && key)
	{
		Json::Value& val = root[key];
		if (val.isNumeric())
		{
			char tmp[32] = { 0 };
			sprintf(tmp, "%lld", val.asInt64());
			valString = tmp;
		}
		else if (val.isString())
		{
			return val.asString();
		}
	}
	return valString;
}

boost::shared_ptr<ParsingObject> ParsingObject::getSubObjectByKey(const char* key)
{
	boost::shared_ptr<ParsingObject> objectPtr;

	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull() && root.isObject() && key)
	{
		Json::Value& val = root[key];
		if (!val.isNull())
		{
            boost::shared_ptr<ParsingHandle> handler;
            handler.reset(new ParsingHandle(&val, false));
			
            objectPtr.reset(new ParsingObject(handler));
		}
	}
	return objectPtr;
}

long long ParsingObject::getSubNumbericByIndex(const int index)
{
	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull())
	{
		Json::Value &value = root[index];
		if (value.isNumeric())
		{
			return value.asInt64();
		}
	}
	return 0;
}

std::string ParsingObject::getSubStringByIndex(const int index)
{
	std::string valString;

	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull())
	{
		Json::Value& val = root[index];
		if (val.isNumeric())
		{
			char tmp[32] = { 0 };
			sprintf(tmp, "%lld", val.asInt64());
			valString = tmp;
		}
		else if (val.isString())
		{
			return val.asString();
		}
	}
	return valString;
}

boost::shared_ptr<ParsingObject> ParsingObject::getSubObjectByIndex(const int index)
{
	boost::shared_ptr<ParsingObject> objectPtr;
	if (mParsingHandle)
	{
		Json::Value& root = mParsingHandle->getValue();
		if (root.isArray())
		{
			Json::Value& valChild = root[index];
			if (!valChild.isNull())
			{
				boost::shared_ptr<ParsingHandle> handler;
                handler.reset(new ParsingHandle(&valChild, false));
				objectPtr.reset(new ParsingObject(handler));
			}
		}
		else
		{
			int i = 0;
			Json::Value::iterator it = root.begin();
			while(i < index && it != root.end())
			{
				++ i;
				++ it; 
			}

			Json::Value &valChild = (*it);
			if (!valChild.isNull())
			{
				boost::shared_ptr<ParsingHandle> handler;
                handler.reset(new ParsingHandle(&valChild, false));
				objectPtr.reset(new ParsingObject(handler));
			}
		}
	}
	return objectPtr;
}

	
void ParsingObject::enumAllSub(EnumAllSubCall callback, void* usrData)
{
	if (!mParsingHandle)
	{
		ErrLog(<< __FUNCTION__ << "| internal error , mParsingHandle is null!");
		return ;
	}

	Json::Value& root = mParsingHandle->getValue();
	if (!root.isNull() && root.size())
	{
		Json::Value::iterator it = root.begin();
		while (it != root.end())
		{
//			boost::shared_ptr<ParsingHandle> handler = boost::make_shared<ParsingHandle>(&(*it), false);
//			boost::shared_ptr<ParsingObject> objectPtr = boost::make_shared<ParsingObject>(handler);
            
            boost::shared_ptr<ParsingHandle> handler;
            handler.reset(new ParsingHandle(&(*it), false));
            
            boost::shared_ptr<ParsingObject> objectPtr;
            objectPtr.reset(new ParsingObject(handler));
            
			callback(objectPtr, usrData);
			++ it;
		}
	}
}
