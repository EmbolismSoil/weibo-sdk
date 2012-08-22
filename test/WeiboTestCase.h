#pragma once
#ifndef WEIBOUNITETST_WEIBOTESTCASE
#define WEIBOUNITETST_WEIBOTESTCASE

#include <boost/shared_ptr.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <IWeiboMethod.hxx>

//#define UNITTEST_STATUSES
//#define UNITTEST_COMMENTS
//#define UNITTEST_DIRECTMESSAGES
//#define UNITTEST_USER
//#define UNITTEST_FRIENDSHIPS
//#define UNITTEST_ACCOUNTS
//#define UNITTEST_FAVORITES
//#define UNITTEST_TRENDS
//#define UNITTEST_TAGS
//#define UNITTEST_SEARCHES
//#define UNITTEST_SUGGESTIONS
//#define UNITTEST_SHORTURL
//#define UNITTEST_INTERNAL_INTERFACE

#if defined(UNITTEST_INTERNAL_INTERFACE)
namespace weibo { class IWeiboInternalMethod; }
#endif //

/** test case for weibo
*
* @author welbon
*
* @date 2011-11-03
*/
class WeiboTestCase : public CPPUNIT_NS::TestFixture
{
public:
	WeiboTestCase();
	virtual ~WeiboTestCase();

public:
	void setUp(){}
	void tearDown(){}

	void standardOptionForWaiting(unsigned int id);

protected:
	std::string mUsrName;
	std::string mPassword;

private:
	CPPUNIT_TEST_SUITE(WeiboTestCase);

	// start login
	CPPUNIT_TEST (oauth2);

	// get my login id
	CPPUNIT_TEST (getAccountGetUID);

	// Required test
	CPPUNIT_TEST (getStatusesFriendTimeline);
	CPPUNIT_TEST (getCommentsShow);
	CPPUNIT_TEST (getFriendshipsFriends);
	CPPUNIT_TEST (getFriendshipsFriendsFollowers);

	CPPUNIT_TEST (postStatusesUpload);

#if defined(UNITTEST_STATUSES)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 微博读取
	CPPUNIT_TEST (getStatusesPublicTimeline);
	CPPUNIT_TEST (getStatusesFriendTimeline);
	CPPUNIT_TEST (getStatusesHomeTimeline);
	CPPUNIT_TEST (getStatusesUserTimeline);
	CPPUNIT_TEST (getStatusesTimelineBatch);
	CPPUNIT_TEST (getStatusesRepostTimeline);
	CPPUNIT_TEST (getStatusesRepostByMe);
	CPPUNIT_TEST (getStatusesMentions);
	CPPUNIT_TEST (getStatusesShow);
	CPPUNIT_TEST (getStatusesShowBatch);
	CPPUNIT_TEST (getStatusesQueryMID);
	CPPUNIT_TEST (getStatusesQueryID);
	CPPUNIT_TEST (getStatusesRepostDaily);
	CPPUNIT_TEST (getStatusesRepostWeekly);
	CPPUNIT_TEST (getStatusesHotCommmentsDaily);
	CPPUNIT_TEST (getStatusesHotCommmentsWeekly);

	// 微博写入
	CPPUNIT_TEST (postStatusesRepost);
	CPPUNIT_TEST (postStatusesDestroy);
	CPPUNIT_TEST (postStatusesUpdate);
	CPPUNIT_TEST (postStatusesUploadUrlText);
	CPPUNIT_TEST (postStatusesUpload);
#endif //#define UNITTEST_STATUSES


#if defined(UNITTEST_COMMENTS)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 评论读取
	CPPUNIT_TEST (getCommentsShow);
	CPPUNIT_TEST (getCommentsByMe);
	CPPUNIT_TEST (getCommentsToMe);
	CPPUNIT_TEST (getCommentsTimeline);
	CPPUNIT_TEST (getCommentsMentions);

	// 评论写入
	CPPUNIT_TEST (getCommentsShowBatch);
	CPPUNIT_TEST (postCommentsCreate);
	CPPUNIT_TEST (postCommentsReply);
	CPPUNIT_TEST (postCommentsDestroy);
	CPPUNIT_TEST (postCommentsDestroyBatch);

#endif //UNITTEST_COMMENTS

#if defined(UNITTEST_DIRECTMESSAGES)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 私信读取
	CPPUNIT_TEST (getDirectMessages);
	CPPUNIT_TEST (getDirectMessagesSent);
	CPPUNIT_TEST (getDirectMessagesUserList);
	CPPUNIT_TEST (getDirectMessagesCoversation);
	CPPUNIT_TEST (getDirectMessagesShowBatch);
	CPPUNIT_TEST (getDirectMessagesIsCapable);

