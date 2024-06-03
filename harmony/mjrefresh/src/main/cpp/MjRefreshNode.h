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
#ifndef HARMONY_MHREFRESHNODE_H
#define HARMONY_MHREFRESHNODE_H
#include "RNOH/arkui/NativeNodeApi.h"
#include "RNOH/arkui/ArkUINode.h"

class RefreshNodeDelegate {
public:
    virtual ~RefreshNodeDelegate() = default;
    virtual void onRefresh(){};
    virtual void pullRefreshStateChange(int32_t state);
};

namespace rnoh {
    class MjRefreshNode : public ArkUINode {
    protected:
        RefreshNodeDelegate *m_refreshNodeDelegate;
        static constexpr float REFRESH_NODE_SIZE = 29;

    public:
        MjRefreshNode();
        ~MjRefreshNode();

        void insertChild(ArkUINode &child, std::size_t index);
        void removeChild(ArkUINode &child);
        void onNodeEvent(ArkUI_NodeEventType eventType, EventArgs& eventArgs);
        MjRefreshNode &setNativeRefreshing(bool isRefreshing);
        MjRefreshNode &setRefreshNodeDelegate(RefreshNodeDelegate *refreshNodeDelegate);
        MjRefreshNode &setRefreshContent(ArkUINode &refreshContent);
    };
} // namespace rnoh
#endif // HARMONY_MHREFRESHNODE_H