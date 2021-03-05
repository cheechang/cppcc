<template>
<div class="create-group-metting">
    <v-modal @close="$emit('close')">
        <!-- 添加background覆盖modal，避免添加/邀请群成员loading时可以进行其他操作 -->
        <div class="group-background" v-if="isLoading"></div>
        <div class="create-group">
            <div class="create-group-left">
                <p class="group-title">{{currentTitle}}</p>
                <v-input class="search-input" v-model="inputSearch" :placeholder="$t('groups.search')" size="is-small" :position="inputSearch==''?'left':'right'" @input="searchFromLocal">
                    <i v-if="inputSearch==''" class="icon search-icon" slot="expand">&#xe68c;</i>
                    <i v-else class="icon" slot="expand" @click="clearInput">&#xe650;</i>
                </v-input>
                <transition name="slide-up">
                    <div class="create-contact-list" ref="groups" @scroll.passive.stop="loadMoreData">
                        <v-card-list>
                            <v-card v-for="(item,index) in memberList" :key="index" :title="item.remark||item.name" @click="changeItemState(item)">
                                <v-avatar size="is-small" :src="item.thumbAvatar" :sex="item.gender" :offline="false" shape="round" slot="leftAvatar"></v-avatar>
                                <v-avatar slot="after" class="avatar-bg" :offline="false" shape="round" :src="isSelectItem(item,true)" />
                            </v-card>
                        </v-card-list>
                    </div>
                </transition>
            </div>
            <div class="create-group-right">
                <i class="icon" @click="$emit('close')">&#xe603;</i>
                <div class="create-meeting-name">{{`${$t('groups.topic')}:`}}
                    <v-input maxlength="20" :placeholder="$t('groups.enterTopic')" v-model="meetingName" :readonly="false"></v-input>
                </div>
                <div class="create-meeting-remark">{{`${$t('groups.remarks')}:`}}
                    <v-input maxlength="30" :placeholder="$t('groups.enterRemarks')" v-model="meetingRemark" :readonly="false"></v-input>
                </div>
                <div class="member-list-area">
                    <div class="member-list-title">{{getSelectedNum()}}</div>
                    <div class="member-list">
                        <v-card-list>
                            <v-card v-for="(item,index) in selectedList" :key="index" :title="item.name || item.remark">
                                <v-avatar size="is-small" :src="item.thumbAvatar" :sex="item.gender" :offline="false" shape="round" slot="leftAvatar"></v-avatar>
                                <v-avatar slot="after" class="avatar-bg" :offline="false" shape="round" :src="isSelectItem(item,false)" @icon-click="changeItemState(item)" />
                            </v-card>
                        </v-card-list>
                    </div>
                </div>
                <div class="modal-card-footer" slot="footer-bottom">
                    <!-- <v-checkbox class="select-all" v-model="checkStatus" @change="selectedAll">{{$t('rtc.selectAll')}}</v-checkbox> -->
                    <v-tooltip type="is-danger" :lable="tipLable" :active="tipActive" always>
                        <v-button :type="`${buttonType} is-primary`" :ripple="false" :disable="selectMemberIds.length==0||meetingName.trim()==''" @click.self="handleMeeting">{{$t('common.confirm')}}</v-button>
                    </v-tooltip>
                    <v-button @click="$emit('close'), selectMemberIds=[]">{{$t('common.cancel')}}</v-button>
                </div>
            </div>
        </div>
    </v-modal>
</div>
</template>

<script>
import { mapGetters } from "vuex";
import ContactMixin from "../Contact/ContactMixin";
import { MsgImgTemplate } from "../Chat/Msg";
const { remote } = require('electron');
const rtcplugin = remote.getGlobal('service')['rtcplugin'];

