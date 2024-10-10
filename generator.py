import os

def escape_latex(s):
    """
    转义 LaTeX 特殊字符
    """
    replacements = {
        '\\': r'\textbackslash{}',
        '&': r'\&',
        '%': r'\%',
        '$': r'\$',
        '#': r'\#',
        '_': r'\_',
        '{': r'\{',
        '}': r'\}',
        '~': r'\textasciitilde{}',
        '^': r'\textasciicircum{}',
    }
    for key, value in replacements.items():
        s = s.replace(key, value)
    return s

def create_latex_file(content):
    with open("output.tex", "w", encoding="utf-8") as latex_file:
        # 写入封面，页眉，页脚，页码，章节目录等基本设置
        latex_file.write(r"""
\documentclass{ctexbook}  % 使用ctexbook文档类，支持中文并允许使用\chapter
\usepackage[utf8]{inputenc}
\usepackage{fancyhdr}
\usepackage{fancyvrb}
\usepackage{tocloft}
\usepackage{geometry}
\geometry{a4paper, margin=1in}

% 页眉和页脚
\pagestyle{fancy}
\fancyhf{}
\fancyhead[L]{XCPC算法模板} % 左侧页眉
\fancyhead[R]{\leftmark} % 右侧页眉

% 更新章节标题格式
\renewcommand{\sectionmark}[1]{\markright{#1}} % 用于 section
\renewcommand{\subsectionmark}[1]{\markboth{#1}{}} % 用于 subsection
\cfoot{\thepage}

% 封面设置
\title{XCPC 算法模板}
\author{MaxDYF}
\date{\today}

\begin{document}

\maketitle
\newpage

% 目录生成
\tableofcontents
\newpage
""")

        # 写入遍历目录生成的内容
        latex_file.write(content)

        # 结束文档
        latex_file.write(r"""
\end{document}
""")

def generate_latex_content():
    root_dir = "."  # 当前根目录
    latex_content = ""

    def traverse_directory(current_path, depth):
        nonlocal latex_content
        folder_name = escape_latex(os.path.basename(current_path))
        if depth == 1:  # 一级目录作为章节
            latex_content += f"\\chapter{{{folder_name}}}\n"
        elif depth == 2:  # 二级目录作为节
            latex_content += f"\\section{{{folder_name}}}\n"

        try:
            entries = sorted(os.listdir(current_path))
        except PermissionError:
            return  # 如果没有权限访问该目录，则跳过

        for entry in entries:
            entry_path = os.path.join(current_path, entry)
            if os.path.isdir(entry_path):
                if entry == ".git":
                    continue  # 忽略 .git 目录
                traverse_directory(entry_path, depth + 1)
            elif os.path.isfile(entry_path) and entry.endswith(".cpp"):
                # 处理 .cpp 文件
                file_name = os.path.splitext(entry)[0]  # 去掉后缀
                file_name_escaped = escape_latex(file_name)
                latex_content += f"\\subsection{{{file_name_escaped}}}\n"  # 文件名作为子节

                # 读取cpp文件内容并用verbatim环境插入LaTeX
                try:
                    with open(entry_path, "r", encoding="utf-8") as cpp_file:
                        cpp_content = cpp_file.read()
                        # 转义反斜杠和百分号等特殊字符
                        # cpp_content_escaped = cpp_content.replace('\\', r'\textbackslash{}').replace('%', r'\%')
                        cpp_content_escaped = cpp_content.replace('\\', r'\textbackslash{}')
                        latex_content += "\\begin{Verbatim}[fontsize=\\small]\n"
                        latex_content += cpp_content_escaped
                        latex_content += "\n\\end{Verbatim}\n"
                        latex_content += "\let\cleardoublepage\clearpage\n\n"
                except Exception as e:
                    print(f"无法读取文件 {entry_path}: {e}")

    traverse_directory(root_dir, 0)
    return latex_content

if __name__ == "__main__":
    latex_content = generate_latex_content()
    create_latex_file(latex_content)
    print("LaTeX 文件 'output.tex' 已生成。")
