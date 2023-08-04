// MIT License
// Copyright (c) 2022 - 谢中朝
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// @Author:  xiezhongzhao
// @Email:   2234309583@qq.com
// @Data:    2023/7/26 17:56
// @Version: 1.0

#ifndef LIGHTNING_RUNTIME_IR_HPP
#define LIGHTNING_RUNTIME_IR_HPP

#include <glog/logging.h>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include <lightning/layer/layer.hpp>
#include <lightning/runtime/ir.hpp>
#include <lightning/runtime/runtime_operand.hpp>
#include <lightning/runtime/runtime_op.hpp>

namespace lightning{

    // 计算图结构，由多个计算节点和节点之间的数据流图组成
    class RuntimeGraph{
    public:
        // 初始化计算图
        // @param param_path 计算图的结构文件
        // @param bin_path 计算图中的权重文件
        RuntimeGraph(std::string para_path, std::string bin_pth);

        // 对模型重新进行build
        void ReBuildGraph(const std::string& input_name,
                          const std::string& output_name);

        // 构建计算图
        // @param input_name 计算图输入节点名称
        // @param output_name 计算图输出节点的名称
        void Build(const std::string& input_name, const std::string& output_name);

        // 设置权重文件
        // @param bin_path 权重文件路径
        void set_bin_path(const std::string& bin_path);

        // 设置结构文件
        void set_param_path(const std::string& param_path);

        // 返回结构文件
        const std::string& param_path() const;

        // 返回权重文件
        const std::string& bin_path() const;

        // 计算图的执行，根据深度优先搜索的顺序执行
        // @param inputs 计算图的输入张量
        // @param debug 是否调试，如果调试则输出一些中间信息
        std::vector<std::shared_ptr<Tensor<float>>> Forward(
                const std::vector<std::shared_ptr<Tensor<float>>>& inputs,
                bool debug = false);
    private:
        // 计算图的初始化
        bool Init();

        // 构建模型的拓扑执行顺序
        void ReverseTopo(const std::shared_ptr<RuntimeOperator>& root_op);

        // 计算图节点中的输入操作数
        // @param inputs pnnx中输入操作数
        // @param runtime_operator 计算图节点
        static void InitGraphOperatorsInput(
                const std::vector<pnnx::Operand*>& inputs,
                const std::shared_ptr<RuntimeOperator>& runtime_operator);

        // 计算图节点中的输出操作数
        // @param outputs pnnx中输出操作数
        // @param runtime_operator 计算图节点
        static void InitGraphOperatorsOutput(
                const std::vector<pnnx::Operand*>& outputs,
                const std::shared_ptr<RuntimeOperator>& runtime_operator);

        // 计算图中节点属性
        // @param attrs pnnx中的节点属性
        // @param runtime_operator 计算节点
        static void InitGraphAttrs(
                const std::map<std::string, pnnx::Attribute>& attrs,
                const std::shared_ptr<RuntimeOperator>& runtime_operator);

        // 计算图中节点参数
        static void InitGraphParams(
                const std::map<std::string, pnnx::Parameter>& params,
                const std::shared_ptr<RuntimeOperator>& runtime_operator);

        // 根据计算图中计算节点返回layer
        // @param op 计算图中的计算节点
        static std::shared_ptr<Layer> CreateLayer(
                const std::shared_ptr<RuntimeOperator>& op);

        // 探查下一层的计算节点
        // @param current_op 当前计算节点
        // @param layer_output_data 当前节点的输出，赋予到下一层计算节点的输入张量
        static void ProbeNextLayer(
                const std::shared_ptr<RuntimeOperator>& current_op,
                const std::vector<std::shared_ptr<Tensor<float>>>& layer_output_datas);
    private:
        enum class GraphState{
            NeedInit = -2,
            NeedBuild = -1,
            Complete = 0,
        };

    public:
        // 返回模型当前状态
        GraphState graph_state() const;

    private:
        GraphState graph_state_ = GraphState::NeedInit;
        std::string input_name_;  //计算图输入节点的名称
        std::string output_name_; //计算图输出节点的名称
        std::string param_path_;  // 计算图的结构文件
        std::string bin_path_;    // 计算图的权重文件

        // 保存所有节点，根据唯一的name索引
        std::map<std::string, std::shared_ptr<RuntimeOperator>> operators_maps_;
        // 拓扑排序后的计算图节点
        std::vector<std::shared_ptr<RuntimeOperator>> topo_operators_;
        // 计算图的计算节点
        std::vector<std::shared_ptr<RuntimeOperator>> operators_;
        // pnnx的graph
        std::unique_ptr<pnnx::Graph> graph_;

    };
}

#endif //LIGHTNING_RUNTIME_IR_HPP
