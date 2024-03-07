import React from "react";
import MJRefresh, { finishRefreshCommands,beginRefreshCommands, NativeProps as Props, VoidEventData } from "./src/js/MJRefreshNativeComponent";
import type * as ReactNative from "react-native";
type MJRefreshControlProps = Props & {
  HeaderComponent?: React.ReactNode;
  renderHeader?: () => React.ReactElement | React.ReactElement;
};

export class MJRefreshControl extends React.Component<MJRefreshControlProps>  {
  mjRefreshRef: React.ElementRef<typeof MJRefresh> | null =
    null;
  _onMJRefresh = (e: ReactNative.NativeSyntheticEvent<VoidEventData>) => {
    let { onRefresh } = this.props;
    onRefresh && onRefresh(e);
  }
  _onMJPulling = (e: ReactNative.NativeSyntheticEvent<VoidEventData>) => {
    let { onPulling } = this.props;
    onPulling && onPulling(e);
  }
  _onMJReleaseToRefresh = (e: ReactNative.NativeSyntheticEvent<VoidEventData>) => {
    let { onReleaseToRefresh } = this.props;
    onReleaseToRefresh && onReleaseToRefresh(e);
  }
  _onMJRefreshIdle = (e: ReactNative.NativeSyntheticEvent<VoidEventData>) => {
    let { onRefreshIdle } = this.props;
    onRefreshIdle && onRefreshIdle(e);
  }

  finishRefresh = (
  ) => {
    console.log("--------------------enter finishRefresh function")
    if (this.mjRefreshRef) {
      finishRefreshCommands.finishRefresh(
        this.mjRefreshRef
      );
    }
  };

  beginRefresh = (
    ) => {
      console.log("--------------------enter beginRefresh function")
      if (this.mjRefreshRef) {
        beginRefreshCommands.beginRefresh(
          this.mjRefreshRef
        );
      }
    };
  render() {
    const nativeProps = {
      ...this.props,
      ...{
        onRefresh: this._onMJRefresh,
        onRefreshIdle: this._onMJRefreshIdle,
        onReleaseToRefresh: this._onMJReleaseToRefresh,
        onPulling: this._onMJPulling,
      },
    };
    return (
      <MJRefresh
        ref={(ref) => {
          this.mjRefreshRef = ref;

        }}

        {...nativeProps}
      >
        {this.props.children}
      </MJRefresh>
    );
  }
}

export default MJRefreshControl;