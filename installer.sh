#!/bin/bash

set -e

#Color & ANSI code
GREEN="\033[0;32m"
BLUE="\033[0;34m"
RED="\033[0;31m"
NC="\033[0m" #No color

#Github info
GITHUB_USER="JoyRay0"
REPO_NAME="AppManagerCLI"
VERSION="v1.0.5"
DOWNLOAD_URL="https://github.com/${GITHUB_USER}/${REPO_NAME}/releases/download/${VERSION}/app"
INSTALL_PATH="/usr/local/bin/appmanager"


echo -e "${BLUE}==============================${NC}"
echo -e "Installing AppManagerCLI"
echo -e "${BLUE}==============================${NC}"

echo -e " " #For free space

#Downloading file from github
sudo curl -L -o "$INSTALL_PATH" "$DOWNLOAD_URL"

#Set executable permission for file
sudo chmod +x "$INSTALL_PATH"

echo -e " "
echo -e "${GREEN}[✔] Download Complete${NC}"
echo -e "Now run [app] on your terminal"