export default {
    mixins: [ContactMixin],
    data() {
        return {
            isLoading: false,
            tipLable: "",
            tipActive: false,
            noneImg: require("vrv-static/resources/images/contact/groupChooseNone.png"),
            selectImg: require("vrv-static/resources/images/contact/groupChooseSelect.png"),
            deleteImg: require("vrv-static/resources/images/contact/groupChooseDelete.png"),
            manDefault: require("vrv-static/resources/images/contact/manDefault.png"),
            memberCount: 0,
            selectMemberIds: [],
            currentTitle: this.$t('groups.createVideoCon'),
            meetingName: this.$t('groups.videoCon'),
            meetingRemark: "",
            inputSearch: "",
            searchResult: null,
            requiredLength: 20,
            maxSelectLength : 20,
            totalLength: 0,
            checkStatus : false
        };
    },
    props: {
        isInviteMember: true,
        isBurn: false,
        userInfo: Map | Function,
        groupInfo: {
            type: Object,
            default: () => {
                return {
                    userId: "",
                    groupId: ""
                };
            }
        }
    },
    computed: {
        ...mapGetters(["contact_contactList", "chat_objectInfo", "chat_chatList"]),
        buttonType() {
            return this.isLoading ? "is-loading" : "";
        },
        /** 左侧可选列表 */
        memberList() {
            let members = this.chat_objectInfo[this.groupInfo.groupId] || [];
            let list = _.values(members).filter(
                e => e.id && e.isApp !== 1 && e.id !== this.user_account.userId
            );
            this.totalLength = list.length;
            return (
                this.searchResult ||
                _.orderBy(list, ["pingyin"], ["asc"]).slice(0, this.requiredLength)
            );
        },
        /** 右侧已选中列表 */
        selectedList() {
            let resultRightList = this.chat_objectInfo[this.groupInfo.groupId] || [];
            resultRightList = _.values(resultRightList);
            let list = resultRightList.filter(
                e => e.id && e.isApp !== 1 && e.id !== this.user_account.userId
            );
            if(list.length > this.maxSelectLength){
                this.checkStatus = this.selectMemberIds.length >= this.maxSelectLength;
            }else{
                this.checkStatus = this.selectMemberIds.length >= list.length;
            }
            
            return resultRightList.filter(
                e => this.selectMemberIds.indexOf(e.id) > -1
            );
        }
    },
    created() {},
    watch: {
        inputSearch() {
            if (this.inputSearch !== "") return;
            this.searchResult = null;
        }
    },
    methods: {
        /**
         * 滚动加载更多：避免数据量过大造成的加载卡顿
         */
        loadMoreData() {
            if (this.isScrollToBottom(this.$refs.groups))
                this.requiredLength = this.totalLength.length;
        },
        /**
         * 显示联系人的选中状态：默认/选中/删除按钮
         * @param {Object} id- 用户id
         * @param {Boolean} isLeft- 左侧/右侧默认选中状态不同
         */
        isSelectItem({
            id
        }, isLeft) {
            return isLeft ?
                this.selectMemberIds.indexOf(id) > -1 ?
                this.selectImg :
                this.noneImg :
                this.deleteImg;
        },
        getSelectedNum() {
            return `${this.$t('rtc.selectedFriend',{value:this.memberCount,count:this.maxSelectLength})}`;
        },
        /**
         * 改变选中状态 && 添加删除
         * @param {Object} id- 选中item对应的用户id
         */
        changeItemState({
            id
        }) {
            if (this.selectMemberIds.indexOf(id) > -1) {
                this.selectMemberIds.forEach((element, i) => {
                    id === element && this.selectMemberIds.splice(i, 1);
                });
            } else {
                if(this.selectMemberIds.length >= this.maxSelectLength){
                    // this.$t('groups.SelectedMax',{count : maxSelectLength})
                    this.showToast(this.$t('rtc.SelectedMax',{count : this.maxSelectLength}),'is-danger');
                }else{
                    this.selectMemberIds.push(id);
                }
            }
            this.memberCount = this.selectMemberIds.length;
        },
        handleMeeting() {
            let serverInfo = this.$Service.rtc.getMultiServerSync();
            let { turnAddr } = serverInfo;
            let serverUrl = "";
            let serverPort = "";
            let locale = this.$i18n.locale;
            if (turnAddr && turnAddr.indexOf(":") !== -1) {
                serverUrl = turnAddr.split(":")[0];
                serverPort = turnAddr.split(":")[1];
            }
            console.log("zxj::handleMeeting==>", serverInfo);            
      
            const roomID = this.groupInfo.groupId+'-'+new Date().getTime();
            const title = this.meetingName;
            const desc = this.meetingRemark;
            const memberIds = this.selectMemberIds;
            memberIds.push(this.user_account.userId);
            const mode = 'mcalling'; //mcalling | meeting | living
            let fields = [{[this.$t('chat.creator')]: this.user_account.name }];
            if(desc)
            {
                fields.push({[this.$t('chat.remark')]: desc });
            }
            const adminId = this.user_account.userId;
            const startTime = new Date().getTime();
            const stopTime = new Date().getTime() + 60 * 60 * 1000;
            const groupId = this.groupInfo.groupId;

            let detailUrl = {
                subType: 14,
                roomID,
                adminId,
                startTime,
                stopTime,
                mode,
                groupId,
                title ,
                desc,
                serverUrl,
                serverPort
            };
            this.$Service.log('CreateGroupMeeting::handleMeeting>>', JSON.stringify(detailUrl));

            // const request = require('request');
            // const options = {
            //     url: 'https://172.16,16.130:3443?init=true&roomID=111',
            //     headers: {
            //         'User-Agent': 'request'
            //     }
            // };
            // request(options, function (error, response, body) {
            //     console.log('error:', error); // Print the error if one occurred
            //     console.log('statusCode:', response && response.statusCode); // Print the response status code if a response was received
            //     console.log('body:', body); // Print the HTML for the Google homepage.
            // });
            const msgBean = {
                fromId: this.user_account.userId,
                targetId: this.groupInfo.groupId,
                title: this.$t('groups.videoCon'),
                titleColor: "#FFFFFF",
                titleBGColor: "#003557",
                content: title,
                fields:`\"fields\":${JSON.stringify(fields)}` ,
                detailUrl: JSON.stringify(detailUrl),
                limitRange: memberIds,
                creator: this.user_account.name,
                relatedUsers: memberIds,
                isNeedHandleUnread: true
            };
            let msg = new MsgImgTemplate(msgBean);
            
            console.log("createGroupMeeting::handleMeeting1 ==>", msg, this.isBurn);
            rtcplugin.callMutil({
                reqType:1,
                groupId,
                roomId : roomID,
                roomName : title,
                members : memberIds,
                userId : this.user_account.userId,
                userName : this.user_account.name,
                adminId : this.user_account.userId,
                extendJson:{ mode:this.isBurn ? 'single' : 'normal'}
            }, res =>{
                // rtcplugin.joinMeeting({
                //     reqType:3,
                //     groupId,
                //     roomId : roomID,
                //     members : memberIds,
                //     userId : this.user_account.userId,
                //     userName : this.user_account.name,
                //     adminId : this.user_account.userId
                // }, cb => {
                //    console.log('zxj::joinMeeting >> call ',cb);
                // });
                console.log('zxj::callMutil>>',res);
                this.$emit('close');
            });
            // this.$Service.chat.sendMessage(msg.messageObject, result => {
            //     console.log("createGroupMeeting::handleMeeting ==>", result);
            //     if (result.code === 0) {
            //         msg.messageObject.msgId = result.msgId;
            //         this.$store.commit("SET_CHATCONTENT", msg);
            //     }
            //     this.$emit('close');
            // });
        },
        /**
         * 群成员-本地搜索
         */
        searchFromLocal(value) {
            if (!value.trim()) return;
            this.isSearchFinished = false;
            let groupSearchMemberParam = {
                groupId: this.groupInfo.groupId,
                key: value
            };
            this.$Service.search.groupSearchMember(groupSearchMemberParam, resp => {
                console.log("群成员搜索", resp);
                // return resp.members || [];
                this.searchResult = resp.members && resp.members.filter(item =>{
                  return item.id !== this.user_account.userId && item.isApp !== 1
                });
                setTimeout(() => {
                    this.isSearchFinished = true;
                }, 0);
            });
            // this.$Service.search.searchFromLocal({ key: value }, resp => {
            //   console.log("本地搜索", resp);
            //   this.searchResult =
            //     (resp.users &&
            //       resp.users.filter(element => {
            //         return element.id !== this.user_account.userId && element.isUser;
            //       })) ||
            //     [];
            // });
        },
        /**
         * 清空本地搜索输入内容
         */
        clearInput() {
            this.inputSearch = "";
        },
        selectedAll(){
            this.checkStatus = !this.checkStatus;
            if(this.checkStatus){
                let members = this.chat_objectInfo[this.groupInfo.groupId] || [];
                let list = _.values(members).filter(
                    e => e.id && e.isApp !== 1 && e.id !== this.user_account.userId
                );
                list = this.searchResult ||
                _.orderBy(list, ["pingyin"], ["asc"]).slice(0, this.maxSelectLength);
                // let list = this.memberList;
                list.forEach(member =>{
                    this.selectMemberIds.push(member.id);
                });
            }else{
                this.selectMemberIds = [];
            }
            this.memberCount = this.selectMemberIds.length;
            console.log('zxj::createGroup>>');
        },
        /**
         * 顶部提示气泡
         */
        showToast(m, t){
            this.$toast.open({
                duration: 2000,
                message: m,
                position: 'is-top',
                type: t
            });
        },
    }
};
</script>

