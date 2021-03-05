<template>
    <div class="server-pre-login">
        <v-avatar class="logo server-login-logo" :sex="6" :shape="'round'" :src="avatar"></v-avatar>
        <v-tip
            class="server-login-tip"
            :tipLabelMsg="errorMsg"
            :isLabelTip="isErrorBox"
            :tipPosition="'is-top'"
            @close="isErrorBox = false"
        >
            <v-input
                class="inputs auth-input"
                hasLine
                hasLabel  
                v-model="server"
                :isAuth="true"
                :inputLineSite="'-1px'"
                :customType="'input-size'"
                :isBorder="false"
                :isBulma="false"
                :maxlength="50"
                :placeholder="$t('auth.server')"
                @keyup-enter="next"
            >
            </v-input>
        </v-tip>
        <v-btn
            class="auth-button server-login-btn"
            :size="'v-button--max_width'"
            :disable="isDisable"
            :type="lodingState"
            @click="next"
            >{{$t('auth.next')}}
        </v-btn>
    </div>
</template>
<script>
import vBtn from '../../Auth/common/button.vue';
import vTip from '../../Auth/common/tooltip.vue';
import { getErrorMsg } from '../../../utils/utils.js';
import LoginTypeMixins from '../../Auth/Login/LoginTypeMixins'
import { mapGetters } from 'vuex';
export default {
    mixins:[LoginTypeMixins],
    components: {
        vBtn,
        vTip
    },
    data() {
        return {
            server: '',
            isLoading: false,
            errorMsg: '',
            isErrorBox: false,
            avatar: require('vrv-static/resources/images/common/logo.png')
        }
    },
    methods:{
        next(){
            console.log('next:::');
            if (this.isLoading) {
                return;
            }
            this.isLoading = true;
            this.$Service.auth.prelogin({ server: this.server }, this._preloginHandler);
        },
        _preloginHandler(resp){
            console.log('_preloginHandler_resp:',resp)
            if (resp.code !== 0 || resp === undefined || resp.json === undefined || resp.json === '') {
            this.isLoading = false;
            //this.isActing = false;
            this.errorMsg = getErrorMsg(resp.code);
            this.isErrorBox = true;
            console.log(this.isErrorBox);
            return;
            }
            let obj = JSON.parse(resp.json);
            let multipleServers = Object.values(this.auth_multipleServers);
            console.log('multipleServers:',multipleServers); 
            if(multipleServers.some((el)=>{
                return el.elogo === obj.elogo;
            })){
                this.$toast.open({
                    message: this.$t('auth.serverHasLogin'),
                    type: 'is-danger'
                });
                this.isLoading = false;
                console.log('this.isLoading:',this.isLoading)
                return;
            }
            let infos = {server:this.server,elogo:obj.elogo,loginTypes:[]};
            if(this.$oauth){
                this.$oauth.getLoginType(null, resp=>{
                    infos.loginTypes = this.parseOauthResp(resp,obj);
                    this.$emit('pre-login-succ',infos)
                })     
            }
            else{
                infos.loginTypes = this.getLoginTypeByServer(obj);
                this.$emit('pre-login-succ',infos)
            }  
        }
    },
    computed:{
        ...mapGetters([
            'auth_multipleServers'
        ]),
        isDisable() {
            let regexp = /[ \f\n\r\t\v]/;
            return this.server === '' || regexp.test(this.server);
        },
        lodingState() {
            return this.isLoading ? "is-loading" : "";
        }
    }
}
</script>
<style lang="scss" scoped>
@import '../../Auth/_auth';
.server-pre-login{
    height: 100%;
    width: 280px;
    display: flex;
    flex-direction: column;
    .server-login-tip{
        top:125px;
        /deep/ .input{
            font-size: $--font-size-mid;
        }
    }
    .server-login-logo{
        top:50px;
    }
    .server-login-btn{
        top:140px;
    }
    
}

</style>