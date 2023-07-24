git 拉取远程指定分支内容
git checkout -b 分支名 origin/分支名

### 忽略已经被推送到远程的文件

git update-index --assume-unchanged 忽略文件路径

git update-index --no-assume-unchanged 跟踪文件路径

### git 删除分支

1. 远程：git push origin --delete 分支名
2. 本地：git branch -d 分支名
