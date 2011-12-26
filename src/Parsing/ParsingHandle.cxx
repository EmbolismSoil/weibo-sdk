#include "ParsingHandle.hxx"
#include <json/json.h>
#include <util/common/StringUtil.hxx>

using namespace weibo;

ParsingHandle::ParsingHandle(Json::Value* val, bool owner)
: mValRoot(val)
, mIsOwner(owner)
{
}

ParsingHandle::~ParsingHandle()
{
	reset(NULL, false);
}

bool ParsingHandle::parse(const char* source)
{
	reset(NULL, false);

	mIsOwner = true;
	Json::Reader reader;
	std::string src = Util::StringUtil::getNotNullString(source);
	if (!src.empty())
	{
		if (!mValRoot)
		{
			mValRoot = new Json::Value();
		}
		bool ret = reader.parse(src, *mValRoot);
		mErrorMessage = reader.getFormatedErrorMessages();
		return ret;
	}
	return false;
}

void ParsingHandle::reset(Json::Value* val, bool owner)
{
	if (mValRoot && mIsOwner)
	{
		delete mValRoot;
		mIsOwner = false;
	}
	mValRoot = val;
	mIsOwner = owner;
}

const char* ParsingHandle::getErrorMessage()const
{
	return mErrorMessage.c_str();
}

Json::Value& ParsingHandle::getValue()
{
	if (!mValRoot)
	{
		mValRoot = new Json::Value();
	}
	return *mValRoot;
}
