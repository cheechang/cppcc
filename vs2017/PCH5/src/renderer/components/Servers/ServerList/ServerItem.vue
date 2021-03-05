<template>
    <div class="server-item" @dblclick.stop="dbClick(serverData.userId)">
        <div class="server-icon">
            <div class="msg-icon" v-if="serverData.isMsg && serverData.isOnline">
            </div>
            <i
            v-if ="!serverData.isOnline || isMe"
            class="icon online-icon"
            :title="onlineStatusInfo.name"
            v-html="onlineStatusInfo.icon"
            :style="{color:onlineStatusInfo.color}"
            ></i>
            <v-avatar
                class="avatar-account"
                size="is-small"
                :sex="user_account.gender"
                :src="serverData.avatar"
                :offline="false"
                shape="round"
            ></v-avatar>
        </div>
        <span class="server-name" :class="{'server-name-online':isShowNameOnline}" :title="serverData.server">
            {{serverData.server}}
        </span>
        <i class="icon btn-server-del" v-if="serverData.userId!==user_account.userId" :title="$t('common.delete')" @click.stop="$emit('delItem',serverData.userId)">&#xe650;</i>
    </div>
</template>
<script>
import { getOnlineStatusInfo } from "../../../utils/utils.js";
import { mapGetters } from 'vuex';
export default {
    data(){
      return{
          onlineStatusInfo:{},
      }  
    },
    created(){
      this.getOnlineState();
    },
    props:{
        serverData:Object
    },
    computed:{
        ...mapGetters(['user_account']),
        isMe(){
          return this.serverData.userId === this.user_account.userId
        },
        isShowNameOnline(){
          return this.serverData.isOnline || this.isMe;
        }
    },
    methods:{
        dbClick(userId){
            if(userId === this.user_account.userId) return;
            this.$emit('dblclickItem',userId)
        },
        getOnlineState(){
          if(this.serverData.userId === this.user_account.userId){
            this.onlineStatusInfo = {name:this.$t('auth.currentAccount'),icon:'&#xe699;',color:'#57E26D'};
          }
          else{
            this.onlineStatusInfo = getOnlineStatusInfo(8);
          }
        }
    }
}
</script>
<style lang="scss" scoped>
.server-item{
    height: 103px;
    width: 150px;
    justify-content: center;
    display: flex;
    flex-direction: column;
    align-items: center;
    position: relative;
    margin-left: 15px;
    transition: 0.5s cubic-bezier(0.5, 0.8, 0.5, 1);
    border-radius: 10px;
    //background:rgba(118, 122, 130,0.45);
    &:hover {
        background: rgba(181, 187, 197, 0.3);
        .btn-server-del {
            display: block !important;
        }
    }
    .msg-icon{
        width: 10px;
        height: 10px;
        border-radius: 50%;
        background-color: red;
        position: absolute;
        right: -5px;
        z-index: 10;
    }
    .server-icon{
        position: relative;
        .online-icon{
            font-size: 16px;
            position: absolute;
            bottom: -7px;
            right: -7px;
            z-index: 10;
        }
    }
    .server-name{
        margin-top: 5px;
        color: #fff; 
        white-space: nowrap;
        text-overflow: ellipsis;
        overflow: hidden;
        max-width: 125px;
        font-size: 14px;
        color: #aaa;
    }
    .server-name-online{
        color:#fff !important;
    }
    .btn-server-del {
        display: none;
        position: absolute;
        right: 0px;
        top: 0px;
        font-size:$--font-size-big;
        color:#fff;
      &:hover {
        cursor:pointer;
      }
    }
}
</style>