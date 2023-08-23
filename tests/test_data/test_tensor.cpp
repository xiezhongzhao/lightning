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
// @Data:    2023/8/4 17:27
// @Version: 1.0

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <lightning/data/tensor.hpp>
#include <lightning/data/tensor_util.hpp>

TEST(test_tensor, tensor_init1){
    using namespace lightning;
    Tensor<float> f1(3, 224, 224);
    ASSERT_EQ(f1.channels(), 3);
    ASSERT_EQ(f1.rows(), 224);
    ASSERT_EQ(f1.cols(), 224);
    ASSERT_EQ(f1.size(), 3 * 224 * 224);
}

TEST(test_tensor, tensor_init1_1d){
    using namespace lightning;
    Tensor<float> f1(3);
    const auto& raw_shapes = f1.raw_shapes();
    ASSERT_EQ(raw_shapes.size(), 1);
    ASSERT_EQ(raw_shapes.size(), 1);
    ASSERT_EQ(raw_shapes.at(0), 3);
}

TEST(test_tensor, tensor_init1_2d){
    using namespace lightning;
    Tensor<float> f1(32,24);
    const auto& raw_shapes = f1.raw_shapes();
    ASSERT_EQ(raw_shapes.size(), 2);
    ASSERT_EQ(raw_shapes.at(0), 32);
    ASSERT_EQ(raw_shapes.at(1), 24);
}

TEST(test_tensor, test_init1_2d_1){
    using namespace lightning;
    Tensor<float> f1(1, 24);
    const auto& raw_shapes = f1.raw_shapes();
    ASSERT_EQ(raw_shapes.size(), 1);
    ASSERT_EQ(raw_shapes.at(0), 24);
}

TEST(test_tensor, tensor_init2){
    using namespace lightning;
    Tensor<float> f1(std::vector<uint32_t>{3, 224, 224});
    ASSERT_EQ(f1.channels(), 3);
    ASSERT_EQ(f1.rows(), 224);
    ASSERT_EQ(f1.cols(), 224);
    ASSERT_EQ(f1.size(), 224 * 224 * 3);
}

TEST(test_tensor, copy_construct1){
    using namespace lightning;
    Tensor<float> f1(3, 224, 224);
    f1.Rand();
    Tensor<float> f2(f1);
    ASSERT_EQ(f2.channels(), 3);
    ASSERT_EQ(f2.rows(), 224);
    ASSERT_EQ(f2.cols(), 224);
}

TEST(test_tensor, copy_construct2){
    using namespace lightning;
    Tensor<float> f1(3, 2, 1);
    Tensor<float> f2(3, 224, 224);
    f2.Rand();
    f1 = f2;
    ASSERT_EQ(f1.channels(), 3);
    ASSERT_EQ(f1.rows(), 224);
    ASSERT_EQ(f1.cols(), 224);
    ASSERT_TRUE(arma::approx_equal(f2.data(), f1.data(), "absdiff", 1e-4));
}

TEST(test_tensor, move_construct1){
    using namespace lightning;
    Tensor<float> f1(3, 2, 1);
    Tensor<float> f2(3, 224, 224);
    f1 = std::move(f2);
    ASSERT_EQ(f1.channels(), 3);
    ASSERT_EQ(f1.rows(), 224);
    ASSERT_EQ(f1.cols(), 224);
}

TEST(test_tensor, move_construct2){
    using namespace lightning;
    Tensor<float> f2(3, 224, 224);
    Tensor<float> f1(std::move(f2));
    ASSERT_EQ(f1.channels(), 3);
    ASSERT_EQ(f1.rows(), 224);
    ASSERT_EQ(f1.cols(), 224);

    ASSERT_EQ(f2.data().memptr(), nullptr);
}

TEST(test_tensor, set_data){
    using namespace lightning;
    Tensor<float> f2(3, 224, 224);
    arma::fcube cube1(224, 224, 3);
    cube1.randn();
    f2.set_data(cube1);

    ASSERT_TRUE(arma::approx_equal(f2.data(), cube1, "absdiff", 1e-4));
}

TEST(test_tensor, data){
    using namespace lightning;
    Tensor<float> f2(3, 224, 224);
    f2.Fill(1.f);
    arma::fcube cube1(224, 224, 3);
    cube1.fill(1.);
    f2.set_data(cube1);

    ASSERT_TRUE(arma::approx_equal(f2.data(), cube1, "absdiff", 1e-4));
}

