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
// @Data:    2023/7/26 15:54
// @Version: 1.0

#ifndef LIGHTNING_LAYER_FACTORY_HPP
#define LIGHTNING_LAYER_FACTORY_HPP

#include <map>
#include <memory>
#include <string>

#include <lightning/layer/layer.hpp>
#include <lightning/runtime/runtime_op.hpp>

namespace lightning{

    class LayerRegisterer{
    private:
        typedef ParseParameterAttrStatus (*Creator)(
                const std::shared_ptr<RuntimeOperator>& op,
                std::shared_ptr<Layer>& layer);
        typedef std::map<std::string, Creator> CreateRegistry;
    public:
        friend class LayerRegistererWrapper;
        friend class RegistryGarbageCollector;

        // add the op to register
        static void RegisterCreator(const std::string& layer_type,
                                    const Creator& create);

        // initialize the layer with op params
        static std::shared_ptr<Layer> CreateLayer(
                const std::shared_ptr<RuntimeOperator>& op);

        // return the register
        static CreateRegistry* Registry();

        // return the registered ops
        static std::vector<std::string> layer_types();

    private:
        static CreateRegistry* registry_;
    };

    // op registry
    class LayerRegistererWrapper{
    public:
        LayerRegistererWrapper(const std::string& layer_type,
                               const LayerRegisterer::Creator& creator){
            LayerRegisterer::RegisterCreator(layer_type, creator);
        }
    };

    // manage the memory of op registry
    class RegistryGarbageCollector{
    public:
        ~RegistryGarbageCollector(){
            if(LayerRegisterer::registry_ != nullptr){
                delete LayerRegisterer::registry_;
                LayerRegisterer::registry_ = nullptr;
            }
        }
        friend class LayerRegisterer;
    private:
        RegistryGarbageCollector() = default;
        RegistryGarbageCollector(const RegistryGarbageCollector&) = default;
    };
}

#endif //LIGHTNING_LAYER_FACTORY_HPP











