<template>
  <transition name="list">
    <div class="group-card-info" v-if="isLoadFinished&&userId==activeIndex" :style="{top:position-80+'px'}" @contextmenu.stop @dblclick.stop @dragstart.prevent>
      <v-avatar class="info-img" :src="thumbAvatar||cardInfo.thumbAvatar" :sex="gender||cardInfo.gender" size=""></v-avatar>
      <div class="info-user">
        <div class="card-operate" v-if="user_account.userId!==userId">
          <div class="operate-btn">
            <v-tooltip class="operate-tooltip" type="is-light" position="is-top" :lable="$t('organizations.addFriend')" always></v-tooltip>
            <i class="icon add-friend" v-if="!contact_contactList[userId]" @click="addFriend">&#xe62c;</i>
          </div>
          <div class="operate-btn" v-if="allowChat">

            <v-tooltip class="operate-tooltip" type="is-light" position="is-top" :lable="$t('contacts.message')" always></v-tooltip>
            <i class="icon send-msg" @click="startChat(cardInfo, 1)">&#xe664;</i>
          </div>
        </div>
        <a class="user-name" :title="remark||cardInfo.name" @click="expendMemberInfo">{{remark||cardInfo.name}}</a>
        <div class="user-phone">
          <p>{{ $t('groups.phone') }}</p>
          <div class="texts">{{cardInfo.phone}}</div>
        </div>
        <div class="user-email">
          <p>{{ $t('contacts.email') }}</p>
          <div class="texts">{{cardInfo.email}}</div>
        </div>
        <div class="user-job">
          <p>{{ $t('organizations.position') }}</p>
          <div class="texts">{{ $t('groups.empty') }}</div>
        </div>
      </div>
    </div>
  </transition>
