<template>
  <div class="settings-invite-friend" v-if="isCanCreateInviteCode">
    <v-modal v-if="openToast" cardSize="invite-code-config"  @close="isShowDelayBox= false">
      <create-invite-code @update-invite-code="updateInviteCode" @close="openToast=false"></create-invite-code>
    </v-modal>
    <div class="require-config">
      <i class="icon share-icon" :title="$t('common.share')" @click="createQrImg">&#xe6d9;</i>
      <i class="icon config-icon" :title="$t('user.setting')" @click="openToast=true">&#xe653;</i>
    </div>
    <qr-code class="invite-code-info" id="invite-code-info" :isShowDetail="false" :gender="6" :text="computedQrcodeLink" :width="180" :height="180">
      <div class="qrcode-invite-info">
        <div class="verify-code">
          <span>{{$t('user.inviteCode') + '：'}}</span>
          <span class="infos code" v-cloak>{{ computedVerifyCode }}</span>
        </div>
        <div class="effective-time">
          <span>{{ $t('user.expiryDate') + '：' }}</span>
          <span class="infos time" v-cloak>{{ $t('user.endDate') + computedInvalidTime }}</span>
        </div>
        <div class="effective-count">
          <span>{{ $t('user.maxFriends') + '：' }}</span>
          <span class="infos count" v-cloak>{{ computedEffectiveCount }}</span>
        </div>
      </div>
    </qr-code>
    <!-- <div class="invite-setting-btn">
      <v-button type="is-primary" @click="openToast=true">{{'设置'}}</v-button>
      <v-button type="is-primary" @click.native="createQrImg">{{'分享'}}</v-button>
    </div> -->
  </div>
