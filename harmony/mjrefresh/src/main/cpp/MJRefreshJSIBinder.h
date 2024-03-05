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



#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
class MJRefreshJSIBinder : public ViewComponentJSIBinder {

    facebook::jsi::Object createDirectEventTypes(facebook::jsi::Runtime &rt) override
    {
        facebook::jsi::Object events(rt);
        events.setProperty(rt, "topOnRefresh", createDirectEvent(rt, "onRefresh"));
        events.setProperty(rt, "topOnRefreshIdle", createDirectEvent(rt, "onRefreshIdle"));
        events.setProperty(rt, "topOnReleaseToRefresh", createDirectEvent(rt, "onReleaseToRefresh"));
        events.setProperty(rt, "topOnPulling", createDirectEvent(rt, "onPulling"));
        return events;
    }
};
} // namespace rnoh

