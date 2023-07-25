### Lightning轻量级推理框架
![](./imgs/lightning.png)      
#### 安装环境       
* 开放语言: C++ 17      
* 数学计算库: Armadillo + OpenBlas       
* 加速库: OpenMP       
* 单元测试: Google Test       
* 性能测试: Google Benchmark        

#### 代码结构       
`src`是源码目录       
* `data/`是张量类Tensor的实现和Tensor初始化方法     
* `layer/`算子实现
* `parser/`解析模型
* `runtime/`计算图结构               

`test`是框架的单元测试        
`benchmark`为google benchmark, 主要对模型进行性能测试         

#### 平台支持
- ✅ = known work and runs fast with good optimization
- ✔️= known work, but speed may not be fast enough
- ❔ = shall work, not confirmed
- / = not applied

|            | Windows | Linux | Android | macOS | iOS |
| ---------- | ------- | ----- | ------- | ----- | --- |
| intel-cpu  | /️      | ✔️    | ❔      | /️    | /   |
| intel-gpu  | /️      | ✔️    | ❔      | /    | /   |
| amd-cpu    | /️      | ✔️    | ❔      | /️    | /   |
| amd-gpu    | /️      | ✔️    | /      | /    | /   |
| nvidia-gpu | /️      | ✔️    | /      | /    | /   |
| qcom-cpu   | /      | /️    | /      | /     | /   |
| qcom-gpu   | /      | /️    | /️      | /     | /   |
| arm-cpu    | /      | /    | /      | /     | /   |
| arm-gpu    | /      | /    | /️      | /     | /   |
| apple-cpu  | /       | /     | /       | /️    | /  |
| apple-gpu  | /       | /     | /       | /️    | /️  |

---

#### nanodet模型推理     
`image_path`代表图像路径，`param_path`为模型参数文件，`bin_path`为权重文件     
```c++
const std::string& image_path = "";     
const std::string& param_path = "";     
const std::string& bin_path = "";      
```
推理效果图：       
*****

#### 支持算子    
*  Convolution
*  AdaptivePooling
*  MaxPooling
*  Expression(抽象语法树)
*  Flatten, View(维度展平和变形)
*  Sigmoid
*  HardSigmoid
*  HardSwish
*  ReLU
*  Linear(矩阵相乘)
*  Softmax
*  BatchNorm
*  Upsample
*  SiLU
*  Concat

#### 性能测试       
模型推理十次耗时取平均值                 

| **input size**         | **模型名称**     | **计算设备**              | **耗时**         |
|------------------------| ---------------- | ------------------------- |----------------|
| 224×224 batch = 8      | MobileNetV3Small | CPU(armadillo + openblas) | *** ms / image |
| 224×224 batch = 8      | ResNet18         | CPU(armadillo + openblas) | *** ms / image |
| 224×224 batch =16      | ResNet18         | CPU(armadillo + openblas) | *** ms / image |
| 640×640 batch = 8      | Yolov5nano       | CPU(armadillo + openblas) | *** ms / image |
| **640×640** batch = 8  | **Yolov5s**      | CPU(armadillo + openblas) | *** ms / image |
| **640×640** batch = 16 | **Yolov5s**      | CPU(armadillo + openblas) | *** ms / image |


#### 参考       
1. 推理框架NCNN:  https://github.com/Tencent/ncnn          
2. Caffe框架: https://github.com/BVLC/caffe      
3. KuiperInfer框架: https://github.com/zjhellofss/KuiperInfer        


