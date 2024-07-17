/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HARMONY_MJREFRESHCOMPONENTINSTANCE_H
#define HARMONY_MJREFRESHCOMPONENTINSTANCE_H

#include "MjRefreshNode.h"
#include "RNOH/CppComponentInstance.h"
#include "MjRefreshStackNode.h"
#include "ShadowNodes.h"


namespace rnoh {
    class MjRefreshComponentInstance: public CppComponentInstance<facebook::react::MJRefreshShadowNode>, public RefreshNodeDelegate {
    private:
        MjRefreshNode m_refreshNode;
        MjRefreshStackNode m_rowStyleNode;
        bool idle = true;
    public:
        MjRefreshComponentInstance(Context context);

        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;

        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;
    
        MjRefreshNode &getLocalRootArkUINode() override;
    
        void handleCommand(std::string const &commandName, folly::dynamic const &args) override;
    
        void onRefresh() override;

        void pullRefreshStateChange(int32_t state, float_t percent) override;
        
        bool isRefreshControlComponentInstance() const {return true;};
    };
} // namespace rnoh

#endif // HARMONY_MJREFRESHCOMPONENTINSTANCE_H
