import os, sys, argparse
from cairosvg import svg2png
from wordcloud import WordCloud
from selenium import webdriver
from selenium.webdriver.common.by import By
# Can add argparse in the future
parser = argparse.ArgumentParser(description = 'Get optional wordcloud effect')

parser.add_argument('-t', '--text-path', action = 'store', type = str, help = 'File path of your text file')
parser.add_argument('-f', '--font', action = 'store', type = str, help = 'Font of your text')
parser.add_argument('-sp', '--spiral', action = 'store', type = int, help = 'Spiral of wordcloud, 0 for Archimedean, 1 for Rectangular')
parser.add_argument('-sc', '--scale', action = 'store', type = int, help = 'Scale of wordcloud, 0 for log n, 1 for sqrt n, 2 for n')
parser.add_argument('-a', '--angle', action = 'store', type = int, help = 'The step of each word\'s angle for wordcloud')
parser.add_argument('-af', '--angle-from', action = 'store', type = int, help = 'The start interval of step of angle')
parser.add_argument('-ae', '--angle-end', action = 'store', type = int, help = 'The end interval of step of angle')
args =parser.parse_args()

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
def SVG2PNG(imgin, imgout):
	svg2png(url = imgin, write_to = imgout)

	return 

def main():
	driver.get(url)

	text = ['wordcloud.txt']
	font = 'impact'
	angle = 5
	angle_from = -60
	angle_to = 60
	spiral = 0
	text, font, angle, angle_from, angle_to, spiral, scale = get_input() # With argparse

	driver.quit()
