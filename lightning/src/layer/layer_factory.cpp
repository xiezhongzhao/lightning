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

#include <set>
#include <lightning/layer/layer_factory.hpp>

namespace lightning{

    LayerRegisterer::CreateRegistry* LayerRegisterer::registry_ = nullptr;

    void LayerRegisterer::RegisterCreator(const std::string &layer_type,
                                          const Creator &creator) {
        CHECK(creator != nullptr);
        CreateRegistry* registry = Registry();
        CHECK_EQ(registry->count(layer_type), 0)
            << "Layer type: " << layer_type << "has already registered !";
        registry->insert({layer_type, creator});
    }

    LayerRegisterer::CreateRegistry* LayerRegisterer::Registry() {
        if(registry_ == nullptr){
            registry_ = new CreateRegistry();
            static RegistryGarbageCollector c;
        }
        CHECK(registry_ != nullptr) << "Global layer register init failed !";
        return registry_;
    }

    std::shared_ptr<Layer> LayerRegisterer::CreateLayer(
            const std::shared_ptr<RuntimeOperator> &op) {
        CreateRegistry* registry = Registry();
        const std::string& layer_type = op->type;
        LOG_IF(FATAL, registry->count(layer_type) <= 0)
            << "Can not find the layer type: " << layer_type;
        const auto& creator
            = registry->find(layer_type)->second;

        LOG_IF(FATAL, !creator) << "Layer creator is empty !";
        std::shared_ptr<Layer> layer;
        const auto& status = creator(op, layer);
        LOG_IF(FATAL, status != ParseParameterAttrStatus::kParameterAttrParseSuccess)
            << "Create the layer: " << layer_type
            << "failed, error code: " << int(status);
        return layer;
    }

    std::vector<std::string> LayerRegisterer::layer_types() {
        std::set<std::string> layer_types_unique;
        CreateRegistry* registry = Registry();
        for(const auto& [layer_type,
                         _]
                         : *registry){
            layer_types_unique.insert(layer_type);
        }
        std::vector<std::string> layer_types(layer_types_unique.begin(),
                                             layer_types_unique.end());
        return layer_types;
    }
}
