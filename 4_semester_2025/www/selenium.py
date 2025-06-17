from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
import time

service = Service() 
driver = webdriver.Chrome(service=service)

try:
    driver.get("https://www.w3schools.com/html/tryit.asp?filename=tryhtml_button_test")
    driver.switch_to.frame("iframeResult")

    button = driver.find_element(By.TAG_NAME, "button")
    print("Clicking the button...")
    button.click()

    time.sleep(3)

finally:
    driver.quit()
