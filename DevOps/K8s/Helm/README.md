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
* To avoid this situation, we need to tiller's service account in kubernetes, so we need to create a file named rbac-config.yaml. For any detail, please check on [Role-based Access Control](https://docs.helm.sh/using_helm/#role-based-access-control).
### Create rbac-config.yaml
* Create a file named rbac-config.yaml and type the following code:
```sh
apiVersion: v1
kind: ServiceAccount
metadata:
  name: tiller
  namespace: kube-system
---
apiVersion: rbac.authorization.k8s.io/v1beta1
kind: ClusterRoleBinding
metadata:
  name: tiller
roleRef:
  apiGroup: rbac.authorization.k8s.io
  kind: ClusterRole
  name: cluster-admin
subjects:
  - kind: ServiceAccount
    name: tiller
    namespace: kube-system
```
* Create tiller
```sh
$ kubectl create -f rbac-config.yaml
```
