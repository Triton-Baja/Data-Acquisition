## Background
When developing software in teams, several people may need to create, access, modify, and work on the same source code files. As we work with more people and make more and more changes to the code, 
it gets harder to track the different versions and modifications to the code. It also begs the question, how can we make sure that we always have the most updated version of the files 
if multiple people are constantly modifying them. Here is where [distributed version control](https://en.wikipedia.org/wiki/Distributed_version_control) comes into play, since it allows us to have a full history of the entire [codebase](https://en.wikipedia.org/wiki/Codebase). This way, every change that we make to the codebase will be recorded so that we can see who made the changes and when.
Perhaps the most widely used version control system is [Git](https://en.wikipedia.org/wiki/Git), which was originally created for Linux by Linus Torvalds, who is also the creator of Linux.
Today, Git is used alongside [GitHub](https://en.wikipedia.org/wiki/GitHub), its developer platform, which allows us to create, store, and manage code in the cloud. Here, a user or organization is free to create [repositories](https://docs.github.com/en/repositories/creating-and-managing-repositories/about-repositories), 
which you can think of as the codebase for a specific project. For instance, in the [Triton Baja](https://github.com/Triton-Baja) GitHub organization, we currently have two repositories, one for our [website](https://github.com/Triton-Baja/triton-baja-website),
and another for [Data-Acquisition](https://github.com/Triton-Baja/Data-Acquisition).

We will be using Git and GitHub to keep track and store the Data Acquisition codebase.

## GitHub setup
As you can see, we already have set up the Triton Baja organization, so the only thing you need to do is to create a GitHub account if you don't have one yet. This way we can invite you to be part of the organization.

## Git
Ideally, we want to install Git on both the Pi and our personal computers. This way we can always write or read the code from our personal computers, even if we don't have access to the Pi.

### On Pi
Install Git by running
```
sudo apt update
sudo apt install git
```

### On computer
Go to [git downloads](https://git-scm.com/downloads) where you can find the executable. Run the executable and follow the instructions with the default/recommended settings.

## Caching credentials
While using Git doesn't require any credentials (username, password), if we want to connect the local folder to the repository in the cloud and be able to update the repository, we will need to tell Git who we are (our credentials). This is because only team members have write privileges; we wouldn't want just any random person to be able to change our code. We will be using the GitHub CLI for this.

### On Pi
Make sure `curl` and `apt-transport-https` are installed
```
sudo apt update
sudo apt install curl apt-transport-https
```

Get GitHub CLI package from its repository
```
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo tee /usr/share/keyrings/githubcli-archive-keyring.gpg > /dev/null
echo "deb [signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null
```

Install it
```
sudo apt update
sudo apt install gh
```

Verify installation
```
gh --version
```

Cache credentials
```
gh auth login
```

Select `GitHub.com`, `HTTPS`, `Login with a web browser`. Go to [hhtps://github.com/login/device](hhtps://github.com/login/device) on another device (e.g., computer) and type the code

### On computer
Follow [these instructions](https://docs.github.com/en/get-started/getting-started-with-git/caching-your-github-credentials-in-git#github-cli).

## Configure identity
For both, Pi and computer, configure your identity
```
git config --global user.name "your-github-username"
git config --global user.email "your-github-email@example.com"

```

## Cloning
As you can see, I have already created the repository, now you will want to `clone` it such that you can download all the content locally. Let's open our command line/terminal and traverse to the directory where we want to have the repo folder. For instance, if I want the repo on my Desktop (given that I am using Windows), I would do

```
cd C:\Users\super\Desktop
```

Now we can clone the repo
```
git clone https://github.com/Triton-Baja/Data-Acquisition.git
```

Now we should see the `Data-Acquisition` folder on our Desktop (or wherever you cloned it). Let's go into it
```
cd Data-Acquisition
```

# Basig Git Commands
`git pull` allows us to update our local folder to mirror the repository in the cloud. We must always run this command before we start a work session so that we are always working with the most updated files and don't have a conflict later.<br>
`git status` shows you the files you have changed, and whether or not they are on the queue to be uploaded.<br>
`git add file` whenever you have changed a `file`, you will use this command to add it to the "queue" of files to be uploaded to github.<br>
`git commit -m "comment"` Once you have added all the files to the queue, you will give them a commit. Here you will add a text comment, which will appear on GitHub's history. This comment should have useful information regarding what changes you made to the codebase.<br>
`git push` finally, we push (upload) the code to GitHub. Now your changes will be viewable online, and someone would `git pull` to see those changes reflected on their local computer.

## Exercise
Let's practice with a simple exercise. First let's pull in case anyone else has pushed any change.
```
git pull
```

Open your File Explorer (Windows) or Finder (MAC OS). Go to the `Data-Acquisition` folder, then go into the `test` folder. Here, create an empty text file with your name, e.g., `Giovanni.txt`. Now let's check the status on the terminal. You should see changes in the `test/` folder
```
git status
```

Now let's add it to the queue
```
git add test/your_name.txt
```

If we check the status again, now we should see it has been added
```
git status
```

Since we are done adding files, let's commit
```
git commit -m "Created your_name.txt for testing"
```

Now let's push
```
git push
```

Now if you go to the [test](https://github.com/Triton-Baja/Data-Acquisition/tree/main/test) folder on GitHub you should be able to see your file.
