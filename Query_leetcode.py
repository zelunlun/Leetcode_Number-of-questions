from selenium import webdriver
from selenium.webdriver.common.by import By
import sys
import time

account = sys.argv[1]


website = 'https://leetcode.com/' + account + '/'

driver = webdriver.Chrome()
try:
    driver.get(website)
except:
    print("Sytax")

time.sleep(3)
question_number = driver.find_element(By.CSS_SELECTOR, ".text-\[24px\].font-medium.text-label-1.dark\:text-dark-label-1")
print(f"Your Leetcode have sloved : {question_number.text} topics.")
