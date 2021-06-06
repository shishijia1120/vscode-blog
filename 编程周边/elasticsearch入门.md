使用ipython测试elasticsearch
```python
from elasticsearch import Elasticsearch
es=Elasticsearch("http://192.168.221.130:9200")
# 1. 创建名为posts的index
es.indices.create(index="posts",ignore=400)
>>>{'acknowledged': True, 'shards_acknowledged': True, 'index': 'posts'}

mapping={'properties':{'content':{'type':'text','analyzer':'ik_max_word','search_analyzer':'ik_max_word'}}}

# 2. 设置Mapping，每个文档有个 content 字段，它的类型是 text，词法分析器是 ik
es.indices.put_mapping(index='posts',body=mapping)
>>>{'acknowledged': True}
# 3. 插入文档，每个文档必须使用唯一的 id
es.index(index='posts', id=1, body={'content': '美国留给伊拉克的是个烂摊子吗'})  

es.index(index='posts', id=2, body={'content': '公安部：各地校车将享最高路权'})

# 4. 搜索 '中国'
es.search(index='posts', body={'query': {'match': {'content': '中国'}}})

body = {
    ...:     "query" : { "match" : { "content" : "中国" }},
    ...:     "highlight" : {
    ...:         "pre_tags" : ["<tag1>", "<tag2>"],
    ...:         "post_tags" : ["</tag1>", "</tag2>"],
    ...:         "fields" : {
    ...:             "content" : {}
    ...:         }
    ...:     }
    ...: }

# 5. 搜索 '中国'，同时高亮关键词，比如实际项目中可以替换 <tag1></tag1> 为 <span style='color: red; background: yellow;'></span>
es.search(index='posts', body=body)  

# 6. 删除Index及里面的所有文档
es.indices.delete('posts') 
>>>{'acknowledged': True}
```