#ifndef WEIBOUNITTEST_WEIBOTESTCASEHELPER_H
#define WEIBOUNITTEST_WEIBOTESTCASEHELPER_H

#include <map>
#include <IWeibo.hxx>
#include <IWeiboMethod.hxx>
#include "ParsingDefine.hxx"

namespace weibo
{
	class ParsingObject;
}

class WeiboTestCaseResult
{
public:
	WeiboTestCaseResult();
	virtual ~WeiboTestCaseResult();

	std::string outputString();

	enum eResultType
	{
		ERT_UNKNOW, 
		ERT_CORRECT,
		ERT_ERROR,
	};

	eResultType resultType_;

	//std::string respBody_;

	int errorCode_;
	int subErrorCode_;

	weibo::ParsingBasePtr pasringPtr_;
};

typedef boost::shared_ptr<WeiboTestCaseResult> WeiboTestCaseResultPtr;

class WeiboTestCaseHelper
{
public:
	WeiboTestCaseHelper();
	virtual ~WeiboTestCaseHelper();

	weibo::IWeiboMethod* getWeiboMethod();

	WeiboTestCaseResultPtr checkoutReqResult(unsigned int optionId);

	const char* getMYID();

	void onResponseProcess(unsigned int optionId, weibo::ParsingObject* result, const int errCode, const int errSubCode, bool isComplated);

	static const char* getAppModulePath();
	static const wchar_t* getAppModulePathW();

	void setAccountInfo(const char* account, const char* password);

protected:
	void onWeiboRespComplated(unsigned int methodOption, const char* httpHeader, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask);
	void onWeiboRespErrored(unsigned int optionId, const int errCode, const int errSubCode, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask);
	void onWeiboRespStoped(unsigned int optionId, const weibo::UserTaskInfo* pTask);

	void initializeParsingMap();

protected:
	typedef std::map<unsigned int, WeiboTestCaseResultPtr> UnitTestResultMAP;
	typedef std::map<unsigned int, weibo::ParsingBasePtr> UnitTestParsingMAP;

	std::string mMYID;
	boost::shared_ptr<weibo::IWeibo> mWeiboPtr;
	UnitTestResultMAP mResultMap;
	UnitTestParsingMAP mParsingMap;
};

#endif //WEIBOUNITTEST_WEIBOTESTCASEHELPER_H
