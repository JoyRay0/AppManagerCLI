#!/bin/bash

set -e

#Color & ANSI code
GREEN="\033[0;32m"
BLUE="\033[0;34m"
RED="\033[0;31m"
NC="\033[0m" #No color

#Gtihub info
GITHUB_USER="JoyRay0"
REPO_NAME="AppManagerCLI"
VERSION="v1.0.1"
DOWNLOAD_URL="https://github.com/${GITHUB_USER}/${REPO_NAME}/releases/download/${VERSION}/app"
INSTALL_PATH="/usr/local/bin/app"


echo -e "${BLUE}==============================${NC}"
echo -e "Installing AppManagerCLI"
echo -e "${BLUE}==============================${NC}"

#Checking PHP-cli is available or not

echo -e " " #For free space 

if ! command -v php &> /dev/null;
then

    echo -e "${RED}[✖] PHP-cli Not Found${NC}"

    echo -e " " 

    #For Debian/Ubuntu based distros
    if command -v apt &> /dev/null;
    then

        sudo apt install php-cli php-curl -y

    #For Fedora/RHL based distros
    elif command -v dnf &> /dev/null; 
    then

        sudo dnf install php-cli php-curl -y

    #For Arch based distros
    elif command -v pacman &> /dev/null;
    then

        sudo pacman -Syu php --noconfirm

    else

        echo -e "${RED}[✖] Linux Distro Not dected. Please Install PHP-cli manually${NC}"
        exit 1

    fi

else

    echo -e "${GREEN}[✔] PHP-cli Found${NC}"

fi

#Downloading file from github
sudo curl -L -o "$INSTALL_PATH" "$DOWNLOAD_URL"

#Set executable permission for file
sudo chmod +x "$INSTALL_PATH"

echo -e " "
echo -e "${GREEN}[✔] Download Complete${NC}"
echo -e "Now run [app] on your terminal"


