import os
import json

def cpp_files_to_snippets():
    snippets = {}

    # 递归遍历根目录及子目录
    for root, _, files in os.walk("."):
        for filename in files:
            if filename.endswith(".cpp"):
                # 构造文件的完整路径
                filepath = os.path.join(root, filename)
                with open(filepath, 'r', encoding='utf-8') as file:
                    content = file.readlines()

                # 以文件名作为代码片段的名称
                snippet_name = os.path.splitext(filename)[0]
                snippet_content = ''.join(content)

                # 转换为适合JSON格式的代码片段格式
                snippet_lines = [line.replace('"', '\"') for line in snippet_content.splitlines()]

                # 构造VS Code的代码片段JSON结构
                snippets[snippet_name] = {
                    "prefix": snippet_name,
                    "body": snippet_lines,
                    "description": f"Snippet from {filepath}"
                }

    # 将结果写入cpp.json文件
    with open("cpp.json", "w", encoding='utf-8') as json_file:
        json.dump(snippets, json_file, indent=4, ensure_ascii=False)

if __name__ == "__main__":
    cpp_files_to_snippets()
