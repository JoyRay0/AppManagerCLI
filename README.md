# 🚀 AppManagerCLI

A lightweight, blazing-fast, and modular Command Line Interface (CLI) application built to streamline package management and deployment. Designed for developers who love the terminal, efficiency, and full control over their workflows.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-orange)]()
[![Language: PHP](https://img.shields.io/badge/language-PHP-777BB4.svg?style=flat&logo=php&logoColor=white)]()



## ✨ Features

*   **⚡ High Performance:** Zero bloat, instant execution, and minimal system footprint.

*   **📂 Central Gateway Architecture:** Handle all remote configurations and API endpoints efficiently from a centralized setup.

*   **🎨 Clean Terminal UI:** Standard-compliant, structured, and color-coded console output for smooth debugging.


## 🚀 Getting Started

## 📋 Prerequisites

Before installing, ensure your environment meets the following requirements:
*   **Operating System:** Linux (Debian/Ubuntu based, RHL/Fedora based, Arch based etc.) or macOS
*   **Runtime:** PHP-cli or PHP (Version 7.4 or higher recommended)


## ⚙️ Installation

Choose **one** of the methods below to get started:

### Method 1: Quick Auto-Installation (Recommended)
---
Run the following single-line command in your terminal. It will automatically download and set up the `AppManagerCLI` environment for you:

```bash
curl -sSL https://raw.githubusercontent.com/JoyRay0/AppManagerCLI/main/installer.sh | bash
```

### Method 2: Manual Installation
---
If you prefer to configure it yourself, follow these steps:

1. **Install PHP :** Ensure PHP is installed on your system.

2. **Download Release :** Download the  `app` execution file from the latest `release` folder.

3. **Run the App :** Navigate to the folder and execute the file via PHP:

```bash
php app
```

## 🛠️ Usage & Commands

```bash
app
```

or

```bash
php app
```

### Supported Commands

| Command | Description |
|---------|-------------|
| `app list` or `php app list` | Display the comprehensive list of available commands and titles. |
| `app add` or `php app add` | Initialize and add a new application to the manager. |
| `app delete` or `php app delete` | Safely remove an application from tracking.  |
| `app reset` or `php app reset` | Hard-reset the entire environment setup and configs. |
| `app run [id]` or `php app run [id]` | Launch an installed application directly using its assigned number or ID. |


## 📦 Data & Activity Tracking

The core system automatically structures and persists your settings and activity logs inside the `/home/username/appmanager` or `/Users/username/appmanager` directory:

- `app_commands.json` : This file tracks the internal indexing of all added applications. It dynamically lists every app with its specific Number, Title, and Command configuration.

- `app_log.txt` : A runtime log file that maintains full traceability. Every time a command (add, delete, reset) is executed, it records timestamps and status updates for debugging.

## 🤝 Contributing

Contributions make the open-source community an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated.

1. **Fork the Project**

2. **Create your Feature Branch** (`git checkout -b feature/AmazingFeature`)

3. **Commit your Changes** (`git commit -m 'Add some AmazingFeature'`)

4. **Push to the Branch** (`git push origin feature/AmazingFeature`)

5. **Open a Pull Request**

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.