	// 私信写入
	CPPUNIT_TEST (postDirectMessagesNew);
	CPPUNIT_TEST (postDirectMessagesDestory);
	CPPUNIT_TEST (postDirectMessagesDestoryBatch);
#endif //UNITTEST_COMMENTS

#if defined(UNITTEST_USERS)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 用户读取
	CPPUNIT_TEST (getUsersShow);
	CPPUNIT_TEST (getUsersDomainShow);
	CPPUNIT_TEST (getUsersShowBatch);
#endif //#if defined(UNITTEST_USERS)

#if defined(UNITTEST_FRIENDSHIPS)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 关注读取
	CPPUNIT_TEST (getFriendshipsFriends);
	CPPUNIT_TEST (getFriendshipsInCommon);
	CPPUNIT_TEST (getFriendshipsBilateral);
	CPPUNIT_TEST (getFriendshipsBilateralIDs);
	CPPUNIT_TEST (getFriendshipsFriendIDs);
	CPPUNIT_TEST (getFriendshipsFriendRemarkBatch);

	// 粉丝读取
	CPPUNIT_TEST (getFriendshipsFriendsFollowers);
	CPPUNIT_TEST (getFriendshipsFriendsFollowersIDs);
	CPPUNIT_TEST (getFriendshipsFriendsFollowersActive);

	// 关系链读取
	CPPUNIT_TEST (getFriendshipsFriendsChainFollowers);

	// 关系状态
	CPPUNIT_TEST (getFriendshipShow);

	// 关系写入
	CPPUNIT_TEST (postFriendshipsCreate);
	CPPUNIT_TEST (postFriendshipsCreateBatch);
	CPPUNIT_TEST (postFriendshipsRemarkUpdate);
	CPPUNIT_TEST (postFriendshipsDestroy);
	CPPUNIT_TEST (postFriendshipsFollowersDestroy);

#endif //#if defined(UNITTEST_FRIENDSHIPS)

#if defined(UNITTEST_ACCOUNTS)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 帐号读取
	CPPUNIT_TEST (getAccountProfileBasic);
	CPPUNIT_TEST (getAccountProfileEducation);
	CPPUNIT_TEST (getAccountProfileEducationBatch);
	CPPUNIT_TEST (getAccountProfileCareer);
	CPPUNIT_TEST (getAccountProfileCareerBatch);
	CPPUNIT_TEST (getAccountGetPrivacy);
	CPPUNIT_TEST (getAccountProfileSchoolList);
	CPPUNIT_TEST (getAccountRateLimitStatus);
	CPPUNIT_TEST (getAccountGetUID);

	// 帐号写入
	CPPUNIT_TEST (postAccountProfileBasicUpdate);
	CPPUNIT_TEST (postAccountProfileEduUpdate);
	CPPUNIT_TEST (postAccountProfileEduDestroy);
	CPPUNIT_TEST (postAccountProfileCarUpdate);
	CPPUNIT_TEST (postAccountProfileCarDestroy);
	CPPUNIT_TEST (postAccountAvatarUpload);
	CPPUNIT_TEST (postAccountUpdatePrivacy);
#endif //UNITTEST_ACCOUNTS

#if defined(UNITTEST_FAVORITES) 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 收藏读取
	CPPUNIT_TEST (getFavorites);
	CPPUNIT_TEST (getFavoritesShow);
	CPPUNIT_TEST (getFavoritesByTags);

	CPPUNIT_TEST (postFavoritesCreate);
	CPPUNIT_TEST (getFavoritesTags);
	CPPUNIT_TEST (postFavoritesTagUpdate);
	CPPUNIT_TEST (postFavoritesTagsUpdateBatch);
	CPPUNIT_TEST (postFavoritesDestroy);
	CPPUNIT_TEST (postFavoritesDestroyBatch);
	CPPUNIT_TEST (postFavoritesTagsDestroyBatch);
#endif //UNITTEST_FAVORITES

#if defined(UNITTEST_TRENDS) 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 话题读取
	CPPUNIT_TEST (getTrends);
	//CPPUNIT_TEST (getTrendsStatuses);
	CPPUNIT_TEST (getTrendsHourly);
	CPPUNIT_TEST (getTrendsDaily);
	CPPUNIT_TEST (getTrendsWeekly);

