/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