</template>
<script>
import config from '../../.././../../comm/config';
import { getInviteCodeLink } from '../../../Group/ChatGroupInfo/QrLink.js';
import QrCode from '../../../Group/ChatGroupInfo/QrCode.vue';
import CreateInviteCode from './CreateInviteCode'
const moment = require('moment');
const { clipboard, nativeImage } = require('electron')
import html2canvas from 'html2canvas';
import { mapGetters } from 'vuex'
export default {
  data() {
    return {
      verifyCode: {},
      openToast: false,
      isCanCreateInviteCode: false
    }
  },
  components: {
    QrCode,
    CreateInviteCode
  },
  computed: {
    ...mapGetters(['user_account', 'user_serverHost']),
    computedQrcodeLink() {
      return getInviteCodeLink({
        host: this.$initInfo.mark=='inte'?'http://im.linkdood.com':undefined,
        serverhost: this.user_serverHost,
        code: this.verifyCode && this.verifyCode.inviteCode
      })
    },
    computedVerifyCode() {
      return this.verifyCode && this.verifyCode.inviteCode
    },
    computedInvalidTime() {
      if (!this.verifyCode) return
      // let diff = (this.verifyCode.invalidTime - this.verifyCode.createdAt)/1000/3600/24
      // console.log('diff:::', diff)
      return this.getDateDiff(parseInt(this.verifyCode.invalidTime)) + '（' + this.verifyCode.diffDay
    },
    computedEffectiveCount() {
      return this.verifyCode && this.verifyCode.effectiveCount
    }
  },
  mounted() {
    let data = {
      effectiveCount: 20,
      effectiveSeconds: 2*24
    }
    this.$Service.contact.canMakeVerifyCode(null, resp => {
      console.log('生成邀请码权限:::', resp)
      if(resp.code === 0){
        this.isCanCreateInviteCode = true
        this.getInviteCodeResult(data)
      }else if(resp.code === 100001717){
        this.isCanCreateInviteCode = false
        this.$toast.open({ message: this.$t('user.denied'), type: 'is-info' })
      }
    })
  },
  methods: {
    async updateInviteCode({ effectiveCount,effectiveSeconds }) {
      console.log(effectiveCount, effectiveSeconds)
      await this.getInviteCodeResult({ effectiveCount, effectiveSeconds })
      this.openToast = false
    },
    getInviteCodeResult({ effectiveCount=20,effectiveSeconds=2*24 }) {
      let param = {
        createUserID : this.user_account.userId,
        effectiveSeconds : effectiveSeconds*60*60+'',
        digit : 4,
        effectiveCount : effectiveCount,
      }
      console.log('param::::', JSON.stringify(param))
      this.$Service.contact.makeVerifyCode(param, resp => {
        if( resp.code === 0 ){
          console.log("makeVerifyCode:::", resp)
          this.verifyCode = resp.verifyCode && JSON.parse(resp.verifyCode)
          this.$Service.log('生成邀请码::::failed');
          if (!this.verifyCode) return
          this.$Service.log(`生成邀请码::::有效次数：${this.verifyCode.effectiveCount}--截止日期：${this.verifyCode.invalidTime}--创建日期：${this.verifyCode.createdAt}`);
          if (effectiveSeconds/24 < 1) {
            this.verifyCode.diffDay = effectiveSeconds+this.$t('user.hours')+'）'
          } else if(effectiveSeconds/24 < 2) {
            this.verifyCode.diffDay = effectiveSeconds/24+this.$t('user.day')+'）'
          } else {
            this.verifyCode.diffDay = effectiveSeconds/24 + this.$t('user.day') + this.$t('user.plural');
          }
          if (effectiveCount===0) {
            this.verifyCode.effectiveCount = this.$t('user.unlimited')
          } else {
            this.verifyCode.effectiveCount = effectiveCount + this.$t('user.members')
          }
        }else{
          console.error('makeVerifyCode failed ', resp.code);
        }
      })
    },
    createQrImg(event) {
      event.preventDefault();  
      html2canvas(document.getElementById("invite-code-info"),{allowTaint: true}).then((canvas)=> {
        this.$toast.open({ message: this.$t('contacts.copied'), type: 'is-info' })
        let qrcodeDataURL = canvas.toDataURL();
        let qrcodeImg = nativeImage.createFromDataURL(qrcodeDataURL)
        clipboard.writeImage(qrcodeImg)
      });
    },
    getDateDiff(nS) {
      let now =  moment(nS)
      let old = moment()
      let diffDay = Math.abs(now.dayOfYear() - old.dayOfYear());
      return now.format('YYYY-MM-DD HH:mm')
    }
  }
}
</script>
<style lang="scss">
.settings-invite-friend {
  width: 100%;
  height: 100%;
  font-size: 14px;
  border-radius: 3px;
  background: #fff;
  overflow: hidden;
  display: flex;
  justify-content: center;
  .require-config {
    display: flex;
    justify-content: flex-end;
    margin-right: 10px;
    margin-top: 10px;
    position: absolute;
    z-index: 1;
    right: 20px;
    top: 20px;
    .icon {
      color: #777;
      &:hover {
        color: #000;
      }
    }
    .config-icon {
      font-size: 22px;
      margin-left: 15px;
    }
    .share-icon {
      font-size: 30px;
    }
  }
  .invite-code-config {
    height: 220px;
    width: 380px;
    border-radius: $--border-radius-base;
    overflow: hidden;
    display: flex;
    .modal-card-body {
      background: #f3f6f8;
    }
  }
  .invite-code-info {
    width: fit-content;
    height: 100%;
    padding: 8px;
    display: flex;
    justify-content: center;
    align-items: center;
    background: #fff;
    flex-direction: column;
    .qrcode-invite-info {
      text-align: center;
      .infos {
        font-weight: bold;
      }
      .verify-code {
        margin-top: 10px;
        margin-bottom: 10px;
        display: flex;
        justify-content: center;
      }
      .effective-time {
        margin-bottom: 2px;
        display: flex;
      }
      .effective-count {
        display: flex;
      }
    }
    .qrcode-logo {
      height: 60px !important;
      width: 60px !important;
      margin: auto;
      // top: -67px; //s 导航栏高度
      img {
        border-radius:$--border-radius-base; 
      }
    }
  }
  .invite-setting-btn {
    display: flex;
    align-items: center;
    justify-content: center;
    position: absolute;
    border: 0;
    bottom: 40px;
    margin: auto;
    width: 100%;
    .button {
      margin-right: 10px;
    }
  }
}
[v-cloak] {
  display: none;
}
</style>