	// 话题写入
	CPPUNIT_TEST (postTrendsFollow);
	CPPUNIT_TEST (postTrendsDestroy);
#endif //

#if defined(UNITTEST_TAGS) 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 标签读取
	CPPUNIT_TEST (getTags);
	CPPUNIT_TEST (getTagsTagsBatch);
	CPPUNIT_TEST (getTagsSuggestions);

	// 标签写入
	CPPUNIT_TEST (postTagsCreate);
	CPPUNIT_TEST (postTagsDestroy);
	CPPUNIT_TEST (postTagsDestroyBatch);

#endif //UNITTEST_TAGS

#if defined(UNITTEST_SEARCHES) 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 搜索
	CPPUNIT_TEST (getSearchSuggestionsUsers);
	CPPUNIT_TEST (getSearchSuggestionsStatues);
	CPPUNIT_TEST (getSearchSuggestionsSchool);
	CPPUNIT_TEST (getSearchSuggestionsCompanies);
	CPPUNIT_TEST (getSearchSuggestionsApps);
	CPPUNIT_TEST (getSearchSuggestionsAtUsers);
	CPPUNIT_TEST (getSearchSuggestionsIntegrate);
	CPPUNIT_TEST (getSearchStatuses);
	//CPPUNIT_TEST (getSearchGeoStatuses);
	CPPUNIT_TEST (getSearchUsers);

#endif //#if defined(UNITTEST_SEARCHES) 

#if defined(UNITTEST_SUGGESTIONS)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 推荐读取
	CPPUNIT_TEST (getSuggestionsFavoritesHot);
	CPPUNIT_TEST (getSuggestionsUsersHot);
	CPPUNIT_TEST (getSuggestionsUsersMayInterested);
	CPPUNIT_TEST (getSuggestionsUsersByStatus);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 推荐写入
	CPPUNIT_TEST (postSuggestionsUsersNotInterested);
#endif //UNITTEST_SUGGESTIONS

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 短链接
#if defined(UNITTEST_SHORTURL)
	CPPUNIT_TEST (getShortURLShorten);
	CPPUNIT_TEST (getShortURLExpand);
	CPPUNIT_TEST (getShortURLShareCounts);
	CPPUNIT_TEST (getShortURLShareStatuses);
	CPPUNIT_TEST (getShortURLCommentCounts);
	CPPUNIT_TEST (getShortURLCommentComments);
#endif //UNITTEST_SHORTURL

#if defined(UNITTEST_INTERNAL_INTERFACE)

	// Suggestion hot
	CPPUNIT_TEST (getSuggestionsStatusesHot);

	// Unread
	CPPUNIT_TEST (getRemindUnreadCount);
	//CPPUNIT_TEST (getRemindUnreadCountSP);
	//CPPUNIT_TEST (postRemindAddCount);
	//CPPUNIT_TEST (postRemindSetCount);
	//CPPUNIT_TEST (postRemindClearCount);

	// File
	CPPUNIT_TEST (getFileAttachmentUploadSign);
	CPPUNIT_TEST (getFileAttachmentUploadBack);
	CPPUNIT_TEST (getFileAttachmentInfo);
	CPPUNIT_TEST (postFileAttachmentDestroy);
	CPPUNIT_TEST (postFileAttachmentRepost);

#endif //

#endif //

	CPPUNIT_TEST_SUITE_END();

	void oauth2();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 微博读取
	void getStatusesPublicTimeline();
	void getStatusesFriendTimeline();
	void getStatusesHomeTimeline();
	void getStatusesUserTimeline();
	void getStatusesTimelineBatch();
	void getStatusesRepostTimeline();
	void getStatusesRepostByMe();
	void getStatusesMentions();
	void getStatusesShow();
	void getStatusesShowBatch();
	void getStatusesQueryMID();
	void getStatusesQueryID();
	void getStatusesRepostDaily();
	void getStatusesRepostWeekly();
	void getStatusesHotCommmentsDaily();
	void getStatusesHotCommmentsWeekly();

	// 微博写入
	void postStatusesRepost();
	void postStatusesDestroy();
	void postStatusesUpdate();
	void postStatusesUploadUrlText();
	void postStatusesUpload();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 评论读取
	void getCommentsShow();
	void getCommentsByMe();
	void getCommentsToMe();
	void getCommentsTimeline();
	void getCommentsMentions();

