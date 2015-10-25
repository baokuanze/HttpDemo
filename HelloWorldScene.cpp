#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace cocos2d::network;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");

    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
   // testHttpGet();
    //testHttpPost();
    downloadImage();
//    auto sp0=Sprite::create();
//    sp0->setTag(0);
//    Vector<Sprite*>vec0;
//    vec0.pushBack(sp0);
//    //使用capacity为5 来创建一个vector<object*>，然后往其中加入一个精灵
//    auto sp1=Sprite::create();
//    sp1->setTag(1);
//    //用一个容量初始化一个vector
//    Vector<Sprite*>vec1(5);
//    //在一个确定的位置插入一个确定的对象
//    vec1.insert(0, sp1);
//    //也可以加入一整个Vector；
//    vec1.pushBack(vec0);
//    
//    for(auto sp:vec1){
//        log("sprite tag=%d",sp->getTag());
//    }
//    Vector<Sprite*>vec2(vec0);
//        if (vec0.equals(vec2)) {
//            log("ve2==vec0");
//        }
//
//    //判断Vector是否为空
//    if (!vec1.empty()) {
//        if (vec1.capacity()==vec1.size()) {
//            //获取vector的capacity和size要注意的是capacity并不一定等于size
//            log("pve1->capacity()==pvec1->size()");
//        }else{//收缩vector以便内存对应上元素的数量
//            vec1.shrinkToFit();
//            log("pvc1->capacity()==%zd;pvc1->size()=%zd",vec1.capacity(),vec1.size());
//        }
//        vec1.swap(vec1.front(), vec1.back());//通过值交换vector中的两个元素
//        if (vec2.contains(sp0)) {
//            //返回一个布尔值，用于只是该对象是否存在于vector中
//            log("The index of sp0 in pvec2 is %zd",vec2.getIndex(sp0));
//        }
//        //移除元素
//        vec1.erase(vec1.find(sp0));
//        vec1.clear();//移除所有元素
//        log("The size of Pvec1 is %zd",vec1.size());
//    }
}
void HelloWorld::testHttpGet(){
    HttpRequest*request=new HttpRequest();
    request->setUrl("http://www.baidu.com");
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag("res");
    //设置请求会掉函数
    request->setResponseCallback(CC_CALLBACK_2(HelloWorld::reqestResponseFunc, this));
    //发送请求
    HttpClient::getInstance()->send(request);
    //设置请求超时时间
    HttpClient::getInstance()->setTimeoutForConnect(20);
    //设置读取超时时间
    HttpClient::getInstance()->setTimeoutForRead(30);
    
}
void HelloWorld::testHttpPost(){
    char data[100];
    sprintf(data, "email=123@qq.com&password=123456&phoneIdentity=555555555");
    log("data=%ld",strlen(data));
    HttpRequest *request=new HttpRequest(); //要释放
    request->setUrl("http://123.56.111.165:8050/userRegister");
    request->setRequestType(HttpRequest::Type::POST);
    request->setRequestData(data, strlen(data));
    request->setResponseCallback(CC_CALLBACK_2(HelloWorld::reqestResponseFunc, this));
    request->setTag("post");
    HttpClient::getInstance()->send(request);
    request->release();
}



void HelloWorld:: reqestResponseFunc( network::HttpClient *sender,cocos2d::network::HttpResponse*response){
    if (!response) {
        MessageBox("wu", "wu");
        return;
    }
    log("%s",response->getHttpRequest()->getTag());
    log("%ld",response->getResponseCode());
    std:: vector<char> *buffer=response->getResponseData();
    char *m=new char[buffer->size()+1];
    for (unsigned i=0; i<buffer->size(); i++) {
        printf("%c",(*buffer)[i]);
               m[i]=(*buffer)[i];
    }
   m[buffer->size()]='\0';
   printf("\n");
}
//下载图片
void HelloWorld::downloadImage(){
    HttpRequest *requset=new HttpRequest();
    requset->setUrl("http://pic1.nipic.com/2008-09-08/200898163242920_2.jpg");
    requset->setRequestType(HttpRequest::Type::GET);
    //这是回调对象和回调函数
    requset->setResponseCallback( CC_CALLBACK_2(HelloWorld::onHttpRequestImageCompleted, this));
    //发送请求
    HttpClient::getInstance()->send(requset);
    requset->release();

}
void HelloWorld::onHttpRequestImageCompleted(HttpClient *sender,HttpResponse *respoinse){
    if(!respoinse){
        return;
    }
    const char *tag=respoinse->getHttpRequest()->getTag();
    log("tag=%s",tag);
    log("%zu",strlen(tag));
    if (0!=strlen(tag)) {
        log("%s completed",respoinse->getHttpRequest()->getTag());
    }
    if (!respoinse->isSucceed()) {
        log("error buffer:%s",respoinse->getErrorBuffer());
    }
    //通过responsize获取数据
    std::vector<char> *buffer=respoinse->getResponseData();

    printf("\n");
    std::string wrpath=FileUtils::getInstance()->getWritablePath();
    wrpath+="a.png";
    log("wrpath=%s",wrpath.c_str());

    Image *image=new Image();
    image->initWithImageData((unsigned char *)buffer->data(), buffer->size());
    image->saveToFile(wrpath);
    
    auto sprite=Sprite::create(wrpath);
    sprite->setPosition(200,200);
    this->addChild(sprite);

    //create Texture2D
//    Texture2D *texture=new Texture2D();
//    bool isImage=texture->initWithImage(image);
//     if( isImage  ){
//         log("Texture2D 初始化");
//    }
//    image->release();
    //设置搜索路径
    std::vector<std:: string>path;
    path.push_back(wrpath.c_str());
    FileUtils::getInstance()->setSearchPaths(path);
}

void HelloWorld::testMap(){
    auto sp0=Sprite::create();
    sp0->setTag(0);
    Map<std::string, Sprite *>map0;
    std::string mapKey0="MAP_KEY_0";
    map0.insert(mapKey0, sp0);
    log("The size of map is %zd",map0.size());
    //使用一个Map来初始化一个Map<K,V>
    Map<std::string, Sprite*>map1(map0);
    std::string mapKey1="MAP_KEY_1";
    if (!map1.empty()) {
        auto spTemp=(Sprite *)map1.at(mapKey0);
        log("sprite tag=%d",spTemp->getTag());
        auto sp1=Sprite::create();
        sp1->setTag(1);
        map1.insert(mapKey1, sp1);
        //获取所有key，存储在std::vector中，用于匹配对象
        std::vector<std::string>mapKeyVec;
        mapKeyVec=map1.keys();
        for (auto key:mapKeyVec) {
            auto sptag=map1.at(key)->getTag();
            log("The sprite tag=%d ,Map key=%s",sptag,key.c_str());
        }
    }


}







