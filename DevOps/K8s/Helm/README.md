# Helm
## Prerequisite
* docker
* kubectl
* (kubeadm + kubelet) or (minikube)
## Install Helm
### From source
```sh
$ wget https://github.com/helm/helm/archive/v3.0.0-alpha.1.tar.gz
$ tar -zxvf helm-v3.0.0-alpha-1-linux-amd64.tar.gz
$ cd linux-amd64/
$ cp helm /usr/local/bin/
```
### From Snap (Linux)
```sh
$ sudo snap install helm --classic
```
### From Homebrew (macOS)
```sh
$ brew install kubernetes-helm
```
### From Chocolatey or scoop (Windows)
```sh
$ choco install kubernetes-helm
or
$ scoop install helm
```

## Use Helm with kubeadm + kubelet
* If we execute `$ helm init`, we will get something like this `Error: Get http://localhost:8080/version: dial tcp 127.0.0.1:8080: connect: connection refused`