TEST(test_tensor, empty){
    using namespace lightning;
    Tensor<float> f2;
    ASSERT_EQ(f2.empty(), true);

    Tensor<float> f3(3, 3, 3);
    ASSERT_EQ(f3.empty(), false);
}

TEST(test_tensor, transform1){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    ASSERT_EQ(f3.empty(), false);
    f3.Transform([](const float& value) {return 1.f; });
    for(int i=0; i < f3.size(); ++i){
        ASSERT_EQ(f3.index(i), 1.f);
    }
}

TEST(test_tensor, clone){
    using namespace lightning;
    std::shared_ptr<Tensor<float>> f3
        = std::make_shared<Tensor<float>>(3,3,3);
    ASSERT_EQ(f3->empty(), false);
    f3->Rand();

    const auto& f4 = TensorClone(f3);
    assert(f4->data().memptr() != f3->data().memptr());
    ASSERT_EQ(f4->size(), f3->size());
    for(int i=0; i < f3->size(); ++i){
        ASSERT_EQ(f3->index(i), f4->index(i));
    }
}

TEST(test_tensor, raw_ptr){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    ASSERT_EQ(f3.raw_ptr(), f3.data().mem);
}

TEST(test_tensor, raw_ptr2){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    ASSERT_EQ(f3.raw_ptr(1), f3.data().mem + 1);
}

TEST(test_tensor, index1){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    ASSERT_EQ(f3.empty(), false);
    std::vector<float> values;
    for(int i=0; i<27; ++i){
        values.push_back(1);
    }
    f3.Fill(values);
    for(int i=0; i<27; ++i){
        ASSERT_EQ(f3.index(i), 1);
    }
}

TEST(test_tensor, flatten1){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    std::vector<float> values;
    for(int i=0; i<27; ++i){
        values.push_back(float(i));
    }
    f3.Fill(values);
    f3.Flatten(false);

    ASSERT_EQ(f3.channels(), 1);
    ASSERT_EQ(f3.rows(), 1);
    ASSERT_EQ(f3.cols(), 27);

    ASSERT_EQ(f3.index(0), 0);
    ASSERT_EQ(f3.index(1), 3);
    ASSERT_EQ(f3.index(2), 6);

    ASSERT_EQ(f3.index(3), 1);
    ASSERT_EQ(f3.index(4), 4);
    ASSERT_EQ(f3.index(5), 7);

    ASSERT_EQ(f3.index(6), 2);
    ASSERT_EQ(f3.index(7), 5);
    ASSERT_EQ(f3.index(8), 8);
}

TEST(test_tensor, flatten2){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    std::vector<float> values;
    for(int i=0; i<27; ++i){
        values.push_back(float(i));
    }
    f3.Fill(values);
    f3.Flatten(true);
    for(int i=0; i<27; ++i){
        ASSERT_EQ(f3.index(i), i);
    }
}

TEST(test_tensor, fill1){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    std::vector<float> values;
    for(int i=0; i<27; ++i){
        values.push_back(float(i));
    }
    f3.Fill(values);
    int index = 0;
    for(int c=0; c<3; ++c){
        for(int i=0; i<f3.rows(); ++i){
            for(int j=0; j<f3.cols(); ++j){
                ASSERT_EQ(f3.at(c, i, j), index);
                index += 1;
            }
        }
    }
}

TEST(test_tensor, fill2_colmajor1){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    std::vector<float> values;
    for(int i=0; i<27; ++i){
        values.push_back(float(i));
    }
    f3.Fill(values, false);
    for(int i=0; i<27; ++i){
        ASSERT_EQ(values.at(i), f3.index(i));
    }
}

TEST(test_tensor, create1){
    using namespace lightning;
    const std::shared_ptr<ftensor>& tensor_ptr = TensorCreate(3, 32, 32);
    ASSERT_EQ(tensor_ptr->empty(), false);
    ASSERT_EQ(tensor_ptr->channels(), 3);
    ASSERT_EQ(tensor_ptr->rows(), 32);
    ASSERT_EQ(tensor_ptr->cols(), 32);
}

