// import { getTargetByProxy, getServiceByProxy } from './proxyService';
// import interfaceParam from './interface'
// const service = getServiceByProxy();
// const AuthService = getTargetByProxy(service, 'authService');
// const ContactService = getTargetByProxy(service, 'contactService');
// const ChatService = getTargetByProxy(service, 'chatService');
// const UserService = getTargetByProxy(service, 'userService');
// const GroupService = getTargetByProxy(service, 'groupService');
// const FileService = getTargetByProxy(service, 'fileService');
// const ConfigService = getTargetByProxy(service, 'configService');
// const SearchService = getTargetByProxy(service, 'searchService');
// const EnterpriseService = getTargetByProxy(service, 'enterpriseService');
// const SysMsgService = getTargetByProxy(service, 'sysMsgService');
// const RtcService = getTargetByProxy(service, 'rtcService');
// // const ProcessService = getTargetByProxy(service, 'processService');
// // export const platformIsMac = getTargetByProxy(service, 'platformIsMac');
// export function initService () {
//     let functionObj = getTargetByProxy(service, 'init');
//     functionObj();
// };
// export function unInitService () {
//     let functionObj = getTargetByProxy(service, 'unInit');
//     functionObj();
// };
// /*
// let path = {
//   filepath:string //路径
// }
// */
// export function fileOperate (path:object) {
//     let functionObj = getTargetByProxy(FileService, 'fileOperate');
//     return functionObj(path);
// };
// export function setLog (level: number, info: string) {
//     let functionObj = getTargetByProxy(service, 'setLog');
//     functionObj(level, info);
// }
// export function authService (action: string, callback: any, param?: interfaceParam.authServiceParam) {
//     let functionObj = getTargetByProxy(AuthService, action);
//     callService(functionObj, callback, param);
// };
// export function contactService (action: string, callback: any, param?: interfaceParam.contactServiceParam) {
//     let functionObj = getTargetByProxy(ContactService, action);
//     callService(functionObj, callback, param);
// };
// export function chatService (action: string, callback: any, param?: interfaceParam.chatServiceParam) {
//   console.log('action::', action)  
//   let functionObj = getTargetByProxy(ChatService, action);
//     return callService(functionObj, callback, param);
// };
// export function userService (action: string, callback: any, param?: interfaceParam.userServiceParam) {
//     let functionObj = getTargetByProxy(UserService, action);
//     callService(functionObj, callback, param);
// };
// export function groupService (action: string, callback: any, param?: interfaceParam.groupServiceParam) {
//     let functionObj = getTargetByProxy(GroupService, action);
//     callService(functionObj, callback, param);
// };
// export function fileService (action: string, callback: any, param?: interfaceParam.fileServiceParam, process?: any) {
//     let functionObj = getTargetByProxy(FileService, action);
//     if (process) {
//         return functionObj(param, callback, process);
//     } else {
//         return callService(functionObj, callback, param);
//     }
// };
// export function configService (action: string, callback: any, param?: interfaceParam.configServiceParam) {
//     let functionObj = getTargetByProxy(ConfigService, action);
//     return callService(functionObj, callback, param);
// };
// export function searchService (action: string, callback: any, param?: interfaceParam.searchServiceParam) {
//     let functionObj = getTargetByProxy(SearchService, action);
//     callService(functionObj, callback, param);
// };
// export function enterpriseService (action: string, callback: any, param?: interfaceParam.enterpriseServiceParam) {
//     let functionObj = getTargetByProxy(EnterpriseService, action);
//     callService(functionObj, callback, param);
// };
// export function sysMsgService (action: string, callback: any, param?: interfaceParam.sysMsgServiceParam) {
//     let functionObj = getTargetByProxy(SysMsgService, action);
//     callService(functionObj, callback, param);
// };
// export function rtcService (action: string, callback: any, param?: interfaceParam.rtcServiceParam) {
//     let functionObj = getTargetByProxy(RtcService, action);
//     callService(functionObj, callback, param);
// };
// // export function processService (action: string, callback?: any, param?: interfaceParam.processServiceParam) {
// //     let functionObj = getTargetByProxy(ProcessService, action);
// //     return callService(functionObj, callback, param);
// // }
// /* 提供给上层使用的同步接口
//  * serviceName: 服务名称，如:configService
//  * functionName: 接口名称
//  * 建议：interface.ts中标注为同步的接口使用
//  * 示例：
//  * async testFunction(){
//  *    var result = await this.$Service.callServiceSync('configService', 'getLoginInfos')
//  *    console.log(result);   // result为获得的结果
//  * }
//  */
// export function callServiceSync (serviceName: string, functionName: any, param?: object) {
//     let functionObj = getTargetByProxy(getTargetByProxy(service, serviceName), functionName);
//     if (param) {
//         return new Promise((resolve, reject) => {
//             functionObj(param, (res: object) => {
//                 resolve(res);
//             })
//         })
//     }
//     else {
//         return new Promise((resolve, reject) => {
//             functionObj((res: object) => {
//                 resolve(res);
//             })
//         })
//     }

// };
// function callService (functionObj: any, callback?: any, param?: object) {
//     if (param) {
//         return functionObj(param, callback);
//     } else {
//         return functionObj(callback);
//     }
// }