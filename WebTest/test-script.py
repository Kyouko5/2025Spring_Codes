'''
Author: Kyouko
Date: 2025-05-29 08:20:00
LastEditTime: 2025-05-29 08:27:30
Description: 请输入文件描述
FilePath: /Code/WebTest/test-script.py
'''
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options

options = Options()
options.add_argument('--headless')  # 无头模式
options.add_experimental_option('excludeSwitches', ['enable-automation'])
options.add_argument('--disable-blink-features=AutomationsControlled')

driver = webdriver.Chrome(options=options)

driver.get("https://www.baidu.com")
print(driver.title)
driver.quit()