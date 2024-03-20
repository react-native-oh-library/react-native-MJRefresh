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

import { Descriptor, ComponentBuilderContext, ViewBaseProps } from 'rnoh';
import { RNOHContext, RNViewBase } from 'rnoh'
import Logger from './Logger';

const TAG: string = "[RNOH] MJRefresh"

export const MJREFRESH_TYPE: string = "MJRefresh"

interface voidDataFun {};

export interface MJRefreshProps extends ViewBaseProps {
  onRefresh: voidDataFun,
  onRefreshIdle: voidDataFun,
  onReleaseToRefresh: voidDataFun,
  onPulling: voidDataFun
}

export type MJRefreshDescriptor = Descriptor<"MJRefresh", MJRefreshProps>;

@Component
export struct MJRefresh {
  @State isRefreshing: boolean = false;
  @State pullRefreshText: string = '下拉刷新';
  @State pullRefreshImage: Resource = $r("app.media.ic_gallery_sort_down");
  ctx!: RNOHContext;
  tag: number = 0;
  @BuilderParam buildCustomComponent: (componentBuilderContext: ComponentBuilderContext) => void;
  @State descriptor: MJRefreshDescriptor = {} as MJRefreshDescriptor;
  private unregisterDescriptorChangesListener?: () => void = undefined;
  private cleanupCommandCallback?: () => void = undefined;

  aboutToAppear() {
    this.descriptor = this.ctx.descriptorRegistry.getDescriptor<MJRefreshDescriptor>(this.tag);
    this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
      (newDescriptor) => {
        this.descriptor = (newDescriptor as MJRefreshDescriptor);
      }
    )
    this.cleanupCommandCallback = this.ctx.commandDispatcher.registerCommandCallback(
      this.tag,
      (command, args: ESObject[]) => {
        if (command === 'finishRefresh') {
          this.isRefreshing = false;
          Logger.info(TAG, '------------ enter harmony finishRefresh');
        }
        if (command === 'beginRefresh') {
          this.isRefreshing = true;
          Logger.info(TAG, '------------ enter harmony beginRefresh');
        }
      });
  }

  aboutToDisappear() {
    this.unregisterDescriptorChangesListener?.();
  }

  onRefresh(): void {
    this.ctx.rnInstance.emitComponentEvent(
      this.tag,
      'onRefresh', {}
    )
  }

  onRefreshIdle(): void {
    this.ctx.rnInstance.emitComponentEvent(
      this.tag,
      'onRefreshIdle', {}
    )
  }

  onReleaseToRefresh(): void {
    this.ctx.rnInstance.emitComponentEvent(
      this.tag,
      'onReleaseToRefresh', {}
    )
  }

  onPulling(): void {
    this.ctx.rnInstance.emitComponentEvent(
      this.tag,
      'onPulling', {}
    )
  }

  @Builder
  private refreshStyle() {
    Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Image(this.pullRefreshImage)
        .width(18)
        .height(18)
        .visibility(!this.isRefreshing ? Visibility.Visible : Visibility.None);
      Progress({ value: 100, total: 100, type: ProgressType.ScaleRing })
        .color('#0091FF')
        .width(18)
        .style({ strokeWidth: 20, scaleCount: 10, scaleWidth: 2 })
        .visibility(this.isRefreshing ? Visibility.Visible : Visibility.None);
      Text(this.pullRefreshText)
        .margin({ left: 7, bottom: 1 })
        .fontSize(17);
    }
  }

  pullRefreshState(state: number) {
    switch (state) {
      case 0:
        this.pullRefreshText = '下拉刷新';
        this.pullRefreshImage = $r("app.media.ic_gallery_sort_down");
        this.isRefreshing = false;
        break;
      case 1:
        this.pullRefreshText = '释放刷新';
        this.pullRefreshImage = $r("app.media.ic_gallery_sort_up");
        this.isRefreshing = false;
        break;
      case 2:
        this.pullRefreshText = '正在刷新';
        break;
      case 3:
        this.isRefreshing = true;
        break;
    }
  }

  build() {
    RNViewBase({ ctx: this.ctx, tag: this.tag }) {
      Column() {
        Refresh({ refreshing: $$this.isRefreshing, offset: 16, friction: 30, builder: this.refreshStyle }) {
        }
        .onStateChange((refreshStatus: RefreshStatus) => {
          if (refreshStatus === RefreshStatus.Drag) {
            this.pullRefreshState(0);
            this.onPulling();
          }
          if (refreshStatus === RefreshStatus.OverDrag) {
            this.pullRefreshState(1);
            this.onReleaseToRefresh();
          }
          if (refreshStatus === RefreshStatus.Refresh) {
            this.pullRefreshState(2);
            this.onRefresh();
          }
          if (refreshStatus === RefreshStatus.Done) {
            this.pullRefreshState(3);
            this.onRefreshIdle();
          }
          Logger.info(TAG, 'Refresh onStatueChange state is ' + refreshStatus);
        })
        .onRefreshing(() => {
        })
        .height('80%').width('100%');
      }
    }
  }
}