# 开发 R 包

假设我们需要开发一个使用 `Rcpp`、`RcppArmadillo` 和 `OPENMP` 的 R 包，并且把 `c++` 函数包装成 `R` 函数，我们需要准备以下文件：

```bash
toyPackage           # 包名，也是根目录名
├── man              # 文档目录，后续可以自动生成
├── src
│   ├── Makevars     # OPENMP 的配置文件
│   ├── Makevars.win # Windows 的配置文件
│   └── code.cpp     # 源代码文件
├── R                # R 代码目录
│   └── code.R
├── DESCRIPTION      # 包的描述文件
├── NAMESPACE        # 包的命名空间，可以自己写
└── README.md        # 包的说明文件
```

我们用一个具体的例子来说明，假设我们希望计算一个 $m \times n$ 矩阵的元素和，我们需要做的事情：

1. 在 `DESCRIPTION` 中添加包的描述信息（（注意 `R` 包的命名规则）
2. 在 `NAMESPACE` 中添加包的命名空间信息
3. 在 `src/code.cpp` 中编写 `c++` 函数
4. 在 `R/code.R` 中编写 `R` 函数调用 `c++` 函数

做好以后，在根目录下运行如下脚本：

```bash
R -e "Rcpp::compileAttributes()" # 编译 `c++` 函数
R -e "roxygen2::roxygenise()"    # 生成 `man` 目录下的 `code.Rd` 文件
```

这样就生成了 `man` 目录下的 `code.Rd` 文件，然后编译安装 `R` 包：

```bash
cd .. ; R CMD build toyPackage
R CMD check toyPackage_0.1.0.tar.gz
R CMD INSTALL toyPackage_0.1.0.tar.gz
```

这样就安装好了 `R` 包，可以测试一下：

```bash
R -e "library(toyPackage)"
```

当提交到 `GitHub` 以后，可以通过 `remotes::install_github` 安装 `R` 包：

```bash
remotes::install_github("chia202/toyPackage")
```
