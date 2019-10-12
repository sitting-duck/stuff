from selenium import webdriver
#from selenium.webdriver.common.keys import Keys
#import time
from selenium.webdriver.common.action_chains import ActionChains

login_page = "https://www.videos.com/login"

video_page = "https://www.videos.com/videos/footage/slow-motion?libraryId=1&page=40&sort=most_relevant&video_quality=HD"

driver = webdriver.Chrome(executable_path="C:\\Users\\Downloads\\chromedriver.exe")

driver.get(login_page)

email_input = driver.find_element_by_name("email")

email_address = ""

email_input.send_keys(email_address)

password_input = driver.find_element_by_name("password")

password = ""

password_input.send_keys(password)

login_button = driver.find_element_by_class_name("btn-primary")
login_button.click()


#browser = webdriver.FireFox()

# doesn't work
#download_icon = driver.find_element_by_link_text("DownloadIcon")

#download_icon = driver.find_element_by_name("DownloadIcon")

#download_icon = driver.find_element_by_css_selector("[title*='DownloadIcon']")

driver.get(video_page)
driver.get(video_page)

#class_name = "action-wrapper download-button action-download"





#hover = ActionChains(driver).move_to_element(download_icon).perform()
videos = driver.find_elements_by_css_selector("video")

for video in videos:

    hover = ActionChains(driver).move_to_element(video).perform()

    download_icon = driver.find_element_by_class_name("download-button").click()

    driver.find_element_by_class_name("download-trigger").click()





#driver.close()








