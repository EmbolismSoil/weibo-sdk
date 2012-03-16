#ifndef WEIBOSDK_SDKMETHODIMPL_HXX
#define WEIBOSDK_SDKMETHODIMPL_HXX

#include "IWeiboMethod.hxx"
#include "SDKRequest.hxx"

/** implements for SDK method.
*
* @author welbon
* 
* @Email: libo.weng@gmail.com
*/
namespace weibo
{
	class SDKManager;

	class SDKMethodImpl : public IWeiboMethod
	{
	public:
		SDKMethodImpl(SDKManager *manager);

		void setUnifiedFormat(const eWeiboRequestFormat format);
		eWeiboRequestFormat getUnifiedFormat() const;
		void setConsumer(std::string &key, std::string& secret);
		void setAccesstoken(std::string &token);

	protected:
		WeiboRequestPtr internalMakeWeiboRequest(unsigned int methodOption, std::string& addtionParam,
			const eWeiboRequestFormat reqformat, const httpengine::HttpMethod method, const UserTaskInfo* pTask);

		eWeiboResultCode internalEnqueue(WeiboRequestPtr requestPtr);

	private:
		SDKManager *mManager;
		eWeiboRequestFormat mUnfiedFormat;
		std::string mConsumerkey;
		std::string mConsumersecret;
		std::string mAccesstoken;

