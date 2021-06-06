# Vue.js实战
## 第二篇 进阶篇
### 11. 插件
#### 11.1 前端路由与vue-router
##### 11.1.1 什么是前端路由
前端路由，即由前端来维护一个路由规则。实现有两种，一种是利用url的hash，就是常说的锚点#，JavaScript通过hashChange事件来监听url的改变，IE7及以下需要用轮询；另一种就是HTML5的History模式，它使url看起来像普通网站那样，以"\"分割，没有#，但页面并没有跳转，不过使用这种模式需要服务端支持，服务端在接收到所有的请求后都指向同一个html文件，不然会出现404.因此，SPA只有一个html，整个网站所有的内容都在这一个html里，通过JavaScript来处理。

##### 11.1.2 vue-router基本用法
- NPM安装vue-router
```
  npm nstall --save vue-router
```
- 在main.js里使用Vue.use()加载插件
```javascript
  import Vue from 'vue'
  import VueRouter from 'vue-router'
  import App from './app.vue'

  Vue.use(VueRouter)
```
- 每个页面对应一个组件，也就是对应一个.vue文件。
- 回到main.js里，完成路由的剩余配置。创建一个数组来制定路由匹配列表，每一个路由映射一个组件
```javascript
  const Routers=[
      {
          path:'/index',
          component:
      },
      {
          path:'/about',
          component:

      }
  ];
```
- 然后继续在main.js里完成配置和路由实例
```javascript
    const RouterConfig={
        //使用HTML5的History路由模式
        mode:'history',
        routes:Routes
    };
    const router=new VueRouter(RouterConfig)

    new Vue({
        .....
    })
```
在RouterConfig里，设置mode为histroy会开启HTML5的History路由模式，通过"/"设置路径。如果不配置mode，就会使用#来设置路径。开启History路由，在生产环境时服务端必须进行配置，将所有路由都指向同一个html，或设置404页面为该html，否则刷新页面会出现404。
- webpack-dev-server也要配置下来支持Histroy路由，在package.json中修改dev命令：
```javascript
  "scripts":{
      "dev":"webpack-dev-server --open --history-api-fallback --config webpack.config.js"
  }
```
  增加了--history-api-fallback，所有的路由都会指向index.html。
- 配置好了这些，最后在跟实例app.vue里再添加一个路由视图<router-view>来挂载所有的路由组件：
- 运行npm run dev 启动服务，然后访问127.0.0.1:8080就可以访问这两个页面了。
- 路由列表的path也可以带参数，如{path:'/user/:id'}

##### 11.1.4 高级用法
在页面发生路由改变时，统一设置。vue-router提供了导航钩子beforeEach和afterEach，它们会在路由即将改变前和改变后触发。
```javascript
const router new VueRouter(RouterConfig);
router.beforeEach((to,from,next))
```