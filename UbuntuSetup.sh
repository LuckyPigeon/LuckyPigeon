# Update ubuntu source list
sudo apt update

# yarn apt key
curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | sudo apt-key add -
echo "deb https://dl.yarnpkg.com/debian/ stable main" | sudo tee /etc/apt/sources.list.d/yarn.list

# Install packages
sudo apt update
sudo apt install -y nodejs npm git openssh-server apt-transport-https ca-certificates \
curl software-properties-common apache2 snap aptitude yarn

# docker apt key
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu bionic stable"
sudo apt update

# Add a try catch in this line later
# This line will make sure we are about to install from the docker repo
apt-cache policy docker-ce

# Installd docker-ce
sudo apt install docker-ce

# Execute docker command without sudo
sudo usermod -aG docker ${USER}

# Reboot the system
sudo systemctl reboot