TEST(test_tensor, create2){
    using namespace lightning;
    const std::shared_ptr<ftensor>& tensor_ptr = TensorCreate({3, 32, 32});
    ASSERT_EQ(tensor_ptr->empty(), false);
    ASSERT_EQ(tensor_ptr->channels(), 3);
    ASSERT_EQ(tensor_ptr->rows(), 32);
    ASSERT_EQ(tensor_ptr->cols(), 32);
}

TEST(test_tensor, tensor_create1){
    using namespace lightning;
    sftensor tensor = TensorCreate(std::vector<uint32_t>{1, 2});
    ASSERT_EQ(tensor->raw_shapes().size(), 1);
    ASSERT_EQ(tensor->raw_shapes().at(0), 2);
}

TEST(test_tensor, tensor_broadcast1){
    using namespace lightning;
    const std::shared_ptr<ftensor>& tensor1 = TensorCreate({3, 1, 1});
    const std::shared_ptr<ftensor>& tensor2 = TensorCreate({3, 32, 32});

    const auto& [tensor11, tensor21]
        = TensorBroadcast(tensor1, tensor2);

    ASSERT_EQ(tensor21->channels(), 3);
    ASSERT_EQ(tensor21->rows(), 32);
    ASSERT_EQ(tensor21->cols(), 32);

    ASSERT_EQ(tensor11->channels(), 3);
    ASSERT_EQ(tensor11->rows(), 32);
    ASSERT_EQ(tensor11->cols(), 32);

//    ASSERT_TRUE(
//        arma::approx_equal(tensor21->data(),tensor2->data(),
//                               "absdiff", 1e-4));  // error
}

TEST(test_tensor, tensor_broadcast2){
    using namespace lightning;
    const std::shared_ptr<ftensor>& tensor1 = TensorCreate({3, 32, 32});
    const std::shared_ptr<ftensor>& tensor2 = TensorCreate({3, 1, 1});
    tensor2->Rand();

    const auto& [tensor11, tensor21]
        = TensorBroadcast(tensor1, tensor2);
    ASSERT_EQ(tensor21->channels(), 3);
    ASSERT_EQ(tensor21->rows(), 32);
    ASSERT_EQ(tensor21->cols(), 32);

    ASSERT_EQ(tensor11->channels(), 3);
    ASSERT_EQ(tensor11->rows(), 32);
    ASSERT_EQ(tensor11->cols(), 32);

    for(uint32_t i=0; i<tensor21->channels(); ++i){
        float c = tensor2->at(i, 0, 0);
        const auto& in_channel = tensor21->slice(i);
        for(uint32_t j=0; j<in_channel.size(); ++j){
            ASSERT_EQ(in_channel.at(j), c);
        }
    }
}

TEST(tensor_tensor, fill2){
    using namespace lightning;
    Tensor<float> f3(3, 3, 3);
    f3.Fill(1.f);
    for(int c=0; c<3; ++c){
        for(int i=0; i<f3.rows(); ++i){
            for(int j=0; j<f3.cols(); ++j){
                ASSERT_EQ(f3.at(c, i, j), 1.f);
            }
        }
    }
}

TEST(test_tensor, add1){
    using namespace lightning;
    const auto& f1 = std::make_shared<Tensor<float>>(3, 224, 224);
    f1->Fill(1.f);
    const auto& f2 = std::make_shared<Tensor<float>>(3, 224, 224);
    f2->Fill(2.f);
    const auto& f3 = TensorElementAdd(f2, f1);
    for(int i=0; i<f3->size(); ++i){
        ASSERT_EQ(f3->index(i), 3.f);
    }
}


TEST(test_tensor, add2){
    using namespace lightning;
    const auto& f1 = std::make_shared<Tensor<float>>(3, 224, 224);
    f1->Fill(1.f);
    const auto& f2 = std::make_shared<Tensor<float>>(3, 1, 1);
    f2->Fill(2.f);
    const auto& f3 = TensorElementAdd(f2, f1);
    for(int i=0; i<f3->size(); ++i){
        ASSERT_EQ(f3->index(i), 3.f);
    }
}

