#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
using namespace cocos2d;
using namespace cocos2d::network;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
    void testHttpGet();
    void testHttpPost();
    //请求回调函数
    void reqestResponseFunc( network::HttpClient *sender,cocos2d::network:: HttpResponse*response);
    //下载图片
    void downloadImage();
    void onHttpRequestImageCompleted(HttpClient *sender,HttpResponse *respoinse);
    void testMap();
    
    
    
    
};


#endif // __HELLOWORLD_SCENE_H__
