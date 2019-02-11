# Docker相關操作

## Docker常用指令

### image相關
* docker images -> 列出image清單
* docker run <docker-image> -> 執行docker image，如果沒有該image，會從dockerhub自動拉一個下來

### container相關(container為執行中的image，每run一個image就會創建一個新的container
* docker exec -i <container-id> -> 執行一個特定container
* docker start <container-id> -> 重新啟動一個特定的container
* docker stop <container-id> -> 停止一個特定的container

## 如何包成Dockerfile

### 基礎用法(進入image之後就是admin囉!因此做什麼事情都不需要sudo!然後除了`IMAGE`外，其他的指令都是選擇性的)
* IMAGE -> 需要一個docker image當作基底
* ADD -> 將檔案加入創建的image的跟目錄中
* COPY -> 將檔案複製到創建的image的跟目錄中
* WORKDIR -> 啟動這個image的時候所要工作的目錄，基本上等於你的`$cd ~`
* RUN -> 需要執行的指令，注意這裡使用的每一個RUN都會創建一個新的container，因此每一次都會回到工作目錄上，因此切記如果要`$RUN cd ./my-folder/`的話，
cd之後要做的事情要用`&&`連起來呦~例如:`RUN cd ./my-folder && apt update`
* EXPOSE -> 要部屬上去的port
* ENV -> 環境變數，送給程式的外部變數
* CMD -> 最後要執行的指令，例如`$python myprogram.py`
### 範例
```
FROM node:8-alpine

WORKDIR /

ADD . /

RUN npm install

# ENV

EXPOSE 3000

CMD npm run start
```
* 寫完之後跑`$docker build -t mywebapp . --no-cache`

## 如何包成docker-compose.yml

### 直接上範例了
```
version: '1.0'
services:
  web:
    image: 
    # environment:
    ports: 3000:3000
    # depends_on:
    deploy: 
      replicas: 3
    update_config:
      parallelism: 2
      delay: 10s
    restart_policy:
      condition: on-failure
```
* 寫完之後跑`$docker-compose up`，如果要build成image，加一個`--build`就可以了
* 停止container使用`$docker-compose down`
