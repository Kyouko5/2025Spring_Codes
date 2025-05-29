from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options  # 导入Options操作类
import time
from datetime import datetime
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import getpass
 
# 获取当前日期（格式：YYYY-MM-DD）
current_date = datetime.now().strftime("%Y-%m-%d")
 
options = Options()
options.add_argument('--headless')  #无头模式
# 设置自动化特性扩展的关闭，防止被服务器检测到是由selenium驱动的
options.add_experimental_option('excludeSwitches', ['enable-automation'])
 
# 设置关闭自动化特性，防止被服务器检测到是由selenium驱动的
options.add_argument('--disable-blink-features=AutomationsControlled')
 
# 关闭证书报错
options.add_argument('ignore-certificate-errors')
# 启动 WebDriver（假设你使用的是 Chrome）  如果这里不进行传参数 就是有界面模式
driver = webdriver.Chrome(options = options)
# driver = webdriver.Chrome()
 
 
time.sleep(1)
 
 
def Longin():
    try:
        # 打开目标网页
        driver.get('https://kyfw.12306.cn/otn/resources/login.html')
 
        # 获取用户输入的账号和密码
        user = input("请输入用户名: ")
        # pwd = input("请输入密码: ")
        pwd = getpass.getpass("请输入密码: ")  # 输入时密码不会显示在屏幕上
 
        # 使用 XPath 定位用户名输入框并输入
        nameuser = driver.find_element(By.XPATH, '//div/input[@id="J-userName"]')
        time.sleep(1)
        nameuser.send_keys(user)
 
        # 定位密码输入框并输入
        password = driver.find_element(By.XPATH, '//div/input[@id="J-password"]')
        time.sleep(1)
        password.send_keys(pwd)
 
        # 登录按钮点击
        driver.find_element(By.XPATH, '//*[@id="J-login"]').click()
 
        # 后续代码保持不变
        code_id = input("请输入身份证后四位:")
        id_cord = driver.find_element(By.XPATH, '/html/body/div[1]/div[4]/div[2]/div[1]/div/div[1]/input')
        id_cord.send_keys(code_id)
        print("验证码正在发送中,请耐心等待")
        time.sleep(1)
        driver.find_element(By.XPATH, '//*[@id="verification_code"]').click()
        time.sleep(1)
        id_code = driver.find_element(By.XPATH, '//*[@id="code"]')
        code = input("请输入验证码:")
        id_code.send_keys(f"{code}")
 
        try:
            error_element = driver.find_element(By.XPATH, '//*[@id="message"]/p')
            if error_element.text == "用户名或密码错误":
                print("密码,用户名,验证码错误,请检查")
            else:
                print("登录成功")
                time.sleep(2)
                driver.find_element(By.XPATH, '//*[@id="link_for_ticket"]').click()
                time.sleep(2)
                driver.find_element(By.XPATH, '//*[@id="sureClick"]')
                train_list = Inquirer()
        except Exception as e:
            print(f"未找到错误提示元素: {e}")
 
    except  Exception as e:
        print("程序运行发生错误", e)

    return train_list
 
def Inquirer():
    try:
        chufadi = input("请输入出发地:")
        # 获取出发地输入框
        from_station_input = driver.find_element(By.XPATH, '//*[@id="fromStationText"]')
        # 清空输入框
        from_station_input.clear()
        # 输入出发地
        from_station_input.send_keys(chufadi)
 
        mudidi = input("请输入目的地:")
        end_station_input = driver.find_element(By.XPATH, '//*[@id="toStationText"]')
        end_station_input.clear()
        end_station_input.send_keys(mudidi)
        from datetime import datetime, timedelta
 
        try:
            # 获取当前日期
            current_date = datetime.now().strftime("%Y-%m-%d")
 
            # 获取用户输入
            user_input = input("不输入默认获取当日,回车跳过输入,输入出发时间格式(2025-5-20):")
 
            # 处理用户输入
            if not user_input.strip():  # 输入为空
                departure_date = current_date
                print(f"未输入日期，将查询今日({departure_date})车票")
            else:
                try:
                    # 验证并格式化日期
                    parsed_date = datetime.strptime(user_input, "%Y-%m-%d")
                    departure_date = parsed_date.strftime("%Y-%m-%d")
                except ValueError:
                    print("警告：输入日期格式不正确，将使用默认日期")
                    departure_date = current_date
 
            # 如果不是查询当日，需要更新日期输入框
            if departure_date != current_date:
                date_input = driver.find_element(By.XPATH, '//*[@id="train_date"]')
                date_input.clear()
                date_input.send_keys(departure_date)
 
            # 点击查询按钮（合并重复逻辑）
            query_button = driver.find_element(By.XPATH, '//*[@id="query_ticket"]')
            query_button.click()
            print(f"正在查询{departure_date}的车票，请稍后...")
 
            list_Train = []
            for trin in range(0, 20):
                dizhi = driver.find_element(By.XPATH, f'//*[@id="train_num_{trin}"]/div/strong')
                time.sleep(1)
                list_Train.append(dizhi.text)
                print(f"""
                出发地                   目的地                   到达时间 
        {list_Train[trin]}    {list_Train[trin+1]}       {list_Train[trin+2]}
                """)
 
        except Exception as e:
            print(f"程序运行发生错误,在输入日期 {e}")
 
    except Exception as e:
        print("程序运行发生错误,在输入地点", e)
        
    return list_Train
 
