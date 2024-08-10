# setSail

# 简介
- 汽车毫米波雷达软件开发源代码
- 配套文章主页：https://zhuanlan.zhihu.com/p/266105833

# 许可证
- BSD-3，详细见 LICENSE。
- 因为此项目用到了Qt及QtCharts，因此请用户同样遵循Qt及QtCharts和许可证，若用户不遵守引发的法律问题，本项目拥有者概不承担责任

# 软件架构
见doc文件夹下的 软件架构.pptx 和 软件架构.xmind


# 文件结构

- src：程序入口
- SW：软件代码，主要包括BSW, RTE, App 和 3rd_Party 等几个部分
- lib：生成的库文件
- bin：生成的二进制可执行文件
- doc：软件的文档，未来可能将函数 api 使用 Doxygen 生成
- SIM：软件级别的仿真，包含两项：在线 online 和 离线 offline。

注：目前仅以离线 offline 软件仿真为主进行算法开发。

# 分支说明

- master（保护）：重大的项目节点推送，需要打上标签
- develop（保护）：每当一个feature完成时，合并到此分支
- feature：项目分割为若干个feature，每次以一个feature为主进行开发
- release：发布分支，当项目的每个版本发布时，释放到此分支，打上标签
- feature_X: 某一个特征分支，每个人建立每个人自己的某个特征分支，在此基础上开发

feature 分支始终保持最新状态

未来的分支图形状（如果下方未渲染，见doc/branch_example.PNG)：

![理想的分支图形状](doc/branch_example.PNG)

注：每次 pull-request 时，需要将远程分支删除，避免产生过多的远程 feature_X分支。

# 环境及依赖

## 环境
- OS: win10
- IDE: vs2019 community
- Language: C++(支持C++11)

## 依赖
- Eigen：做几何变换
- rapidjson：解析json文件

# 参与贡献

- Andy.Yang
- ChengShuhui
