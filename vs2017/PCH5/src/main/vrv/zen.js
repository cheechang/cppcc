let request = require('request-promise');
request = request.defaults({
  jar: true,
  strictSSL: false,
  timeout: 5000
})

//zentaosid=0gs7rohlqvgekm5f47l27n9pp1; keepLogin=on; za=luojin150427; zp=e783ea40dd8a7e99881c13c3e819eb8da0f9943b

class ZenTao {
  /**
   * 禅道操作类，获取个人主页上一些指派给自己的列表信息
   * 禅道API使用m=Module,f=Function,t=Type，其他为f的参数
   * 流程：getSession->login->getXXX
   * 登录，使用禅道账号密码
   * sessionID会自动存入cookies
   * TODO 单例
   * 
   * @param {string} account 
   * @param {string} password 
   * @memberof ZenTao
   */
  static async login(urlHost, account, password) {
    const self = new ZenTao()
    self.HOST = urlHost

    self.sessionID = await self._getSession()
    console.log("sessionID:", self.sessionID)
    const loginStatus = await self._login(account, password)
    console.log("loginStatus:", loginStatus)

    return self
  }

  /**
   * 从禅道服务器获取会话凭据
   * 
   * @returns 
   * @memberof ZenTao
   */
  async _getSession() {
    const body = await request
      .get(this.HOST + '/?m=api&f=getSessionID&t=json')
      .on('error', err => console.error('upload failed:', err))

    const sessionID = body.match(String.raw `\\"sessionID\\":\\"(.*)\\",`)[1]

    return sessionID
  }

  /**
   * 登录的内部实现，使用官方指定的cookie后功能失效（已注释）
   * 
   * @param {string} account 
   * @param {string} password 
   * @returns 
   * @memberof ZenTao
   */
  async _login(account, password) {
    const url = this.HOST + '/index.php?m=user&f=login&t=json&sid=' + this.sessionID
    // const cook = request.cookie('keepLogin=on')
    // const cookieJar = request.jar()
    // cookieJar.setCookie(cook, url)
    const body = await request
      .post({
        url: url,
        form: {
          account,
          password
        }
        // jar: cookieJar
      })
      .on('error', err => console.error('upload failed:', err))

    const status = body.substr(body.indexOf('{"status":') + 11, 7)

    return status
  }

  /**
   * 返回我的主页中指派给我的功能json
   * [task | bug | story ]
   * 
   * @param {string} functionName 
   * @memberof ZenTao
   */
  async getMyFunctionList(functionName, jsonKey) {
    const body = await request
      .get(this.HOST + '/index.php?m=my&f=' + functionName + '&type=assignedTo&orderBy=id_desc&recPerPage=50&t=json')
      .on('error', err => console.error('upload failed:', err))
    const all = JSON.parse(body)
    const data = JSON.parse(all['data'])
    return data[jsonKey]
  }

  /**
   * 返回指派给我的bug
   * TODO bug item需要显示的key const keys = ['id', 'pri', 'productTitle', 'title', 'status', 'stage', 'lastEditedDate']
   * TODO 点击item后 跳转的url: HOST + /index.php?m=bug&f=view&bugID=1401
   * 
   * @returns 
   * @memberof ZenTao
   */
  getBugs() {
    return this.getMyFunctionList('bug', 'bugs')
  }

  /**
   * 返回指派给我的需求
   * TODO bug item需要显示的key const keys = ['id', 'pri', 'productTitle', 'title', 'status', 'stage', 'lastEditedDate']
   * TODO 点击item后 跳转的url: HOST + /index.php?m=story&f=view&storyID=1401
   * 
   * @returns 
   * @memberof ZenTao
   */
  getStories() {
    return this.getMyFunctionList('story', 'stories')
  }

  /**
   * 返回指派给我的任务
   * 
   * @returns 
   * @memberof ZenTao
   */
  getTasks() {
    return this.getMyFunctionList('task', 'tasks')
  }
}

async function main() {
  try {
    const zt = await ZenTao.login('https://192.168.6.10', 'xxxxxx', 'xxxxxx')
    const bugs = await zt.getBugs()
    const stories = await zt.getStories()
    const tasks = await zt.getTasks()
    console.log('bugs, stories, tasks: ', bugs.length, stories.length, tasks.length)
  } catch (err) {
    console.log('error occurs', err);
  }
}

main()

