const md5 = require('js-md5')
let request = require('request-promise')
request = request.defaults({
  jar: true,
  strictSSL: false,
  timeout: 10000,
  gzip: true,
  headers: {
    // 'cache-control': 'no-cache',
    // 'Accept': '*/*',
    // 'accept-encoding': 'gzip, deflate',
    'User-Agent': 'Linkwork/1.7.1'
  }
  // proxy: "http://127.0.0.1:8888" // for fiddle net tool
})

class VRV_HR {
  /**
   * 构造函数，人事行政网管理器
   * 先登录构造后使用
   * TODO 单例构造
   * 
   * @static
   * @param {any} urlHOST 网址
   * @param {any} username 
   * @param {any} password 
   * @returns 
   * @memberof VRV_HR
   */
  static async login(urlHOST, username, password) {
    const self = new VRV_HR()
    self.HOST = urlHOST

    const psw = md5(password)
    const urlLogin = `default.aspx?UserName=${username}&UserPassWord=${psw}&BPers_Id=true`
    const loginBody = await self._request(urlLogin, 'Login')

    const urlMain = loginBody.match("P:'(MainPage/Main.aspx.*)',S:'ok'")
    if (urlMain == null || urlMain.length < 2) {
      throw new Error('登陆返回主页无效')
    }
    const mainBody = await self._request(urlMain[1], 'MainPage')

    return self
  }

  /**
   * 网络请求
   * 
   * @param {string} url 
   * @param {string} action 
   * @returns html body
   * @memberof VRV_HR
   */
  async _request(url, action) {
    return await request(this.HOST + url)
      .on('error', err => {
        console.error(action, err)
      })
      .on('response', resp => {
        console.log(action, resp.statusCode)
      })
  }

  _parseTable(body) {
    let items = []
    const tableRows = body.match(/待审批<\/a>.*<td>待审批<\/td>/g)
    if (tableRows != null) {
      for (const row of tableRows) {
        const cells = row.split('</td><td>')
        items.push(cells.slice(1, -1)) //, cells.length - 6))
      }
    }
    console.log(items)
    return items
  }

  /**
   * 获取请假表
   * 
   * @memberof VRV_HR
   */
  async getVacation() {
    const url = 'PostionM/Postion.aspx?tablename=tue_qj&maintable=&modulename=CTSP&spmodulename=KQ35&moduledesc=&userorder=&puserorder=4441&userid=21FA8DB1-27F3-485F-8A6A-AA54F2FBECCF&dept_code=&readonly=&clientwhere=&SpStat=0&SpcId=2&tabdbclickshow='
    const body = await this._request(url, 'Vacation')
    return this._parseTable(body)
  }
  /**
   * 获取外出表
   * 
   * @memberof VRV_HR
   */
  async getOutwork() {
    const url = 'PostionM/Postion.aspx?tablename=kqwcb_b&maintable=&modulename=CTSP&spmodulename=KQ36B&moduledesc=&userorder=&puserorder=4441&userid=21FA8DB1-27F3-485F-8A6A-AA54F2FBECCF&dept_code=&readonly=&clientwhere=&SpStat=0&SpcId=2&tabdbclickshow='
    const body = await this._request(url, 'Outwork')
    return this._parseTable(body)
  }

  /**
   * 获取外出补报表
   * 
   * @memberof VRV_HR
   */
  async getOutworkSupplement() {
    const url = 'PostionM/Postion.aspx?tablename=kqwcb_b&maintable=&modulename=CTSP&spmodulename=KQ36B&moduledesc=&userorder=&puserorder=4441&userid=21FA8DB1-27F3-485F-8A6A-AA54F2FBECCF&dept_code=&readonly=&clientwhere=&SpStat=0&SpcId=2&tabdbclickshow='
    const body = await this._request(url, 'supplement')
    return this._parseTable(body)
  }
  /**
   * 获取试用期评价表
   * 
   * @memberof VRV_HR
   */
  async getQualifying() {
    const url = 'PostionM/Postion.aspx?tablename=TUESYRYPJB&maintable=&modulename=CTSP&spmodulename=AASY&moduledesc=&userorder=&puserorder=4441&userid=21FA8DB1-27F3-485F-8A6A-AA54F2FBECCF&dept_code=&readonly=&clientwhere=&SpStat=0&SpcId=2&tabdbclickshow='
    const body = await this._request(url, 'Qualifying')
    return this._parseTable(body)
  }

}
async function main() {
  try {
    const hr = await VRV_HR.login('https://192.168.0.83/Hr_new/', 'vrvxxx', 'xxxxxx')
    let items = await hr.getOutwork()
    items = await hr.getOutworkSupplement()
    items = await hr.getQualifying()
    items = await hr.getVacation()
  } catch (error) {
    console.log(error);
  }
}
main()
