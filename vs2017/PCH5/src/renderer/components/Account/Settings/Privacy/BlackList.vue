<template>
  <div class="black-list cutting-line-before">
    <div>{{$t('account.blockedList')}}：</div>
    <div class="open-black-list">
      <div class="clear-chart-btn theme-botton" @click="openBlackList">{{$t('account.blockedList')}}</div>
    </div>
    <v-modal v-if="isShowModal" :cardStyle="cardStyle" @close="isShowModal=false">
      <div class="black-box">
        <div class="balck-title theme-bgc_font">
          <span>{{$t('account.blockedList')}}</span>
          <i class="icon" @click="isShowModal=false">&#xe650;</i>
        </div>
        <v-card-list class="black-list-box">
          <v-card
            v-for="(item, index) in blackList"
            :key="index"
            :title="item.name"
            class="blak-card"
          >
            <v-avatar
              size='is-small'
              :src='item.thumbAvatar||item.avatar'
              :offline="false" 
              shape="round"
              slot="leftAvatar"
            >
            </v-avatar>
            <div class="black-options" slot="right">
              <i class="icon" @click="delBlack(item, index)">&#xe677;</i>
            </div>
          </v-card>
        </v-card-list >
      </div>
    </v-modal>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
export default {
  data() {
    return {
      isShowModal: false,
      blackList: [],
      cardStyle: {
        width: '300px',
        height: '450px',
        borderRadius: '4px'
      }
    }
  },
  computed: {
    ...mapGetters(['user_account'])
  },
  created() {
    
  },
  methods: {
    openBlackList() {
      this.blackList = [],
      this.getBlackList();
      this.isShowModal = true;
    },
    delBlack(item, index) {
      this.$dialog.confirm({
        confirmText: this.$t('common.confirm'),
        cancelText: this.$t('common.cancel'),
        message: this.$t('account.sureRemove'),
        onConfirm: () => {
          this.$Service.log(`移除黑名单入参:::${item.id}`)
          this.$Service.contact.removeBlackList(
            [item.id],
            resp => {
              this.$Service.log(`移除黑名单返回code:::${resp.code}`)
              if (resp.code === 0) {
                this.$delete(this.blackList, index);
                this.$toast.open({message: this.$t('account.removeSucc'), type: 'is-success'})
              }
            }
          )
        }
      });
    },
    getBlackList() {
      this.$Service.contact.getBlackList(
        null,
        resp => {
          if (resp.code === 0) {
            this.$Service.log(`获取黑名单列表返回code:::${resp.code}`)
            resp.userIds.forEach(element => {
              this.$Service.search.getUserInfo(
                {userId: element},
                resp => {
                  this.blackList.push(resp.users);
                }
              )
            })
          }
        }
      )
    }
  }
}
</script>
<style lang="scss" scoped>
.black-list{
  .open-black-list{
    margin-top: 13px;
    padding-left: 80px;
  }
  .black-box{
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
  }
  .balck-title{
    padding: 5px 9px;
    display: flex;
    justify-content: space-between;
  }
  .black-list-box{
    height: 100%;
    overflow-y: auto;
    .blak-card{
      border-bottom: 1px solid $--border-color-blue;
      .black-options{
        width: 30px;
        display: flex;
        justify-content: space-between;
        align-items: center;
        i{
          &:hover{
            color:$--color-danger;
          }
        }
      }
    } 
  }
}
</style>
