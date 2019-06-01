# Helm encounter error log
## Error: error installing: Post http://localhost:8080/apis/extensions/v1beta1/namespaces/kube-system/deployments: dial tcp 127.0.0.1:8080: connect: connection refused
### Minikube solution
* Type `$ minikube start` and you will success. <br>
  Reason: Becuase minikube will setup a k8s configuration file automatically.
### Local k8s solution
* Type the following commands:
```sh
$ mkdir -p $HOME/.kube
$ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
$ sudo chown $(id -u):$(id -g) $HOME/.kube/config
```
<br>
Reason: Set up a k8s configuration file manually
## Error: VERR_VM_DRIVER_INSTALLED-The support driver is not installed. On linux, open returned ENOENT (Minikube setup error)
### Solution
* Minikube support both virtualbox and kvm environment, so you can avoid the error with kvm installation.
  Reason: Intel i386 structure ubuntu can't install virtualbox because the support driver will not be installed
## Error: 0/1 nodes are available: 1 node(s) had taints that the pod didn't tolerate (Pod always stays pending).
### Solution
* Type `$ kubectl taint nodes --all node-role.kubernetes.io/master-`
  Reason: Need to master tainted and labelled with key/value
