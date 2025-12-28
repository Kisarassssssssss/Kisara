from selenium import webdriver
 
# 设置浏览器驱动路径
driver = webdriver.Chrome()
 
# 打开网页
driver.get('https://www.baidu.com')
 
# 获取网页标题
print(driver.title)
 
# 关闭浏览器
driver.quit()