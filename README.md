# ICPC-Template

本项目为个人整理/使用的算法竞赛模板TeX源码。

原版模板使用Pages编写，2018年底退役后再无更新，最近使用TeX复刻并开源。

由于本人能力有限，模板内容可能存在问题，欢迎提交issue。

## Requirements

- XeLaTeX （用于支持中文）[https://www.tug.org/texlive/](https://www.tug.org/texlive/)
- Pygments （用于支持minted语法高亮）[https://pygments.org/](https://pygments.org/)

## How to build

执行**两遍**如下命令：

```
xelatex -shell-escape icpc_template.tex
```

编译后生成的模板文件为`./icpc_template.pdf`。

## License

本项目遵循[MIT](./LICENSE)开源协议。