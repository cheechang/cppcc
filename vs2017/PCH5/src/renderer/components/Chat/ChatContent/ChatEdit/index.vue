<template>
  <div>
    <chat-edit v-if="editType !== 3"  :rewriteText='rewriteText' 
                                      :isEncryptMsg ="isEncryptMsg" 
                                      :isBurn ='isBurn'
                                      :isDelay="isDelay"
                                      :atName="atName" 
                                      :isOpen="isOpen" 
                                      :chatType="chatType" 
                                      :userInfo="userInfo" 
                                      :id="id" 
                                      :rightAtId="rightAtId"
                                      @changeEditType="editType = 3"
                                      @updateEncryptMsg='_updateEncryptMsg'
                                      @updateBurnMsg='_updateBurnMsg'
                                      @updateDelayMsg='_updateDelayMsg'>
    </chat-edit>
    <app-edit v-else @changeEditType="editType = 1" :id="id"></app-edit>
  </div>
</template>
<script>
import chatEdit from './ChatEdit.vue';
import appEdit from './appEdit.vue';
export default {
  data() {
    return {
      editType: 1
    }
  },
  
  mounted() {
    this.editType = this.chatType;
  },

  components: {
    chatEdit,
    appEdit
  },

  methods: {
    _updateEncryptMsg(bool) {
      this.$emit('updateEncryptMsg', bool)
    },
    _updateBurnMsg(bool) {
      this.$emit('updateBurnMsg', bool)
    },
    _updateDelayMsg(bool) {
      this.$emit('updateDelayMsg', bool)
    }
  },
  props: {
    isExpendSidebar: Boolean,
    isOpen: Boolean,
    chatType: Number,
    id: String,
    userInfo: Map | Function,
    atName: Object | String,
    rewriteText: Object | String,
    isEncryptMsg: Boolean,
    isBurn:Boolean,
    isDelay: Boolean,
    rightAtId: Object | String
  }
}
</script>
