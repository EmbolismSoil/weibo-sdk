#include "stdafx.h"
#include "UNITTestIDBuilderPolicy.h"
#include <time.h>
#include <boost/shared_ptr.hpp>
#include <IWeiboMethod.hxx>

#include "ParsingDefine.hxx"
#include "ParsingDataStruct.h"
#include "../common/strconv.h"

using namespace weibo;

UNITTestIDBuilderPolicy::UNITTestIDBuilderPolicy(boost::shared_ptr<WeiboTestCaseHelper> helper, const eRandomIDType idType, 
												 unsigned int optionId, const int counts, const char* forkey)
: mIdType(idType)
, mKey(forkey ? forkey : "")
, mID(weibo::ID::IDT_ID, "")
, mHelperPtr(helper)
{
	using namespace weibo;
	switch(idType)
	{
	case RIT_STATUS:
		{
			findResultFromHelpeListTemplate<ParsingStatus>(optionId ? optionId : WBOPT_GET_STATUSES_FRIENDS_TIMELINE, counts, mString);
		}
		break;

	case RIT_COMMENT:
		{
			findResultFromHelpeListTemplate<ParsingComment>(optionId ? optionId : WBOPT_GET_COMMENTS_TIMELINE, counts, mString);
		}
		break;

	case RIT_USERS:
		{
			findResultFromHelpeListTemplate<ParsingUser>(optionId ? optionId : WBOPT_GET_FRIENDSHIPS_FRIENDS, counts, mString);
		}
		break;

	case RIT_DIRECT_MESSAGE:
		{
			findResultFromHelpeListTemplate<ParsingDirectMessage>(optionId ? optionId : WBOPT_GET_DIRECTMESSAGES, counts, mString);
		}
		break;

	case RIT_FAVORITE:
		{
			findResultFromHelpeListTemplate<ParsingFavorite>(optionId ? optionId : WBOPT_GET_FAVORITES, counts, mString);
		}
		break;

	case RIT_FAVORITE_TAG:
		{
			findResultFromHelpeListTemplate<ParsingFavoriteTag>(optionId ? optionId : WBOPT_GET_FAVORITES_TAGS, counts, mString);
		}
		break;

	case RIT_TREND:
		{
			findResultFromHelpeListTemplate<ParsingTrend>(optionId ? optionId : WBOPT_GET_TRENDS, counts, mString);
		}
		break;

	case RIT_TAG:
		{
			findResultFromHelpeListTemplate<ParsingTag>(optionId ? optionId : WBOPT_GET_TAGS, counts, mString);
		}
		break;

	default:
		break;
	}
}

const char* UNITTestIDBuilderPolicy::asChar()
{
	return mString.c_str();
}

weibo::ID& UNITTestIDBuilderPolicy::asID()
{
	mID.idType = weibo::ID::IDT_ID;
	mID.id = mString;
	return mID;
}

const char *UNITTestIDBuilderPolicy::asWords()
{
	std::string &randomText = mWords;

	//char time_string[80] = { 0 };
	//time_t local_time = time(0);
	//strftime(time_string, 80, "%Y-%m-%d-%H-%M-%S", localtime(&local_time));

	const int eIdType = mIdType;
	switch (eIdType)
	{
	case RIT_STATUS: randomText = "CPPUNIT，单元测试，发布微博 [哈哈]。";  break;
	case RIT_COMMENT: randomText = "CPPUNIT，单元测试，发布评论 [哈哈]。"; break;
	case RIT_DIRECT_MESSAGE: randomText = "CPPUNIT，单元测试，发布私信 [哈哈]。"; break;
	case RIT_TREND: randomText = "TEST-TRENDS:"; break;

	default:
		break;
	}
	randomText += getDateString();
	randomText = CC2UTF8(randomText.c_str()).c_str();

	return randomText.c_str();
}

std::string UNITTestIDBuilderPolicy::getDateString()
{
	std::string dataString;

	char time_string[80] = { 0 };
	time_t local_time = time(0);
	strftime(time_string, 80, "%Y%m%d%H%M%S", localtime(&local_time));

	dataString = time_string;
	return dataString;
}

void UNITTestIDBuilderPolicy::getCommentIDAndStatuseID(std::string& commentId, std::string& statusId)
{
	WeiboTestCaseResultPtr result = mHelperPtr->checkoutReqResult(WBOPT_GET_COMMENTS_TIMELINE);
	if (result)
	{
		weibo::ParsingCommentsListPtr commentListPtr
			= boost::dynamic_pointer_cast<weibo::ParsingCommentsList>(result->pasringPtr_);

		if (commentListPtr && !(commentListPtr->mDataList.empty()))
		{
			weibo::ParsingCommentPtr commentPtr = *(commentListPtr->mDataList.begin());
			commentId = commentPtr->id;
			if (commentPtr->status)
			{
				statusId = commentPtr->status->id;
			}
		}
	}
}