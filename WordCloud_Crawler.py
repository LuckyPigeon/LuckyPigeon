import os, sys, cairosvg
from wordcloud import WordCloud
from selenium import webdriver
from selenium.webdriver.common.by import By
# Can add argparse in the future
'''
text = "Chief Justice Roberts, President Carter, President Clinton, President \
        Bush, President Obama, fellow Americans, and people of the world: \
        thank you. We, the citizens of America, are now joined in a great \
        national effort to rebuild our country and to restore its promise for \
        all of our people. \
        Together, we will determine the course of America and the world for \
        years to come. \
        We will face challenges. We will confront hardships. But we will get \
        the job done. \
        Every four years, we gather on these steps to carry out the orderly \
        and peaceful transfer of power, and we are grateful to President Obama \
        and First Lady Michelle Obama for their gracious aid throughout this \
        transition. They have been magnificent."
'''

# wordcloud = WordCloud(background_color = "white", font_path = "/c/Users/user/Desktop/RemachineScript_Personal_Use.ttf", width = 800, height = 600).generate(text)
# wordcloud = WordCloud(background_color = "white", font_path = "./RemachineScript_Personal_Use.ttf", width = 800, height = 600).generate(text)

# wordcloud.to_file("./wordcloud_sample.png")
url = 'https://www.jasondavies.com/wordcloud/'

driver = webdriver.Chrome(executable_path = "D:\chromedriver.exe")
driver.get(url)

def Set_Text(text):
	tmp = ''
	
	f = open(text, 'r')
	for i in f.readlines():
		tmp += i

	f.close()

	text = tmp

	# Send text
	driver.find_element_by_id('text').clear()
	driver.find_element_by_id('text').send_keys(text)
	driver.find_element_by_id('go').click()

def Set_Spiral():
	# Send Spiral
	# driver.find_element_by_id('archimedean').click()
	driver.find_element_by_id('retangular').click()

def Send_Scale():
	# Send Scale
	# driver.find_element_by_id('scale-log').click()
	# driver.find_element_by_id('scale-sqrt').click()
	driver.find_element_by_id('scale-linear').click()

def Set_Font():
	# Set font
	driver.find_element_by_id('font').clear()
	driver.find_element_by_id('font').send_keys(font)

def Set_Angle():
	# Set angle
	driver.find_element_by_id('angle-count').clear()
	driver.find_element_by_id('angle-count').send_keys(angle)
	driver.find_element_by_id('angle-from').clear()
	driver.find_element_by_id('angle-from').send_keys(angle_from)
	driver.find_element_by_id('angle-to').clear()
	driver.find_element_by_id('angle-to').send_keys(angle_to)

def Word_Line():
	# Set one word per line
	driver.find_element_by_id('per-line').click()

def Downloads():
	# Download
	driver.find_element_by_id('download-svg').click()

# Convert svg to png
'''
def get_input():
	return 
'''
def main():

	convert_url = 'https://cloudconvert.com/'

	driver.get(url)

	text = ['wordcloud.txt']
	font = 'impact'
	angle = 5
	angle_from = -60
	angle_to = 60
	spiral = 0
	# text, font, angle, angle_from, angle_to = get_input() # With argparse

	driver.quit()
