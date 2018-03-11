#! /usr/bin/python3
# -*- coding: utf-8 -*-
# A KKBOX Downloader
from urllib.request import urlopen
from urllib.error import HTTPError
from urllib.error import URLError
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.support.ui import Select
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait
from time import sleep
import re
import random
import os
import sys

def downloader(src_url, name, dirpath = './music_test/'):
	# src_url, path + song_name
	print('src_url : ' + src_url + ', name : ' + name + ', dirpath' + dirpath)
	if dirpath != '.': os.chdir(dirpath)
	return os.system('wget ' + src_url + ' -O ' + name)

def OnlineConverter(yt_url):
	driver = webdriver.PhantomJS()
	# driver = webdriver.Firefox()
	driver.get('https://www.onlinevideoconverter.com/video-converter')
	driver.find_element_by_id('texturl').send_keys('https://www.youtube.com' + yt_url)
	driver.find_element_by_id('convert1').click()
	# download_but = WebDriverWait(driver, 20, 0.5).until(EC.presence_of_element_located((By.ID, 'downloadq')))
	# download_but.find_element_by_id('downloadq').click()
	sleep(20)
	src_bsObj = BeautifulSoup(driver.page_source, 'html.parser')
	driver.close()
	src_url = re.findall(r'href="http://s.*?"', str(src_bsObj.findAll('a')))
	src_url = re.sub(r'href="', '', src_url[0])
	src_url = re.sub(r'"', '', src_url)

	return src_url

def passtube(keyarr):

	url = "https://www.youtube.com/results?search_query="
	for subkey in keyarr: url += subkey + '+'
	url += "lyrics"
	url = re.sub(r',', '', url)
	# can't use else directly
	try:
		html = urlopen(url)
	except URLError as e:
		print(e)
	# else:
	#	print("Other error")
	#	return -1
	bsObj = BeautifulSoup(html.read(), 'html.parser')
	bsObj = bsObj.findAll('div', {'class': 'yt-lockup-content'})
	yt_url = re.findall(r'href="/watch.*?"', str(bsObj[0]))
	yt_url = str(yt_url[0])
	yt_url = re.sub(r'href="', '', yt_url)
	yt_url = re.sub(r'"', '', yt_url)

	return yt_url

def kkbox_daily_single(target):

	url = "https://kma.kkbox.com/charts/daily/song?terr=tw&lang=tc&cate=390"
	try:
		html = urlopen(url)
	except HTTPError as e:
		print("HTTPError")
		return -1, -1, -1
	except URLError as e:
		print("URLError")
		return -1, -1, -1	
	# song_name error will return -1, but I didn't deal with that in print yet
	except ContentTooShortError as e:
		print("ContentTooShortError")
		return -1, -1, -1
	'''
	else:
		print("Other Error")
		return -1, -1, -1
	'''

	bsObj = BeautifulSoup(html.read(), "html.parser")
	bsObj = bsObj.findAll('script')[-2]
	musicstr = bsObj.text
	musicstr = re.sub('\n', '', musicstr)
	musicstr = re.sub(r'\\', '', musicstr)
	musicstr = re.split('var', musicstr)[3]
	
	song_name = re.findall(r'"song_name":".*?"', musicstr)
	artist_name = re.findall(r'"artist_name":".*?"', musicstr)
	rankings = re.findall(r'"rankings":{"this_period":.*?,"last_period":.*?}', musicstr)

	for i in range(len(song_name)): 
		song_name[i] = re.sub(r'"song_name":"', '', song_name[i])
		song_name[i] = re.sub(r'"', '', song_name[i])
		artist_name[i] = re.sub(r'"artist_name":"', '', artist_name[i])
		artist_name[i] = re.sub(r'"', '', artist_name[i])
		rankings[i] = re.sub(r'"rankings":{', '', rankings[i])
		rankings[i] = re.sub(r'}', '', rankings[i])

	
	song_name = song_name[:target]
	artist_name = artist_name[:target]
	rankings = rankings[:target]

	return song_name, artist_name, rankings 
	
def kkbox_daily_new(target):

	url = "https://kma.kkbox.com/charts/daily/newrelease?terr=tw&lang=tc&cate=390"
	try:	
		html = urlopen(url)
	except HTTPError as e:
		print("HTTPError")
		return -1, -1, -1
	except URLError as e:
		print("URLError")
		return -1, -1, -1
	except ContentTooShortError as e:
		print("ContentTooShortError")
		return -1, -1, -1
	'''
	else:
		print("Other Error")
		return -1, -1, -1
	'''

	bsObj = BeautifulSoup(html.read(), 'html.parser')
	bsObj = bsObj.findAll('script')[-2]
	musicstr = bsObj.text
	musicstr = re.sub('\n', '', musicstr)
	musicstr = re.sub(r'\\', '', musicstr)
	musicstr = re.split('var', musicstr)[3]

	song_name = re.findall(r'"song_name":".*?"', musicstr)
	artist_name = re.findall(r'"artist_name":".*?"', musicstr)
	rankings = re.findall(r'"rankings":{"this_period":.*?,"last_period":.*?}', musicstr)

	for i in range(len(song_name)): 
		song_name[i] = re.sub(r'"song_name":"', '', song_name[i])
		song_name[i] = re.sub(r'"', '', song_name[i])
		artist_name[i] = re.sub(r'"artist_name":"', '', artist_name[i])
		artist_name[i] = re.sub(r'"', '', artist_name[i])
		rankings[i] = re.sub(r'"rankings":{', '', rankings[i])
		rankings[i] = re.sub(r'}', '', rankings[i])

	song_name = song_name[:target]
	artist_name = artist_name[:target]
	rankings = rankings[:target]

	return song_name, artist_name, rankings

def main():
	'''
	song_type = input("新歌或單曲: ")
	target = eval(input("請輸入要下載前幾名的歌曲: "))
	'''
	strpath = input("請輸入下載的地址(0為沒有): ")
	
	target = 2

	if sys.argv[1] == "新歌":
		song_name, artist_name, rankings = kkbox_daily_new(target)
	else:
		song_name, artist_name, rankings = kkbox_daily_single(target)
	
	# song_name error will return -1, but I didn't deal with that in print yet
	if(song_name == -1):
		print(sys.argv[1] + "函式錯誤")
		return
	for i in range(target):
		print("Song Name: ", song_name[i],", Artist Name: ", artist_name[i],", Rankings: ", rankings[i])

	for i in range(target):
		# print("Song Name: ", song_name[i],", Artist Name: ", artist_name[i],", Rankings: ", rankings[i])

		# keyarr is the string of the keyword
		tmp_song_arr = song_name[i].split()
		tmp_artist_arr = artist_name[i].split()
		keyarr = tmp_artist_arr + tmp_song_arr
		yt_url = passtube(keyarr) # keyarr = song_name.split() + artist_name.split()
		src_url = OnlineConverter(yt_url) # url is the youtube music url with lyrics
		print(src_url)
		name = ''
		'''
		for artist in artist_name: name += artist + '\ '
		name += '-\ '
		for song in song_name: name += song + '\ '
		'''
		for i in keyarr: name += i + '\ '
		name = re.sub(',', '', name)
		name = re.sub('\(', '', name)
		name = re.sub('\)', '', name)
		'''
		if dirpath: 
			music_file = downloader(src_url, name, dirpath)
		else: 
			music_file = downloader(src_url, name)
		'''
		music_file = downloader(src_url, name)
		os.chdir('..')
		if music_file: print('Download Error !\n')

if __name__ == "__main__":
	main()
