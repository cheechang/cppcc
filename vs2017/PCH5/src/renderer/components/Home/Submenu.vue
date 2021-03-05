<template>
    <div>
        <!-- 断线重连提示 -->
        <!--<Disconnect v-if="showDisconnect" :tip="disConnectTip"></Disconnect>-->
        <!-- 加载动画   -->
        <!--<Animates v-if="isShowAnimate" loadTop="200"></Animates>-->
        <vue-scroll>
            <!-- 右键菜单 -->
            <div class="card list-card-item theme-list-items" :class="{'theme-list-items-active': active==item.functionCode}" v-for="(item,index) in menuList" :key="index" @click.stop="selectItem(item)">
                <div class="card-content" ref="card">
                    <div class="media">
                        <div class="media-left" :title="item.functionName">
                            <img class="img-icon" :src="item.functionCode?require('vrv-static/resources/images/navicon/'+item.functionCode+'.png'):require('vrv-static/resources/images/navicon/Mien.png')" >
                        </div>
                        <div class="media-content">
                            <div class="title">
                                <!-- 名称显示 -->
                                <div class="title-left">
              <span class="title-content">{{item.functionName}}
              </span>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </vue-scroll>
    </div>
</template>

<script>
  export default {
    name: "Submenu",
    data() {
      return {

      }},
    props: {
      menuList: Array,
      active:String
    },
    created() {
    },
    methods: {
      // * 选择右键菜单的某项
      selectItem(item) {
        console.log("item", item);
        this.$emit("toParent",{homeUrl:item.functionCode!=='Video70th'?`file:///${this.$is.isDev?'':__dirname+'/'}pcdist/index.html?window=home&path=${item.functionCode==='AcademyHome'?'academyApp':item.functionCode}`:`http://${this.$config.clientConfig.auth.webServer}/zx70/`,functionCode:item.functionCode})
      }
    }
  };
</script>

<style lang="scss" scoped>
    .list-card-item {
        .card-content {
            height: 3.8rem;
            padding: 0.5rem;
            .img-icon{
                width: 40px;
                height: 40px;
            }
            .title-left {
                display: flex;
                align-items: center;
                max-width: 75%;
                .title-content {
                    @include ellipsis;
                }
                .chatlist-isCompany {
                    font-size: $--font-size-mid;
                    color: $--color-msg-prompt-low;
                    font-size: 14px;
                    width: 10px;
                    height: 13px;
                    background: #fff;
                    margin-left: 6px;
                    border-radius: 15px;
                    // margin-top: 3px;
                }
            }
            .has-at-me {
                .contents {
                    width: 48%;
                }
            }

            .all-notify {
                .contents {
                    width: 28%;
                }
            }

            .rtcfile-notify {
                .contents {
                    color: $--color-msg-prompt-middle;
                }
            }
            .chatlist-subscript {
                display: flex;
                position: absolute;
                right: 4px;
                margin-top: 2px;
            }

            .chatlist-time {
                font-size: 0.7rem;
                font-weight: 500;
                margin-right: 4px;
            }

            .chatlist-unreadcount {
                font-weight: 500;
                margin-left: 2px;
            }

            .disturb-mode {
                background: $--color-msg-prompt-low;
            }

            &:hover .chatlist-unreadcount {
                display: none;
            }

            &:hover .remind {
                display: none;
            }

            .btn-chatlist-del {
                display: none;
                position: absolute;
                right: -6px;
                top: -2px;
                font-size: $--font-size-big;
                &:hover {
                    cursor: pointer;
                }
            }
            .remind {
                border-radius: $--border-radius-circle;
                display: flex;
                justify-content: center;
                align-items: center;
                width: 16px;
                position: absolute;
                left: -15px;
                top: -4px;
                .icon {
                    font-size: $--font-size-primary;
                    color: get-grey-color(lighten-1);;
                }
            }
            .notice-at-me {
                color: $--color-msg-prompt-middle;
                font-size: $--font-size-small;
                font-weight: 500;
                white-space: nowrap;
            }
            .msg-fail-notify {
                color: $--color-msg-prompt-danger;
            }
        }
        &:hover .btn-chatlist-del {
            display: block;
        }
    }
</style>