#下面这个会确定元素加载完才会进行下一步
 
def Get_ticket():
    time_list = []
    chechi_number = driver.find_element(By.XPATH, '//*[@id="trainum"]')
    chechi_number = int(chechi_number.text)
    for i in range(chechi_number):
        time_list.append(driver.find_element(By.XPATH, f'//*[@id="train_num_{i}"]/div[3]/strong[1]').text)
 
    move_time = input("请输入出发时间段,\n1: 06:00--12:00\n2: 12:00--18:00\n3: 18:00--24:00")
 
    # 创建显式等待对象
    wait = WebDriverWait(driver, 10)
 
    if move_time == '1':
        """
        //*[@id="cc_start_time"]/option[*]  选着时间段 
        #这个是通过固定时间选定这个预订标签  onclick 这个下面的时间 选着这个标签 
        //a[@class="btn72" and contains(@onclick, '21:02')]
        """
        driver.find_element(By.XPATH, '//*[@id="cc_start_time"]/option[3]').click()
        accurate_time = input("输入准确时间,将会自动购买靠近该时间的车票(12:00)")
        closest = get_closest_time(accurate_time, time_list)
        print(f"最接近 {accurate_time} 的时间是: {closest}")
        print('所有时间为', str(time_list))
 
        # 添加显式等待
        wait.until(
            EC.visibility_of_element_located((By.XPATH, f'//a[@class="btn72" and contains(text(), "{closest}")]')))
 
        # 点击预定按钮
        driver.find_element(By.XPATH, f'//a[@class="btn72" and contains(@onclick, "{closest}")]').click()
        time.sleep(1)
        driver.find_element(By.XPATH, '//*[@id="normalPassenger_0"]').click()  # 点击坐车人按钮
        driver.find_element(By.XPATH, '//*[@id="dialog_xsertcj_cancel"]').click()  # 点击取消按钮
        driver.find_element(By.XPATH, '//*[@id="submitOrder_id"]').click()  # 点击提交订单按钮
 
    if move_time == '2':
        driver.find_element(By.XPATH, '//*[@id="cc_start_time"]/option[4]').click()
        accurate_time = input("输入准确时间,将会自动购买靠近该时间的车票(12:00)")
        closest = get_closest_time(accurate_time, time_list)
        print(f"最接近 {accurate_time} 的时间是: {closest}")
        print('所有时间为', str(time_list))
 
        # 添加显式等待
        wait.until(
            EC.visibility_of_element_located((By.XPATH, f'//a[@class="btn72" and contains(text(), "{closest}")]')))
 
        # 点击预定按钮
        driver.find_element(By.XPATH, f'//a[@class="btn72" and contains(@onclick, "{closest}")]').click()
        time.sleep(1)
        driver.find_element(By.XPATH, '//*[@id="normalPassenger_0"]').click()  # 点击坐车人按钮
        driver.find_element(By.XPATH, '//*[@id="dialog_xsertcj_cancel"]').click()  # 点击取消按钮
        driver.find_element(By.XPATH, '//*[@id="submitOrder_id"]').click()  # 点击提交订单按钮
 
    if move_time == '3':
        driver.find_element(By.XPATH, '//*[@id="cc_start_time"]/option[5]').click()
        accurate_time = input("输入准确时间,将会自动购买靠近该时间的车票(12:00)")
        closest = get_closest_time(accurate_time, time_list)
        print(f"最接近 {accurate_time} 的时间是: {closest}")
        print('所有时间为', str(time_list))
 
        # 添加显式等待
        wait.until(
            EC.visibility_of_element_located((By.XPATH, f'//a[@class="btn72" and contains(text(), "{closest}")]')))
 
        # 点击预定按钮
        driver.find_element(By.XPATH, f'//a[@class="btn72" and contains(@onclick, "{closest}")]').click()
        time.sleep(1)
        driver.find_element(By.XPATH, '//*[@id="normalPassenger_0"]').click()  # 点击坐车人按钮
        driver.find_element(By.XPATH, '//*[@id="dialog_xsertcj_cancel"]').click()  # 点击取消按钮
        driver.find_element(By.XPATH, '//*[@id="submitOrder_id"]').click()  # 点击提交订单按钮
 
def get_closest_time(user_time, time_list):
    user_minutes = int(user_time[:2]) * 60 + int(user_time[3:])
    time_diffs = [(abs(int(t[:2]) * 60 + int(t[3:]) - user_minutes), t) for t in time_list]
    return min(time_diffs)[1]
 
 
if __name__ == '__main__':
    actual_trains = Longin()

    # 断言测试
    expected_trains = [
        'G5', 'G2817', 'G7', 'G1727', 'G2421', 'G9',
        'G11', 'G675', 'G1817', 'G1821', 'G139', 'G15'
    ]
    for train in expected_trains:
        assert train in actual_trains, f"未找到车次: {train}"
    print("所有预期车次均已正确输出！")
    input("回车结束")
    driver.quit()
 
# 等待一段时间以观察结果
# time.sleep()
input("回车结束")
# 关闭浏览器
driver.quit()
 
 