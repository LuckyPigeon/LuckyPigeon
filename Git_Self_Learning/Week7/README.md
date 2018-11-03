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
![](../image/git%20branch.jpg)
## Label
* 而Label就是當在樹枝(新的branch)或樹幹(master branch)commit的時候，commit本身會形成一個節點，使用`$ git log --oneline --graph`可以看出來，用source tree也可以看出來，而新該節點就可以稱為label
## 身為一個mxnet contributer，最近在trace mxnet的跟目錄時，發現了一些有趣的事情~
### Snapcraft
### ReadtheDocs
### AppVeyor
