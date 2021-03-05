<template>
  <div ref="wrap"
    class="atwho-wrap"
    @compositionstart="handleCompositionStart"
    @compositionend="handleCompositionEnd"
    @input="handleInput()"
    @keydown="handleKeyDown"
    @keyup="handleKeyUp"
  >
  <transition name="slide-up">
    <div  v-if="atwho" class="atwho-panel">
      <div  v-if="list" class="tab_complete_ui_header">
            <span id="chat_input_tab_ui_header_query">
              <!-- 选择要<strong>@</strong>的成员 -->
              {{$t('chat.selectAtMember')}}
            </span>
            <span class="header_help">
              <strong>↑</strong> <strong>↓</strong>  {{$t('chat.atShortCut')}}
              <span class="left_margin">
                <strong>↵</strong> {{$t('chat.atSeletc')}}
              </span>
              <span class="left_margin">
                <strong>esc</strong> {{$t('chat.atClose')}}
              </span>
            </span>
          </div>
      <div class="atwho-inner">
        <keep-alive>
        <div class="atwho-view"  v-if="list">

          <ul class="atwho-ul">
            <li v-for="(item, index) in list"
                class="atwho-li"
                :class="isCur(index) && 'atwho-cur'"
                :ref="isCur(index) && 'cur'"
                :data-index="index"
                :key = "index"
                @mouseenter="handleItemHover"
                @click="handleItemClick">
              <span class="opera-at"></span>
              <v-avatar size='is-small'
                        class="at-avatar"
                        :src='item.thumbAvatar'
                        :sex='item.genter' >
              </v-avatar>
              <slot name="item" :item="item">
                <span v-text="itemName(item)"></span>
              </slot>
            </li>
          </ul>
        </div>
        </keep-alive>
      </div>
    </div>
    </transition>
    <slot></slot>
  </div>
</template>

<style  lang="scss">




.atwho-wrap {

  .tab_complete_ui_header {
    border-radius:  $--border-radius-base  $--border-radius-base 0 0;
    padding: 5px 10px 4px;
    background: #faf8f6;
    color: get-grey-color(darken-1);
    font-size: $--font-size-small;
    border-bottom: solid 1px #ccc;
    background-clip: padding-box;
    height: 30px;
    overflow: hidden;
     .header_help {
      float: right;
      margin-left: 1rem;
    }
    .left_margin{
      margin-left: 12px;
    }
    strong{
      color: get-grey-color(darken-1);
      font-weight: 700;
    }
  }

  .atwho-panel {
    position: absolute;
    // bottom:50px;
    left:50px;
    width: calc(100% - 50px);
    max-height: 300px;
    border-radius: inherit;
    box-shadow: $--box-shadow-elevation;
    
    .atwho-view {
      cursor: default;
      background-color: rgba(255,255,255,.94);
      width: 100%;
      max-height: 270px;
      overflow-y: auto;
      color: $--color-text-primary;
      @include z-index(menu);
      .atwho-ul {
        list-style:none;
        max-height: 270px;
        padding: 0;
        margin: 0;
        .atwho-li {
          display: block;
          box-sizing: border-box;
          height: 30px;
          padding: 0 12px;
          white-space: nowrap;
          font-size: $--font-size-small;
          display: flex;
          align-items: center;
          .opera-at{
            width: 9px;
            height: 9px;
            border-radius: $--border-radius-circle;
            background: rgb(121, 219, 121);
            margin-right: 10px;
          }
          .at-avatar{
            width: 20px;
            height: 20px;
            margin-right: 10px;
            border-radius: $--border-radius-base; 
          }
          span {
            @include ellipsis;
            font-weight: 600;
          }

          &.atwho-cur {
            background: get-blue-color(accent-4);
            color: white;
            .opera-at{
              background: #fff;
            }
          }
        }
      }
    }
  }
}

</style>
