import type {HostComponent,ViewProps} from 'react-native';
import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';
import codegenNativeCommands from "react-native/Libraries/Utilities/codegenNativeCommands";
import type {
  BubblingEventHandler,
  Double,
  Int32,
  DirectEventHandler,
  Float
  } from 'react-native/Libraries/Types/CodegenTypes';
  
export type OnPullingEventData = Readonly<{
    percent: Float;
  }>

export interface NativeProps extends ViewProps {
  onRefresh?:DirectEventHandler<VoidEventData>,
  onRefreshIdle?:DirectEventHandler<VoidEventData>,
  onReleaseToRefresh?:DirectEventHandler<VoidEventData>,
  onPulling?:DirectEventHandler<OnPullingEventData>
  // 添加其它 props
}

export default codegenNativeComponent<NativeProps>(
  'MJRefreshView',
) as HostComponent<NativeProps>;
export type VoidEventData = Readonly<{}>;

type MjRefreshControlType = HostComponent<NativeProps>;
export interface NativeCommands {
  finishRefresh: (
    viewRef: React.ElementRef<MjRefreshControlType>
  ) => void,
  beginRefresh: (
    viewRef: React.ElementRef<MjRefreshControlType>
  ) => void
}
export const finishRefreshCommands: NativeCommands = codegenNativeCommands<NativeCommands>({
  supportedCommands: ["finishRefresh"],
});
export const beginRefreshCommands: NativeCommands = codegenNativeCommands<NativeCommands>({
  supportedCommands: ["beginRefresh"],
});