# Contribution Guidelines to ncio

This guide will walk you through how to submit changes to **ncio** and set you up as a developer. Please read this guide before starting your contribution work.
Reading time: 5 minutes.

 
Contents
========

* [Terminology](#terminology)
* [Workflow](#workflow)
* [Setup](#setup)
* [Submitting a pull request](#submitting-a-pull-request)
* [Code Style](#code-style)
         

## Terminology
- `upstream`: the project remote repo  https://github.com/ORNL/ncio
- `origin`: a fork remote repo _e.g._  https://github.com/williamfgc/ncio
- `Pull Request (PR)`: a request to merge from one branch onto another using GitHub. The most common case is from a remote branch in `origin` onto `upstream` `main` branch.

For those new to `git`, we recommend reading about git concepts such as `branch`, `commmit`, `merge`, `rebase` at https://git-scm.com/. 

## Workflow
**ncio** uses a GitHub fork-and-branch pull request (PR) workflow for contributions on the main branch. While each individual developer has their own copy of the repo to work in, changes are then submitted to the main `upstream` `main` branch repository via pull-requests made with branches from your fork. Ideally, each PR branch would cover a specific topic with few commits. A maximum of 5 commits per PR branch is a good rule of thumb, but it's at the reviewers discretion.

## Setup
To setup your local repository for development (requires a GitHub account):

1. Fork the main repository on GitHub:
    1. Navigate to https://github.com/ORNL/ncio in your browser.
    2. Click the `[Fork]` button in the upper right-hand side of the page.
  
2. Clone the upstream repository to your local machine:
  
    ```
    $ git clone https://github.com/ORNL/ncio.git
    ```
    
3. Run the `scripts/development/setup.sh` script.  The script will configure an `upstream` remote and link your local main branch to the `upstream` repo. IMPORTANT: check you system ssh public keys are registered to use ssh, otherwise http would be used to set the repos.
    
    ```
    $ cd ncio
    $ ./scripts/development/setup.sh
    ```
    
## Submitting a pull request

0. Update main (it's good practice to keep the `main` branch up to date):
    
	```
    $  git checkout main
    $  git pull   
	```

1. Create a branch:
    
	```
    $  git checkout -b my-bug-fix
	```
  
2. Make changes and commit locally as needed. Keep commits to a max of 5 (check `git rebase` to reduce number of commits).

	```
    $  git commit -a -m "Fixing bug" 
	```
  
3. Push branch to your fork

    ```
    $  git push origin my-bug-fix
    ```
    
4. Go to https://github.com/ORNL/ncio , you should see a message at the top that informs you of your recently pushed branch, something like: `<your-topic-branch-name> (1 minute ago)`.  On the right side, select the `[Compare & pull request]` button. If not, click on the `[New pull request]` button and set up the PR.

## Code Style
1. C++: `ncio` uses clang-format version 6.0 for `C++17` code style formatting. Check for pluings with your favorite Integrated Development Environment, *e.g.* CppStyle in Eclipse

## File sizes
`ncio` repo aims to be kept light-weight. Please open an issue before attempting to include large files. Binary and text data files are discouraged.
