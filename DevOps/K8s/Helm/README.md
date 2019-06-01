![](https://sweetcode.io/wp-content/uploads/2018/06/helm_logo_transparent.png)
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
* Add tiller's service account in kubernetes, which need to create a file named rbac-config.yaml. For any detail, please check on [Role-based Access Control](https://docs.helm.sh/using_helm/#role-based-access-control).
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
$ sudo swapoff -a
$ kubectl create -f rbac-config.yaml
```
## Use helm with minikube
```sh
$ sudo swapoff -a
$ minikube start
```
## Use helm to deploy tiller
```sh
$ helm init --service-account tiller --skip-refresh
$ kubectl get pod -n kube-system -l app=helm # Get tiller pod
$ helm version # Get helm's verion
```
## Use helm to deploy nginx ingress
* Ingress is one of k8s resources, and a way to deploy k8s cluster to outside.
* Helm is compose by Ingress & Ingress Controller
* There's a lot of Ingress Controller, such as Nginx, HAProxy, Traefik ... etc.
### Search nginx-ingress library
```sh
$ helm search nginx-ingress
```
### Use helm to deploy Nginx Ingress Controller
* There are two ways
  * hostNetwork `controller.hostNetwork=true`
  * exteralIP (recommend)
  `$ helm install --name nginx-ingress --set "rbac.create=true,controller.service.externalIPs[0]=192.168.10.123,controller.service.externalIPs[1]=192.168.10.124,controller.service.externalIPs[2]=192.168.10.125" stable/nginx-ingress # Activate rbac support`
### Get service & ingress
```sh
$ kubectl get service # Check service has been set up
$ kubectl get ingress # Check ingress has been set up
```
## Access Nignx Ingress Controller
```sh
$ kubectl --namespace default get services -o wide -w nginx-ingress-controller # Use this to get externalip
```
