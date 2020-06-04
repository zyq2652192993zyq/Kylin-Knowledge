> # Git

参考资料：

* [Learning Git branch](https://learngitbranching.js.org/?locale=zh_CN)
* [CS visualized: Useful Git command](https://dev.to/lydiahallie/cs-visualized-useful-git-commands-37p1#merge)
* 《从0开始学习GitHub》

# 配置Git

一般Ubuntu系统中都预先装有`git`，在终端输入：

```bash
git --version
```

如果恰好没有安装则：

```shell
sudo apt-get install git
```

配置个人信息：

```shell
git config --global user.name "Your name"
git config --global user.email "email@example.com"
```

想要连接到GitHub，终端输入

```
ssh -T git@github.com
```

如果返回信息是：

```shell
Warning: Permanently added ‘github.com,204.232.175.90’ (RSA) to the list of known hosts. 
Permission denied (publickey).
```

则说明可以连接。

```bash
sudo apt-get install ssh
cd ~/.ssh
ssh-keygen -t rsa -C "email@example.com"
```

然后输入以下命令查看密钥：

```shell
cat id_rsa.pub
```

在GitHub里依次`Settings -> SSH Keys -> Add SSH Key`即可

在终端里输入如下命令：

```shell
ssh -T git@github.com
```

如果返回如下信息：

```shell
Hi "Your Name"! You’ve successfully authenticated, but GitHub does not provide shell access.
```

则表明添加成功。

# 本地使用Git

比如我们新建一个目录：

```bash
$ mkdir test
$ cd test
$ touch README.md
```

## `git status`

在进行任何 Git 操作之前，都要先切换到 Git 仓库目录，也就是先要先切换到项目的文件夹目录下。比如我们在新建的`test`目录下输入：

```bash
$ git status
fatal: not a git repository (or any of the parent directories): .git
```

这个错误信息表明当前目录还不是一个`git`仓库。

## `git init`

那么我们对当前目录进行初始化：

```bash
$ git init
Initialized empty Git repository in /home/kylin/Downloads/test/.git/
$ gti status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	README.md

nothing added to commit but untracked files present (use "git add" to track)
```

初始化后默认在`master`分支，并提示`README.md`是`Untracked files`，即文件还没有被提交到`git`仓库里。

## `git add`

系统提示可以用`git add`去操作想要提交的文件：

```bash
$ git add README.md
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

	new file:   README.md

```

系统提示`Changes to be committed`，即`README.md`等待被提交，也可以用`git rm --cached`移除这个缓存。

## `git commit`

利用`git commit`提交：

```bash
$ git commit -m "first commit"
[master (root-commit) 05d6198] first commit
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 README.md
$ git status
On branch master
nothing to commit, working tree clean
```

`-m`后面跟随的是对于本次提交的一些说明信息。

## `git log`

输入`git log`查看`git`日志：

```bash
$ git log
commit 05d6198c33e606cf6d26cd7a22dfe40640d17f0e (HEAD -> master)
Author: zyq2652192993zyq <2652192993@qq.com>
Date:   Wed May 6 16:53:09 2020 +0800

    first commit
```

`git log`可以查看所有产生的`commit`记录，备注信息是`first commit`。

`git add`相当于先把提交项添加到一个缓存，然后用`git commit`进行提交。这样是为了防止错误提交。

## `git branch`

`branch`是分支的意思，分支是个很重要的概念，团队协作时每个人在各自的分支完成相应的任务，不同人之间互不影响，最后合并起来。可以通过`git branch`查看当前分支

```bash
$ git branch
* master
```

如果想要新建一个分支：

```bash
$ git branch newBranch
$ git branch
* master
  newBranch
```

会发现`master`前面有个`*`，表明虽然我们新建了一个分支，但是当前所在的分支还是`master`，新建的分支和`master`分支是一模一样的。

## `git checkout`

如果想在新建的分支完成一些操作，首先需要切换到目标分支：

```bash
$ git checkout newBranch
Switched to branch 'newBranch'
$ git branch
  master
* newBranch
```

发现此时`*`在`newBranch`前面，表明当前在`newBranch`分支。

如果想把新建分支并直接切换到新分支：

```bash
git checkout -b newBranch
```

`-b`是创建一个新分支`newBranch`，然后用`checkout`命令切换到新分支。

## `git merge`

我们在新建的分支执行的操作在没有合并到`master`分支之前，`master`分支是没有任何改动的。此时需要两个步骤：

* 首先切换到`master`分支
* 将想要合并的分支合并过来：`git merge newBranch`

```bash
$ git checkout master
$ git merge newBranch
```

## `git branch -d`

假如分支的代码已经合并到`master`了，那么这个新的分支就不需要了，可以用`git branch -d newBranch`进行删除。

```bash
$ git branch -d newBranch
Deleted branch newBranch (was 05d6198).
```

## `git branch -D`

假如我们新建的分支没有合并到`master`，执行`git branch -d`会失败。如果仍然想不合并就删除分支，就需要`-D`命令。

```bash
$ git checkout -b newBranch1 # 新建分支并切换到分支newBranch1
Switched to a new branch 'newBranch1'
$ echo "Hello world" > README.md # 修改README.md
$ git add README.md
[newBranch1 f5d0a1d] change to README.md
 1 file changed, 1 insertion(+)
$ git commit -m "change to README.md"
On branch newBranch1
nothing to commit, working tree clean
$ git checkout master
Switched to branch 'master'
$ git branch -d newBranch1
error: The branch 'newBranch1' is not fully merged.
If you are sure you want to delete it, run 'git branch -D newBranch1'.
$ git branch -D newBranch1
Deleted branch newBranch1 (was f5d0a1d).
```

## `git tag`

`git tag`就是给代码标记版本

```bash
$ git checkout -b a
Switched to a new branch 'a'
$ git tag v1.0
$ git tag
v1.0
```

# 远程使用Git

## SSH

git服务器一般都选择使用SSH公钥来进行授权，所以向GitHub提交代码第一步就要添加SSH key配置。

## 生成SSH key

我们的操作环境是在Windows下使用WSL，在终端输入`ssh`查看是否安装：

```bash
$ ssh
usage: ssh [-46AaCfGgKkMNnqsTtVvXxYy] [-b bind_address] [-c cipher_spec]
           [-D [bind_address:]port] [-E log_file] [-e escape_char]
           [-F configfile] [-I pkcs11] [-i identity_file]
           [-J [user@]host[:port]] [-L address] [-l login_name] [-m mac_spec]
           [-O ctl_cmd] [-o option] [-p port] [-Q query_option] [-R address]
           [-S ctl_path] [-W host:port] [-w local_tun[:remote_tun]]
           [user@]hostname [command]
```

出现以上信息表明系统已经安装了`ssh`，如果没有安装`ssh`，则可以：

```bash
$ sudo apt-get install ssh
```

安装好`ssh`后，输入`ssh-keygen -t rsa`，这里`rsa`是利用`rsa`算法生成密钥，接着输入三个回车（不需要输入密码），然后就会生成两个文件`id_rsa`和`id_rsa.pub`，其中`id_rsa`是密钥，`id_rsa.pub`是公钥，在Linux环境下，这两个文件在`~/.ssh`下面。

```bash
$ ls ~/.ssh
authorized_keys  id_dsa  id_dsa.pub  id_rsa  id_rsa.pub  known_hosts
```

接下来需要将`id_rsa.pub`内容添加到GitHub上，这样本地`id_rsa`密钥根GitHub的`id_rsa.pub`公钥配对，授权成功才可以提交代码。

## GitHub上添加SSH key

在GitHub的`setting`选项里依次选择：

```
SSH and GPG keys -> New SSH key
```

然后把`id_rsa.pub`的内容添加到`Key`下面就可以了。

添加成功后终端输入：

```bash
$ ssh -T git@github.com
Hi zyq2652192993zyq! You've successfully authenticated, but GitHub does not provide shell access.
```

## Push & Pull

把我们在本地修改的代码推到远程仓库使用命令`push`

```bash
$ git push origin master
```

如果想把远程仓库的代码同步到本地，使用命令`pull`：

```bash
$ git pull origin master
```

## 提交代码

首先`clone`我们自己的项目，执行：

```bash
$ git clone git@github.com:zyq2652192993zyq/test.git
```

这里的`test`指在GitHub里的仓库名称。执行完成后不需要`git init`的操作，并且本地仓库也和远程仓库进行了关联。

如果本地已经有一个`git`仓库，比如本地有一个`test2`的仓库，需要在GitHub上新建一个`test`项目。

* 首先在GitHub上新建一个`test`项目。
* 第二步把本地`test2`仓库和GitHub上的`test`仓库进行关联。

```bash
$ git remote add origin git@github.com:zyq2652192993zyq/test.git
```

查看当前项目有哪些远程仓库使用：

```bash
$ git remote -v
```

在提交代码前需要设置自己的用户名和邮箱，在初始配置的时候已经设置了，这里就不再设置了。

# Git进阶

我们每次`commit`都会产生一条`log`，`log`里标记了提交人的姓名和邮箱，所以需要在提交前设置用户名和邮箱。

如果某一个项目需要特定的邮箱，只需切换到项目，去掉`--global`参数即可。

## `alias`

`alias`相当于对某些命令的“快捷键”，比如每次输入`commit`会很麻烦，我们可以：

```bash
$ git config --global alias.co checkout
```

这样`co`就是`checkout`的别名，执行`git co`和`git checkout`是一样的效果。

```bash
$ git config --global alias.cm 'commit -m "update"'
```

还可以利用`alias`来设置一些组合：

```bash
$ git config --global alias.psm 'push origin master'
```

可以利用`alias`来对`git log`进行简单的美化：

```bash
$ git log --graph --pretty=format:'%Cred%h%Creset -
%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
--date=relative
```

但是每次输入这么一长串命令太累了，所以可以用`alias`进行简化：

```bash
$ git config --global alias.lg "log --graph --pretty=format:'%Cred%h%Creset -
%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit
--date=relative"
```

## 其他配置

`git`默认的编辑器是`vi`，可以换成`vim`：

```bash
$ git config --global core.editor "vim"
```

开启`git`着色，美化：

```bash
$ git config --global color.ui true
```

设置显示中文文件名

```bash
$ git config --global core.quotepath false
```

默认在`~/.gitconfig`文件下，可以通过`git config -l`查看

## `diff`

`diff`命令主要查看我们对代码做了哪些改动。

注意`git diff`只比较当前文件和暂存区文件差异（`git add`），其他用法：

```bash
# 比较两次提交之间的差异,id可以通过log信息查看
$ git diff <$id1> <$id2>
# 比较两个分支的差异
$ git diff <branch1> <branch2>
```

## `checkout`

`checkout`除了有切换的功能，还可以执行撤销，但是只能撤销还有`add`进暂存区的文件。

```bash
$ git checkout filename
```

## `stash`

原则上每次`commit`的代码应该有实际意义，如果代码写到一半，并且还没有`commit`，那么可以用命令`stash`先保存起来，用`git status`查看也发现当前分支很干净。

执行以下命令发现暂存区多了一条记录：

```bash
$ git stash list
```

还原暂存起来的代码：

```bash
$ git stash apply
```

然后删除在`stash`的记录：

```bash
$ git stash drop
```

上述两个动作可以进行合并：

```bash
$ git stash pop
```

`pop`会首先还原代码，然后自动删除在`stash`暂存的记录。

如果想清除`stash`所有的记录，可以使用：

```bash
$ git stash clear
```

## `merge` & `rebase`

`merge`已经有合并的功能了，为什么还需要`rebase`？

* `merge`合并可以清晰的知道修改源于哪个分支
* `rebase`会首先进行比较，然后按照时间进行排序，合并后更有逻辑性。

```bash
# using merge command
$ git checkout master
$ git merge newBranch
# using rebase command
$ git checkout master
$ git rebase newBranch
```

## 解决冲突

一般在开发过程中尽量避免各自开发的代码产生相互干扰，但是特殊情况下，比如A修改了一个基础库的一个类，B也修改了这个类，那么假如A首先`merge`，没有任何问题，但是当B进行`merge`的时候就会提示`conflicts`。

# Git分支管理



# 避免每次`git push`输入用户名和密码

第一步：在根目录（`/home/user/`）下创建文件`.git-credentials`。

第二步：在该文件中添加信息：

```
https://username:password@github.com
```

其中`username`和`password`替换为自己的账户名和密码。

第三部：执行命令：

```bash
$ git config --global credential.helper store
```

执行完后，在根目录下的`.gitconfig`中会多出：

```
[credential]
    helper = store
```

第四步：重启`bash`，然后接下来每次`git push`就不需要输入账户名和密码了。

# `git clone`出错

在执行`git clone [git link]`的时候报错：

```
error: RPC failed; curl 18 transfer closed with outstanding read data remaining
```

可以有三种解决方案，第二种方案，也就是只`clone`最近的一个版本最有效。

* 加大缓冲区

```bash
$ git config --global http.postBuffer 524288000 # 缓冲区大致扩充到500M
```

* 只`clone`最近的一个版本

```bash
$ git clone https://github.com/[reposity].git --depth 1
```

* 更换协议

`clone http`方式换成`SSH`的方式，即 `https://` 改为 `git://`

















 