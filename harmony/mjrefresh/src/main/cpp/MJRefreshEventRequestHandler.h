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


#include "EventEmitters.h"
#include "RNOH/ArkJS.h"
#include "RNOH/EventEmitRequestHandler.h"
#include "RNOH/NativeLogger.h"

using namespace facebook;
namespace rnoh {

class MJRefreshEventRequestHandler : public EventEmitRequestHandler {
public:
    void handleEvent(EventEmitRequestHandler::Context const &ctx) override
    {
        ArkJS arkJs(ctx.env);
        auto eventName = ctx.eventName;
        auto eventEmitter = ctx.shadowViewRegistry->getEventEmitter<facebook::react::MJRefreshEventEmitter>(ctx.tag);
        if (eventEmitter == nullptr) {
            return;
        }
        if (ctx.eventName == "onRefresh") {
            eventEmitter->onRefresh({});
        } else if (ctx.eventName == "onRefreshIdle") {
            react::MJRefreshEventEmitter::OnRefreshIdle event{};
            eventEmitter->onRefreshIdle(event);
        } else if (eventName == "onReleaseToRefresh") {
            react::MJRefreshEventEmitter::OnReleaseToRefresh event{};
            eventEmitter->onReleaseToRefresh(event);
        } else if (eventName == "onPulling") {
            react::MJRefreshEventEmitter::OnPulling event{};
            eventEmitter->onPulling(event);
        }
    };
};
} // namespace rnoh

