# Linkdood

> Linkdood Linkdood H5客户端

## Build Setup

``` bash
# 安装依赖项
yarn install

# 启动electron, 热加载刷新
yarn dev

# 构建产品包体积优化
yarn dist

```

## 项目文件说明

``` bash
Linkdood/
    ├── src/                    # 源码根目录
    │   ├── main/               # node主进程
    │   │   ├── index.ts        # 主入口 
    │   │   ├── app-windows.ts  # 主窗口
    │   │── renderer/           # 浏览器进程
    │   │   ├── ui              # 页面 
    │   │   │   ├── vrvui/      # 公用组建  
    │   │   ├── main.ts         # 入口
    │   │   ├── App.vue         # vue根组建入口    
    │   ├── comm/               # 通用库
    │   ├── service/            # IMSDK service model
    │   ├── crash               # 异常崩溃窗口
    └── test/
    ├── static/            # 资源目录，各客户端icon及其他资源
    ├── .babelrc           # js语法转换到ES6的工具
    ├── .gitignore         # git版本控制时忽略的文件和目录
    ├── package.json       # nodejs的npm配置工具
    ├── CHANGELOG.md       # 更改的历史记录
    ├── README.md          # 项目说明入口
```

## Vue风格规范

1. 组件名为多个单词 name: 'TodoItem'
2. 组件的 data 必须是一个函数
3. Prop 定义应该尽量详细
``` js
props: {
  status: {
    type: String,
    required: true,
    validator: function (value) {
```

4. 总是用 key 配合 v-for
``` html
<ul>
  <li
    v-for="todo in todos"
    :key="todo.id"
  >
    {{ todo.text }}
  </li>
</ul>
```

5. 为组件样式设置作用域 <style scoped>
6. 私有属性名 $_myGreatMixin_update
7. 每个组件单独分成文件
8. 每个组件单独分成文件 驼峰式
9. 组建名，基础的Base/单例的The/紧耦合TodoList.vue+TodoListItem.vue
10. 多个特性的元素应该分多行撰写，每个特性一行
11. 组件模板应该只包含简单的表达式，复杂的表达式则应该重构为计算属性或方法
12. 应该把复杂计算属性分割为尽可能多的更简单的属性
13. 非空 HTML 特性值应该始终带引号 
14. 组件/实例的选项应该有统一的顺序。
> * el: 副作用 (触发组件外的影响)
> * name/parent 全局感知 (要求组件以外的知识)
> * functional 组件类型 (更改组件的类型)
> * delimiters/comments 模板修改器 (改变模板的编译方式)
> * components/directives/filters/ 模板依赖 (模板内使用的资源)
> * extends/mixins 组合 (向选项里合并属性)
> * inheritAttrs/model/props/propsData 接口 (组件的接口)
> * data/computed 本地状态 (本地的响应式属性)
> * watch 事件 (通过响应式事件触发的回调)
> * methods 生命周期钩子 (按照它们被调用的顺序)/非响应式的属性 (不依赖响应系统的实例属性)
> * template/render/renderError 渲染 (组件输出的声明式描述)

15. 应该优先通过 prop 和事件进行父子组件之间的通信，而不是 this.$parent 或改变 prop。

# 安装工具流程

## node，安装node版本升级切换工具nvm
1. 下载安装 https://github.com/coreybutler/nvm-windows/releases/download/1.1.6/nvm-setup.zip
2. nvm node_mirror https://npm.taobao.org/mirrors/node    #设置node安装包源
3. nvm npm_mirror https://registry.npm.taobao.org/  #设置npm包源
4. cat ~/.npmrc  #验证设置已成功
> * registry=https://registry.npm.taobao.org/
> * electron_mirror=https://npm.taobao.org/mirrors/electron/
> * sass_binary_site=https://npm.taobao.org/mirrors/node-sass/
> * PHANTOMJS_CDNURL=https://npm.taobao.org/dist/phantomjs
> * CHROMEDRIVER_CDNURL=http://npm.taobao.org/mirrors/chromedriver

2. nvm list
> * * 8.9.0 (Currently using 32-bit executable)
> *   8.4.0
> *  6.11.3

3. nvm install v8.9.0 32  #安装V8.9 32bit
4. nvm use v8.9.0 32  #切换到V8.9 32bit

## 安装yarn
npm i -g yarn

## 安装npm源切换器
1. npm i -g nrm
2. nrm ls  #列出所有的npm源
> *   npm ---- https://registry.npmjs.org/
> *   cnpm --- http://r.cnpmjs.org/
> * * taobao - https://registry.npm.taobao.org/
> *   nj ----- https://registry.nodejitsu.com/
> *   rednpm - http://registry.mirror.cqupt.edu.cn/
> *   npmMirror  https://skimdb.npmjs.com/registry/
> *   edunpm - http://registry.enpmjs.org/

3. nrm use taobao  #选择taobao源

## 安装yrm源切换器用于yarn，方法同nrm

## 不要使用cnpm，尤其是混用cnpm和npm，cnpm自己创建了快捷方式的文件夹