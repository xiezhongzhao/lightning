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
// @Data:    2023/7/25 17:07
// @Version: 1.0

#ifndef LIGHTNING_STATUS_CODE_HPP
#define LIGHTNING_STATUS_CODE_HPP

namespace lightning{

    enum class RuntimeParameterType {
        kParameterUnknown = 0,
        kParameterBool = 1,
        kParameterInt = 2,

        kParameterFloat = 3,
        kParameterString = 4,
        kParameterIntArray = 5,
        kParameterFloatArray = 6,
        kParameterStringArray = 7,
    };

    enum class InferStatus {
        kInferUnknown = -1,
        kInferSuccess = 0,

        kInferFailedInputEmpty = 1,
        kInferFailedWeightParameterError = 2,
        kInferFailedBiasParameterError = 3,
        kInferFailedStrideParameterError = 4,
        kInferFailedDimensionParameterError = 5,
        kInferFailedInputOutSizeMatchError = 6,

        kInferFailedOutputSizeError = 7,
        kInferFailedShapeParameterError = 9,
        kInferFailedChannelParameterError = 10,
        kInferFailedOutputEmpty = 11,

        kInferLayerNotImplement = 12,
    };

    enum class ParseParameterAttrStatus {
        kParameterMissingUnknown = -1,
        kParameterMissingStride = 1,
        kParameterMissingPadding = 2,
        kParameterMissingKernel = 3,
        kParameterMissingUseBias = 4,
        kParameterMissingInChannel = 5,
        kParameterMissingOutChannel = 6,

        kParameterMissingEps = 7,
        kParameterMissingNumFeatures = 8,
        kParameterMissingDim = 9,
        kParameterMissingExpr = 10,
        kParameterMissingOutHW = 11,
        kParameterMissingShape = 12,
        kParameterMissingGroups = 13,
        kParameterMissingScale = 14,
        kParameterMissingResizeMode = 15,
        kParameterMissingDilation = 16,
        kParameterMissingPaddingMode = 16,

        kAttrMissingBias = 21,
        kAttrMissingWeight = 22,
        kAttrMissingRunningMean = 23,
        kAttrMissingRunningVar = 24,
        kAttrMissingOutFeatures = 25,
        kAttrMissingYoloStrides = 26,
        kAttrMissingYoloAnchorGrides = 27,
        kAttrMissingYoloGrides = 28,

        kParameterAttrParseSuccess = 0
    };

}

#endif //LIGHTNING_STATUS_CODE_HPP
