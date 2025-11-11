from flask import Flask
app = Flask(__name__)

@app.route('/')
#注册 URL 路由，将 URL 路径映射到处理函数
def hello_world():
    return 'Hello, World from WSL!'

if __name__ == '__main__':
#检查当前脚本是否被直接运行
#这个条件确保下面的代码只在直接运行此脚本时执行
#如果这个文件被其他 Python 文件导入，__name__ 就不是 '__main__'，下面的代码不会运行
 app.run(debug=True)