TEST(test_tensor, add3){
    using namespace lightning;
    const auto& f1 = std::make_shared<Tensor<float>>(3, 224, 224);
    f1->Fill(1.f);
    const auto& f2 = std::make_shared<Tensor<float>>(3, 1, 1);
    f2->Fill(2.f);
    const auto& f3 = TensorElementAdd(f1, f2);
    for(int i=0; i<f3->size(); ++i){
        ASSERT_EQ(f3->index(i), 3.f);
    }
}

TEST(test_tensor, add4){
    using namespace lightning;
    const auto& f1 = std::make_shared<Tensor<float>>(3, 224, 224);
    f1->Fill(3.f);
    const auto& f2 = std::make_shared<Tensor<float>>(3, 1, 1);
    f2->Fill(2.f);

    const auto& f3 = std::make_shared<Tensor<float>>(3, 224, 224);
    TensorElementAdd(f1, f2, f3);
    for(int i=0; i<f3->size(); ++i){
        ASSERT_EQ(f3->index(i), 5.f);
    }
}

TEST(test_tensor, mul1){
    using namespace lightning;
    const auto& f1 = std::make_shared<Tensor<float>>(3, 224, 224);
    f1->Fill(3.f);
    const auto& f2 = std::make_shared<Tensor<float>>(3, 224, 224);
    f2->Fill(2.f);
    const auto& f3 = TensorElementMultiply(f2, f1);
    for(int i=0; i<f3->size(); ++i){
        ASSERT_EQ(f3->index(i), 6.f);
    }
}

TEST(test_tensor, mul2){
    using namespace lightning;
    const auto& f1 = std::make_shared<Tensor<float>>(3, 224, 224);
    f1->Fill(3.f);
    const auto& f2 = std::make_shared<Tensor<float>>(3, 1, 1);
    f2->Fill(2.f);
    const auto& f3 = TensorElementMultiply(f2, f1);
    for(int i=0; i<f3->size(); ++i){
        ASSERT_EQ(f3->index(i), 6.f);
    }
}

TEST(test_tensor, mul3){
    using namespace lightning;
    const auto& f1 = std::make_shared<Tensor<float>>(3, 224, 224);
    f1->Fill(3.f);
    const auto& f2 = std::make_shared<Tensor<float>>(3, 1, 1);
    f2->Fill(2.f);

    const auto& f3 = std::make_shared<Tensor<float>>(3, 224, 224);
    TensorElementMultiply(f1, f2, f3);
    for(int i=0; i<f3->size(); ++i){
        ASSERT_EQ(f3->index(i), 6.f);
    }
}

TEST(test_tensor, mul4){
    using namespace lightning;
    const auto& f1 = std::make_shared<Tensor<float>>(3, 224, 224);
    f1->Fill(3.f);
    const auto& f2 = std::make_shared<Tensor<float>>(3, 1, 1);
    f2->Fill(2.f);

    const auto& f3 = std::make_shared<Tensor<float>>(3, 224, 224);
    TensorElementMultiply(f2, f1, f3);
    for(int i=0; i<f3->size(); ++i){
        ASSERT_EQ(f3->index(i), 6.f);
    }
}

TEST(test_tensor, shapes){
    using namespace lightning;
    Tensor<float> f3(2, 3, 4);
    const std::vector<uint32_t>& shapes = f3.shapes();
    ASSERT_EQ(shapes.at(0), 2);
    ASSERT_EQ(shapes.at(1), 3);
    ASSERT_EQ(shapes.at(2), 4);
}

TEST(test_tensor, raw_shapes1){
    using namespace lightning;
    Tensor<float> f3(2, 3, 4);
    f3.Reshape({24});
    const auto& shapes = f3.raw_shapes();
    ASSERT_EQ(shapes.size(), 1);
    ASSERT_EQ(shapes.at(0), 24);
}

TEST(test_tensor, raw_shapes2){
    using namespace lightning;
    Tensor<float> f3(2, 3, 4);
    f3.Reshape({4, 6});
    const auto& shapes = f3.raw_shapes();
    ASSERT_EQ(shapes.size(), 2);
    ASSERT_EQ(shapes.at(0), 4);
    ASSERT_EQ(shapes.at(1), 6);
}

TEST(test_tensor, raw_shape3){
    using namespace lightning;
    Tensor<float> f3(2, 3, 4);
    f3.Reshape({4, 3, 2});
    const auto& shapes = f3.raw_shapes();
    ASSERT_EQ(shapes.size(), 3);
    ASSERT_EQ(shapes.at(0), 4);
    ASSERT_EQ(shapes.at(1), 3);
    ASSERT_EQ(shapes.at(2), 2);
}

