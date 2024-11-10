## Background
When developing software in teams several people may need to create, access, modify, and work on the same source code files. As we work with more people and make more and more changes to the code, 
it gets harder to track the different versions and modifications to the code. It also begs the question, how can we make sure that we always have the most updated version of the files 
if multiple people are constantly modifying them. Here is where [distributed version control](https://en.wikipedia.org/wiki/Distributed_version_control) comes into play, since it allows us to have a full history of the entire [codebase](https://en.wikipedia.org/wiki/Codebase).
Perhaps the most widely used version control system is [Git](https://en.wikipedia.org/wiki/Git), which was originally created for Linux by Linus Torvalds, who is also the creator of Linux.
Today, Git is used alongside [GitHub](https://en.wikipedia.org/wiki/GitHub), its developer platform, which allows us to create, store, and manage code in the cloud. Here, a user or organization is free to create [repositories](https://docs.github.com/en/repositories/creating-and-managing-repositories/about-repositories), 
which you can think of as the codebase for a specific project. For instance, in the [Triton Baja](https://github.com/Triton-Baja) GitHub organization, we currently have two repositories, one for our [website](https://github.com/Triton-Baja/triton-baja-website),
and another for [Data-Acquisition](https://github.com/Triton-Baja/Data-Acquisition).

We will be using Git and GitHub to keep track and store the Data Acquisition codebase.

## GitHub setup
As you can see, we already have set up the Triton Baja organization, so the only thing you need to do if to creae a GitHub account if you don't have one yet. This way we can invite you to be part of the organization.

# Git
Ideally we want to install Git on both the Pi and our personal computers. This way we can always write or read the code from our personal computers, even if we don't have access to the Pi.

## On Pi
Install Git by running
```
sudo apt update
sudo apt install git
```

## On computer
Go to [git downloads](https://git-scm.com/downloads) where you can find the executable. Run the executable and follow the instructions with the default/recommended settings.
