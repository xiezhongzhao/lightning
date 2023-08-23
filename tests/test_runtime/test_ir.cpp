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
// @Data:    2023/8/17 17:03
// @Version: 1.0

#include <gtest/gtest.h>
#include <glog/logging.h>

#include <lightning/data/tensor.hpp>
#include <lightning/runtime/ir.hpp>
#include <lightning/runtime/runtime_ir.hpp>

static std::string ShapeStr(const std::vector<int>& shapes){
    std::ostringstream ss;
    for(int i=0; i<shapes.size(); ++i){
        ss << shapes.at(i);
        if(i != shapes.size()-1){
            ss << " x ";
        }
    }
    return ss.str();
}

TEST(test_ir, pnnx_graph_ops){
    using namespace lightning;
    std::string root_dir = "/mnt/e/WorkSpace/CPlusPlus/lightning/";
    std::string bin_path(root_dir + "tmp/linear/test_linear.pnnx.bin");
    std::string param_path(root_dir + "tmp/linear/test_linear.pnnx.param");

    std::unique_ptr<pnnx::Graph> graph = std::make_unique<pnnx::Graph>();
    int load_result = graph->load(param_path, bin_path);

    ASSERT_EQ(load_result, 0);
    const auto& ops = graph->ops;
    for(int i=0; i<ops.size(); ++i){
        LOG(INFO) << ops.at(i)->name;
    }
}

TEST(test_ir, pnnx_graph_operands){
    using namespace lightning;

    std::string root_dir = "/mnt/e/WorkSpace/CPlusPlus/lightning/";
    std::string bin_path(root_dir + "tmp/linear/test_linear.pnnx.bin");
    std::string param_path(root_dir + "tmp/linear/test_linear.pnnx.param");

    std::unique_ptr<pnnx::Graph> graph = std::make_unique<pnnx::Graph>();
    int load_result = graph->load(param_path, bin_path);

    ASSERT_EQ(load_result, 0);
    const auto& ops = graph->ops;
    for(int i=0; i<ops.size(); ++i){
        const auto& op = ops.at(i);
        LOG(INFO) << "OP Name: " << op->name;
        LOG(INFO) << "OP Inputs";
        for(int j=0; j<op->inputs.size(); ++j){
            LOG(INFO) << "Input name: " << op->inputs.at(j)->name
                      << " shape: " << ShapeStr(op->inputs.at(j)->shape);
        }
        LOG(INFO) << "OP Output";
        for(int j=0; j<op->outputs.size(); ++j){
            LOG(INFO) << "Output name: " << op->outputs.at(j)->name
                      << " shape: " << ShapeStr(op->outputs.at(j)->shape);
        }
        LOG(INFO) << "---------------------------------------------";
    }
}