<style lang="scss">
.create-group-metting {
    width: 480px;

    .group-background {
        width: 100%;
        height: 100%;
        position: absolute;
        z-index: 9;
    }

    .create-group {
        display: flex;

        .create-group-left {
            width: 233px;
            flex: 1;

            .group-title {
                margin: 5px 0px 0px 10px;
                color: $--color-black;
            }

            .search-input {
                margin-left: 10px;
                margin-top: 15px;
                margin-right: 23px;
                .is-small {
                    border-radius: $--border-radius-large;
                }

                .icon {
                    pointer-events: all;
                    height: 30px;
                    top: 0;   // fit xp
                    // right: 0; //fit xp 
                }
            }

            .create-contact-list {
                height: 419px;
                margin-right: 10px;
                margin-top: 10px;
                overflow-x: hidden;

                .avatar-bg {
                    width: 20px;
                    height: 20px;
                }
            }

            .list-title {
                background: #eef4fd;
                font-size: 13px;
                color: $--color-black;
                height: 24px;
                width: 100%;
            }
        }

        .create-group-right {
            width: 233px;
            flex: 1;

            .member-list-area {
                width: 100%;
                height: 350px;

                .member-list-title {
                    color: $--color-black;
                    width: 100%;
                    height: 30px;
                    font-size: 13px;
                    vertical-align: middle;
                    display: table-cell;
                }

                .member-list {
                    overflow-x: hidden;
                    width: 100%;
                    height: 320px;

                    .avatar-bg {
                        width: 20px;
                        height: 20px;
                    }
                }
            }

            .modal-card-footer {
                display: flex;
                justify-content: flex-end;

                .select-all {
                    width: 90px;
                    height: 28px;
                    top: 2px;
                    font-size: 14px;
                    position: relative;
                }
                .button {
                    font-size: 14px;
                    border-radius: $--border-radius-large;
                    width: 70px;
                    height: 28px;
                }
            }

            .create-meeting-name {
                width: 100%;
                height: 30px;
                align-items: center;
                margin-top: 43px;
                display: flex;
                flex: 1;
                font-size: small;
                color: $--color-black;
                @include ellipsis;

                .input {
                    font-size: 13px;
                    height: 30px;
                    margin-left: 5px;
                    margin-right: 25px;
                    padding-right: 0px;
                }
            }

            .create-meeting-remark {
                width: 100%;
                height: 30px;
                align-items: center;
                margin-top: 4px;
                display: flex;
                flex: 1;
                font-size: small;
                color: $--color-black;
                @include ellipsis;

                .input {
                    font-size: 13px;
                    height: 30px;
                    margin-left: 5px;
                    margin-right: 25px;
                    padding-right: 0px;
                }
            }

            .icon {
                display: flex;
                @include get-grey-color(darken-1);
                font-size: 12px;
                width: 30px;
                height: 30px;
                right: 0px;
                top: 0px;
                position: absolute;

                &:hover {
                    background: #8f91b7;
                }
            }
        }
    }

    .modal-card {
        width: 466px;
        border-radius: $--border-radius-base;
    }
}
</style>
