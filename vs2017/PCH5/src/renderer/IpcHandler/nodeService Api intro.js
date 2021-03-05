/************************************auth 认证模块******************************************** */
	/**
    * \brief 获取注册验证码
    * 函数名称 getRegCode(auth模块)
	* @param[in] getRegCodeParam 传入对象
	* @param[out] cb 传入接收结果回调 _1 result 接收结果的对象
    * void getRegCode(getRegCodeParam,cb);
    * let getRegCodeParam  = {
    *  account: string,     // 传入注册账号 目前只支持手机注册 手机账户格式为“0086********”
    *  server: string,      // 服务器名称
    *  type: number,        // 1.获取手机号注册验证码 2.获取手机号登录验证码
    *  }
    * let result = {
    *  code:number,   // 错误码
    *  time:number    // 超时
    * }
    **/


    /**
    * \brief 老注册
    * 函数名称 signupOld(auth模块)
	* @param[in] signupOldParam 传入对象
	* @param[out] cb 传入接收结果回调 _1 result 接收结果的对象
    * void signupOld(signupOldParam,cb);
    * let signupOldParam  = {
    *  regCode: string,     // 传入验证码
    *  pwd: string,         // 传入密码
    *  user: string         // 传入用户名，建议使用真实姓名
    *  }
    * let result = {
    *  code:number   // 错误码
    *  userId:string  // 用户Id
    * }
    **/


    /**
    * \brief 注册
    * 函数名称 signup(auth模块)
	* @param[in] signupParam 传入对象
	* @param[out] cb 传入接收结果回调 _1 result 接收结果的对象
    * void signup(signupParam,cb);
    * let signupParam  = {
    *  regCode: string,     // 传入验证码
    *  account: string,     // 传入注册账号 目前只支持手机注册 手机账户格式为“0086********”
    *  }
    * let result = {
    *  code:number,   // 错误码
    *  userId:string  // 用户Id
    * }
    **/


    /**
    * \brief 同时设置昵称和密码(signup后调用)(setNameAndPasswd)
    * 函数名称 setNameAndPasswd(auth模块)
	* @param[in] setNameAndPasswdParam 传入对象
	* @param[out] cb 传入接收结果回调 _1 result 接收结果的对象
    * void setNameAndPasswd(setNameAndPasswdParam,cb);
    * let setNameAndPasswdParam  = {
    *  name: string,        // 传入名称
    *  passwd: string,      // 传入密码
    *  }
    * let result = {
    *  code:number   // 错误码
    * }
    **/