</template>
<script>
import { mapGetters } from 'vuex';
import _ from 'lodash';
import ContactMixin from '../../Contact/ContactMixin';
export default {
  mixins: [ContactMixin],
  data() {
    return {
      cardInfo: {
        phone: '',
        email: ''
      },
      buddyCardIndex: -1,
      chatCardIndex: -1,
      isLoadFinished: Boolean,
      activeIndex: -1,
      position: '',
      remark: '',
      thumbAvatar: '',
      gender: ''
      // isApp: false
    };
  },
  props: {
    userId: Number | String,
    senderId: Number | String
  },
  watch: {
    activeIndex(value) {
      if(value===-1) return;
      this.isContactToDo();
    }
  },
  computed: {
    ...mapGetters(['contact_contactList', 'contact_groupExtension']),
    allowChat() {
      let extend = this.contact_groupExtension[this.$route.query.id];
      let isFriend = this.contact_contactList[this.userId];
      return (extend && extend.disallowStrangerChat && extend.disallowStrangerChat == 0) || isFriend
    }
  },
  created(){
    this.$signalMonitor.$on('sendPosition', this.createCard);
  },
  beforeDestroy() {
    this.$signalMonitor.$off('sendPosition', this.createCard);
  },
  methods: {
    expendMemberInfo() {
      this.cardInfo.remark = this.remark;
      this.$signalMonitor.$emit('expendMemberInfo', this.cardInfo);
      this.activeIndex = -1
    },
    /**
     * 判断是否是好友获取对应用户信息
     */
    isContactToDo() {
      this.isLoadFinished = false;
      // this.isApp ? this.getAppInfo() :
        this.contact_contactList[this.userId] ? this.getContactInfo() : this.getUserInfo();
    },
    /**
     * 生成当前卡片位置
     * @param {Number} position - y坐标
     * @param {Number} activeIndex - 选中卡片id
     */
    createCard({position, activeIndex, remark, thumbAvatar, gender}) {
      if (activeIndex !== this.userId) return;
      this.remark = remark;
      this.thumbAvatar = thumbAvatar;
      this.gender = gender;
      // this.isApp = value.isApp;
      this.position = position;
      this.activeIndex = activeIndex;
    },
    /**
     * 获取好友信息
     * 
     */
    getContactInfo() {
      this.$Service.contact.getContactInfo({ userId: this.userId }, resp => {
        console.log('获取好友信息', resp);
        this.cardInfo = resp;
        this.cardInfo.phone =
          (resp.phones[0] && resp.phones[0].substring(4)) || this.$t('groups.empty');
        this.cardInfo.email = resp.emails[0] || this.$t('groups.empty');
        this.isLoadFinished = true;
      });
    },
    /**
     * 获取陌生人信息
     * 
     */
    getUserInfo() {
      // this.$Service.search.getUserInfoSync({ userId: this.userId }, resp=>{
      this.$Service.search.getUserInfo({ userId: this.userId }, resp => {
        console.log('获取陌生人信息', resp);
        this.cardInfo = resp.users;
        this.cardInfo.phone =
          (resp.users.phones&&resp.users.phones[0] && resp.users.phones[0].substring(4)) || this.$t('groups.empty');
        this.cardInfo.email = (resp.users.emails&&resp.users.emails[0]) || this.$t('groups.empty');
        this.isLoadFinished = true;
      });
    },
    // getAppInfo() {
    //   this.$Service.user.getAppInfo({ appId: this.userId }, resp => {
    //     console.log('获取App信息', resp);
    //   })
    // },
    addFriend() {
      this.$dialog.prompt({
        message: this.$t('search.verfication')+':',
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        inputAttrs: {
          value: this.$t('search.iAm') + this.user_account.name
        },
        required: false,
        onConfirm: value => {
          let addContactParam = {
            userId: this.userId,
            info: value
          };
          this.$Service.contact.addContact(addContactParam, resp => {
            if (resp.code !== 0) {
              this.$toast.open({
                message: this.$t(`ErrorCode.${resp.code}`),
                type: 'is-danger'
              });
            } else {
              this.$Service.contact.getVerifyType({userId: this.userId}, resp => {
                console.log('获取对方好友验证方式', resp)
                let verifyInfo = {
                  1: this.$t('groups.requestSent'),
                  3: this.$t('contacts.chatNow')
                }
                console.log(resp.type,verifyInfo[resp.type])
                this.$toast.open({message: verifyInfo[resp.type], type: 'is-success'})
              })
            } 
          });
        }
      });
    }
  }
};
</script>
<style lang="scss">
@mixin card-flex {
  flex: 1;
  display: flex;
  align-items: center;
  font-size: 12px;
  @include get-grey-color(darken-1);
  font-weight: 500;
}
.group-card-info {
  position: fixed;
  right: 209px; // 防止临界点 导致移入不到card上
  box-shadow: $--box-shadow-elevation;
  width: 280px;
  height: 120px;
  display: flex;
  align-items: center;
  background: #fff;
  border-radius: $--border-radius-base;
  z-index: 9;
  overflow: hidden;
  // border-bottom-left-radius: 60px;
  // border-top-left-radius: 60px;
  .info-img {
    width: 120px;
    height: 120px;
  }
  .info-user {
    // flex: 1;
    width: 160px;
    display: flex;
    flex-direction: column;
    padding: 10px;
    user-select: initial;
    .card-operate {
      display: flex;
      position: absolute;
      top: 12px;
      right: 24px;
      .operate-btn {
        transition: all 0.3s ease;
        .operate-tooltip {
          display: none;
        }
        .icon {
          height: 100%;
          @include get-grey-color(darken-1);
          line-height: 24px;
        }
        .send-msg {
          font-size: 18px;
        }
        &:hover .operate-tooltip {
          display: block;
        }
      }
    }
    .user-name {
      width: 90px;
      @include ellipsis;
      text-decoration:none;
      color: $--color-black;
      text-decoration-skip: ink;
      &:hover{
        text-decoration:underline;        
      }
    }
    .texts {
      flex: 1;
      color: $--color-black;
      @include ellipsis;
    }
    p {
      margin-right: 8px;
    }
    .user-phone {
      @include card-flex;
      margin-top: 10px;
    }
    .user-email {
      @include card-flex;
    }
    .user-job {
      @include card-flex;
    }
  }
}
</style>
