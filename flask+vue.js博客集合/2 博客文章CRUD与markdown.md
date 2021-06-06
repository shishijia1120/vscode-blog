# 博客文章CRUD与Markdown
## 1. 后台
---
### 1.1 数据库
Post数据模型：
```python
class Post(PaginatedAPIMixin, db.Model):
    __tablename__ = 'posts'
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(255))
    summary = db.Column(db.Text)
    body = db.Column(db.Text)
    timestamp = db.Column(db.DateTime, index=True, default=datetime.utcnow)
    views = db.Column(db.Integer, default=0)
```
## 1.2 RESTful API设计
创建app/api/posts.py:

## 2. 前端博客CURD操作
---
预设实现功能：
1. 发布文章功能
    - 难点：post的body需要支持markdown
2. 显示博客列表
    - 显示内容（post.title/summary/body/time/author/view/及author._avator），其中body只能截取一定字数。注意布局美观
    - 如果是用户自己发布的博客，出现编辑和删除按钮
    - 点击用户头像或用户名，需跳转到用户的profile页面
    - 点击博客title或阅读全文需需跳转到博客详情页面
    - 重点：分页导航条的设计
3. 显示博客详情
    - 基本功能，显示博客的title、author、time、 view、body（借助组件vue-markdown）还有文章目录
    - 提供编辑、删除按钮
    - 后续功能，显示评论
4. 编辑博客
   - 点击编辑后，在home页面直接出现窗口
5. 删除博客
### 2.1 发布文章支持Markdown
1. 在element -ui中使用markdown编辑器：

- 下载组件mavon-editor
```
cnpm install mavon-editor -S
```
   - 在home.vue中引入组件
```javascript
<script>
  import { mavonEditor } from 'mavon-editor'
  import 'mavon-editor/dist/css/index.css'
</script>

comoponents: {
    mavonEditor
}
```
  - 使用组件
```html
 <mavon-editor style="height: 100%;width: 100%;" v-model="value"></mavon-editor>
```
2. 表单内容html
```html
<div>
    <el-form
      v-if="sharedState.is_authenticated"
      :label-position="labelPosition"
      label-width="80px"
      :model="postForm"
      :rules="rules">
      <el-form-item label="标题" prop="title">
        <el-input v-model="postForm.title"></el-input>
        <small v-show="postForm.titleError">{{postForm.titleError}}</small>
      </el-form-item>
      <el-form-item label="摘要" prop="summary">
        <el-input v-model="postForm.summary"></el-input>
      </el-form-item>
      <el-form-item label="内容" prop="body">
        <mavon-editor style="height: 100%;width: 100%;" v-model="postForm.body"></mavon-editor>
        <small v-show="postForm.bodyError">{{postForm.bodyError}}</small>
      </el-form-item>
    </el-form>
    <div style="display:flex;justify-content:center;">
      <el-button type="primary" @click="onSubmitAdd">发布</el-button>
    </div>
  </div>
``` 
3. 提交表单的onSubmitAdd()方法
```javascript
onSubmitAdd(e) {
      this.postForm.errors = 0;
      if (!this.postForm.title) {
        this.postForm.errors++;
        this.postForm.titleError = "Title is required.";
      } else {
        this.postForm.titleError = null;
      }

      if (!this.postForm.body) {
        this.postForm.errors++;
        this.postForm.bodyError = "Body is required.";
        // 给 bootstrap-markdown 编辑器内容添加警示样式，而不是添加到 #post_body 上
        // $(".md-editor")
        //   .closest(".form-group")
        //   .addClass("u-has-error-v1"); // Bootstrap 4
      } else {
        this.postForm.bodyError = null;
      }

      if (this.postForm.errors > 0) {
        // 表单验证没通过时，不继续往下执行，即不会通过 axios 调用后端API
        return false;
      }

      const path = "/api/posts";
      const payload = {
        title: this.postForm.title,
        summary: this.postForm.summary,
        body: this.postForm.body
      };
      this.$axios
        .post(path, payload)
        .then(response => {
          //handle success
          this.getPosts();
          this.$toasted.success("发布成功", { icon: "fingerprint" });
          (this.postForm.title = ""),
            (this.postForm.summary = ""),
            (this.postForm.body = "");
        })
        .catch(error => {
          //handle error
          consloe.log(error.response.data);
        });
    },
```
### 2.2 显示博客列表

