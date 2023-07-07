# 回调函数效率对比
直接使用函数指针与使用虚函数作为回调的效率对比  

## 步骤
* 生成工程: `./bootstrap.sh release`
* 生成随机数据, 模拟等待分发回调的消息号: 执行 `example_gen_rand`
* 安装 gperftools 和 perf
* 在 build 目录, 执行 `pprof.sh` 生成 CPU 采样
* 在 build 目录, 执行 `perfstat.sh` 生成如: branch-misses, cache-misses 的一些数据
