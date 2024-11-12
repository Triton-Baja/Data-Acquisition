# Neovim
As you can tell by now, `nano` isn't the most helpful editor. It doesn't come with C/C++ support, barely any code highlighting, no auto completions, and no linting. Let's fix that by switching to neovim. 
Since we are using a Pi, which is ARM architecture we'll have to build it from source to get the most updated version. 

## Installing Neovim
First let's install the dependencies
```
sudo apt update
sudo apt install -y ninja-build gettext libtool libtool-bin autoconf automake cmake g++ pkg-config unzip curl doxygen clangd
```

Then let's increase git's buffer size
```
git config --global http.postBuffer 524288000
```

Clone the repo
```
git clone https://github.com/neovim/neovim
cd neovim
```

Get into the stable version
```
git checkout stable
```

Build and install
```
make CMAKE_BUILD_TYPE=Release
sudo make install
```

Verify installation
```
nvim --version
```

## Installing a nerd font
This will help us see icons as characters. First let's install `Fontconfig`, which manages fonts on Linux
```
sudo apt update
sudo apt install fontconfig
```

We'll use the JetBrains Mono Nerd
```
wget https://download.jetbrains.com/fonts/JetBrainsMono-2.304.zip
unzip JetBrainsMono-2.304.zip
```

Now let's install it for single user
```
mkdir -p ~/.local/share/fonts
mv fonts/ttf/*.ttf ~/.local/share/fonts/
mv fonts/variable/*.ttf ~/.local/share/fonts/
mv fonts/webfonts/*.ttf ~/.local/share/fonts/
```

Refresh ftonc cache
```
fc-cache -fv
```

Verify installation
```
fc-list | grep "JetBrains Mono"
```

## Seting up NV Chad
This will be our base configuration for Neovim. First we'll remove the default neovim configuration
```
rm -rf ~/.local/share/nvim
```

Clone the NV CHad repo
```
git clone -b v2.0 https://github.com/NvChad/NvChad ~/.config/nvim --depth 1
```

Now follow [this video](https://www.youtube.com/watch?v=lsFoZIg-oDs), which will show you how to finish setting up neovim. Start at 1:15 and follow at least until 7:05
