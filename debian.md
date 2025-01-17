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

## 3. et personal config

<details>

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

<details>

ibus-libpinyin

- `sudo apt install ibus-libpinyin`
- `ibus-setup`
- Input Method > Add > Chinese > pinyin > add > close
- `Win` > Settings
  - Settings > keyboard > input source + > other > chinese pinyin
- `Win` + `Space` change chinese input
</details>

### 4.3 fcitx5 && flypy

[小鹤音形](https://flypy.com/)

- `sudo apt install fcitx5 fcitx5-rime rime-data-double-pinyin`
- `wget http://ys-n.ysepan.com/116124318/319108762/h4954374733QJITGvujH81/%E5%B0%8F%E9%B9%A4%E9%9F%B3%E5%BD%A2%E2%80%9C%E9%BC%A0%E9%A1%BB%E7%AE%A1%E2%80%9Dfor%20macOS.zip -O flypy.zip`
- `file-roller --extract-to=. flypy.zip`
- `sudo cp -r "小鹤音形Rime平台鼠须管for macOS"/rime/* /usr/share/rime-data/ && cd /usr/share/rime-data && sudo rime_deployer --add-schema luna_pinyin_simp double_pinyin_flypy`
- `fcitx5 remote -r`
- press `Ctrl`+`Space` start && press `F4` select


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
- `~/Desktop/run`
- `sudo apt install apt-transport-https`
- `sudo apt update`
- `sudo apt install code`

> [visual studio docs](https://code.visualstudio.com/docs/setup/linux) - install on linux

### 4.6 latex

- `sudo apt install texlive-full`

### 4.7 Miniconda

<details>

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

</details>

### 4.7 python

- `python -m pip install -i https://pypi.tuna.tsinghua.edu.cn/simple --upgrade pip`
- `pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple`
- `mkdir .venv | cd .venv | python -m venv .`

### 4.8 driver

- `sudo apt install linux-headers-$(uname -r)`

### 4.9 github cli

```shell
type -p curl >/dev/null || (sudo apt update && sudo apt install curl -y)
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
&& sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
&& echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
&& sudo apt update \
&& sudo apt install gh -y
```

> [github](https://github.com/cli/cli/blob/trunk/docs/install_linux.md) - cli dosc on linux

### 4.10 clash verge

- `sudo apt install clash-verge_1.4.2_amd64.deb`

> [clash](https://github.com/clash-verge-rev/clash-verge-rev) - clash on linux

### 4.11 Jekyll
[Template of Jekyll Theme - Minimal Mistakes](https://github.com/mmistakes/mm-github-pages-starter)

- username.github.io

### 4.11.1 test local
```
@_config.yml
+ theme: "minimal-mistakes-jekyll"
+ # remote_theme: "mmistakes/minimal-mistakes"
+ github: []

- # theme: "minimal-mistakes-jekyll"
- remote_theme: "mmistakes/minimal-mistakes"

@Gemfile
+ gem "minimal-mistakes-jekyll"
+ gem "webrick"
```

- `sudo apt install ruby-full build-essential zlib1g-dev`
```shell
echo '# Install Ruby Gems to ~/gems' >> ~/.bashrc
echo 'export GEM_HOME="$HOME/gems"' >> ~/.bashrc
echo 'export PATH="$HOME/gems/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```
- `gem sources --add https://mirrors.tuna.tsinghua.edu.cn/rubygems/ --remove https://rubygems.org/`
- `gem install jekyll bundler`
- `bundle config mirror.https://rubygems.org https://mirrors.tuna.tsinghua.edu.cn/rubygems`
- `bundle install`
- `bundle exec jekyll serve`