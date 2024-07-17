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
#include "MjRefreshNode.h"
#include <arkui/native_node.h>

static constexpr ArkUI_NodeEventType REFRESH_NODE_EVENT_TYPES[] = {NODE_REFRESH_ON_REFRESH, NODE_REFRESH_STATE_CHANGE, NODE_REFRESH_ON_OFFSET_CHANGE};

namespace rnoh {
    MjRefreshNode::MjRefreshNode()
        : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_REFRESH)) {
        for (auto eventType : REFRESH_NODE_EVENT_TYPES) {
            maybeThrow(NativeNodeApi::getInstance()->registerNodeEvent(m_nodeHandle, eventType, eventType, this));
        }
    }

    MjRefreshNode::~MjRefreshNode() {
        for (auto eventType : REFRESH_NODE_EVENT_TYPES) {
            NativeNodeApi::getInstance()->unregisterNodeEvent(m_nodeHandle, eventType);
        }
    }

    MjRefreshNode &MjRefreshNode::setRefreshContent(ArkUINode &refreshContent) {
        ArkUI_AttributeItem loadingItem = {.object = refreshContent.getArkUINodeHandle()};
        maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_REFRESH_CONTENT, &loadingItem));
        return *this;
    }

    MjRefreshNode &MjRefreshNode::setRefreshNodeDelegate(RefreshNodeDelegate *refreshNodeDelegate) {
        m_refreshNodeDelegate = refreshNodeDelegate;
        return *this;
    }

    void MjRefreshNode::insertChild(ArkUINode &child, std::size_t index) {
        maybeThrow(NativeNodeApi::getInstance()->addChild(m_nodeHandle, child.getArkUINodeHandle()));
    }

    void MjRefreshNode::removeChild(ArkUINode &child) {
        maybeThrow(NativeNodeApi::getInstance()->removeChild(m_nodeHandle, child.getArkUINodeHandle()));
    }

    MjRefreshNode &MjRefreshNode::setNativeRefreshing(bool isRefreshing) {
        ArkUI_NumberValue refreshingValue[] = {{.u32 = isRefreshing}};
        ArkUI_AttributeItem refreshingItem = {refreshingValue, sizeof(refreshingValue) / sizeof(ArkUI_NumberValue)};
        maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_REFRESH_REFRESHING, &refreshingItem));
        return *this;
    }

    void MjRefreshNode::onNodeEvent(ArkUI_NodeEventType eventType, EventArgs &eventArgs) {
        if (eventType == ArkUI_NodeEventType::NODE_REFRESH_ON_REFRESH) {
            if (m_refreshNodeDelegate != nullptr) {
                m_refreshNodeDelegate->onRefresh();
            }
        }

        if (eventType == ArkUI_NodeEventType::NODE_REFRESH_STATE_CHANGE && m_refreshNodeDelegate) {
            switch (eventArgs->i32) {
            case 2:
            case 3:
            case 4: {
                m_refreshNodeDelegate->pullRefreshStateChange(eventArgs->i32, 0);
                break;
            }
            }
        }

        if (eventType == ArkUI_NodeEventType::NODE_REFRESH_ON_OFFSET_CHANGE && m_refreshNodeDelegate) {
            if (eventArgs->f32 > 0 && eventArgs->f32 <= 64) {
                float_t percent = eventArgs[0].f32 / 64;
                m_refreshNodeDelegate->pullRefreshStateChange(1, percent);
            }
        }
    }
} // namespace rnoh