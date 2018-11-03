git init morvan && cd morvan
git config core.sparseCheckout true
echo '/sklearn/*' >> .git/info/sparse-checkout
git reset --hard
git remote -v
git remote add origin https://github.com/MorvanZhou/tutorials.git
git pull origin master:master --depth 10
du -h

