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
sudo apt-get update && apt-get install -y apt-transport-https curl
curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
cat <<EOF >/etc/apt/sources.list.d/kubernetes.list
deb https://apt.kubernetes.io/ kubernetes-xenial main
EOF
sudo apt-get update
sudo apt-get install -y kubelet kubeadm kubectl
sudo apt-mark hold kubelet kubeadm kubectl

# Restart kubelet
sudo systemctl daemon-reload
sudo systemctl restart kubelet

# Create a single cluster with kubeadm
sudo kubeadm init --pod-network-cidr=10.244.0.0/16 --apiserver-advertise-address=<ip-address>

# kubeadm join <master-ip>:<master-port> --token <token> --discovery-token-ca-cert-hash sha256:<hash>
# Above will pop out after do kubeadm init, keep that in somewhere, you can add other cluster with
# the command

# Set kube flannel network to pass bridged IPv4 traffic to iptables’ chains
sudo sysctl net.bridge.bridge-nf-call-iptables=1

# Configure flannel network
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/bc79dd1505b0c8681ece4de4c0d86c5cd2643275/Documentation/kube-flannel.yml
```

### With minikube + kubectl
```sh
# kubectl install
sudo apt-get update && sudo apt-get install -y apt-transport-https
curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee -a /etc/apt/sources.list.d/kubernetes.list
sudo apt-get update
sudo apt-get install -y kubectl

# minikube install
curl -Lo minikube https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64 \
  && chmod +x minikube
sudo cp minikube /usr/local/bin && rm minikube
```