	private:
		virtual eWeiboResultCode oauth2(const char* userName, const char* password, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode endSession();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 微博读取
		virtual eWeiboResultCode getStatusesPublicTimeline(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesFriendTimeline(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesHomeTimeline(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesUserTimeline(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesTimelineBatch(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesRepostTimeline(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesRepostByMe(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesMentions(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesShow(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesShowBatch(const char* inputIDs, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesQueryMID(const char *weiboId, const int type, const int is_batch = 0, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesQueryID(const char *mId, const int type, const int is_batch = 0, const int inbox = 0, const int isBase62 = 0, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesRepostDaily(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesRepostWeekly(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesHotCommmentsDaily(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getStatusesHotCommmentsWeekly(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 微博写入
		virtual eWeiboResultCode postStatusesRepost(const char *weiboId, const char *statusText, const int isComment, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postStatusesDestroy(const char *weiboId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postStatusesUpdate(const char* statusText, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postStatusesUploadUrlText(const char* statusText, const char *picInfo, bool isPicUrl, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postStatusesUpload(const char* statusText, const char *filePath, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 评论读取
		virtual eWeiboResultCode getCommentsShow(const char *weiboId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getCommentsByMe(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getCommentsToMe(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getCommentsTimeline(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getCommentsMentions(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 评论写入
		virtual eWeiboResultCode getCommentsShowBatch(const char* commentIds, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postCommentsCreate(const char* id, const char* comment, const int commentOri,VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postCommentsDestroy(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postCommentsDestroyBatch(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postCommentsReply(const char* commentId, const char* comment, const char* weiboId
			, const int withoutMention, const int commentOri, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 私信读取
		virtual eWeiboResultCode getDirectMessages(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getDirectMessagesSent(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getDirectMessagesUserList(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getDirectMessagesCoversation(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getDirectMessagesShowBatch(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getDirectMessagesIsCapable(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 私信写入
		virtual eWeiboResultCode postDirectMessagesNew(const char* text, const ID& uid, const char* fields = NULL,
			const char* weiboId = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postDirectMessagesDestory(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postDirectMessagesDestoryBatch(const char* ids, const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 用户读取
		virtual eWeiboResultCode getUsersShow(ID& usrId, const char* extend = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getUsersDomainShow(const char* domain = NULL, const char* extend = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getUsersShowBatch(ID& usrId, const char* extend = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 关注读取
		virtual eWeiboResultCode getFriendshipsFriends(ID& usrId, const int order/*= 0*/, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFriendshipsInCommon(const char* id, const char* suid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFriendshipsBilateral(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFriendshipsBilateralIDs(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFriendshipsFriendIDs(ID& usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFriendshipsFriendRemarkBatch(const char* uids, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 粉丝读取
		virtual eWeiboResultCode getFriendshipsFriendsFollowers(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFriendshipsFriendsFollowersIDs(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFriendshipsFriendsFollowersActive(ID &usrIDs, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 关系链读取
		virtual eWeiboResultCode getFriendshipsFriendsChainFollowers(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 关系状态
		virtual eWeiboResultCode getFriendshipShow(ID& sourceId, ID& targetId, UserTaskInfo* pTask = NULL) ;

		// 关系写入
		virtual eWeiboResultCode postFriendshipsCreate(ID &usrId, const int skipCheck, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFriendshipsCreateBatch(const char* uids, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFriendshipsDestroy(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFriendshipsFollowersDestroy(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFriendshipsRemarkUpdate(const char* uid, const char* remark, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 帐号读取
		virtual eWeiboResultCode getAccountProfileBasic(const char *uid, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getAccountProfileEducation(const char* uid, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getAccountProfileEducationBatch(const char* uids, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getAccountProfileCareer(const char* uid, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getAccountProfileCareerBatch(const char* uids, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getAccountGetPrivacy(UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getAccountProfileSchoolList(const int province = 0, const int city = 0, const int area = 0, const int type = 0, 
			const char* capital = 0, const char* keyword = 0, const int counts = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getAccountRateLimitStatus(UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getAccountGetUID(UserTaskInfo* pTask = NULL);

		// 帐号写入
		virtual eWeiboResultCode postAccountProfileBasicUpdate(const BasicInfo& basic, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postAccountProfileEduUpdate(const EducationInfo& edu, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postAccountProfileEduDestroy(const char* id, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postAccountProfileCarUpdate(const CareerInfo& career, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postAccountProfileCarDestroy(const char* id, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postAccountAvatarUpload(const char* filePath, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postAccountUpdatePrivacy(const int comment = 0, const int geo = 0, const int message = 0,
			const int realname = 0, const int badge = 0, const int mobile = 0, UserTaskInfo* pTask = NULL);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 收藏读取
		virtual eWeiboResultCode getFavorites(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFavoritesShow(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFavoritesByTags(const char* tid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getFavoritesTags(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 收藏写入
		virtual eWeiboResultCode postFavoritesCreate(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFavoritesDestroy(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFavoritesDestroyBatch(const char* ids, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFavoritesTagUpdate(const char* tagId, const char* tagName, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFavoritesTagsUpdateBatch(const char* tagId, const char* tagName, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postFavoritesTagsDestroyBatch(const char* tagId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 话题读取
		virtual eWeiboResultCode getTrends(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getTrendsStatuses(const char* trendWords, const char* provinceId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getTrendsHourly(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getTrendsDaily(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getTrendsWeekly(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 话题写入
		virtual eWeiboResultCode postTrendsFollow(const char* trendName, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postTrendsDestroy(const char* trendId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 标签读取
		virtual eWeiboResultCode getTags(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getTagsTagsBatch(const char* uids, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getTagsSuggestions(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		// 标签写入
		virtual eWeiboResultCode postTagsCreate(const char* tags, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postTagsDestroy(const char* tagId, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode postTagsDestroyBatch(const char* tagIds, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 搜索
		virtual eWeiboResultCode getSearchSuggestionsUsers(const char* q, const int count = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchSuggestionsStatues(const char* q, const int count = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchSuggestionsSchool(const char* q, const int count = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchSuggestionsCompanies(const char* q, const int count = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchSuggestionsApps(const char* q, const int count = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchSuggestionsAtUsers(const char* q, const int type, const int count = 0, const int range = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchSuggestionsIntegrate(const char* query, const int sort_user = 0, const int sort_app = 0,
			const int sort_grp = 0, const int user_count = 0, const int app_count = 0, const int grp_count = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchStatuses(const char* q, const int filter_ori = 0, const int filter_pic = 0, const char* fuid = 0, 
			const int province = 0, const int city = 0, const char* starttime = NULL, const char* endtime = NULL, const int count = 0, 
			const int page = 0, const bool needcount = 0, const int base_app = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchGeoStatuses(const float longitude, const float latitudeconst, const int range = 0, const int time = 0,
			const int sort_type = 0, const int page = 0, const int count = 0, const int base_app = 0, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getSearchUsers(const char* q, const int snick = 0, const int sdomain = 0, const int sintro = 0, const int stag = 0, 
			const int province = 0, const int city = 0, const char* gender = 0, const char* comorsch = 0, const int sort = 0,
			const int count = 0, const int page = 0, const int base_app = 0, UserTaskInfo* pTask = NULL);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 推荐读取
		virtual eWeiboResultCode getSuggestionsFavoritesHot(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getSuggestionsUsersHot(const char* category, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getSuggestionsUsersMayInterested(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;
		virtual eWeiboResultCode getSuggestionsUsersByStatus(const char* content, const int num = 0, const char* url = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 推荐写入
		virtual eWeiboResultCode postSuggestionsUsersNotInterested(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Short URL
		virtual eWeiboResultCode getShortURLShorten(const char* url_long, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getShortURLExpand(const char* url_short, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getShortURLShareCounts(const char* url_short, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getShortURLShareStatuses(const char* url_short, VariableParams* var = NULL, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getShortURLCommentCounts(const char* url_short, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getShortURLCommentComments(const char* url_short, VariableParams* var = NULL, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getShortUrlInfo(const char* shortUrlIDs, UserTaskInfo* pTask = NULL);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Unread
		virtual eWeiboResultCode getRemindUnreadCount(const char* uid, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postStatusesResetCount(const int type, UserTaskInfo* pTask = NULL);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Groups
		virtual eWeiboResultCode getGroupsJoined(const char* uid, const int page, const int count, 
			const int type, const int filter, const int sort, const int member_limit, const int simplify, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getGroupsShowBatch(const char* gids, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getGroupsGetAnnouncement(const char* gid, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getGroupsAdmin(const char* gid, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getGroupsUsers(const char* gid, VariableParams* var, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getGroupsSuggestionMayInterested(const int count, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getGroupsChatIsBlocked(const char* gids, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postGroupsChatBlock(const char* gid, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode postGroupsChatUnblock(const char* gid, UserTaskInfo* pTask = NULL);
		virtual eWeiboResultCode getGroupsUsersJoinedStatuses(const char* uid,int simplify,VariableParams* var = NULL,UserTaskInfo* pTask = NULL);
	};

}


#endif //WEIBOSDK_SDKMETHODIMPL_HXX