TEST(test_tensor, raw_view1){
    using namespace lightning;
    Tensor<float> f3(2, 3, 4);
    f3.Reshape({24}, true);
    const auto& shapes = f3.raw_shapes();
    ASSERT_EQ(shapes.size(), 1);
    ASSERT_EQ(shapes.at(0), 24);
}

TEST(test_tensor, raw_view2){
    using namespace lightning;
    Tensor<float> f3(2, 3, 4);
    f3.Reshape({4, 6}, true);
    const auto& shapes = f3.raw_shapes();
    ASSERT_EQ(shapes.size(), 2);
    ASSERT_EQ(shapes.at(0), 4);
    ASSERT_EQ(shapes.at(1), 6);
}

TEST(test_tensor, raw_view3){
    using namespace lightning;
    Tensor<float> f3(2, 3, 4);
    f3.Reshape({4, 3, 2}, true);
    const auto& shapes = f3.raw_shapes();
    ASSERT_EQ(shapes.size(), 3);
    ASSERT_EQ(shapes.at(0), 4);
    ASSERT_EQ(shapes.at(1), 3);
    ASSERT_EQ(shapes.at(2), 2);
}

TEST(test_tensor, paddding1){
    using namespace lightning;
    Tensor<float> tensor(3, 4, 5);
    ASSERT_EQ(tensor.channels(), 3);
    ASSERT_EQ(tensor.rows(), 4);
    ASSERT_EQ(tensor.cols(), 5);

    tensor.Fill(1.f);
    tensor.Padding({1, 2, 3, 4}, 0);
    ASSERT_EQ(tensor.rows(), 7);
    ASSERT_EQ(tensor.cols(), 12);

    int index = 0;
    for(int c=0; c<tensor.channels(); ++c){
        for(int r=0; r<tensor.rows(); ++r){
            for(int c_=0; c_<tensor.cols(); ++c_){
                if((r>=2 && r<=4) && (c_>=3 && c_<=7)){
                    ASSERT_EQ(tensor.at(c,r,c_), 1.f)
                        << c << " " << " " << r << " " << c_;
                }
                index += 1;
            }
        }
    }
}

TEST(test_tensor, padding2){
    using namespace lightning;
    ftensor tensor(3, 4, 5);
    ASSERT_EQ(tensor.channels(), 3);
    ASSERT_EQ(tensor.rows(), 4);
    ASSERT_EQ(tensor.cols(), 5);

    tensor.Fill(1.f);
    tensor.Padding({2, 2, 2, 2}, 3.14f);
    ASSERT_EQ(tensor.rows(), 8);
    ASSERT_EQ(tensor.cols(), 9);

    int index = 0;
    for(int c=0; c<tensor.channels(); ++c){
        for(int r=0; r<tensor.rows(); ++r){
            for(int c_=0; c_<tensor.cols(); ++c_){
                if(c_ <= 1 || r <= 1){
                    ASSERT_EQ(tensor.at(c, r, c_), 3.14f);
                }else if(c>=tensor.cols()-1 || r>=tensor.rows()-1){
                    ASSERT_EQ(tensor.at(c, r, c_), 3.14f);
                }
                if((r>=2 && r<=5) && (c_>=2 && c_<=6)){
                    ASSERT_EQ(tensor.at(c, r, c_), 1.f);
                }
                index += 1;
            }
        }
    }
}

TEST(test_tensor, review1){
    using namespace lightning;
    Tensor<float> tensor(3, 4, 5);
    std::vector<float> values;
    for(int i=0; i<60; ++i){
        values.push_back(float(i));
    }

    tensor.Fill(values);

    tensor.Reshape({4, 3, 5}, true);
    auto data = tensor.slice(0);
    int index = 0;
    for(int i=0; i<3; ++i){
        for(int j=0; j<5; ++j){
            ASSERT_EQ(data.at(i,j), index);
            index += 1;
        }
    }

    data = tensor.slice(1);
    index = 0;
    for(int i=0; i<3; ++i){
        for(int j=0; j<5; ++j){
            ASSERT_EQ(data.at(i,j), index+15);
            index += 1;
        }
    }

    data = tensor.slice(2);
    index = 0;
    for(int i=0; i<3; ++i){
        for(int j=0; j<5; ++j){
            ASSERT_EQ(data.at(i,j), index+30);
            index += 1;
        }
    }

    data = tensor.slice(3);
    index = 0;
    for(int i=0; i<3; ++i){
        for(int j=0; j<5; ++j){
            ASSERT_EQ(data.at(i,j), index+45);
            index += 1;
        }
    }
}

