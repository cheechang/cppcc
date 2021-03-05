import { mapGetters } from 'vuex';
/**
 * 通讯录模块 公共变量、方法、vuex数据
 */
const mixin = {
  data() {
    return {
      
    }
  },
  directives: {
    
  },
  computed: {
    ...mapGetters(['user_groupToneList', 'user_account'])
  },
  methods: {
    /**
     * 从SDK获取群提示音的信息
     */
    getGroupSoundFromSDK(groupId) {
      this.$Service.group.getGroupBeepTone({groupId}, resp => {
        this.getGroupBeepToneHandler(resp, groupId)
      });
    },
    getGroupBeepToneHandler(info, groupId) {
      if (info.code !== 0) {
        return;
      }
      console.log('后台获取的提示音:::', info)
      let toneInfo = (info.toneInfo && this.formatToneInfo(info.toneInfo)) || 'push6';
      console.log('vuex的情况::', this.user_groupToneList);
      let param = {
        settings: [{
          key: 'groupSounds',
          value: ''
        }]
      }
      if (this.user_groupToneList) {
        //  vuex存在，则说明数据库中存在，只需要更新
        let toneInfoList = {...this.user_groupToneList};
        this.$set(toneInfoList, groupId, toneInfo);
        this.$store.dispatch('SET_GROUPTONES', toneInfoList);
        param.settings[0].value = JSON.stringify(toneInfoList);
        this.$Service.user.updateLocalSetting(param, resp => {
          console.log('更新群提示音至本地 ', resp.code);
        });
        return;
      }

      //  不存在则需要添加到本地数据库
      let newToneInfo = {[groupId]: toneInfo};
      // 更新vuex
      this.$store.dispatch('SET_GROUPTONES', newToneInfo);
      // 添加本地数据库设置信息
      param.settings[0].value = JSON.stringify(newToneInfo)
      this.$Service.user.addLocalSetting(param.settings, resp => {
        console.log('添加群提示音至本地 ', resp.code);
      });
    },
    /**
     * 设置群提示音
     */
    setGroupTone(groupId, toneInfo) {
      return new Promise((resolve, reject) => {
        this.$Service.group.setGroupBeepTone(
        {
          groupId,
          toneInfo: toneInfo + '.mp3'
        }, resp => {
            if (resp.code !== 0) {
              reject();
            }
            resolve();
          }
        )
      })
    },
    /**
     * 更新群提示音至本地
     */
    updateGroupToneToLocal(toneInfoList) {
      let newToneInfo = JSON.stringify(toneInfoList);
      this.$Service.user.updateLocalSetting({
        settings: [{
          key: 'groupSounds',
          value: newToneInfo
        }]
      }, resp => {
        if (resp.code !== 0) {
          console.log('更新群提示音至本地失败');
        }else{
          console.log('更新群提示音至本地成功');
        }
      })
    },
    // 删除群本地提示音
    deleteGroupLocalTone(groupId){
      if (this.user_groupToneList && this.user_groupToneList[groupId]){
        let toneInfoList = JSON.parse(JSON.stringify(this.user_groupToneList));
        delete toneInfoList[groupId];
        if (Object.keys(toneInfoList).length === 0){
          // vuex 删完后 toneInfoList没有内容 删除本地设置
          this.$Service.user.deleteLocalSetting(['groupSounds'], resp => {
            console.log('删除本地群设置音字段')
            console.log('删除结果：：',resp)
          })
        }else{
          this.$Service.user.updateLocalSetting({
              settings: [{
                key: 'groupSounds',
                value: JSON.stringify(toneInfoList)
              }]
            },
            resp => {
              if (resp.code === 0) {
                this.$store.dispatch('SET_GROUPTONES', toneInfoList)
                console.log('更新群提示音至本地成功,当前列表为：', this.user_groupToneList);
              } else {
                console.log('更新群提示音至本地失败');
              }
            }
          );
        }
      }else{
        console.log('vuex没有该群提示音信息，不予处理')
      }
    },
    /**
     * 格式化群提示音 修正提示音信息
     */
    formatToneInfo(toneInfo){
      return toneInfo.split('.')[0];
    },
    /**
     * 请求添加群
     * @param {String} groupId - 群ID
     */
    addGroup(groupId) {
      this.$dialog.prompt({
        message: this.$t('search.verfication')+':',
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: {value: this.$t('search.iAm') + this.user_account.name, maxlength: 60},
        required: false, // 验证信息选填
        onConfirm: value => {
          let addGroupParam = {groupId, verify_info: value};
          this.$Service.group.addGroup(addGroupParam, resp=>{
            this.$Service.log(`添加群请求：code:${resp.code},id:${groupId}`);
            let toastMsg = {message: this.$t('groups.groupRequestSent'),type: 'is-success'}
            if (resp.code !== 0) {
              toastMsg = {message: this.$t(`ErrorCode.${resp.code}`),type: 'is-danger'}
            }
            this.$toast.open(toastMsg);
          });
        }
      });
    }


  }
};
export default mixin;
