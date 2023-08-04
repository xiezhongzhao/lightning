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
// @Data:    2023/7/25 17:04
// @Version: 1.0

#ifndef LIGHTNING_RUNTIME_OP_HPP
#define LIGHTNING_RUNTIME_OP_HPP

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include <lightning/runtime/ir.hpp>
#include <lightning/runtime/runtime_attr.hpp>
#include <lightning/runtime/runtime_operand.hpp>
#include <lightning/runtime/runtime_parameter.hpp>

namespace lightning{

    class Layer;

    // 计算图中计算节点
    struct RuntimeOperator{
        bool has_forward = false;
        std::string name;  // 计算节点名称
        std::string type;  // 计算节点类型
        std::shared_ptr<Layer> layer; // 节点对应的计算Layer

        std::vector<std::string> output_names; // 节点输出名称
        std::shared_ptr<RuntimeOperand> output_operands; // 节点的输出操作数

        // 节点的输入操作数
        std::map<std::string, std::shared_ptr<RuntimeOperand>> input_operands;
        // 节点的输入操作数， 顺序排序
        std::vector<std::shared_ptr<RuntimeOperand>> input_operands_seq;
        // 输出节点的名字和节点对应
        std::map<std::string, std::shared_ptr<RuntimeOperator>> output_operators;

        // 算子的参数信息
        std::map<std::string, std::shared_ptr<RuntimeParameter>> params;
        // 算子的属性信息，内含权重信息
        std::map<std::string, std::shared_ptr<RuntimeAttribute>> attribute;
    };

    class RuntimeOperatorUtils{
    public:
        /*
        * 如果图是第一次运行，则根据节点输入operand的形状准备好后续Layer计算中所需要的Tensor
        * 如果图是第二次以上运行，则检查输入operand的形状和operand中张量的形状是否匹配
        * @param operators 计算图中的计算节点
        * */
        static void InitOperatorInput(
                const std::vector<std::shared_ptr<RuntimeOperator>>& operators);

        /*
        * 如果图是第一次运行，则根据节点输出operand的形状准备好后续Layer计算中所需要的Tensor
        * 如果图是第二次以上运行，则检查输出operand的形状和operand中张量的形状是否匹配
        * @param pnnx_operators pnnx图节点
        * @param operators KuiperInfer计算图中的计算节点*
        * */
        static void InitOperatorOutput(
                const std::vector<pnnx::Operator*>& pnnx_operators,
                const std::vector<std::shared_ptr<RuntimeOperator>>& operators);
    };
}
#endif //LIGHTNING_RUNTIME_OP_HPP
