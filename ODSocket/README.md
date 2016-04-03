#ODSocket说明文档

>* ODSocekt对socket的一些操作都做好了封装，让socket的链接变得简单，同时它也是跨平台的。  

##DEMO:
```C++
void HelloWorld::connectServer(){
    ODSocket cSocket;

    cSocket.Init();
    cSocket.Create(AF_INET, SOCK_STREAM, 0);

    const char* ip = "115.28.47.161";
    int port = 7777;
    bool result = cSocket.Connect(ip, port);

    int retryTimes = 0;
    while (result == false && retryTimes < 7) {
        log("retry connecting...");

        result = cSocket.Connect(ip, port);
        retryTimes++;

\#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        Sleep(500);
\#else
        usleep(500);
\#endif

    }
    if (result) {
        log("connect to server suc!");
    }
    else {
        log("can not connect to server");
    }
}
```
##大致使用流程：
>* 创建ODSocket对象;
>* 调用Init函数进行初始化;
>* 调用Create函数创建socket;
>* 指定服务器IP和端口，调用Connect函数开始连接服务器;
