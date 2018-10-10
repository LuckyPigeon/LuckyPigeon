# Lecture 1
## Git基礎流程練習
* 關鍵字: hacktoberfest 2018
* 報名至10/31
* 送五個PR就可以得到hacktoberfest 2018上衣x1+很多github&digitalocean的小貼紙
![](https://hacktoberfest.digitalocean.com/assets/hacktoberfest-2018-social-card-c8d2e1489f647f2e0a26e6f598adeb760872818905b34cd437afc7ac2857ceab.png)
### 第一步
#### 創建世界
`$ git init <directory_name> && cd <directory_name>`
#### 查看目前有多少平行宇宙
`$ git remote -v`
#### 設定平行宇宙
`$ git remote add <new_remote_name> <site>`
or
#### 將舊世界更新為新世界
`$ git pull <remote_name> <remote_branch>:<local_branch>`
### 第二步
* 這個步驟在自己的專案中可以省略
#### 查看分支
* 通常一開始會在master
`$ git branch`
#### 新增分支
`$ git branch <new_branch_name>`
#### 切換分支
`$ git checkout <branch_name>`
### 第三步
#### 加入更新列表
* 在更改完成後
1) 將現在目錄以下的所有檔案加入更新列表
`$ git add .`
or
2) 將所有檔案加入更新列表
`$ git add -a`
or
3) 將特定檔案加入更新列表(俗稱手動更新)
`$ git add <file_name>`
### 第四步
#### 在記錄檔裡面寫上"做了什麼事"
`$ git commit -m "<message>"`
#### 檢查記錄檔
* 這個步驟是選擇性的
* 這個指令的格式不太令人喜歡
* 按q離開
`$ git log`
* 我通常會加上兩個參數
* --oneline -> 一行表示完一個紀錄 --graph -> 畫出圖表
### 第五步
#### 將自己的更新公開
* remote_branch是主宇宙的branch名稱，通常是origin
* 兩個branch_name通常會是同一個名稱，表示"我要從本地端的a分支公開到世界端的b分支"
`$ git push <remote_branch> <branch_name>:<branch_name>`
### 第六步
#### 檢查是否一切更新到定位
`$ git pull <remote_name> <branch_name>:<branch_name>`
