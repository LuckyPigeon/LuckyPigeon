# Week 7
## Tag
* 在git裡面，你可以在自己的repo上標記版本，而這個標記的標籤就叫做tag
* 基本上Tag有四種運作方式
* 第一種，列出所有標籤，假設新的版本是v1.4
`$ git tag`
or
`$ git tag -l v1.4`
* 第二種，建立標籤，假設新的版本是v1.4
```
$ git tag -a v1.4 -m 'my version 1.4' 新增一個含有附註的tag
$ git tag 看看tag是否新增成功了
$ git show v1.4 顯示tag的詳細資訊
```
* 第三種，簽署標籤，這個操作是建立在假設使用者有gpg private key的時候，假設新的版本是v1.5
```
$ git tag -s v1.5 -m 'my signed 1.5 tag' 簽署tag
$ git show v1.5 顯示tag的詳細資訊
```
* 第四種，驗證標籤，這個操作是建立在假設使用者有gpg public key的時候，假設新的版本是v1.5
`$ git -v tag v1.5`
* 如果沒有gpg public key的話，會顯示
```
gpg: Signature made Wed Sep 13 02:08:25 2006 PDT using DSA key ID F3119B9A
gpg: Can't check signature: public key not found
error: could not verify the tag 'v1.5'
```
## Branch
* Branch就像是樹枝的分支，而git像是一個環狀的大樹，用專業術語來說，可以說是DAG(有向無環圖)，長出的樹枝繼承了原有的資料(檔案)，並且在樹枝上可以新增新的資料(檔案)
![](../image/git%20branch.png)
## Label
* 而Label就是當在樹枝(新的branch)或樹幹(master branch)commit的時候，commit本身會形成一個節點，使用`$ git log --oneline --graph`可以看出來，用source tree也可以看出來，而新該節點就可以稱為label
## 身為一個mxnet contributer，最近在trace mxnet的跟目錄時，發現了一些有趣的事情~
### Snapcraft
* 當你的App想要在LINUX的各種[distribution](https://zh.wikipedia.org/wiki/Linux%E5%8F%91%E8%A1%8C%E7%89%88)都能跑的話，就可以把你的app丟上snapcraft，snapcraft會自動將你的系統對所有你想要發布的LINUX版本進行測試，讓你的APP可以橫跨多個LINUX distribution
* 當然由於snapcraft上你可以發布自己的專案上去，也可以將許多跨平台的package抓下來套用在自己的專案上
* 主要需要設定snapcraft.yml，這裡面定義了該專案snapcraft所需的設定，另外要加上snap.<language>如snap.python這樣的語言平台設定，參考下面簡介來取得更詳細的資訊
* [這是snapcraft的簡介](http://os.51cto.com/art/201708/548494.htm)
### ReadtheDocs
* 所有的專案都免不了寫說明文件，但現在有許多大廠都有自己的一套格式，每個使用者愛好的說明文件格式也都不一樣，有些人喜歡PDF，有些人則愛好原生html
* 因此ReadtheDocs誕生了
* 主要設定一個readthedocs.yml就可以讓使用者用多平台來閱讀說明文件了
* [ReadtheDocs Docs](https://docs.readthedocs.io/en/latest/yaml-config.html)
### AppVeyor
* 剛剛提到了要在LINUX上面跨版本執行專案、那麼現今最多人使用的WINDOWS也必須要有一個這樣的軟體，才能讓自己的專案普及化~
* AppVeyor就是在做這件事，AppVeyor是模擬專案在WINDOWS上的CI/CD，測試並部屬，讓專案最後也能在WINDOWS上發揚光大
* [AppVeyor簡介加教學](https://ypwalter.blogspot.com/2017/03/windows-ci-appveyor.html)
