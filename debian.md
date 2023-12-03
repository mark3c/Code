# debian personal tutorial

## 1. Prepare a USB device

Platform: win10 x86_64

### 1.1 download operating system image

Distribution: Debian GNU/Linux
Version: Debian 12 "bookworm"
Architecture: amd64

- [ ] small image: 64-bit PC netinst iso
- [x] complete image: 64-bit PC torrents (DVD)
  - debian-12.2.0-amd64-DVD-1.iso

> [debian](https://www.debian.org/distrib/) - official img
> [qBittorrent](https://www.qbittorrent.org/download) - how to download .torrent

### 1.2 create bootable USB drive

USB Tool: ventoy
USB Storage: 8GB
Boot System: UEFI

- Ventoy2Disk.exe
  - select Device
  - Install
- format device to NTFS on win system tools
- VentoyPlugson.exe
  - Start
  - Theme Plugin
- move image to /USBdisk/Ventoy/

> [ventoy](https://www.ventoy.net/en/download.html) - tool boot make
> [gnome](https://www.gnome-look.org/p/1009236) - a theme files

## 2. Install image

### 2.1 into bios

Laptop: ASUS x550j

- power on, press and hold `F2` into bios
- Save & Exit > Boot Override > UEFI: SanDisk,  press `Enter`

### 2.2 configure

- debian-12.2.0-amd64-DVD-1.iso > grub2 > Graphical installation
<br>
- laguage: English
- location: other > Asia > China
- locales: en_US.UTF-8
- keyboard: American English
<br>
- network:
  - [ ] Ethernet
  - [x] wireless > {wifi} > WPA/WPA2 PSK > {password}
- hostname: ~~laptop~~
- domain: ~~debian~~
<br>
- root password:
- full name:
- user name: aiolia
- user password:
<br>
- disk:
  Guided - use entire disk disk > {sda disk} > Separate /home partition > Finish partitioning and write changes to disk > Yes
<br>
- network mirror: ***No***
  Useless have a well connection, could to update after now.
- package usage survey:
<br>
- software:
  - [x] Debian desktop environment
    - [x] GNOME
  - [x] web server
  - [x] SSH server
  - [x] standard system utilities
<br>
- GRUB boot loader: Yes
- Device: {sda disk}
<br>
- continue to reboot
- remove USB

## 3. (Skip) Set personal config

<details>
<summary>Show</summary>
welcome page, just skip.

### 3.1 settings

- press `Win`
- directly type `settings`, press `Enter`
<br>
- `settings` opened
- Notification > Do not Disturb Sound
- Notification > System Volume > 0
- Displays > Night Light
- Mouse & Touchpad > Edge Scrolling
- Mouse & Touchpad > Tap to Click
- Users > Automatic Login

### 3.2 tweask

- `tweaks` opened
- windows titlebars > maximize, minimize

### 3.3 Firefox ESR

- `firefox` opened
- Settings > General > Zoom > 150%

</details>

## 4. Sofetware

### 4.0 vi

<details>
<summary>Show</summary>

</details>

### 4.1 sudo

- `Win` > `terminal`
- `su - root`, then type password invisible to switch root
- `chmod u+w /etc/sudoers`
- `vi /etc/sudoers`

aiolia means group name, also user name.

```vim
%sudo ALL=(ALL:ALL) ALL
%aiolia ALL=(ALL:ALL) NOPASSWD:ALL
```

- `su aiolia`

### 4.2 apt mirror

- `sudo chmod u+w /etc/apt/sources.list`
- `sudo vi /etc/apt/sources.list`

```shell
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm main contrib non-free non-free-firmware
# deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm main contrib non-free non-free-firmware

deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm-updates main contrib non-free non-free-firmware
# deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm-updates main contrib non-free non-free-firmware

deb https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm-backports main contrib non-free non-free-firmware
# deb-src https://mirrors.tuna.tsinghua.edu.cn/debian/ bookworm-backports main contrib non-free non-free-firmware

deb https://mirrors.tuna.tsinghua.edu.cn/debian-security bookworm-security main contrib non-free non-free-firmware
# deb-src https://mirrors.tuna.tsinghua.edu.cn/debian-security bookworm-security main contrib non-free non-free-firmware
```

- `sudo apt install apt-transport-https ca-certificates`
- `sudo apt update`
- `sudo apt upgrade`

> [Tsinghua](https://mirrors.tuna.tsinghua.edu.cn/help/debian/) - debian mirrors support by tsinghua

### 4.3 ibus

ibus-libpinyin

- `sudo apt install ibus-libpinyin`
- `ibus-setup`
- Input Method > Add > Chinese > pinyin > add > close
- `Win` > Settings
  - Settings > keyboard > input source + > other > chinese pinyin
- `Win` + `Space` change chinese input

### 4.4 vim

- `sudo apt install vim`

### 4.5 vscode

- `vim ~/Desktop/run`

```shell
sudo apt-get install wget gpg
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -D -o root -g root -m 644 packages.microsoft.gpg /etc/apt/keyrings/packages.microsoft.gpg
sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
rm -f packages.microsoft.gpg
```

- `chmod u+x ~/Desktop/run`
- `~/Desktop/run
- `sudo apt install apt-transport-https`
- `sudo apt update`
- `sudo apt install code`

> [visual studio docs](https://code.visualstudio.com/docs/setup/linux) - install on linux

### 4.6 latex

- `sudo apt install texlive-latex-base`
- `sudo apt install texlive-lang-english texlive-lang-chinese`

### 4.7 Miniconda

- `mkdir -p ~/miniconda3`
- `wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh`
- `bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3`
- `rm -rf ~/miniconda3/miniconda.sh`
- `~/miniconda3/bin/conda init bash`
- reload terminal

> [miniconda](https://docs.conda.io/projects/miniconda/en/latest/index.html) - official docs

#### 4.7.1 anaconda mirror

- `conda config --set show_channel_urls yes`
- `vim ~/.condarc`

```shell
channels:
  - defaults
show_channel_urls: true
default_channels:
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/r
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/msys2
custom_channels:
  conda-forge: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  msys2: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  bioconda: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  menpo: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  pytorch: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  pytorch-lts: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  simpleitk: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
  deepmodeling: https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/
```

- `conda clean -i`

> [Tsinghua](https://mirrors.tuna.tsinghua.edu.cn/help/anaconda) - conda mirrors support by tsinghua

#### 4.7.2 env

create env named opencv

- `(base) aiolia@debian:~$`
- `conda create -n opencv`
- `conda activate opencv`
- `(opencv) aiolia@debian:~$`

### 4.8 driver

- `sudo apt install linux-headers-$(uname -r)`

### 4.7 clash verge

- `apt install clash-verge_1.4.2_amd64.deb`

> [clash](https://github.com/clash-verge-rev/clash-verge-rev) - clash on linux
