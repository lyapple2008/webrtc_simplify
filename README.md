# webrtc_simplify
webrtc源码简化

# 源码目录简化
|原目录|简化后目录|备注|
|---|---|----|
|api|api| 除了.git文件夹，全部保留
|audio|audio| 除了.git文件夹，全部保留
|base|base| 除了.git文件夹，全部保留
build||只与编译相关
build_overrides|build_overrides| 除了.git文件夹，全部保留
|call|call| 除了.git文件夹，全部保留
|common_audio|common_audio| 除了.git文件夹，全部保留
|common_video|common_video| 除了.git文件夹，全部保留
|data||资源文件不保存
|examples||样例工程不保存
|logging|logging| 除了.git文件夹，全部保留
|media|media| 除了.git文件夹，全部保留
|modules|modules| 除了.git文件夹，全部保留
|p2p|p2p| 除了.git文件夹，全部保留
|pc|pc| 除了.git文件夹，全部保留
|resources||资源文件不保存
|rtc_base|rtc_base| 除了.git文件夹，全部保留
|rtc_tools|rtc_tools| 除了.git文件夹，全部保留
|sdk|sdk| 除了.git文件夹，全部保留
|stats|stats| 除了.git文件夹，全部保留
|style-guide|style-guide| 除了.git文件夹，全部保留
|system_wrappers|system_wrappers| 除了.git文件夹，全部保留
|test|test| 测试相关，后期可以排除
|testing|testing|测试相关，后期可以排除
|third_party||第三方库，太大，单独管理
|tools||一些测试工具
|tools_webrtc|tools_webrtc| 除了.git文件夹，全部保留
|video|video| 除了.git文件夹，全部保留
|其它文件|其它文件| 除了.git文件夹，全部保留

# 编译
- 编译前需要将从webrtc官方仓库下载的build目录和third_party目录拷贝到本目录下，同时还需要将webrtc官方src目录的上一级的.cipd目录拷贝到上一级目录

```
# webrtc官方仓库
|--src/
|--.cipd/

# 本仓库
|--webrtc_simplfy/
|--.cipd/
```

- 编译参数
> gn gen out/Release --args='target_os="android" target_cpu="arm" rtc_include_tests=false rtc_build_tools=false rtc_build_examples=false'   
> ninja -C out/Release