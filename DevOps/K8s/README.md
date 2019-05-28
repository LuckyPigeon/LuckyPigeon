![](https://cdn-images-1.medium.com/max/1200/1*6NVMEmo0qDcQjpXcXI8dtg.png)
# This folder contains k8s sample codes and k8s documentation

## Directory tree
* example - K8s example<br>
  |- mypod-api.yml<br>
  |- myreplicacontroller-api.yml<br>
  |- myreplicaset-api.yml<br>
  |- mydeployment-api.yml<br>
  |- myserivce-api.yml<br>
  |- myhpa-api.yml
* README.md - This folder structure and k8s installation

## K8s installation

### Prerequisite
* docker

### With kubelet + kubeadm + kubectl
```sh
# kubelet + kubeadm + kubectl installation
$ sudo apt-get update && apt-get install -y apt-transport-https curl
$ curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
$ cat <<EOF >/etc/apt/sources.list.d/kubernetes.list
  deb https://apt.kubernetes.io/ kubernetes-xenial main
  EOF
$ sudo apt-get update
$ sudo apt-get install -y kubelet kubeadm kubectl
$ sudo apt-mark hold kubelet kubeadm kubectl

# Restart kubelet
$ sudo systemctl daemon-reload
$ sudo systemctl restart kubelet

# Create a single cluster with kubeadm
$ sudo kubeadm init --pod-network-cidr=10.244.0.0/16 --apiserver-advertise-address=<ip-address>

# kubeadm join <master-ip>:<master-port> --token <token> --discovery-token-ca-cert-hash sha256:<hash>
# Above will pop out after do kubeadm init, keep that in somewhere, you can add other cluster with
# the command

# We might encounter "Get http://localhost:8080/api?timeout=32s: dial tcp 127.0.0.1:8080: connect: connection refused", then do the following
$ mkdir -p $HOME/.kube
$ sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
$ sudo chown $(id -u):$(id -g) $HOME/.kube/config

# Set kube flannel network to pass bridged IPv4 traffic to iptables’ chains
$ sudo sysctl net.bridge.bridge-nf-call-iptables=1

# Configure flannel network
$ kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/bc79dd1505b0c8681ece4de4c0d86c5cd2643275/Documentation/kube-flannel.yml

# Check all services that we created
$ kubectl get pods --all-namespaces
```

### With minikube + kubectl
```sh
# kubectl install
$ sudo apt-get update && sudo apt-get install -y apt-transport-https
$ curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
$ echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee -a /etc/apt/sources.list.d/kubernetes.list
$ sudo apt-get update
$ sudo apt-get install -y kubectl

# minikube install
$ curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64 \
  && chmod +x minikube
$ sudo cp minikube /usr/local/bin && rm minikube

# Start minikube
$ minikube start
$ minikube dashboard
```

### K8s network
* K8s's network will autometically assign a internal ip address to each node
* Here are the recommendations:
  * VMware environment -> NSX-T
  * K8s-labs use -> weave net
  * Your own scratch system -> you can choose whatever you like, but recommend flannel
  * K8s has a built-in network -> Kube-router

### Kubectl instructions
```sh
# Add --all at the end of command -> get all from current namespace
# Add --all-namespaces at the end of command -> get all from all namespaces
# For example: kubectl get pods --all and kubectl get pods --all-namespaces
# Get all active pods
$ kubectl get pods

# Get all active replicaset
$ kubectl get replicasets

# Get all active deployment
$ kubectl get deployments

# Get all active service
$ kubectl get services

# Create new pod/replicaset/deployment/service from file
$ kubectl create -f <file-name>

# Delete pod/replicaset/deployment/service from file
$ kubectl delete -f <file-name>

# Want to change any configuration of file in command line not from file
$ kubectl set deployment/<the-deployment-name> <what-do-you-want-to-change>

# Want to change any configuration of deployment after changed the file
$ kubectl apply -f <deployment-file-name>
$ kubectl rollout status deployment/<the-deployment-name>

# Check rollout history
$ kubectl rollout history deployment/<the-deployment-name>

# Want to unchange any configuration of deployment
$ kubectl rollout undo deployment/<the-deployment-name>

# Want to unchange any configuration to a specific revision
$ kubectl rollout undo deployment/<the-deployment-name> --to-revision=<number>

# Want to change the scaling replicas
$ kubectl scale deployment/<the-deployment-name> --replicas=<number>

# Want to change the deployment scaling to autoscaling
$ kubectl autoscale deployment/<the-deployment-name> --min=<number1> --max=<number2> --cpu-percent=<number3>
```

### Trouble Shooting
* Q: 0/1 nodes are available: 1 node(s) had taints that the pod didn't tolerate.<br>
A: `$ kubectl taint nodes --all node-role.kubernetes.io/master-`
