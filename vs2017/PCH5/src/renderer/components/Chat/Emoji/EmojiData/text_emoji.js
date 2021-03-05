const TEXT_EMOJI = [
  //共有453个表情
  { class: ":blue:", name: "[忧郁]", code: "1f60c" },
  { class: ":heng:", name: "[哼哼]", code: "1f60f" },
  { class: ":kiss:", name: "[亲亲]", code: "1f61a" },
  { class: ":naughty:", name: "[淘气]", code: "1f61c" },
  { class: ":spit_tongue:", name: "[吐舌头]", code: "1f61d" },
  { class: ":cry:", name: "[大哭]", code: "1f62d" },
  { class: ":happy:", name: "[高兴]", code: "1f604" },
  { class: ":winks:", name: "[媚眼]", code: "1f609" },
  { class: ":buxie:", name: "[不屑]", code: "1f612" },

  { class: ":youxian:", name: "[悠闲]", code: "1f614" },
  { class: ":crazy:", name: "[抓狂]", code: "1f616" },
  { class: ":air_kiss:", name: "[飞吻]", code: "1f618" },
  { class: ":fennu:", name: "[愤怒]", code: "1f621" },
  { class: ":kuanghan:", name: "[狂汗]", code: "1f625" },
  { class: ":intimidation:", name: "[吓死了]", code: "1f628" },
  { class: ":waterfall_sweat:", name: "[瀑布汗]", code: "1f630" },
  { class: ":jingkong:", name: "[惊恐]", code: "1f631" },
  { class: ":blind:", name: "[刺瞎]", code: "1f632" },


  { class: ":sluggish:", name: "[呆滞]", code: "1f633" },
  { class: ":smog:", name: "[雾霾]", code: "1f637" },
  { class: ":Pointing_up:", name: "[向上指]", code: "1f446" },
  { class: ":Pointing_down:", name: "[向下指]", code: "1f447" },
  { class: ":Pointing_left:", name: "[向左指]", code: "1f448" },
  { class: ":Pointing_right:", name: "[向右指]", code: "1f449" },
  { class: ":come_on:", name: "[加油]", code: "1f4aa" },
  { class: ':fist:', name: '[拳头]', code: '1f44a' },
  { class: ":haode:", name: "[好的]", code: "1f44c" },

  { class: ":Amazing:", name: "[厉害]", code: "1f44d" },
  { class: ":despise:", name: "[鄙视]", code: "1f44e" },
  { class: ":applaud:", name: "[鼓掌]", code: "1f44f" },
  { class: ":baifo:", name: "[啊弥陀佛]", code: "1f64f" },
  { class: ":ear:", name: "[耳朵]", code: "1f442" },
  { class: ":nose:", name: "[鼻子]", code: "1f443" },
  { class: ":mouth:", name: "[嘴巴]", code: "1f444" },
  { class: ":no:", name: "[no]", code: "261d" },
  { class: ":yeah:", name: "[yeah]", code: "270c" },

  { class: ":chengzi:", name: "[橙子]", code: "1f34a" },
  { class: ":pingguo:", name: "[苹果]", code: "1f34e" },
  { class: ":xigua:", name: "[西瓜]", code: "1f349" },
  { class: ":caomei:", name: "[草莓]", code: "1f353" },
  { class: ":mifan:", name: "[米饭]", code: "1f35a" },
  { class: ":miantiao:", name: "[面条]", code: "1f35c" },
  { class: ":yidalimian:", name: "[意大利面]", code: "1f35d" },
  { class: ":mianbao:", name: "[面包]", code: "1f35e" },
  { class: ":shutiao:", name: "[薯条]", code: "1f35f" },
  
  { class: ":shousi:", name: "[寿司]", code: "1f363" },
  { class: ":shabing:", name: "[沙冰]", code: "1f367" },
  { class: ":eye:", name: "[眼睛]", code: "1f440" },
  { class: ":xiyan:", name: "[吸烟]", code: "1f6ac" },
  { class: ":pijiu:", name: "[啤酒]", code: "1f37a" },
  { class: ":ganbei:", name: "[干杯]", code: "1f37b" },
  { class: ":yaobunengting:", name: "[药不能停]", code: "1f48a" },
  { class: ":zuanjie:", name: "[钻戒]", code: "1f48d" },
  { class: ":xinyousuoshu:", name: "[心有所属]", code: "1f49e" },
  
  { class: ":yeshu:", name: "[椰树]", code: "1f334" },
  { class: ":hongmeigui:", name: "[红玫瑰]", code: "1f339" },
  { class: ":hanbao:", name: "[汉堡]", code: "1f354" },
  { class: ":mifantuan:", name: "[米饭团]", code: "1f359" },
  { class: ":hebaodan:", name: "[荷包蛋]", code: "1f373" },
  { class: ":jiweijiu:", name: "[鸡尾酒]", code: "1f378" },
  { class: ":hudiejie:", name: "[蝴蝶结]", code: "1f380" },
  { class: ":shengrikuaile:", name: "[生日快乐]", code: "1f382" },
  { class: ":shendanshu:", name: "[圣诞树]", code: "1f384" },

  { class: ":qiqiu:", name: "[气球]", code: "1f388" },
  { class: ":qingzhu:", name: "[庆祝]", code: "1f389" },
  { class: ":huangguan:", name: "[皇冠]", code: "1f451" },
  { class: ":jiaoying:", name: "[脚印]", code: "1f463" },
  { class: ":lingdang:", name: "[铃铛]", code: "1f514" },
  { class: ":kafei:", name: "[咖啡]", code: "2615" },
  { class: ":defhuo:", name: "[火]", code: "1f525" },
  { class: ":shandian:", name: "[闪电]", code: "26a1" },
  { class: ":xingxingshanshuo:", name: "[星星闪烁]", code: "2728" },

  { class: ":guanjun:", name: "[冠军]", code: "1f3c6" },
  { class: ":zhadan:", name: "[炸弹]", code: "1f4a3" },
  { class: ":feixiang:", name: "[翔]", code: "1f4a9" },
  { class: ":jinqian:", name: "[金钱]", code: "1f4b0" },
  { class: ":xinxiang:", name: "[信箱]", code: "1f4ea" },
  { class: ":kuaiting:", name: "[快艇]", code: "1f6a4" },
  { class: ":zixinche:", name: "[自行车]", code: "1f6b2" },
  { class: ":gongjiao:", name: "[公交]", code: "1f68c" },
  { class: ":junma:", name: "[骏马]", code: "1f40e" },

  { class: ":wujiaxing:", name: "[五角星]", code: "1f31f" },
  { class: ":houtou:", name: "[猴头]", code: "1f435" },
  { class: ":nanhai:", name: "[男孩]", code: "1f466" },
  { class: ":nvhai:", name: "[女孩]", code: "1f467" },
  { class: ":dashu:", name: "[大叔]", code: "1f468" },
  { class: ":a_yi:", name: "[阿姨]", code: "1f469" },
  { class: ":chouxie:", name: "[抽血]", code: "1f489" },
  { class: ":yaoshi:", name: "[钥匙]", code: "1f511" },
  { class: ":jiaosuo:", name: "[枷锁]", code: "1f512" },

  { class: ":feichuan:", name: "[飞船]", code: "1f680" },
  { class: ":dongche:", name: "[动车]", code: "1f684" },
  { class: ":xiaoqiche:", name: "[小汽车]", code: "1f697" },
  { class: ":fanchuan:", name: "[帆船]", code: "26f5" },
  { class: ":sangna:", name: "[桑拿]", code: "2668" },
  { class: ":feiji:", name: "[飞机]", code: "2708" },
  { class: ":laoshu:", name: "[老鼠]", code: "1f42d" },
  { class: ":niunai:", name: "[奶牛]", code: "1f42e" },
  { class: ":laohu:", name: "[老虎]", code: "1f42f" },

  { class: ":youling:", name: "[幽灵]", code: "1f47b" },
  { class: ":tianshi:", name: "[天使]", code: "1f47c" },
  { class: ":defji:", name: "[鸡]", code: "1f414" },
  { class: ":zhangyu:", name: "[章鱼]", code: "1f419" },
  { class: ":redaiyu:", name: "[热带鱼]", code: "1f420" },
  { class: ":xiaoji:", name: "[小鸡]", code: "1f423" },
  { class: ":q_ie:", name: "[企鹅]", code: "1f427" },
  { class: ":kaola:", name: "[考拉]", code: "1f428" },
  { class: ":jingyu:", name: "[鲸鱼]", code: "1f433" },

  { class: ":xiaogou:", name: "[小狗]", code: "1f436" },
  { class: ":zhutou:", name: "[猪头]", code: "1f437" },
  { class: ":qingwa:", name: "[青蛙]", code: "1f438" },
  { class: ":caomao:", name: "[草帽]", code: "1f452" },
  { class: ":qunzi:", name: "[裙子]", code: "1f457" },
  { class: ":kuloutou:", name: "[骷髅头]", code: "1f480" },
  { class: ":kouhong:", name: "[口红]", code: "1f484" },
  { class: ":huhudashui:", name: "[呼呼大睡]", code: "1f4a4" },
  { class: ":yushui:", name: "[雨水]", code: "1f4a6" },

  { class: ":chuiqi:", name: "[吹气]", code: "1f4a8" },
  { class: ":beike:", name: "[贝壳]", code: "1f41a" },
  { class: ":maomaochong:", name: "[毛毛虫]", code: "1f41b" },
  { class: ":kalaOK:", name: "[卡拉OK]", code: "1f3a4" },
  { class: ":shexiangji:", name: "[摄像机]", code: "1f3a5" },
  { class: ":def777:", name: "[777]", code: "1f3b0" },
  { class: ":jita:", name: "[吉他]", code: "1f3b8" },
  { class: ":fangzi:", name: "[房子]", code: "1f3e1" },
  { class: ":yiyuan:", name: "[医院]", code: "1f3e5" },

  { class: ":yinghang:", name: "[银行]", code: "1f3e6" },
  { class: ":ATM:", name: "[ATM]", code: "1f3e7" },
  { class: ":lvdian:", name: "[旅店]", code: "1f3e8" },
  { class: ":24xiaoshi:", name: "[24小时营业]", code: "1f3ea" },
  { class: ":jiaotang:", name: "[教堂]", code: "26ea" },
  { class: ":hongzhong:", name: "[红中]", code: "1f004" },
  { class: ":diannao:", name: "[电脑]", code: "1f4bb" },
  { class: ":C_D:", name: "[CD]", code: "1f4bf" },
  { class: ":honglvdeg:", name: "[红绿灯]", code: "1f6a5" },

  { class: ":luzhang:", name: "[路障]", code: "1f6a7" },
  { class: ":matong:", name: "[马桶]", code: "1f6bd" },
  { class: ":xizao:", name: "[洗澡]", code: "1f6c0" },
  { class: ":shouqiang:", name: "[手枪]", code: "1f52b" },
  { class: ":zhaopei:", name: "[招牌]", code: "1f488" },
  { class: ":fenxin:", name: "[粉心]", code: "1f493" },
  { class: ":dianhua:", name: "[电话]", code: "260e" },
  { class: ":gushi:", name: "[股市]", code: "303d" },
  { class: ":meihua:", name: "[梅花]", code: "2663" },

  { class: ":chuanzhen:", name: "[传真]", code: "1f4e0" },
  { class: ":iphone:", name: "[IPHONE]", code: "1f4f1" },
  { class: ":zhaoxiangji:", name: "[照相机]", code: "1f4f7" },
  { class: ":nan1:", name: "[男]", code: "1f6b9" },
  { class: ":nv1:", name: "[女]", code: "1f6ba" },
  { class: ":shoudibao:", name: "[手提包]", code: "1f45b" },
  { class: ":nanxie:", name: "[男鞋]", code: "1f45f" },
  { class: ":yusan:", name: "[雨伞]", code: "1f302" },
  { class: ":defyueliang:", name: "[月亮]", code: "1f319" },

  { class: ":duanxiu:", name: "[短袖]", code: "1f455" },
  { class: ":bijini:", name: "[比基尼]", code: "1f459" },
  { class: ":gaogengxie:", name: "[高跟鞋]", code: "1f460" },
  { class: ":nvxue:", name: "[女靴]", code: "1f462" },
  { class: ":xueren:", name: "[雪人]", code: "26c4" },
  { class: ":tingzhi:", name: "[停止]", code: "2b55" },
  { class: ":bacha:", name: "[八叉]", code: "274c" },
  { class: ":taiyang:", name: "[太阳]", code: "2600" },
  { class: ":yunduo:", name: "[云朵]", code: "2601" },

  { class: ":xiayu:", name: "[下雨]", code: "2614" },
  { class: ":wenhao:", name: "[问号]", code: "2753" },
  { class: ":gantanhao:", name: "[感叹号]", code: "2757" },
  { class: ":xiangzuoshang:", name: "[向左上]", code: "2196" },
  { class: ":xiangyoushang:", name: "[向右上]", code: "2197" },
  { class: ":xiangyuoxia:", name: "[向右下]", code: "2198" }, //
  { class: ":xiangzuoxia:", name: "[向左下]", code: "2199" },
  { class: ":kuaijin:", name: "[快进]", code: "23ea" },
  { class: ":kuaitui:", name: "[快退]", code: "23e9" },

  { class: ":xiayige:", name: "[下一个]", code: "25b6" },
  { class: ":shangyige:", name: "[上一个]", code: "25c0" },
  { class: ":xiangyou:", name: "[向右]", code: "27a1" },
  { class: ":xiangzuo:", name: "[向左]", code: "2b05" },
  { class: ":xiangshang:", name: "[向上]", code: "2b06" },
  { class: ":xiangxia:", name: "[向下]", code: "2b07" },
  { class: ":baiyangzuo:", name: "[白羊座]", code: "2648" },
  { class: ":jinniuzuo:", name: "[金牛座]", code: "2649" },
  { class: ":shaugnzizuo:", name: "[双子座]", code: "264a" },

  { class: ":juxiezuo:", name: "[巨蟹座]", code: "264b" },
  { class: ":shizizuo:", name: "[狮子座]", code: "264c" },
  { class: ":chunvzuo:", name: "[处女座]", code: "264d" },
  { class: ":tianchenzuo:", name: "[天秤座]", code: "264e" },
  { class: ":tianxiezuo:", name: "[天蝎座]", code: "264f" },
  { class: ":sheshouzuo:", name: "[射手座]", code: "2650" },
  { class: ":moxiezuo:", name: "[魔蝎座]", code: "2651" },
  { class: ":shuipingzuo:", name: "[水瓶座]", code: "2652" },
  { class: ":shaungyuzuo:", name: "[双鱼座]", code: "2653" },
  { class: ":liumangxin:", name: "[六芒星]", code: "1f52f" },

  { class: ":heitao:", name: "[黑桃]", code: "2660" },
  { class: ":hongtao:", name: "[红桃]", code: "2665" },
  { class: ":fangkuai:", name: "[方块]", code: "2666" },
  { class: ":canjiren:", name: "[残疾人]", code: "267f" },
  { class: ":jinggao:", name: "[警告]", code: "26f0" },
  { class: ":zuqiu:", name: "[足球]", code: "26bd" },
  { class: ":bangqiu:", name: "[棒球]", code: "26be" },
  { class: ":penquan:", name: "[喷泉]", code: "26f2" },
  { class: ":yeying:", name: "[野营]", code: "26fa" },

  { class: ":jiayouzhan:", name: "[加油站]", code: "26fd" },
  { class: ":jiandao:", name: "[剪刀]", code: "2702" },
  { class: ":xinghao:", name: "[星号]", code: "2733" },
  { class: ":juzixing:", name: "[橘子星]", code: "2734" },
  { class: ":hongxin:", name: "[红心]", code: "2764" },
  { class: ":luying:", name: "[录音]", code: "27b0" },
  { class: ":zhufu1:", name: "[祝]", code: "3297" },
  { class: ":mimi:", name: "[秘密]", code: "3299" },
  { class: ":hongA:", name: "[红A]", code: "1f170" },

  { class: ":hongB:", name: "[红B]", code: "1f171" },
  { class: ":hongO:", name: "[红O]", code: "1f17e" },
  { class: ":defAB:", name: "[AB]", code: "1f18e" },
  { class: ":tingche:", name: "[停车]", code: "1f17f" },
  { class: ":COOL:", name: "[COOL]", code: "1f192" },
  { class: ":defNew:", name: "[NEW]", code: "1f195" },
  { class: ":defOK:", name: "[OK]", code: "1f197" },
  { class: ":defUP:", name: "[UP!]", code: "1f199" },
  { class: ":defhere:", name: "[HERE]", code: "1f201" },

  { class: ":deftop:", name: "[TOP]", code: "1f51d" },
  { class: ":defID:", name: "[ID]", code: "1f194" },
  { class: ":defVS:", name: "[VS]", code: "1f19a" },
  { class: ":defcao:", name: "[艹]", code: "1f202" },
  { class: ":defwu:", name: "[无]", code: "1f21a" },
  { class: ":defzhi:", name: "[指]", code: "1f22f" },
  { class: ":defkong:", name: "[空]", code: "1f233" },
  { class: ":defman:", name: "[满]", code: "1f235" },
  { class: ":defyou:", name: "[有]", code: "1f236" },

  { class: ":defyue:", name: "[月]", code: "1f237" },
  { class: ":defsheng:", name: "[申]", code: "1f238" },
  { class: ":defge:", name: "[割]", code: "1f239" },
  { class: ":defgong:", name: "[当铺]", code: "1f23a" },
  { class: ":defde:", name: "[得]", code: "1f250" },
  { class: ":xuanwo:", name: "[漩涡]", code: "1f300" },
  { class: ":liuxing:", name: "[流星]", code: "1f320" },
  { class: ":riluo:", name: "[日落]", code: "1f304" },
  { class: ":richu:", name: "[日出]", code: "1f305" },

  { class: ":huanghun:", name: "[黄昏]", code: "1f306" },
  { class: ":zhaoyang:", name: "[朝阳]", code: "1f307" },
  { class: ":caihong:", name: "[彩虹]", code: "1f308" },
  { class: ":dalangtaotian:", name: "[大浪滔天]", code: "1f30a" },
  { class: ":xianrenzhang:", name: "[仙人掌]", code: "1f335" },
  { class: ":yujingxiang:", name: "[郁金香]", code: "1f337" },
  { class: ":haitang:", name: "[海棠]", code: "1f33a" },
  { class: ":xiangrukui:", name: "[向日葵]", code: "1f33c" },
  { class: ":puwei:", name: "[蒲苇]", code: "1f33e" },

  { class: ":siyecao:", name: "[四叶草]", code: "1f340" },
  { class: ":fengye:", name: "[枫叶]", code: "1f341" },
  { class: ":luoye:", name: "[落叶]", code: "1f342" },
  { class: ":lvye:", name: "[绿叶]", code: "1f343" },
  { class: ":fanqie:", name: "[番茄]", code: "1f345" },
  { class: ":qiezi:", name: "[茄子]", code: "1f346" },
  { class: ":fantuan:", name: "[饭团]", code: "1f358" },
  { class: ":gaijiaofan:", name: "[盖浇饭]", code: "1f35b" },
  { class: ":chuanchuanxiang:", name: "[串串香]", code: "1f361" },

  { class: ":guandongzhu:", name: "[关东煮]", code: "1f362" },
  { class: ":shengdai:", name: "[圣代]", code: "1f366" },
  { class: ":dangao:", name: "[蛋糕]", code: "1f370" },
  { class: ":kuaican:", name: "[快餐]", code: "1f371" },
  { class: ":lamian:", name: "[拉面]", code: "1f372" },
  { class: ":canju:", name: "[餐具]", code: "1f374" },
  { class: ":chashui:", name: "[茶水]", code: "1f375" },
  { class: ":baijiu:", name: "[白酒]", code: "1f376" },
  { class: ":liwu:", name: "[礼物]", code: "1f381" },

  { class: ":wanshengjie:", name: "[万圣节]", code: "1f383" },
  { class: ":shendanlaoren:", name: "[圣诞老人]", code: "1f385" },
  { class: ":yanhua:", name: "[烟花]", code: "1f387" },
  { class: ":yanhuo:", name: "[烟火]", code: "1f386" },
  { class: ":ribenqi:", name: "[日本旗]", code: "1f38c" },
  { class: ":xianrenqiu:", name: "[仙人球]", code: "1f38d" },
  { class: ":hanguoren:", name: "[韩国人]", code: "1f38e" },
  { class: ":liuyan:", name: "[留言]", code: "1f390" },
  { class: ":zhaopian:", name: "[照片]", code: "1f391" },

  { class: ":beibao:", name: "[背包]", code: "1f392" },
  { class: ":motianlun:", name: "[摩天轮]", code: "1f3a1" },
  { class: ":guoshangche:", name: "[过山车]", code: "1f3a2" },
  { class: ":luxiang:", name: "[录像]", code: "1f3a6" },
  { class: ":tingyingyue:", name: "[听音乐]", code: "1f3a7" },
  { class: ":caisepan:", name: "[彩色盘]", code: "1f3a8" },
  { class: ":maozi:", name: "[帽子]", code: "1f3a9" },
  { class: ":chepiao:", name: "[车票]", code: "1f3ab" },
  { class: ":paidianying:", name: "[拍电影]", code: "1f3ac" },

  { class: ":zhongba:", name: "[中靶]", code: "1f3af" },
  { class: ":taiqiu:", name: "[台球]", code: "1f3b1" },
  { class: ":yingfu:", name: "[音符]", code: "1f3b5" },
  { class: ":sakasi:", name: "[萨克斯]", code: "1f3b7" },
  { class: ":yinyue:", name: "[音乐]", code: "1f3b9" },
  { class: ":xiaohao:", name: "[小号]", code: "1f3ba" },
  { class: ":wangqiu:", name: "[网球]", code: "1f3be" },
  { class: ":huaxue:", name: "[滑雪]", code: "1f3bf" },
  { class: ":lanqiu:", name: "[篮球]", code: "1f3c0" },

  { class: ":saicheqi:", name: "[赛车旗]", code: "1f3c1" },
  { class: ":zoulu:", name: "[走路]", code: "1f6b6" },
  { class: ":paobu:", name: "[跑步]", code: "1f3c3" },
  { class: ":chonglang:", name: "[冲浪]", code: "1f3c4" },
  { class: ":ganlanqiu:", name: "[橄榄球]", code: "1f3c8" },
  { class: ":youyong:", name: "[游泳]", code: "1f3ca" },
  { class: ":dasha:", name: "[大厦]", code: "1f3e2" },
  { class: ":lvguan:", name: "[旅馆]", code: "1f3e3" },
  { class: ":zhonglou:", name: "[钟楼]", code: "1f3eb" },

  { class: ":bangonglou:", name: "[办公楼]", code: "1f3ec" },
  { class: ":gongchang:", name: "[工厂]", code: "1f3ed" },
  { class: ":siyuan:", name: "[寺院]", code: "1f3ef" },
  { class: ":chengbao:", name: "[城堡]", code: "1f3f0" },
  { class: ":defshe:", name: "[蛇]", code: "1f40d" },
  { class: ":mianyang:", name: "[绵羊]", code: "1f411" },
  { class: ":houzi:", name: "[猴子]", code: "1f412" },
  { class: ":yezhu:", name: "[野猪]", code: "1f417" },
  { class: ":daxiang:", name: "[大象]", code: "1f418" },
  { class: ":defyu:", name: "[鱼]", code: "1f41f" },

  { class: ":gezi:", name: "[鸽子]", code: "1f426" },
  { class: ":luotuo:", name: "[骆驼]", code: "1f42b" },
  { class: ":haitun:", name: "[海豚]", code: "1f42c" },
  { class: ":tuzi:", name: "[兔子]", code: "1f430" },
  { class: ":huangshulang:", name: "[黄鼠狼]", code: "1f431" },
  { class: ":defma:", name: "[马]", code: "1f434" },
  { class: ":shuashu:", name: "[花鼠]", code: "1f439" },
  { class: ":wangcai:", name: "[旺财]", code: "1f43a" },
  { class: ":zongxiong:", name: "[棕熊]", code: "1f43b" },
  { class: ":zhengzhuang:", name: "[正装]", code: "1f454" },

  { class: ":hefu:", name: "[和服]", code: "1f458" },
  { class: ":pixie:", name: "[皮鞋]", code: "1f45e" },
  { class: ":liangxie:", name: "[凉鞋]", code: "1f461" },
  { class: ":fuqi:", name: "[夫妻]", code: "1f46b" },
  { class: ":gongfuyuan:", name: "[公务员]", code: "1f46e" },
  { class: ":tunvlang:", name: "[兔女郎]", code: "1f46f" },
  { class: ":wangzi:", name: "[王子]", code: "1f471" },
  { class: ":xiaoer:", name: "[小儿]", code: "1f472" },
  { class: ":yingduren:", name: "[印度人]", code: "1f473" },

  { class: ":yeye:", name: "[爷爷]", code: "1f474" },
  { class: ":nainai:", name: "[奶奶]", code: "1f475" },
  { class: ":youer:", name: "[幼儿]", code: "1f476" },
  { class: ":gongren:", name: "[工人]", code: "1f477" },
  { class: ":gongzhu:", name: "[公主]", code: "1f478" },
  { class: ":waixinren:", name: "[外星人]", code: "1f47d" },
  { class: ":guaiwu:", name: "[怪物]", code: "1f47f" },
  { class: ":mogui:", name: "[魔鬼]", code: "1f479" },
  { class: ":shuibian:", name: "[随便]", code: "1f481" },

  { class: ":shibing:", name: "[士兵]", code: "1f482" },
  { class: ":tiaowu:", name: "[跳舞]", code: "1f483" },
  { class: ":meijia:", name: "[美甲]", code: "1f485" },
  { class: ":an_mo:", name: "[按摩]", code: "1f486" },
  { class: ":meifa:", name: "[美发]", code: "1f487" },
  { class: ":lieyanhongchun:", name: "[烈焰红唇]", code: "1f48b" },
  { class: ":zuanshi:", name: "[钻石]", code: "1f48e" },
  { class: ":lianai:", name: "[恋爱]", code: "1f48f" },
  { class: ":meiguihua:", name: "[玫瑰花]", code: "1f490" },

  { class: ":aiqing:", name: "[爱情]", code: "1f491" },
  { class: ":hunli:", name: "[婚礼]", code: "1f492" },
  { class: ":xinsuile:", name: "[心碎了]", code: "1f494" },
  { class: ":langman:", name: "[浪漫]", code: "1f495" },
  { class: ":yijianchuanxin:", name: "[一箭穿心]", code: "1f498" },
  { class: ":lanxin:", name: "[蓝心]", code: "1f499" },
  { class: ":lvxin:", name: "[绿心]", code: "1f49a" },
  { class: ":huangxin:", name: "[黄心]", code: "1f49b" },
  { class: ":zixin:", name: "[紫心]", code: "1f49c" },

  { class: ":aixin:", name: "[爱心]", code: "1f49f" },
  { class: ":dengpao:", name: "[灯泡]", code: "1f4a1" },
  { class: ":shengqi:", name: "[生气]", code: "1f4a2" },
  { class: ":huilv:", name: "[汇率]", code: "1f4b1" },
  { class: ":GDP:", name: "[GDP]", code: "1f4b9" },
  { class: ":yi_zi:", name: "[椅子]", code: "1f4ba" },
  { class: ":gongwenbao:", name: "[公文包]", code: "1f4bc" },
  { class: ":guanqu:", name: "[光驱]", code: "1f4bd" },
  { class: ":dvd:", name: "[DVD]", code: "1f4c0" },

  { class: ":shuben:", name: "[书本]", code: "1f4da" },
  { class: ":xiexin:", name: "[写信]", code: "1f4dd" },
  { class: ":leida:", name: "[雷达]", code: "1f4e1" },
  { class: ":tongzhi:", name: "[通知]", code: "1f4e2" },
  { class: ":yanggshengqi:", name: "[扬声器]", code: "1f4e3" },
  { class: ":laixin1:", name: "[来信]", code: "1f4eb" },
  { class: ":jixin:", name: "[寄信]", code: "1f4ee" },
  { class: ":laidian:", name: "[来电]", code: "1f4f2" },
  { class: ":zhengdong:", name: "[震动]", code: "1f4f3" },

  { class: ":guanji:", name: "[关机]", code: "1f4f4" },
  { class: ":xinhao:", name: "[信号]", code: "1f4f6" },
  { class: ":dianshiji:", name: "[电视机]", code: "1f4fa" },
  { class: ":shouyinji:", name: "[收音机]", code: "1f4f9" },
  { class: ":lvxiangdai:", name: "[录像带]", code: "1f4fc" },
  { class: ":laba:", name: "[喇叭]", code: "1f50a" },
  { class: ":fangdajin:", name: "[放大镜]", code: "1f50d" },
  { class: ":kaisuo:", name: "[开锁]", code: "1f513" },
  { class: ":jinzhi18:", name: "[禁止18岁]", code: "1f51e" },

  { class: ":sujing:", name: "[肃静]", code: "1f528" },
  { class: ":biaozhi:", name: "[标志]", code: "1f530" },
  { class: ":snachaji:", name: "[三叉戟]", code: "1f531" },
  { class: ":hongqiu:", name: "[红球]", code: "1f534" },
  { class: ":yidian:", name: "[一点]", code: "1f550" },
  { class: ":liangdian:", name: "[二点]", code: "1f551" },
  { class: ":sandian:", name: "[三点]", code: "1f552" },
  { class: ":sidian:", name: "[四点]", code: "1f553" },
  { class: ":wudian:", name: "[五点]", code: "1f554" },

  { class: ":liudian:", name: "[六点]", code: "1f555" },
  { class: ":qidian:", name: "[七点]", code: "1f556" },
  { class: ":badian:", name: "[八点]", code: "1f557" },
  { class: ":jiudian:", name: "[九点]", code: "1f558" },
  { class: ":shidian:", name: "[十点]", code: "1f559" },
  { class: ":shiyidian:", name: "[十一点]", code: "1f55a" },
  { class: ":shierdian:", name: "[十二点]", code: "1f55b" },
  { class: ":fushishan:", name: "[富士山]", code: "1f5fb" },
  { class: ":tieta:", name: "[铁塔]", code: "1f5fc" },

  { class: ":ziyounvshengxiang:", name: "[自由女神像]", code: "1f5fd" },
  { class: ":fandui:", name: "[反对]", code: "1f645" },
  { class: ":zhichi:", name: "[支持]", code: "1f646" },
  { class: ":yonggong:", name: "[用功]", code: "1f647" },
  { class: ":dianche:", name: "[电车]", code: "1f683" },
  { class: ":huochetou:", name: "[火车头]", code: "1f685" },
  { class: ":huoche:", name: "[火车]", code: "1f687" },
  { class: ":huochelaile:", name: "[火车来了]", code: "1f689" },
  { class: ":fubiao:", name: "[浮标]", code: "1f68f" },

  { class: ":d120:", name: "[120]", code: "1f691" },
  { class: ":d119:", name: "[119]", code: "1f692" },
  { class: ":d110:", name: "[110]", code: "1f693" },
  { class: ":chuzuche:", name: "[出租车]", code: "1f695" },
  { class: ":suv:", name: "[SUV]", code: "1f699" },
  { class: ":kacha:", name: "[卡车]", code: "1f69a" },
  { class: ":lunchuan:", name: "[轮船]", code: "1f6a2" },
  { class: ":jingzhixiyan:", name: "[禁止吸烟]", code: "1f6ad" },
  { class: ":nannv:", name: "[男女]", code: "1f6bb" },

  { class: ":yinger:", name: "[婴儿]", code: "1f6bc" },
  { class: ":cesuo:", name: "[WC]", code: "1f6be" },
  { class: ":taohua:", name: "[桃花]", code: "1f338" },
  { class: ":TM:", name: "[TM]", code: "2122" },
  { class: ":uncomfortable:", name: "[难受]", code: "1f623" },
  { class: ":sad:", name: "[伤心]", code: "1f622" },
  { class: ":angry:", name: "[生气]", code: "1f620" },
  { class: ":oops:", name: "[囧]", code: "1f61e" },
  { class: ":sweat:", name: "[汗]", code: "1f613" },

  { class: ":color:", name: "[色]", code: "1f60d" },
  { class: ":lovely:", name: "[可爱]", code: "1f60a" },
  { class: ":dumbfounding:", name: "[哭笑不得]", code: "1f602" },
  { class: ":bared_teeth:", name: "[呲牙]", code: "1f601" },
  { class: ":sleep:", name: "[睡觉]", code: "1f62a" },
  { class: ":gaoerfu:", name: "[高尔夫]", code: "26f3" },
  { class: ":Hands:", name: "[双手]", code: "1f64c" },
  { class: ":tuizhang:", name: "[推掌]", code: "1f450" },
  
  { class: ":Oath:", name: "[五魁首]", code: "270b" },
  { class: ":xuanshi:", name: "[宣誓]", code: "270a" },


  // { class: ":sleep1:", name: "[睡着]", code: "1f634" },
  // { class: ":smile:", name: "[吐舌头]", code: "1f61d" },
  // { class: ':shy:', name: '[害羞]', code: 'e298ba' },
  // { class: ':palm:', name: '[手掌]', code: '1f446' },
  // { class: ':fist:', name: '[拳头]', code: '1f44a' },
  // { class: ':yeah:', name: '[yeah]', code: '1f616s' },
  // { class: ':jinghao:', name: '[#]', code: '-35f2f1d' },
  // { class: ':ling:', name: '[0]', code: '' },
  // { class: ':yi:', name: '[1]', code: '' },
  // { class: ':er:', name: '[2]', code: '-35ef31d' },
  // { class: ':san:', name: '[3]', code: '' },
  // { class: ':si:', name: '[4]', code: '' },
  // { class: ':wu:', name: '[5]', code: '' },
  // { class: ':liu:', name: '[6]', code: '' },
  // { class: ':qi:', name: '[7]', code: '' },
  // { class: ':ba:', name: '[8]', code: '' },
  // { class: ':jiu:', name: '[9]', code: '' },
  // { class: ':copy:', name: '[copy]', code: '00a9' },
  // { class: ':right:', name: '[right]', code: '00ae' },
  
  
  
  // { class: ":jinyu:", name: "[金鱼]", code: "1f38f" },

  // { class: ":jiudian:", name: "[酒店]", code: "1f3e9" },
];
export default TEXT_EMOJI