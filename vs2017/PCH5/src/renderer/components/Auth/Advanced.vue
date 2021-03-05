<template>
  <div class="advanced">
    <v-field class="fields">
      <v-auto-complete
        ref="vautocomplete"
        v-model="countryArea"
        :data="filteredOptionsArray1"
        :originArray="originArray"
        hasLine
        :isBorder="false"
        :openOnFocus="true"
        :menuCanShow="isOptionShow"
        :isAuth="true"
        @change="active => isOptionShow = !active"
        @select="selected"
      >
      </v-auto-complete>
      <i class="icon icon-option" :class="{'scale-icon': !isOptionShow}" @click.self.stop="isOptionShow=!isOptionShow">&#xe77a;</i>
    </v-field>
    <v-btn
      class="auth-button"
      :size="'v-button--max_width'"
      :type="buttonType"
      :disable="!isDisable"
      @click="confirm"
    >{{$t('common.confirm')}}</v-btn>
  </div>
</template>
<script>
import { mapGetters } from 'vuex';
import vBtn from './common/button.vue';
export default {
  components: {
    vBtn
  },
  data() {
    return {
      countryArea: '',
      isOptionShow: true,
      nationCode: ''
    }
  },
  computed: {
    ...mapGetters(['auth_server', 'auth_nationCode']),
    buttonType() {
      return this.isLoading ? 'is-loading' : '';
    },
    filteredOptionsArray1() {
      let areaCode = this.$i18n.messages[`${this.$i18n.locale}`].AreaCode;
      let optionsArray = [];
      if (!this.countryArea) return;
      _.filter(areaCode,(code,name) => {
        if(name.toUpperCase().indexOf(this.countryArea.toUpperCase()) >= 0||code.indexOf(this.countryArea) >= 0) {
          optionsArray.push(name)
        }
      })
      return optionsArray;
    },
    originArray() {
      return Object.keys(this.$i18n.messages[`${this.$i18n.locale}`].AreaCode)
    },
    isDisable() {
      return this.originArray.indexOf(this.countryArea) > -1
    }
  },
  watch: {
    isOptionShow(val) {
      val ? this.$emit('is-nodrag', false) : this.$emit('is-nodrag', true)
    }
  },
  created() {

    let areaCode = this.auth_nationCode === '' ? this.$Service.config.getSystemNationCode() : this.auth_nationCode
    console.log('code:::', areaCode);
    this.initNationOption(areaCode);
    document.onkeydown = e => {
      if (this.isLoading || this.server === '' || !this.isOptionShow) {
        //  登录中则不响应
        return;
      }
      if (e.keyCode !== 13) {
        return;
      }
      this.confirm();
    }
  },
  methods: {
    initNationOption(areaCode) {
      _.filter(this.$i18n.messages[`${this.$i18n.locale}`].AreaCode,(code,name) => {
        if(name.indexOf(areaCode) >= 0||code.indexOf(areaCode) >= 0) {
          this.nationCode = areaCode
          console.log(code, name, areaCode);
          this.countryArea = name;
        }
      })
    },
    selected({val, index}) {
      this.$Service.log(`选择国家码:::${this.nationCode}`)
      this.countryArea = val;
      this.nationCode = this.$i18n.messages[`${this.$i18n.locale}`].AreaCode[val]
    },
    confirm() {
      this.$store.commit('SET_NATIONCODE', this.nationCode);
      this.$router.go(-1);
    }
  }
}
</script>
<style lang="scss" scoped>
@import './_auth';
.advanced{
  display: flex;
  flex-direction: column;
  width: 280px;
  height: auto;
  /deep/ input{
    font-size: $--font-size-mid;
    height: 2.6em;
    padding-left: 10px;
    border: none !important;
  }
  /deep/ .input-line{
    bottom: -3px;
  }
  .input[disabled]{
    background-color: none !important;
  }
  .fields {
    margin-bottom: 0;
    height: 39px;
    position: relative;
    border-bottom: 1px solid $--border-color-blue !important;
    display: inline-flex;
    .icon-option {
      position: absolute;
      right: 0;
      top: 13px;
      @include z-index(btn);
    }
    .auth-icon{
      position: absolute;
      padding-top: 13px;
      padding-left: 6px;
      @include z-index(image);
    }
  }
}
</style>
