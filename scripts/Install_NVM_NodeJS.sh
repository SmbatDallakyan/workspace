sudo apt-get update
sudo apt-get install build-essential libssl-dev
curl https://raw.githubusercontent.com/creationix/nvm/v0.25.0/install.sh | bash
source ~/.profile

nvm install 6.9.4
nvm current
nvm alias default 6.9.4
nvm use 6.9.4
