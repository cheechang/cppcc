<template>
    <v-modal @close='closereferMaterials'>
        <div class="box-title" slot="header-top">
          <!-- {{$t('cppcc.referMaterials')}} -->
           <span class="icon-bgc">
                <d-icon class="close-modal" icon='d-icon-circle-close-outline' size="mini" color='#fff' @click="closereferMaterials"></d-icon>
            </span>
        </div>
        <div class="referMaterials-card">
          <webview class="home-url" nodeintegration :src="Url" ></webview>
        </div>
    </v-modal>
</template>

<script>
  export default {
    name:'CppccReferMaterials',
    props:['id'],
    data(){
        return {
            Url:''
        }
    },
    created() {
        this.Url = `file:///${this.$is.isDev?'':__dirname+'/'}pcdist/index.html?window=document&groupId=${this.id}`
        console.log('this.id',this.Url+this.id)
    },
    methods:{
      closereferMaterials(){
        console.log('触发')
        this.$emit('closeRefer')
      }
    }
  }
</script>

<style lang="scss" scoped>
/deep/ .modal-card{
  width: 80%;
  height: 95%;
  header{
    height: 30px;
    color: #fff;
    font-weight: 600;
    text-align: center;
    line-height: 30px;
    background-color: #4a78cc;
      .close-modal{
        padding-right: 10px;
        position: absolute;
        bottom: -5px;
        right: -8px;
      }
  }
  .referMaterials-card{
    background-color: #fff;
    height: 100%;
    width: 100%;
    .home-url {
       width: 100%;
       height: 100%;
       background: #fff;
    }
  }
  .icon-bgc{
    display: inline-block;
    width: 20px;
    height: 20px;
    background-color: #4A78CC;
    border-radius: 50%;
    position: absolute;
    right: 10px;
    top: 5px;
    &:hover{
      background-color:#FF6666 !important;
    }
  }
}
</style>