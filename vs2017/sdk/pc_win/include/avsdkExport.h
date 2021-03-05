
#ifndef LINKDOOD_AVSDK_H_
#define LINKDOOD_AVSDK_H_

#include <windows.h>
#include <string>

#define VIDEOSIPINTERFACE_API_EX extern "C"  _declspec(dllexport)

class CallBack {

public:

	virtual void onIceGatheringComplete(const char* type, const char* sdp) = 0;

	virtual void onIceConnected() = 0;

	virtual void onIceDisconnected() = 0;

	virtual void onPeerConnectionError(const char *description) = 0;

	virtual void onMessage(const char* data, size_t size) = 0;

};

struct AVParam{
	AVParam() :ordered_(true), maxRetransmitTime_(-1), maxRetransmits_(-1){}

	HWND local_;
	HWND remote_;
	char *ice_server_;
	char *ice_port_;
	char *ice_user_;
	char *ice_pwd_;
	bool audio_on_;
	bool video_on_;
	CallBack *call_back_;

	bool data_on_;
	bool ordered_ ;
	
	int maxRetransmitTime_;
	int maxRetransmits_;
};

struct serResult{
	std::string stunAddr;
	std::string turnAddr;
	std::string account;
	std::string password;
};

class AVSDK {
public:

	virtual void SetAVParam(const AVParam param) = 0;       // 第一步

	virtual void CreateOffer() = 0;                         // 第二步

	virtual void CreateAnswer(const char* sdp) = 0;

	virtual void SetRemoteDescription(const char* sdp, const char* type) = 0;

	virtual void Destroy() = 0;

	virtual void TurnOnVideo(bool enable) = 0;

	virtual bool Send(unsigned char *data, size_t size) = 0;

};

VIDEOSIPINTERFACE_API_EX void createAVSDKSDKSDK(AVSDK*& p);

VIDEOSIPINTERFACE_API_EX void destroyAVSDKSDKSDK(AVSDK*& p);

#endif