1. 博客列表页面
```html
  <div v-if="posts" class="postsList">
    <div v-for="(post, index) in posts.items" :key="index">
      <router-link :to="{path: `/user/${post.author.id}`}" :title="post.author.name || post.author.username">
          <el-avatar size="small" :src="post.author._links.avatar"></el-avatar>
      </router-link>

      <div class="media-body">
      <div class="">
        <h5>
           <router-link v-bind:to="{ path: `/post/${post.id}`}">{{post.title}}</router-link>
        </h5>
        <div>
        <span>{{$moment(post.timestamp).fromNow()}}</span> / <router-link :to="{path: `/user/${post.author.id}`}"><span v-if="post.author.name">{{post.author.name}}</span><span v-else>{{post.author.username}}</span></router-link>
      </div>
      </div>

      <vue-markdown
        :source="post.summary" v-highlight>
      </vue-markdown>

    <div>
    <ul>
      <li>{{post.views}}</li>
      <li>
        <router-link v-bind:to="{path: `/post/${post.id}`}">阅读全文</router-link>
      </li>
      <li v-if="post.author.id==sharedState.user_id">
          <el-button type="primary">编辑</el-button>
      </li>
       <li v-if="post.author.id==sharedState.user_id">
          <el-button type="primary">删除</el-button>
      </li>
    </ul>
    </div>

  </div>
    </div>
  </div>
```
2. 实现方法getPosts()
```python
created () {
  this.getPosts()
  ...
}
```
3. 重点：分页导航条的实现：
### 2.3 显示博客详情
1. 显示博客详情流程：在博客列表页面，点击某一条博客的title或阅读全文按钮，v-bind:to="{ path: `/post/${post.id}`}".
跳转到postDatail.vue。

```javascript
export default {
  name: 'Post',
  components: {
    VueMarkdown
  },
  data() {
    return {
      sharedState: store.state,
      post: {},
      editForm: {
        title: '',
        summary: '',
        body: '',
        errors: 0,  // 表单是否在前端验证通过，0 表示没有错误，验证通过
        titleError: null,
        bodyError: null
      },
      showToc: true
    }
  },
  methods: {
    getPost (id) {
      const path = `/api/posts/${id}`
      this.$axios.get(path)
        .then((response) => {
          this.post = response.data
        })
        .catch((error) => {
          // eslint-disable-next-line
          console.error(error)
        });
    },
 created () {
    const post_id = this.$route.params.id
    this.getPost(post_id)
```

已经获得对应的post,显示具体详情的页面，尤其是显示博客的内容body：



(1) vue-markdown

由于后台python自动转换成HTML文档，数据库中只保存Markdown原文，前端渲染使用vue-markdown插件
```
cnpm install vue-markdown --save
```
在Post.vue中，引入子组件vue-markdown:
```python
<template>
  <div class="container">
    ...
           <!-- vue-markdown 开始解析markdown，它是子组件，通过 props 给它传值即可 -->
            <vue-markdown
              :source="post.body">
            </vue-markdown>
    ...
  </div>
</template>
<script>
// 导入 vue-markdown 组件解析 markdown 原文为　HTML
import VueMarkdown from 'vue-markdown'
export default {
  name: 'Post',
  components: {
    VueMarkdown
  },
  data() {
    return {
      sharedState: store.state,
      post: {}, //注意post类型为{}
      editForm: {
        title: '',
        summary: '',
        body: '',
        errors: 0,  
        titleError: null,
        bodyError: null
      },
      showToc: true
    }
  },
  ...
</script>
```
此时，页面中代码是没有语法高亮的。



(2) highlight.js
使用highlight.js语法高亮：
- 安装highlight.js
```
cnpm install highlight.js --save
```
在postDetail.vue组件中：
```javascript
<script>
// vue-router 从 Home 页路由到 Post 页后，会重新渲染并且会移除事件，自定义的指令 v-highlight 也不生效了
// 所以，这个页面，在 mounted() 和 updated() 方法中调用 highlightCode() 可以解决代码不高亮问题
import hljs from 'highlight.js'
const highlightCode = () => {
  let blocks = document.querySelectorAll('pre code');
  blocks.forEach((block)=>{
    hljs.highlightBlock(block)
  })
}

export default {
  ...
  mounted () {
    highlightCode()
  },
  updated () {
    highlightCode()
  }
}
</script>
```
先选中一款模板，在front-end/src/main.js中导入css文件
```javascript
// 样式文件，浅色：default, atelier-dune-light  深色：atom-one-dark, atom-one-dark-reasonable, monokai
import 'highlight.js/styles/atom-one-dark-reasonable.css'
```
(3) 做文章目录(有点难，暂空)
2. 编辑博客
3. 删除博客
### 2.4 修改博客
用户登录后，自己发布的文章会显示编辑按钮，点击后显示编辑表单：

### 2.5删除博客
用户登录后，自己发布的文章会显示删除按钮，同时使用vue-sweetalert2插件弹出警告信息：
```
cnpm install --save vue-sweealert2
```
修改main.js:
```javascript
import VueSweetalert2 from 'vue-sweetalert2'
Vue.use(VueSweetalert2)
```
在Home.vue组件中使用:
```javascript

```