![](https://www.kubernetes.org.cn/img/2018/01/20180111160842.jpg)
# Helm example
## Helm tree
![](https://image.slidesharecdn.com/helm-180627143212/95/helm-the-better-way-to-deploy-on-kubernetes-reinhard-ngele-codemotion-amsterdam-2018-9-638.jpg?cb=1530110045)
## Helm folder functionality
* Chart.yaml -> Basic information about the chart.
* LICENSE -> OPTIONAL: The license for the chart.
* README.md -> OPTIONAL: A human-readable README file.
* requirements.yaml -> OPTIONAL: A YAML file listing dependencies for the chart.
* values.yaml -> The configuration variables for this chart.
* charts/ -> A directory of this chart dependent chart.
* templates/ -> A directory of templates, which contains all the k8s yaml files that you want to deploy.
* templates/NOTES.txt -> OPTIONAL: A plain text file containing short usage notes.
* templates/_helpers.tpl -> The constant configuration value for this chart, e.g. fullname, name ... etc.
## Example usage
* go to the root of this directory and type the following commands.
```sh
# Note that in minikube + kvm enviornment should add a "sudo" at the head of command.
$ helm install . # Start to deploy all the files in templates folder to k8s
$ helm list # List the success deployed helm chart
$ helm delete {release-name} # Delete the success deployed helm chart
```
## Chart (templates) modification instruction
1. Add your yaml file into templates folder
2. Convert all the changable or reuseable value to {{variable_name}} format. 
   Notice that chagable or reuseable value such as replicas or labels, unchagable such as version, 
   {{variable_name}} such as {{ .Values.replicaCount }}
3. Type `$ Helm install .` to test your chart.
4. Congradulation! You make a modification success!