TEST(test_tensor, review2){
    using namespace lightning;
    arma::fmat f1 =
            "1, 2, 3, 4;"
            "5, 6, 7, 8";
    arma::fmat f2 =
            "1, 2, 3, 4;"
            "5, 6, 7, 8";
    sftensor data = TensorCreate(2, 2, 4);
    data->slice(0) = f1;
    data->slice(1) = f2;
    data->Reshape({16}, true);
    for(uint32_t i=0; i<8; ++i){
        ASSERT_EQ(data->index(i), i+1);
    }
    for(uint32_t i=8; i<15; ++i){
        ASSERT_EQ(data->index(i-8), i-8+1);
    }
}

TEST(test_tensor, review3){
    using namespace lightning;
    arma::fmat f1 =
            "1, 2, 3, 4;"
            "5, 6, 7, 8";
    sftensor data = TensorCreate(1, 2, 4);
    data->slice(0) = f1;
    data->Reshape({4, 2}, true);

    arma::fmat data2 = data->slice(0);
    ASSERT_EQ(data2.n_rows, 4);
    ASSERT_EQ(data2.n_cols, 2);
    uint32_t index = 1;
    for(uint32_t row=0; row<data2.n_rows; ++row){
        for(uint32_t col=0; col<data2.n_cols; ++col){
            ASSERT_EQ(data2.at(row, col), index);
            index += 1;
        }
    }
}

TEST(test_tensor, review4){
    using namespace lightning;
    arma::fmat f1 =
            "1, 2, 3, 4;"
            "5, 6, 7, 8";
    arma::fmat f2 =
            "9, 10, 11, 12;"
            "13, 14, 15, 16";

    sftensor data =  TensorCreate(2, 2, 4);
    data->slice(0) = f1;
    data->slice(1) = f2;
    data->Reshape({4, 2, 2}, true);
    for(uint32_t c=0; c<data->channels(); ++c){
        const auto& in_channel = data->slice(c);
        ASSERT_EQ(in_channel.n_rows, 2);
        ASSERT_EQ(in_channel.n_cols, 2);
        float n1 = in_channel.at(0, 0);
        float n2 = in_channel.at(0, 1);
        float n3 = in_channel.at(1, 0);
        float n4 = in_channel.at(1, 1);
        ASSERT_EQ(n1, c * 4 + 1);
        ASSERT_EQ(n2, c * 4 + 2);
        ASSERT_EQ(n3, c * 4 + 3);
        ASSERT_EQ(n4, c * 4 + 4);
    }
}

TEST(test_tensor, is_same1){
    using namespace lightning;
    std::shared_ptr<Tensor<float>> in1 =
            std::make_shared<Tensor<float>>(3, 32, 32);
    in1->Fill(2.f);
    std::shared_ptr<Tensor<float>> in2 =
            std::make_shared<Tensor<float>>(3, 32, 32);
    in2->Fill(2.f);
    ASSERT_EQ(TensorIsSame(in1, in2), true);
}

TEST(test_tensor, tensor_create2){
    using namespace lightning;
    sftensor tensor = TensorCreate(std::vector<uint32_t>{3});
    ASSERT_EQ(tensor->raw_shapes().size(), 1);
    ASSERT_EQ(tensor->raw_shapes().at(0), 3);
}

TEST(test_tensor, tensor_create3){
    using namespace lightning;
    sftensor tensor = TensorCreate(std::vector<uint32_t>{3, 12, 32});
    ASSERT_EQ(tensor->raw_shapes().size(), 3);
    ASSERT_EQ(tensor->raw_shapes().at(0), 3);
    ASSERT_EQ(tensor->raw_shapes().at(1), 12);
    ASSERT_EQ(tensor->raw_shapes().at(2), 32);
}

