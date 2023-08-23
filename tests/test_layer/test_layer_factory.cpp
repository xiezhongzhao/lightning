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
// @Data:    2023/8/4 17:46
// @Version: 1.0

#include <gtest/gtest.h>
#include <lightning/layer/layer_factory.hpp>

using namespace lightning;
ParseParameterAttrStatus TestCreateLayer(const std::shared_ptr<RuntimeOperator> &op,
                                         std::shared_ptr<Layer> &layer){
    layer = std::make_shared<Layer>("test3");
    return ParseParameterAttrStatus::kParameterAttrParseSuccess;
}

TEST(test_layer_factory, init){
    using namespace lightning;
    const auto &r1 = LayerRegisterer::Registry();
    const auto &r2 = LayerRegisterer::Registry();
    ASSERT_EQ(r1, r2);
}

TEST(test_layer_factory, registerer){
    using namespace lightning;
    const uint32_t size1 = LayerRegisterer::Registry()->size();
    LayerRegisterer::RegisterCreator("test1", TestCreateLayer);
    const uint32_t size2 = LayerRegisterer::Registry()->size();
    LayerRegisterer::RegisterCreator("test2", TestCreateLayer);
    const uint32_t size3 = LayerRegisterer::Registry()->size();

    ASSERT_EQ(size2-size1, 1);
    ASSERT_EQ(size3-size1, 2);
}

TEST(test_layer_factory, create){
    using namespace lightning;
    LayerRegisterer::RegisterCreator("test3", TestCreateLayer);
    std::shared_ptr<RuntimeOperator> op = std::make_shared<RuntimeOperator>();
    op->type = "test3";
    std::shared_ptr<Layer> layer = LayerRegisterer::CreateLayer(op);
    ASSERT_EQ(layer->layer_name(), "test3");
}


