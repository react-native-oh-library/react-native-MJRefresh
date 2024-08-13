import React from 'react';
import * as ReactNative from "react-native";
import MJRefreshView, { finishRefreshCommands, beginRefreshCommands, NativeProps, VoidEventData, OnPullingEventData } from "./src/js/MJRefreshNativeComponent";
import MJScrollView from './MJScrollView'
import MJFlatlist from './MJFlatList'

class MJRefresh extends React.Component<NativeProps>  {
    mjRefreshRef: React.ElementRef<typeof MJRefresh> | null =
        null;
    _onMJRefresh = (e: ReactNative.NativeSyntheticEvent<VoidEventData>) => {
        let { onRefresh } = this.props;
        onRefresh && onRefresh(e);
    }
    _onMJPulling = (e: ReactNative.NativeSyntheticEvent<OnPullingEventData>) => {
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
            <MJRefreshView
                ref={(ref) => {
                    this.mjRefreshRef = ref;

                }}

                {...nativeProps}
            >
                {this.props.children}
            </MJRefreshView>
        );
    }
}
export const ScrollView = MJScrollView;
export const FlatList = MJFlatlist;
export default MJRefresh;