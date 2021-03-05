<template>
<div class="card-search-list">
  <div class="card-search-subtitle" v-if="list.length!==0">{{subtitle}}</div>
  <div class="card-search-item" v-for="item in list" :key="item.id||item.groupId||item.appID">
    <card-img :ratio="'100%'" :sex="item.gender||sex" :img="item.updateAvatar||item.thumbAvatar||item.avatar||item.appIcon" :name="item.name||item.groupName||item.appName" :isAvatarBg="true" :hasCorner="false"></card-img>
    <div class="card-actions">
      <div class="spacer"></div>
      <div class="card-text" v-if="item.relation">{{item.relation}}</div>
      <div class="card-button-list" v-if="currentState(item, index)" v-for="(buttonItem, index) in buttonLists" :key="index">
        <v-button class="card-button" :title="buttonItem.tooltip" @click="$emit('click-button', item)">
          <div class="button-content">
            <i v-if="!item.tag" :class="`icon icon-action icon-${buttonItem.id}`" v-html="buttonItem.icon"></i>
            <i v-else class="icon icon-load">&#xe6ac;</i>
          </div>
        </v-button>
      </div>
    </div>
  </div>
</div>
</template>
<script>
import CardImg from '../../Common/CardLists/CardImg'
export default {
  props: {
    list: Array,
    buttonLists: Array,
    subtitle: String,
    sex: {
      type: Number,
      default: 0
    },
    isApp: Boolean
  },
  methods: {
    currentState(item, index) {
      if(item.relation) {
        console.log('item.relation::::::::::::::', item.name || item.appName || item.groupName)
        if(item.relation.includes(this.$t('contacts.buddy'))) {
          console.log('好友::::::::::::::')
          return index == 1;
        } else if (item.relation.includes(this.$t('search.group'))) { 
          console.log('群::::::::::::::', index)
          return index == 1;
        } else {
          console.log('自己/应用::::::::::::::')
          return false;
        }
      } else {
        console.log('陌生人::::::::::::::', item.name || item.appName || item.groupName)
        return index == 0;
      }
    }
  },
  components: {
    CardImg
  }
}
</script>
<style lang="scss">
.card-search-list {
  display: flex;
  width: 100%;
  overflow-y: auto;
  flex-wrap: wrap;
  // justify-content: space-between;
  .card-search-subtitle {
    display: flex;
    align-items: center;
    font-size: 14px;
    width: 100%;
    height: 48px;
    color: rgba(0, 0, 0, 0.54);
    font-weight: 600;
    margin-left: 20px;
  }
  .card-search-item {
    width: 25%;
    display: block;
    background-color: #fff;
    border-color: #fff;
    color: rgba(0, 0, 0, 0.87);
    border-radius: 3px;
    min-width: 0;
    position: relative;
    text-decoration: none;
    transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1);
    margin: 7px 20px;
    box-shadow: 0px 2px 1px -1px rgba(0,0,0,0.2), 0px 1px 1px 0px rgba(0,0,0,0.14), 0px 1px 3px 0px rgba(0,0,0,0.12);
    &:hover {
      box-shadow: 0px 7px 8px -4px rgba(0,0,0,0.01), 0px 2px 17px 2px rgba(0,0,0,0.14), 0px 6px 6px 2px rgba(0,0,0,0.12);
      // box-shadow: 0px 7px 8px -4px rgba(0,0,0,0.01), 0px 12px 17px 2px rgba(0,0,0,0.14), 0px 5px 22px 4px rgba(0,0,0,0.12);
    }
    .card-actions {
      align-items: center;
      display: flex;
      white-space: nowrap;
      .card-text {
        font-size: 12px;
        height: 40px;
        display: flex;
        align-items: center;
        margin-left: 5px;
        margin-right: 5px;
        color: rgba(0, 0, 0, 0.54);
      }
      .card-button-list {
        width: 100%;
        display: flex;
        justify-content: flex-end;
        .card-button {
          width: 30px;
          height: 30px;
          padding: 0;
          margin: 5px;
          border-radius: $--border-radius-circle;
          .button-content {
            width: 100%;
            height: 100%;
            display: flex;
            align-items: center;
            justify-content: center;
            .icon-msg {
              font-size: 14px;
              padding-top: 4px;
            }
            .icon-load {
              animation: suerSettLoading 0.7s linear infinite;
            }
          }
          .icon {
            width: 100%;
            height: 100%;
            &:hover {
              position: relative;
              width: 30px;
              height: 30px;
              cursor: pointer;
              &:hover::before {
                background: currentColor;
              }
              &:before {
                border-radius: 50%;
                color: inherit;
                content: '';
                position: absolute;
                left: 0;
                top: 0;
                height: 100%;
                opacity: 0.12;
                transition: 0.3s cubic-bezier(0.25, 0.8, 0.5, 1);
                width: 100%;
              }
            }
          }
        }
      }
      .spacer {
        flex-grow: 1 !important;
      }
    }
    .is-section {
      font-size: 14px !important;
      max-width: 100% !important;
    }
  }
}
</style>

