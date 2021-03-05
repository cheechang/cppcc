export const OptionType = {
    Percent: 'kPercent', //进度
    Begin: 'kBegin', //开始
    Cancel: 'kCancel', //取消
    End: 'kEnd', //完成
    Busy: 'kBusy', // 忙
    Timeout: 'kTimeout', // 超时
    Reject: 'kReject', // 拒绝
    Error: 'kError' // 错误
  };
  
  export const RtcStatus = {
    NORMAL: 'normal', // 默认状态
    BEGIN: 'begin', // 开始请求
    OFFER: 'offer', // 请求
    ANSWER: 'answer', // 响应
    CANCEL: 'cancel', // 取消
    CONNECTION: 'connection', // 连接
    DISCONNECT: 'disconnect', // 断开
    BUSY: 'busy', // 忙
    TIMEOUT: 'timeOut', // 超时
    CLOSE:'close',
    ERROR: 'error', // 错误
    ERROR_OFFER:'offer_error',//offer 失败
    ERROR_ANSWER:'answer_error',//answer 失败
    ERROR_NET:'net_error',//网络断开
    ERROR_NOSPACE:'noSpace_error',// 磁盘错误
    ERROR_OPENFAILED:'OpenFileFailed_error',// 打开文件错误
    RELAY:'relay', // 服务中转
  }
  
  export const FileStatus = { // 等待 发送中 完成 取消
    NORMAL: 'normal', // 默认状态
    // WAIT: 'wait',
    BEGIN: 'begin',
    // SENDING: 'sending',
    // RECEIVING:'receiving',
    END: 'end',
    ENDALL:'endAll',
    CANCEL: 'cancel',
    ACCEPT:'accept',
    BUSY: 'busy', // 忙
    TIMEOUT: 'timeOut', // 超时
    ERROR_NET:'net_error',//网络断开
    ERROR_OFFER:'offer_error',// createOffer失败
    ERROR_ANSWER:'answer_error',// answer 失败
    ERROR_RTC:'rtc_error',//RTC断开
    ERROR_NOSPACE:'noSpace_error',// 磁盘错误
    ERROR_OPENFAILED:'OpenFileFailed_error',// 打开文件错误
    PROGRESS:'progress',
    HOST:'host', // 服务中转
    SRFLX:'srflx', // 服务中转
    PRFLX:'prflx', // 服务中转
    RELAY:'relay', // 服务中转
  }
  
  export const RtcMethod = {
    SETID :'setId',
    FILE_INFO: 'fileinfo',
    REQUEST: 'request',
    RECVALL: 'RecvAll',
    FIRST4BYTES: 'first4bytes',
    ACCEPT:'accept',
    CANCEL: 'cancel',
    RESULT: 'result',
    CLOSE: 'close'
  }
  
  export const SubType = {
    SEND : 50, // 发送
    SUCCESS_SEND : 51,// 发送完成
    SUCCESS_RECEIVE : 52,// 接收完成
    REFUSE : 53,// 接收端拒绝
    CANCEL_SENDER : 54,// 发送方取消
    CANCEL_RECEIVER : 55,// 接收方取消
    DISCONNECTION_SENDER: 56,// 发送方断开
    DISCONNECTION_RECEIVER: 57,// 接收方断开
    BUSY_SENDER : 59,// 发送方忙
    BUSY_RECEIVER : 60,// 接收方忙
    TIMEOUT :58 // 超时
  }
  