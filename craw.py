import re
from urllib.request import urlopen
from bs4 import BeautifulSoup
from selenium import webdriver

def crawler(song, artist):
    yturl = 'https://www.youtube.com/'
    html = urlopen('https://www.youtube.com/results?search_query=' + re.sub(' ', '+', song) + '+' + re.sub(' ', '+', artist) + '+lyrics')
    bsObj = BeautifulSoup(html.read(), 'html.parser')

    s = str(bsObj)
    result = re.findall(r'/watch.+?"', s)[0]
    result = yturl + result

    driver = webdriver.Chrome(executable_path = 'D:\chromedriver.exe')
    driver.get('https://www.youtubeto.com/zh/')
    driver.find_element_by_id('url').send_keys(result)
    driver.find_element_by_id('DownloadMP3').click()

    driver.quit()
