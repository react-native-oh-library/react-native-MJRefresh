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

#include "MjRefreshComponentInstance.h"
#include <bits/alltypes.h>
namespace rnoh {
    MjRefreshComponentInstance::MjRefreshComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
        m_refreshNode.setRefreshNodeDelegate(this);
    }

    void MjRefreshComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                     std::size_t index) {
        if (childComponentInstance->getComponentName() != "ScrollView") {
            m_rowStyleNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
            m_refreshNode.setRefreshContent(m_rowStyleNode);
        } else {
            m_refreshNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
        }
    }

    void MjRefreshComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        m_refreshNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    MjRefreshNode &MjRefreshComponentInstance::getLocalRootArkUINode() { return m_refreshNode; }

    void MjRefreshComponentInstance::onRefresh() {
    }

    void MjRefreshComponentInstance::handleCommand(const std::string &commandName, const folly::dynamic &args) {
        if (commandName == "finishRefresh") {
            m_refreshNode.setNativeRefreshing(false);
        }

        if (commandName == "beginRefresh") {
            m_refreshNode.setNativeRefreshing(true);
        }
    }

    void MjRefreshComponentInstance::pullRefreshStateChange(int32_t state, float_t percent) {
        switch (state) {
        case 1: {
            if (idle) {
                facebook::react::MJRefreshEventEmitter::OnPulling event{};
                event.percent = (int)(100.0 * percent + 0.5) / 100.0;
                m_eventEmitter->onPulling({event});
            }
            break;
        }
        case 2: {
            m_eventEmitter->onReleaseToRefresh({});
            break;
        }
        case 3: {
            idle = false;
            m_eventEmitter->onRefresh({});
            break;
        }
        case 4: {
            m_eventEmitter->onRefreshIdle({});
            idle = true;
            break;
        }
        }
    }

} // namespace rnoh