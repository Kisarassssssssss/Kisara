import requests
from bs4 import BeautifulSoup

url = 'https://www.baidu.com'

response = requests.get(url)
# 手动设置编码为utf-8
response.encoding = 'utf-8'

soup = BeautifulSoup(response.text, 'html.parser')
title = soup.title.text
print("网页标题:", title,"\n")
# 获取所有的<a>标签
links = soup.find_all('a')
 
# 打印所有链接
for link in links:
    href = link.get('href')
    print(href,"\n")