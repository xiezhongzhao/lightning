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
// @Data:    2023/8/4 17:47
// @Version: 1.0

#include <gtest/gtest.h>
#include <glog/logging.h>

#include <lightning/data/tensor.hpp>
#include <lightning/layer/relu.hpp>

TEST(test_layer, forward_relu1){
    using namespace lightning;
    std::shared_ptr<Tensor<float>> input
        = std::make_shared<Tensor<float>>(32, 224, 512);
    input->Rand();
    std::vector<std::shared_ptr<Tensor<float>>> inputs;
    inputs.push_back(input);
    std::vector<std::shared_ptr<Tensor<float>>> outputs(1);

    ReluLayer relu_layer;
    const auto status = relu_layer.Forward(inputs, outputs);
    ASSERT_EQ(status, InferStatus::kInferSuccess);
    for(int i=0; i<inputs.size(); ++i){
        std::shared_ptr<Tensor<float>> input_ = inputs.at(i);
        input_->Transform([](const float f){
            if(f < 0){
                return 0.f;
            }else{
                return f;
            }
        });
        std::shared_ptr<Tensor<float>> output_ = outputs.at(i);
        CHECK(input_->size() == output_->size());
        uint32_t size = input_->size();
        for(uint32_t j=0; j<size; ++j){
            ASSERT_EQ(output_->index(j), input_->index(j));
        }
    }
}