	// 评论写入
	void getCommentsShowBatch();
	void postCommentsCreate();
	void postCommentsDestroy();
	void postCommentsDestroyBatch();
	void postCommentsReply();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 私信读取
	void getDirectMessages();
	void getDirectMessagesSent();
	void getDirectMessagesUserList();
	void getDirectMessagesCoversation();
	void getDirectMessagesShowBatch();
	void getDirectMessagesIsCapable();

	// 私信写入
	void postDirectMessagesNew();
	void postDirectMessagesDestory();
	void postDirectMessagesDestoryBatch();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 用户读取
	void getUsersShow();
	void getUsersDomainShow();
	void getUsersShowBatch();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 关注读取
	void getFriendshipsFriends();
	void getFriendshipsInCommon();
	void getFriendshipsBilateral();
	void getFriendshipsBilateralIDs();
	void getFriendshipsFriendIDs();
	void getFriendshipsFriendRemarkBatch();

	// 粉丝读取
	void getFriendshipsFriendsFollowers();
	void getFriendshipsFriendsFollowersIDs();
	void getFriendshipsFriendsFollowersActive();

	// 关系链读取
	void getFriendshipsFriendsChainFollowers();

	// 关系状态
	void getFriendshipShow();

	// 关系写入
	void postFriendshipsCreate();
	void postFriendshipsCreateBatch();
	void postFriendshipsDestroy();
	void postFriendshipsFollowersDestroy();
	void postFriendshipsRemarkUpdate();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 帐号读取
	void getAccountProfileBasic();
	void getAccountProfileEducation();
	void getAccountProfileEducationBatch();
	void getAccountProfileCareer();
	void getAccountProfileCareerBatch();
	void getAccountGetPrivacy();
	void getAccountProfileSchoolList();
	void getAccountRateLimitStatus();
	void getAccountGetUID();

	// 帐号写入
	void postAccountProfileBasicUpdate();
	void postAccountProfileEduUpdate();
	void postAccountProfileEduDestroy();
	void postAccountProfileCarUpdate();
	void postAccountProfileCarDestroy();
	void postAccountAvatarUpload();
	void postAccountUpdatePrivacy();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 收藏读取
	void getFavorites();
	void getFavoritesShow();
	void getFavoritesByTags();
	void getFavoritesTags();

	// 收藏写入
	void postFavoritesCreate();
	void postFavoritesDestroy();
	void postFavoritesDestroyBatch();
	void postFavoritesTagUpdate();
	void postFavoritesTagsUpdateBatch();
	void postFavoritesTagsDestroyBatch();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 话题读取
	void getTrends();
	void getTrendsStatuses();
	void getTrendsHourly();
	void getTrendsDaily();
	void getTrendsWeekly();

	// 话题写入
	void postTrendsFollow();
	void postTrendsDestroy();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 标签读取
	void getTags();
	void getTagsTagsBatch();
	void getTagsSuggestions();

	// 标签写入
	void postTagsCreate();
	void postTagsDestroy();
	void postTagsDestroyBatch();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 搜索
	void getSearchSuggestionsUsers();
	void getSearchSuggestionsStatues();
	void getSearchSuggestionsSchool();
	void getSearchSuggestionsCompanies();
	void getSearchSuggestionsApps();
	void getSearchSuggestionsAtUsers();
	void getSearchSuggestionsIntegrate();
	void getSearchStatuses();
	void getSearchGeoStatuses();
	void getSearchUsers();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 推荐读取
	void getSuggestionsFavoritesHot();
	void getSuggestionsUsersHot();
	void getSuggestionsUsersMayInterested();
	void getSuggestionsUsersByStatus();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 推荐写入
	void postSuggestionsUsersNotInterested();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 短链接口
	void getShortURLShorten();
	void getShortURLExpand();
	void getShortURLShareCounts();
	void getShortURLShareStatuses();
	void getShortURLCommentCounts();
	void getShortURLCommentComments();


#if defined(UNITTEST_INTERNAL_INTERFACE)

	weibo::IWeiboInternalMethod* getWeiboInternalMethod();

	// Suggestion hot
	void getSuggestionsStatusesHot();

	// Unread
	void getRemindUnreadCount();
	//void getRemindUnreadCountSP();
	//void postRemindAddCount();
	//void postRemindSetCount();
	//void postRemindClearCount();

	// File
	void getFileAttachmentUploadSign();
	void getFileAttachmentUploadBack();
	void getFileAttachmentInfo();
	void postFileAttachmentDestroy();
	void postFileAttachmentRepost();
#endif //UNITTEST_INTERNAL_INTERFACE

};
